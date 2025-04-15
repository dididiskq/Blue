#include "BmsController.h"

BmsController::BmsController(QObject *parent)
    : QObject{parent}
{
    selfObj = (CHMModule *)parent;
    Discovery = new QBluetoothDeviceDiscoveryAgent;
    Discovery->setLowEnergyDiscoveryTimeout(3000);//设置搜索时间为30000us
    connect(Discovery, SIGNAL(finished()), this, SLOT(findFinish()));
    connect(Discovery, SIGNAL(deviceDiscovered(QBluetoothDeviceInfo)), this, SLOT(addBlueToothDevicesToList(QBluetoothDeviceInfo)));
    connect(Discovery, &QBluetoothDeviceDiscoveryAgent::errorOccurred,
            this, [](QBluetoothDeviceDiscoveryAgent::Error error) {
                qDebug() << "蓝牙发现错误：" << error;
            });
    sendTimer.setInterval(50);
    connect(&sendTimer, &QTimer::timeout, this, &BmsController::sendMsgByQueue);

    m_writeTimeoutTimer.setSingleShot(true);
    connect(&m_writeTimeoutTimer, &QTimer::timeout, this, &BmsController::onWriteTimeout);
}
void BmsController::onWriteTimeout()
{
    if (m_waitingWriteResponse)
    {
        m_waitingWriteResponse = false;
        sendTimer.start(); // 恢复读取队列
        // emit writeOperationCompleted(false, "操作超时");
        emit selfObj->selfViewCommand->selfView.context("HMStmView")->mySignal("-66");
        isWriting = false;
        processNextWriteRequest(); // 继续处理队列
    }
}
BmsController::~BmsController()
{
    // 释放所有服务对象
    foreach (QLowEnergyService *service, serviceList)
    {
        if (service)
        {
            service->deleteLater();
        }
    }
    serviceList.clear();

    // 释放控制器
    if (mController)
    {
        mController->disconnectFromDevice();
        mController->deleteLater();
        mController = nullptr;
    }
}

void BmsController::startSearch()
{
    //先清除之前的
    Discovery->start(QBluetoothDeviceDiscoveryAgent::LowEnergyMethod);
}

void BmsController::searchCharacteristic()
{
    if (currentService && currentService->serviceUuid() == SERVICE_UUID)
    {
        QList<QLowEnergyCharacteristic> chars = currentService->characteristics();

        foreach (const QLowEnergyCharacteristic &c, chars)
        {
            if (!c.isValid()) continue;

            // 严格按UUID匹配特征
            if (c.uuid() == WRITE_UUID)
            {
                m_Characteristic[0] = c;  // 这就是发送命令的特征
                qDebug() << "找到Write特征：" << c.uuid().toString();
            }
            else if (c.uuid() == NOTIFY_UUID)
            {
                m_Characteristic[2] = c;  // 这是接收响应的特征
                qDebug() << "找到Notify特征：" << c.uuid().toString();

                // 写入通知使能值（等价于ENABLE_NOTIFICATION_VALUE）
                QByteArray enableValue = QByteArray::fromHex("0100");
                QLowEnergyDescriptor descriptor = c.descriptor(QBluetoothUuid::DescriptorType::ClientCharacteristicConfiguration);
                currentService->writeDescriptor(descriptor, enableValue); // m_service为对应的QLowEnergyService实例

                // 连接描述符写入完成信号
                connect(currentService, &QLowEnergyService::descriptorWritten,
                        this, &BmsController::onDescriptorWritten);
            }
        }
    }
}

