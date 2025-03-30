#include <qDebug>
#include "hmmodule.h"
#include "hmutils.h"
// 构造函数
CHMModule::CHMModule(QObject *parent)
    : CHMModuleBasics(parent)
{
    /*
        版本:1.00.001.20250117
        @author:skq
    */
    version = "1.00.001.20250224";
    HMUtils::log() << QString("界面程序版本： %1").arg(version) <<HMLog::endl;

    selfMqttCommand = new CHMMqttCommand(this, "HMMain");  // 通讯对象
    selfRegister.setRegister(selfIni.selfRevNames, selfMqttCommand);

    selfViewCommand = new CHMViewCommand(this, "hmView");  // 界面对象
    selfRegister.setRegister(selfIni.selfModuelName, selfViewCommand);

    selfBmsCommand = new BmsController(this);
    initConnectSlots();
}

CHMModule::~CHMModule()
{
    if (selfMqttCommand)
    {
        delete selfMqttCommand;
        selfMqttCommand = NULL;
    }
    if (selfViewCommand)
    {
        delete selfViewCommand;
        selfViewCommand = NULL;
    }

}

void CHMModule::initConnectSlots()
{
    connect(selfViewCommand, &CHMViewCommand::startBle, selfBmsCommand, &BmsController::startSearch);
    connect(selfViewCommand, &CHMViewCommand::sendBlueSlot, selfBmsCommand, &BmsController::viewMessage);
    connect(selfViewCommand, &CHMViewCommand::writeBlueSlot, selfBmsCommand, &BmsController::viewWriteMessage);
    connect(selfViewCommand, &CHMViewCommand::connectBlueSlot, selfBmsCommand, &BmsController::connectBlue);

}
// 重写父类的方法
void CHMModule::doProcessOp(const QVariantMap &op)
{
    QString name = op.value("name").toString();
    QString command = op.value("command").toString();
    CHMCommand* obj = (CHMCommand*)selfRegister.isHasObj(name);
    QVariant result = true;
    if (obj)
    {
        if (obj->isCommand(command))
        {
            obj->isConnect();
            obj->processCommand(command, op, result);
        }
        else {
            HMUtils::log() << name << "模块, " << command << ", 无此命令" << HMLog::endl;
        }
    }
    else {
       HMUtils::log() << name << ", 模块未注册" << HMLog::endl;
    }
}

bool CHMModule::start()
{
    return selfViewCommand->initView();
}

void CHMModule::stop()
{
    HMUtils::log()<<"stop"<<HMLog::endl;
}

void CHMModule::test(QVariantMap &parameters, QVariant &result)
{
    Q_UNUSED(result);
    this->selfThread->appendOp(parameters);
}

void CHMModule::playVoices(const QString path)
{
    // if(selfIni.isUseShell == 0)
    // {
    //     mediaPlayer->stop();
    // //    mediaPlayer->setMedia(QUrl::fromLocalFile(path));
    //     mediaPlayer->setMedia(QUrl::fromLocalFile(QFileInfo(path).absoluteFilePath()));
    //     mediaPlayer->play();
    // }
    // else
    // {
    //     // 如果已经有 aplay 进程在运行，先杀掉它
    //     if (aplayProcess->state() == QProcess::Running)
    //     {
    //         aplayProcess->kill();
    //         aplayProcess->waitForFinished(); // 等待进程结束
    //     }

    //     // 获取音频文件的绝对路径
    //     QString absolutePath = QFileInfo(path).absoluteFilePath();

    //     aplayProcess->start("aplay", QStringList() << absolutePath);

    //     // 检查是否成功启动
    //     if (!aplayProcess->waitForStarted())
    //     {
    //         qWarning() << "Failed to start aplay process.";
    //         return;
    //     }

    //     qDebug() << "Playing audio with aplay:" << absolutePath;
    // }
}





