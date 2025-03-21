#include "hmcom.h"
#include <QDebug>
#include "hmutils.h"
#include <QThread>
CHMCom::CHMCom(const QVariantMap &ini, const QString &name, CHMProtocal *protocal, QObject* parent):
    CHMDevice(parent)
{
    this->selfIni = ini;
    this->selfProtocal = protocal;
    this->selfName = name;
}

CHMCom::~CHMCom()
{
    if (selfPort.isOpen())
    {
        selfPort.close();
    }
}

bool CHMCom::open()
{
    QString port = this->selfIni.value("port", "").toString();
    selfPort.setPortName(port);

    if (!selfPort.open(QIODevice::ReadWrite))
    {
        qDebug() <<port << "打开失败" << endl;
        return false;
    }

    int baurate = this->selfIni.value("baurate", "38400" ).toInt();
    int stopbits = this->selfIni.value("stopbits", "1").toInt();
    int parity = this->selfIni.value("parity", "0").toInt();
    int databits = this->selfIni.value("databits", "8").toInt();
    int flow = this->selfIni.value("flow", "0").toInt();


    //设置波特率和读写方向
    selfPort.setBaudRate(baurate);
    //一位停止位
    selfPort.setStopBits((QSerialPort::StopBits)stopbits);
    //无流控制
    selfPort.setFlowControl((QSerialPort::FlowControl)flow);
    //无校验位
    selfPort.setParity((QSerialPort::Parity)parity);
    //数据位为8位
    selfPort.setDataBits((QSerialPort::DataBits)databits);

    selfPort.clearError();
    selfPort.clear();

    connect(&selfPort, SIGNAL(readyRead()), this, SLOT(readyReadSlot()));
    qDebug() <<port << "打开成功" << endl;
    return true;
}

bool CHMCom::close()
{
    if (selfPort.isOpen())
    {
        selfPort.close();
    }
    return true;
}

CHMProtocal *CHMCom::getProtocal()
{
    return this->selfProtocal;
}

int CHMCom::write(const QVariantMap& op)
{
    QByteArray byte = this->selfProtocal->byte(op);
    int ret = this->selfPort.write(byte);
//    selfPort.flush();
    HMUtils::log(selfName) << ">> " << byte << HMLog::endl;

    if (ret == -1)
    {
        qDebug() << "发送失败" << endl;
    }
    else
    {
    }
    //上成命令   CHMCommand
    //协议命令   CHMDevice
    //心跳

    return ret;
}

void CHMCom::clearBuf()
{
    selfThread->clearExecuteOperations();
}

bool CHMCom::processOp()
{
    selfThread->operationLock();
    bool hasOperations = !selfThread->operations().isEmpty();
    if (hasOperations)
    {
        //如果是发线程 并且启用了收发同步
        if (isUseSync())
        {
            if (!isSyncFlag())
            {
                //可以发送
                setSyncFlag(true);
                emit  startTimer();
                QVariantMap operation = selfThread->operations().first().toMap();
                selfThread->operations().removeFirst();
                selfThread->operationUnlock();
                emit selfThread->deviceEvent(operation);
            }
            else
            {
                //不可以发送
                selfThread->operationUnlock();
                return false;
            }
        }
        else
        {
            QVariantMap operation = selfThread->operations().first().toMap();
            selfThread->operations().removeFirst();
            selfThread->operationUnlock();
            emit selfThread->deviceEvent(operation);
        }

        return true;
    }
    else
    {
        selfThread->operationUnlock();
        return false;
    }
}

void CHMCom::readyReadSlot()
{
    QByteArray arr = selfPort.readAll();
    this->selfArray += arr;
    HMUtils::log(selfName) << "<< " << arr << HMLog::endl;
    qDebug() << "<<"  << arr.toHex() << endl;
    int size = 0;
    int result = 0;

    if(this->selfProtocal)
    {
        QVariantMap op;
        do
        {
            op.clear();
            op = this->selfProtocal->parse(this->selfArray, size, result);
            switch (result)
            {
            case 0:
                //0 保留数据
                //qDebug() << "保留数据" << endl;
                break;
            case -1:
                //-1 移除 size
                this->selfArray.remove(0, size);
                //qDebug() << "移除" << size << endl;
                break;
            default:
            {
                if (result > 0){
                    //>0 成功 移除size
                    QVariant res = true;
                    op["name"] = this->selfName;
                    //深拷贝
                    QVariantMap sop = op;
                    sop.detach();
                    emit sendMsg(sop, res);
                    this->selfArray.remove(0, size);
                    //                qDebug() << "成功, 移除" << size << endl;
                    break;
                }
                else {
                    qDebug() << "返回结果错误：" << result << endl;
                }
            }
            }

        }
        while(!op.isEmpty());

    }
    else
    {
        qDebug() << "未找到协议对象" << endl;
    }
}

void CHMCom::onSendOp(const QVariantMap &op)
{
    write(op);
}






