void BmsController::connectBlue(const QString addr)
{
    // 如果当前控制器存在且未断开，先断开旧连接
    if (mController && mController->state() != QLowEnergyController::UnconnectedState)
    {
        // 使用SingleShot确保只触发一次
        QObject::connect(mController, &QLowEnergyController::disconnected, this,
                         [this, addr]() {
                             mController->deleteLater();
                             mController = nullptr;
                             this->connectBlue(addr); // 重新调用以连接新设备
                         }, Qt::SingleShotConnection);

        mController->disconnectFromDevice();
        isConnected = false;
        return; // 等待断开完成
    }


    for(const auto& dev: deviceList)
    {
        QString currAddr = dev.address().toString();
        if(currAddr == addr)
        {
            currentDevice = dev;
        }
    }
    mController = QLowEnergyController::createCentral(currentDevice,this);

    connect(mController, &QLowEnergyController::serviceDiscovered,this, &BmsController::serviceDiscovered);//扫描目标BLE服务,获取一次触发一次
    connect(mController, &QLowEnergyController::discoveryFinished,this, &BmsController::serviceScanDone);//扫描完成之后会触发此信号

    connect(mController, &QLowEnergyController::errorOccurred,this, [](QLowEnergyController::Error error) {
        Q_UNUSED(error);
        qDebug()<<"Cannot connect to remote device.";
    });//连接出错
    connect(mController, &QLowEnergyController::connected, this, [this]() {
        qDebug()<< "Controller connected. Search services...";
        mController->discoverServices();
        emit selfObj->selfViewCommand->selfView.context("HMStmView")->mySignal("1");
    });//连接成功
    connect(mController, &QLowEnergyController::disconnected, this, []() {
        qDebug()<<"LowEnergy controller disconnected";

    });//断开连接
    mController->connectToDevice();//建立连接
}
//写数据函数
void BmsController::viewWriteMessage(const QVariantMap &op)
{
    if(isConnected == false || isWriting)
    {
        qDebug()<<"蓝牙未连接";
        return;
    }
    QByteArray array;
    QVariantMap v;
    // 获取用户输入（假设通过QSpinBox）

    v = op;
    v["funcCode"] = 0x10;
    array = protocal.byte(v);

    // 将请求加入队列
    writeQueue.enqueue(array);

    // 如果当前无写入操作，立即处理
    if (!isWriting)
    {
        processNextWriteRequest();
    }

    // 暂停读取队列
    // sendTimer.stop();
    // if (currentService && m_Characteristic[0].isValid())
    // {

        //     m_waitingWriteResponse = true;
        //     m_writeTimeoutTimer.start(5000); // 5秒超时
        //     currentService->writeCharacteristic(m_Characteristic[0], array, QLowEnergyService::WriteWithoutResponse);
        // }
        // else
        // {
        //     emit writeOperationCompleted(false, "服务或特征无效");
        //     sendTimer.start(); // 恢复队列
        // }
}
void BmsController::processNextWriteRequest()
{
    if (writeQueue.isEmpty())
    {
        isWriting = false;
        return;
    }
    isWriting = true;
    QByteArray array = writeQueue.dequeue();
    qDebug()<<"发送报文：" << byteArrayToHexStr(array);

    sendTimer.stop();
    if (currentService && m_Characteristic[0].isValid())
    {

        m_waitingWriteResponse = true;
        m_writeTimeoutTimer.stop();      // 重置之前的超时计时
        m_writeTimeoutTimer.start(5000); // 5秒超时
        currentService->writeCharacteristic(m_Characteristic[0], array, QLowEnergyService::WriteWithoutResponse);
    }
    else
    {
        // emit writeOperationCompleted(false, "服务或特征无效");
        emit selfObj->selfViewCommand->selfView.context("HMStmView")->mySignal("-67");
        sendTimer.start(); // 恢复队列
        isWriting = false;
        processNextWriteRequest(); // 继续处理下一个请求
    }
}

