#include <QDebug>
#include <QTimer>
#include <QDebug>
#include <QJsonDocument>
#include "hmutils.h"
#include "hmviewcommand.h"
#include "hmviewcommand.h"
#include <qrencode.h>
#include <QUrl>

//#include <QtConcurrent/QtConcurrentRun>

CHMViewCommand::CHMViewCommand(QObject *parent, const QString &name)
    : CHMCommand(parent)

{
    selfObj = (CHMModule *)parent;
    selfName = name;
    initCommands();
    this->selfView.setName(selfName);

    QObject::connect(&this->selfView, SIGNAL(updateCommand(QVariantMap&, QVariant&)), selfObj, SLOT(test(QVariantMap&, QVariant&)));
    //案例调用




//    m_camera.open(0); // 使用默认摄像头
//    if (!m_camera.isOpened())
//    {
//        qWarning("Failed to open camera!");
//        return;
//    }
//    // 设置定时器，每 30ms 捕获一帧
//    QObject::connect(&m_updateTimer, &QTimer::timeout, this, &CHMViewCommand::updateFrame);
//    m_updateTimer.start(20); // ~33 FPS
}

CHMViewCommand::~CHMViewCommand()
{
    this->close();
}

bool CHMViewCommand::initView()
{


    initViewVariable(); //  初始化客显界面变量
#ifdef Q_OS_LINUX

    QVariantMap OSType;
    OSType["type"] = 0;//WINDOWS
    selfView.context("HMMaintenance")->setFieldValue("OSType", OSType);

#else
    //    HmLog << "OSType===Windows" << HmLogEnd;
#endif
//    HMUtils::log() << "initViews()" <<HMLog::endl;
    if (!selfView.initViews())
    {
        HMUtils::log() << "初始化界面失败" <<HMLog::endl;
        return false;
    }
    return true;
}

bool CHMViewCommand::initViewVariable()
{
    HMUtils::log() <<"initViewVariable:" << QGuiApplication::applicationDirPath() <<HMLog::endl;
    QString absPath = "../";
    #ifdef Q_OS_LINUX
//        absPath = "/sdcard/HMApplication";
        absPath = "/data/data/com.termux/files/home/HMApplication";
    #else
//        absPath = QGuiApplication::applicationDirPath();
    #endif

    selfView.context("HMStmView")->setFieldValue("soh", 0);
    selfView.context("HMStmView")->setFieldValue("soc", 0);
    selfView.context("HMStmView")->setFieldValue("winWidth", this->selfObj->selfIni.winWidth);
    selfView.context("HMStmView")->setFieldValue("winHeight",this->selfObj->selfIni.winHeight);
    selfView.context("HMStmView")->setFieldValue("nodeID", this->selfObj->selfIni.node_id);
    selfView.context("HMStmView")->setFieldValue("isOline", -2);
//    selfView.context("HMStmView")->setFieldValue("codeUrl", "D:/svn_chanpin/tai_zhou/pro/HMStorageView/views/image/QRCode.png");
    return true;
}

void CHMViewCommand::processCommand(const QString& command, const QVariantMap &op, QVariant &result)
{
    Q_UNUSED(command);
    processOp(op);
    result = true;
}

//注册回调
void CHMViewCommand::initCommands()
{   
    selfCommands["start.search.blue"] = &CHMViewCommand::onStartSearchBlue;
    selfCommands["send.to.blue"] = &CHMViewCommand::onSendToBlue;
    selfCommands["send.codeData"] = &CHMViewCommand::onSendCodeData;
    selfCommands["connect.blue"] = &CHMViewCommand::onConnectBlue;
}

bool CHMViewCommand::isCommand(const QString &command)
{
    bool ret = selfCommands.contains(command);
    return  ret;
}

void CHMViewCommand::processOp(const QVariantMap &op)
{
    QString command = op.value("command").toString();
    CHMViewCommand::func f = selfCommands.value(command);
    bool result = false;
    Q_UNUSED(result);
//    if (f != NULL)
//    {
//        result = (this->*f)(op);
//    }
    try
    {
        if (f != NULL)
        {
            result = (this->*f)(op);
        }

    }
    catch (const std::exception& e)
    {
        qDebug()<<command + e.what();
    }
    catch (...)
    {
        qDebug()<<command + "未知异常";
    }
}

void CHMViewCommand::sendOp(const QVariantMap &op)
{
    Q_UNUSED(op);
    HMUtils::log()<<"void CHMViewCommand::sendOp(const QVariantMap &op)"<<HMLog::endl;
}

void CHMViewCommand::clearBuf()
{
    HMUtils::log()<<"clearBuf" << HMLog::endl;
}

void CHMViewCommand::onHeartbeatTimer()
{

}

void CHMViewCommand::disConnect()
{

}

void CHMViewCommand::connect()
{

}

void CHMViewCommand::appendCommand(const QVariantMap &op)
{

    sendOp(op);
}


bool CHMViewCommand::onStartSearchBlue(const QVariantMap &op)
{
    emit startBle();
    return true;
}


void CHMViewCommand::render_image(const QVariantMap op)
{
    QString base64Image = op.value("base64Image", "").toString();
    if (!base64Image.isEmpty())
    {
        selfView.context("HMStmView")->setBase64Image(base64Image);
    }     
}



bool CHMViewCommand::onSendToBlue(const QVariantMap &op)
{
    int type = op.value("type", -1).toInt();
    emit sendBlueSlot(type);
    return true;
}

bool CHMViewCommand::onSendCodeData(const QVariantMap &op)
{
    QVariant imageVar = op.value("codeData");
    if (!imageVar.canConvert<QImage>())
    {
        qDebug() << "无效的 QImage 数据";
        return true;
    }

    QImage image = imageVar.value<QImage>();
    if (image.isNull())
    {
        qDebug() << "图像为空";
        return true;
    }

    if (image.isNull())
    {
        qCritical() << "Error: Image file not loaded!";
        return -1;
    }

    // QImage converted = img.convertToFormat(QImage::Format_RGB32);
    QZXing decoder;
    //QR Code二维码
    decoder.setDecoder(QZXing::DecoderFormat_QR_CODE);
    //可选设置，赋值自文档demo
    decoder.setSourceFilterType(QZXing::SourceFilter_ImageNormal);
    decoder.setTryHarderBehaviour(QZXing::TryHarderBehaviour_ThoroughScanning |
                                  QZXing::TryHarderBehaviour_Rotate);
    QString info = decoder.decodeImage(image);
    if(info == "")
    {

    }
    else
    {
        selfView.context("HMStmView")->setFieldValue("codeData", info);
    }
    qDebug()<<info;

    return true;
}

bool CHMViewCommand::onConnectBlue(const QVariantMap &op)
{
    QString addr = op.value("addr").toString();
    emit connectBlueSlot(addr);
    return true;
}