//读数据
void BmsController::viewMessage(const int type)
{
    if(isConnected == false)
    {
        qDebug()<<"蓝牙未连接";
        return;
    }
    //调用协议
    QByteArray array;
    QVariantMap v;
    if(type >= 0)//大于零的读数据
    {
        v["funcCode"] = 0x03;
        if(type == 0)
        {
            //电池健康、电量
            v["startAddr"] = 0x0000;
            v["regCount"] = 1;
        }
        else if(type == 1)
        {
            //电池健康、电量
            v["startAddr"] = 0x0001;
            v["regCount"] = 1;
        }
        else if(type == 2)
        {
            //电池健康、电量
            v["startAddr"] = 0x0002;
            v["regCount"] = 1;
        }
        else if(type == 3)
        {
            //电池健康、电量
            v["startAddr"] = 0x0003;
            v["regCount"] = 1;
        }
        else if(type == 4)//电压
        {
            //电池健康、电量
            v["startAddr"] = 0x0004;
            v["regCount"] = 2;
        }
        else if(type == 6)//电流
        {
            //电池健康、电量
            v["startAddr"] = 0x0006;
            v["regCount"] = 2;
        }
        else if(type == 8)//电流
        {
            //电池健康、电量
            v["startAddr"] = 0x0008;
            v["regCount"] = 2;
        }
        else if(type == 10)//电流
        {
            v["startAddr"] = 0x000A;
            v["regCount"] = 2;
        }
        else if(type == 12)//电流
        {
            v["startAddr"] = 0x000C;
            v["regCount"] = 2;
        }
        else if(type == 14)
        {
            v["startAddr"] = 0x000E;
            v["regCount"] = 1;
        }
        else if(type == 15)
        {
            v["startAddr"] = 0x000F;
            v["regCount"] = 1;
        }
        else if(type == 16)
        {
            v["startAddr"] = 0x0010;
            v["regCount"] = 1;
        }
        else if(type == 17)
        {
            v["startAddr"] = 0x0011;
            v["regCount"] = 1;
        }
        else if(type == 18)
        {
            v["startAddr"] = 0x0012;
            v["regCount"] = 1;
        }
        else if(type == 19)
        {
            v["startAddr"] = 0x0013;
            v["regCount"] = 1;
        }
        else if(type == 20)
        {
            v["startAddr"] = 0x0014;
            v["regCount"] = 1;
        }
        else if(type == 21)
        {
            v["startAddr"] = 0x0015;
            v["regCount"] = 1;
        }
        else if(type == 22)
        {
            v["startAddr"] = 0x0016;
            v["regCount"] = 1;
        }
        else if(type == 23)
        {
            v["startAddr"] = 0x0017;
            v["regCount"] = 1;
        }
        else if(type == 24)
        {
            v["startAddr"] = 0x0018;
            v["regCount"] = 1;
        }
        else if(type == 25)
        {
            v["startAddr"] = 0x0019;
            v["regCount"] = 1;
        }
        else if(type == 26)
        {
            v["startAddr"] = 0x001A;
            v["regCount"] = 1;
        }
        else if(type == 27)
        {
            v["startAddr"] = 0x001B;
            v["regCount"] = 1;
        }
        else if(type == 28)
        {
            v["startAddr"] = 0x001C;
            v["regCount"] = 1;
        }
        else if(type == 29)
        {
            v["startAddr"] = 0x001D;
            v["regCount"] = 1;
        }
        else if(type == 30)
        {
            v["startAddr"] = 0x001E;
            v["regCount"] = 1;
        }
        else if(type == 31)
        {
            v["startAddr"] = 0x001F;
            v["regCount"] = 1;
        }
        else if(type >= 32 && type <= 63)//单体电池
        {
            v["startAddr"] = type;
            v["regCount"] = 1;
        }
        else
        {
            v["startAddr"] = type;
            if(type == 0x20E || type == 0x402 || type == 0x404 || type >= 0x418)
            {
                v["regCount"] = 2;
            }
            else if(type == 0x236 || type == 0x246 || type == 0x256)
            {
                v["regCount"] = 4;
            }
            else if(type == 0x230)
            {
                v["regCount"] = 6;
            }
            else if(type == 0x23A || type == 0x24A)
            {
                v["regCount"] = 12;
            }
            else if(type == 0x408)
            {
                v["regCount"] = 16;
            }
            else
            {
                v["regCount"] = 1;
            }
        }
    }
    array = protocal.byte(v);
    SendMsg(array);

}
QByteArray createReadSOCRequest()
{
    QByteArray frame;
    frame.append(0x16);    // 从机地址
    frame.append(0x03);    // 功能码
    frame.append(char(0x00));    // 起始地址高
    frame.append(0x14);    // 起始地址低
    frame.append(char(0x00));    // 寄存器数量高
    frame.append(0x01);    // 寄存器数量低

    unsigned short crc = crc16_ccitt(frame.constData(), frame.size());
    frame.append(static_cast<char>(crc & 0xFF));
    frame.append(static_cast<char>((crc >> 8) & 0xFF));

    return frame;
}

void BmsController::SendMsg(const QByteArray& array)
{
    commandQueue.enqueue(array);
    if(!sendTimer.isActive())
    {
        sendTimer.start();
    }
}

void BmsController::sendMsgByQueue()
{
    QLowEnergyService::WriteMode mode = QLowEnergyService::WriteWithResponse;
    //如果特性支持“无响应写入”，则将模式改为 WriteWithoutResponse。此模式不等待设备确认，传输更快但不可靠
    if (m_Characteristic[0].properties() & QLowEnergyCharacteristic::WriteNoResponse)
    {
        mode = QLowEnergyService::WriteWithoutResponse;
    }
    if (!commandQueue.isEmpty())
    {
        QByteArray array = commandQueue.dequeue();
        qDebug()<<"发送报文：" << byteArrayToHexStr(array);
        currentService->writeCharacteristic(m_Characteristic[0], array, mode);
    }
}

void BmsController::getProtectMsgSlot()
{
    for(int i = 1; i <= 24; i++)
    {
        int time = 0x418 + 0x2 * (i - 1);
        int event = 0x448 + 0x2 * (i - 1);
        viewMessage(time);
        viewMessage(event);
    }
}


void BmsController::onDescriptorWritten(const QLowEnergyDescriptor &descriptor, const QByteArray &value)
{
    if (descriptor.uuid() == QBluetoothUuid::DescriptorType::ClientCharacteristicConfiguration)
    {
        quint8 configValue = value[0];
        if (configValue == 0x01)
        {
            // 通知已启用
            qDebug()<<"通知已经启用";
            isConnected = true;
            emit selfObj->selfViewCommand->selfView.context("HMStmView")->mySignal(descriptor.name());
            for(const auto & it: initCmdList)
            {
                viewMessage(it);
            }
        }
        else
        {
            // 通知未启用
            qDebug()<<"通知未启用";
        }
    }
}

void BmsController::findFinish()
{
    //Search Over
    qDebug()<<"Search Over";
}

void BmsController::addBlueToothDevicesToList(QBluetoothDeviceInfo Info)
{
    if(Info.coreConfigurations() & QBluetoothDeviceInfo::LowEnergyCoreConfiguration)
    {
        QString showStr = QString(Info.name()) + QString("(") + QString(Info.address().toString()) + QString (")");
        // qDebug()<<showStr;
        // ui->listWidget->addItem(showStr);
        QVariantMap map;
        map["name"] = Info.name();
        map["address"] = Info.address().toString();
        //渲染到界面
        selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("blueData", map);
        deviceList.append(Info);
    }
}
//服务被找到
void BmsController::serviceDiscovered(const QBluetoothUuid &serviceUuid)
{
    QLowEnergyService *service = mController->createServiceObject(serviceUuid);
    if (!service)
    {
        qDebug()<<"Cannot create service for uuid";
        return;
    }


    //当服务的状态发生变化时
    connect(service, &QLowEnergyService::stateChanged, this,&BmsController::serviceStateChanged);
    //当特性的值发生变化时
    connect(service, &QLowEnergyService::characteristicChanged, this,&BmsController::BleServiceCharacteristicChanged);
    //当特性被读取时
    connect(service, &QLowEnergyService::characteristicRead, this,&BmsController::BleServiceCharacteristicRead);
    //当特性被写入时
    connect(service, SIGNAL(characteristicWritten(QLowEnergyCharacteristic,QByteArray)),this, SLOT(BleServiceCharacteristicWrite(QLowEnergyCharacteristic,QByteArray)));

    //启动服务发现
    if(service->state() == QLowEnergyService::DiscoveryRequired)
    {
        service->discoverDetails();
    }

    serviceList.append(service);
}
//蓝牙服务扫描完成触发此函数
void BmsController::serviceScanDone()
{

    foreach(QLowEnergyService *it, serviceList)
    {
        if(it->serviceUuid() == SERVICE_UUID)
        {
            currentService = it;
            qDebug()<<"serviceScanDone"<<currentService->serviceUuid();
            break;
        }
    }
}

void BmsController::serviceStateChanged(QLowEnergyService::ServiceState s)
{
    if(s != QLowEnergyService::ServiceDiscovered) return;

    // 在此处触发特征处理逻辑
    QLowEnergyService *service = qobject_cast<QLowEnergyService*>(sender());
    if (service && service == currentService) {
        searchCharacteristic();
    }
}

void BmsController::BleServiceCharacteristicWrite(const QLowEnergyCharacteristic &c, const QByteArray &value)
{
    qDebug()<<"消息发送成功"<<QString(value);
    QString str(c.uuid().toString());
    QString str2("instructions %1 send to success!");
    QString str3 = str + QString(":") + str2.arg(QString(value));
}
//接收通知
void BmsController::BleServiceCharacteristicChanged(const QLowEnergyCharacteristic &c, const QByteArray &value)
{
    QString valueStr = byteArrayToHexStr(value);
    if(c.uuid() == NOTIFY_UUID)
    {
        qDebug() << "收到通知数据:" << value.toHex(' ');
        QVariantMap map = protocal.parse(value);
        // qDebug()<<"数据解析内容："<<map;

        if(map.value("error", -1).toInt() == 1)
        {
            qDebug()<<"报文错误";
            return;
        }
        if(map.value("error", -1).toInt() == 2)
        {
            qDebug()<<"command not found";
            return;
        }

        quint16 funcCode = map.value("funcCode").toUInt();

        if (map.value("writeOrread").toUInt() == 0x10)// 写响应功能码
        {
            if (m_waitingWriteResponse)
            {
                m_writeTimeoutTimer.stop();
                m_waitingWriteResponse = false;
                sendTimer.start(); // 恢复读取队列
                qDebug()<<"改写成功";
                // 检查响应是否正确
                if (true)
                {
                    emit selfObj->selfViewCommand->selfView.context("HMStmView")->mySignal("66");
                    isWriting = false;
                    processNextWriteRequest();
                }
                else
                {
                    // emit writeOperationCompleted(false, "设备返回错误");
                }
            }
        }
        else
        {
            if(funcCode == 0x0014)
            {
                selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("soh", map.value("SOH"));
                selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("soc", map.value("SOC"));
            }
            else if(funcCode == 0x0004)
            {
                selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("electYa", map.value("electYa").toString());
            }
            else if(funcCode == 0x0006)
            {
                selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("electLiu", map.value("electLiu").toString());
            }
            else if(funcCode == 0x000C)
            {
                //1表示打开，0表示关闭
                selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("cMos", map.value("cMos"));
                selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("fMos", map.value("fMos"));
            }
            else if(funcCode == 0x0018)
            {
                selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("celllType", map.value("celllType"));
                selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("cellNum", map.value("cellNum"));

            }
            else if(funcCode == 0x0000)
            {
                selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("mosTemperature", map.value("mosTemp"));
            }
            else if(funcCode == 0x0001)
            {
                selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("temperature1", map.value("cell_temp1"));
            }
            else if(funcCode == 0x0002)
            {
                selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("temperature2", map.value("cell_temp2"));
            }
            else if(funcCode == 0x0003)
            {
                selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("temperature3", map.value("cell_temp3"));
            }
            else if(funcCode == 0x0008)
            {
                selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("remaining_capacity", map.value("capacity"));
            }
            else if(funcCode == 0x000A)
            {
                selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("balStatus", map.value("balStatus"));
            }
            else if(funcCode == 0x000E)
            {
                selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("alarmlStatus", map.value("alarm_status"));
            }
            else if(funcCode == 0x000F)
            {
                selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("packStatus", map.value("pack_status"));
            }
            else if(funcCode == 0x0010)
            {
                selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("secondYa", map.value("secondary_voltage"));
            }
            else if(funcCode == 0x0011)
            {
                selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("secondLiu", map.value("secondary_current"));
            }
            else if(funcCode == 0x0012)
            {
                selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("secondTemperature", map.value("secondary_temperature"));
            }
            else if(funcCode == 0x0013)
            {
                selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("mainVer", map.value("mainVer"));
                selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("subVer", map.value("subVer"));
            }
            else if(funcCode == 0x0015)
            {
                selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("rtcY", map.value("rtc_year"));
                selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("rtcM", map.value("rtc_month"));
            }
            else if(funcCode == 0x0016)
            {
                selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("rtcD", map.value("rtc_day"));
                selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("rtcH", map.value("rtc_hour"));
            }
            else if(funcCode == 0x0017)
            {
                selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("rtcM1", map.value("rtc_minute"));
                selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("rtcS", map.value("rtc_second"));
            }
            else if(funcCode == 0x0019)
            {
                selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("afeNum", map.value("afeNum"));
                selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("cusNum", map.value("cusNum"));
            }
            else if(funcCode == 0x001A)
            {
                selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("cycles_number", map.value("cycles_number"));
            }
            else if(funcCode == 0x001B)
            {
                selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("fcc", map.value("full_charge_capacity"));
            }
            else if(funcCode == 0x001C)
            {
                selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("dc", map.value("dc"));
            }
            else if(funcCode == 0x001D)
            {
                selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("maxNoElect", map.value("maxNoElect"));
            }
            else if(funcCode == 0x001E)
            {
                selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("majNoElect", map.value("majNoElect"));
            }
            else if(funcCode == 0x001F)
            {
                selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("functionConfig", map.value("functionConfig"));
            }
            else if(funcCode >= 0x0020 && funcCode <= 0x003F) //单体电压
            {
                cellVlist.append(map.value("cellV"));
                if(cellVlist.size() == 32)
                {
                    double minVal = cellVlist.first().toDouble();
                    double maxVal = minVal;

                    // 遍历列表，更新极值
                    for (const QVariant &variant : cellVlist)
                    {
                        const double value = variant.toDouble();
                        if (value < minVal)
                        {
                            minVal = value;
                        }
                        else if (value > maxVal)
                        {
                            maxVal = value;
                        }
                    }
                    double tem = std::round(( maxVal - minVal) * 100.0) / 100.0;
                    selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("maxYa", maxVal);
                    selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("minYa", minVal);
                    selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("yaCha",tem);
                    selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("cellVlist", cellVlist);
                    cellVlist.clear();
                }
            }
            else if(funcCode >= 0x200 ) //可读写数据and funcCode <= 0x221
            {

                if(funcCode >= 0x418 && funcCode <= 0x446) //保护时间
                {
                    protectMap["protectTime"] = map.value("protectTime").toString();

                }
                else if(funcCode >= 0x448 && funcCode <= 0x476)//保护事件
                {
                    protectMap["protectEvent"] = map.value("protectEvent").toString();
                    selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("protectMap", protectMap);
                    protectMap.clear();
                }
                else
                {
                    QString viewValue = map.value("viewValue").toString();
                    selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue(viewValue, map.value(viewValue));
                }
            }
        }
    }
}

void BmsController::BleServiceCharacteristicRead(const QLowEnergyCharacteristic &c, const QByteArray &value)
{
    QTextCodec *codec = QTextCodec::codecForName("GBK");//指定QString的编码方式
    QString showMsg = c.uuid().toString() + codec->toUnicode(value);//Unicode编码格式输出信息
    QString valuetoHexString = value.toHex();//16进制输出信息

    qDebug()<<value;
    qDebug()<<valuetoHexString;
    // ui->listWidget_recv->addItem(showMsg + valuetoHexString);
    // ui->listWidget_recv->setCurrentRow(ui->listWidget_recv->count()-1);
}
