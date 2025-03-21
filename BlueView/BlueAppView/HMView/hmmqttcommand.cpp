#include <QDebug>
#include <QThread>
#include <QProcess>
#include "hmutils.h"
#include "hmmqttcommand.h"
#include "hmmqttcommand.h"
CHMMqttCommand::CHMMqttCommand(QObject *parent, const QString &name)
    : CHMCommand(parent)
{
    selfObj = (CHMModule *)parent;
    selfName = name;
    initMqttClient();
    initCommands();
    // heartBeatTimerStart(1000);
}

CHMMqttCommand::~CHMMqttCommand()
{
    // if (selfMqttClient)
    // {
    //     delete selfMqttClient;
    //     selfMqttClient = NULL;
    // }
    // this->close();
}

void CHMMqttCommand::initMqttClient()
{
    QString ip =  selfObj->selfIni.selfMqttMap.value("ip", "127.0.0.1").toString();
    QHostAddress host = QHostAddress(ip);
    QStringList topics = selfObj->selfIni.selfTopics;
    int port = selfObj->selfIni.selfMqttMap.value("port", 1883).toInt();
    // selfMqttClient = new CHMMqttClient(topics, selfName, host, port);
    // selfMqttClient->connectToHost();
    // QObject::connect(selfMqttClient, SIGNAL(sendMsg(QVariantMap&,QVariant&))
                     // , selfObj, SLOT(test(QVariantMap&, QVariant&)));

//    QObject::connect(selfMqttClient, SIGNAL(saleTicketAnswer(QVariantMap&,QVariant&))
//                     , this, SLOT(onSaleTicketAnswer(QVariantMap&, QVariant&))/*, Qt::BlockingQueuedConnection*/);
}

void CHMMqttCommand::processCommand(const QString& command, const QVariantMap &op, QVariant &result)
{
    Q_UNUSED(command);
    processOp(op);
    result = true;
}

void CHMMqttCommand::initCommands()
{

    this -> selfCommands["param.setting"] = &CHMMqttCommand::onParamSetting;
    this -> selfCommands["handshake"] = &CHMMqttCommand::onHandShake;
    this->selfCommands["hmView.register.face.answer"] = &CHMMqttCommand::onRegisterAnswer;                      //注册人脸应答
    this->selfCommands["hmView.inquire.face.answer"] = &CHMMqttCommand::onInquireAnswer;                        //有人脸
//    this->selfCommands["hmFaceSDK.preface"] = &CHMMqttCommand::onHaveFace;                                      //000
    this->selfCommands["hmView.login.face.answer"] = &CHMMqttCommand::onInquireUserAnswer;                      //人脸数据
    this->selfCommands["hmView.login.account.answer"] = &CHMMqttCommand::onLoginAccountAnswer;                  //账号登录应答
    this->selfCommands["hmView.login.dingding.answer"] = &CHMMqttCommand::onLoginDingAnswer;                    //钉钉登录应答
    this->selfCommands["hmView.login.NFC.answer"] = &CHMMqttCommand::onLoginNfcAnswer;                          //钉钉登录应答
    this->selfCommands["hmView.borrow.key.answer"] = &CHMMqttCommand::onBorrowKeyAnswer;                        //借钥匙应答
    this->selfCommands["hmView.borrow.inquire.answer"] = &CHMMqttCommand::onBorrowKeyInquireAnswer;             //钥匙记录应答（未登录）
    this->selfCommands["hmView.borrow.inquire.detail.answer"] = &CHMMqttCommand::onBorrowKeyInquireDAnswer;     //钥匙记录详情应答
    this->selfCommands["hmView.logout.answer"] = &CHMMqttCommand::onHmViewLogoutAnswer;                         //登出应答
    this->selfCommands["hmView.other.authorization.answer"] = &CHMMqttCommand::onOtherAuthorizationAnswer;      //其他授权确认
    this->selfCommands["hmView.authorization.keys.answer"] = &CHMMqttCommand::onAuthorizationKeysAnswer;        //可授权钥匙列表应答
    this->selfCommands["hmView.borrow.keys.answer"] = &CHMMqttCommand::onBorrowKeysAnswer;                      //临时授权钥匙列表应答
    this->selfCommands["hmView.authorization.face.answer"] = &CHMMqttCommand::onGrantFaceAnswer;                      //授权人脸应答
    this->selfCommands["hmView.authorization.account.answer"] = &CHMMqttCommand::onGrantAccountAnswer;                      //授权账号应答
    this->selfCommands["hmView.authorization.dingding.answer"] = &CHMMqttCommand::onGrantDingAnswer;                      //授权扫码应答
    this->selfCommands["hmView.authorization.NFC.answer"] = &CHMMqttCommand::onGrantNfcAnswer;                      //关联FNC应答
    this->selfCommands["hmView.related.face.answer"] = &CHMMqttCommand::onRelatedFaceAnswer;                      //关联人脸应答
    this->selfCommands["hmView.related.phone.answer"] = &CHMMqttCommand::onRelatedPhoneAnswer;                      //关联手机号应答
    this->selfCommands["hmView.related.NFC.answer"] = &CHMMqttCommand::onRelatedNfcAnswer;                      //关联FNC应答
    this->selfCommands["hmView.return.answer"] = &CHMMqttCommand::onReturnAnswer;                               //返回应答
    this->selfCommands["hmView.time.out.answer"] = &CHMMqttCommand::onTimeOutAnswer;                            //超时应答
    this->selfCommands["hmView.enter.other.authorization.answer"] = &CHMMqttCommand::onEnterOtherAuthorizationAnswer;                            //超时应答
    this->selfCommands["hmView.enter.login.account.answer"] = &CHMMqttCommand::onEnterLoginAccountAnswer;
    this->selfCommands["hmView.get.key.list.answer"] = &CHMMqttCommand::onGetKeyListAnswer;
    this->selfCommands["hmView.NORMAL"] = &CHMMqttCommand::onNORMAL;
    this->selfCommands["hmView.OFFLINE"] = &CHMMqttCommand::onOFFLINE;
    this->selfCommands["hmView.ONLINE"] = &CHMMqttCommand::onONLINE;
    this->selfCommands["hmView.NOFACE"] = &CHMMqttCommand::onNOFACE;
    this->selfCommands["hmView.MAINTENANCE"] = &CHMMqttCommand::onMAINTENACNCEMODE;
    this->selfCommands["hmView.get.parameters.answer"] = &CHMMqttCommand::onGetParamAnswer;
    this->selfCommands["hmView.maintenance.answer"] = &CHMMqttCommand::onMaintenanceAnswer;
    this->selfCommands["hmView.take.photo.answer"] = &CHMMqttCommand::onTakePhotoAnswer;
    this->selfCommands["hmView.get.verification.code.answer"] = &CHMMqttCommand::onGetQrCodeAnswer;
    this->selfCommands["hmView.get.back.answer"] = &CHMMqttCommand::onGetBackAnswer;
    this->selfCommands["hmView.rfid.write.answer"] = &CHMMqttCommand::onRfidWriteAnswer;
    this->selfCommands["hmView.select.write.keys.answer"] = &CHMMqttCommand::onRfidWriteKeysAnswer;
    this->selfCommands["hmView.get.menu.answer"] = &CHMMqttCommand::onGetMeunAnswer;
    this->selfCommands["hmView.get.maintenanceList.answer"] = &CHMMqttCommand::onGetMaintenanceListAnswer;

}

bool CHMMqttCommand::isCommand(const QString &command)
{
    bool ret = selfCommands.contains(command);
    return  ret;
}

void CHMMqttCommand::processOp(const QVariantMap &op)
{
    QString command = op.value("command").toString();
    CHMMqttCommand::func f = selfCommands.value(command);
    bool result = false;
    Q_UNUSED(result);



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

void CHMMqttCommand::sendOp(const QVariantMap &op)
{
    QString command = op.value("command").toString();
    QString topic = this->selfObj->selfIni.selfPrefix;

//    QString topic = "";
    QString srcName = op.value("srcName", "").toString();
    if(srcName.isEmpty())
    {
        srcName = selfObj->selfIni.selfRevNames.first();
    }
    topic += QString("%1/event/%2/%3")
            .arg(selfObj->selfIni.selfModuelName)
            .arg(srcName)
            .arg(command);
//    topic += QString("%1/event/%2")
//            .arg(selfObj->selfIni.selfModuelName)
//            .arg(srcName);

    QVariantMap sop = op;
    sop["name"] =selfObj->selfIni.selfModuelName;
    if(op.value("isTts", -1).toInt() == 1)
    {
        sop["name"] = "hmMain";
        sop["topic"] = "/server/event/ttsDev/";
    }
    else
    {
        sop["topic"] = topic;
    }


//    sop["topic"] = op.value("topic", "").toString(); //临时使用（非配置文件内容）
    // selfMqttClient->sendOp(sop);
}

void CHMMqttCommand::onHeartbeatTimer()  // 心跳定时器
{
}

void CHMMqttCommand::clearBuf()
{
    HMUtils::log()<<"clearBuf" << HMLog::endl;
}

void CHMMqttCommand::disConnect()
{
    HMUtils::log() << "hmmqttcommand::disConnect" <<HMLog::endl;
    // CHMCommand::disConnect();

}

void CHMMqttCommand::connect()
{
    // CHMCommand::connect();
    firstStart = 1;
//    QVariantMap mm;
//    mm["command"] = "hmView.sale.param";          //  获取设备信息
//    this->sendOp(mm);
}

void CHMMqttCommand::appendCommand(const QVariantMap &op)
{
    sendOp(op);
}


bool CHMMqttCommand::onHandShake(const QVariantMap &op) // 回复心跳
{
    Q_UNUSED(op);
    QVariantMap sop1;
    sop1["command"] = "handshake.answer";
    sop1["version"] = selfObj->version;
    sop1["firstStart"] = firstStart;
    firstStart = 0;
    QVariantMap state;
    state["status"] = 0;
    state["connect"] = 1;
    state["info"] = "正常";
    state["code"] = 0;
    sop1["status"] = state;
    this->sendOp(sop1);
    return true;
}

bool CHMMqttCommand::onParamSetting(const QVariantMap &op)
{
    Q_UNUSED(op);
    return true;
}



bool CHMMqttCommand::onRegisterAnswer(const QVariantMap &op)
{
    int errCode = op.value("errCode", 0).toInt();
    if(errCode != 0)
    {
        QString errMsg = op.value("msg", "").toString();     
        selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("errMsg", errMsg);     
    }
    selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("conFaceErrCode", errCode);
    return true;
}

bool CHMMqttCommand::onInquireAnswer(const QVariantMap &op)
{   
    if(selfObj->selfViewCommand->currentIndex != 21)
    {
        return true;
    }

    int errCode = op.value("errCode", 0).toInt();

    if(errCode != 0)
    {
        QString errMsg = op.value("msg", "").toString();
        selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("errMsg", errMsg);
    }

    selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("errCode", errCode);
    return true;
}

//bool CHMMqttCommand::onHaveFace(const QVariantMap &op)
//{
//    return true;
//}

bool CHMMqttCommand::onInquireUserAnswer(const QVariantMap &op)
{
    if(selfObj->selfViewCommand->currentIndex != 21)
    {
        return true;
    }
    int errCode = op.value("errCode", 0).toInt();
    if(errCode != 0)
    {
        QString errMsg = op.value("msg", "").toString();
        selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("errCodeSec", errCode);
        selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("errMsg", errMsg);      
    }
    else
    {
        QString userName = op.value("userName", "").toString();
        QVariantList list = op.value("data").toList();
        QString jobNumber = op.value("jobNumber", "").toString();
        QString phoneNumber = op.value("phoneNumber", "").toString();
        QString registerTime = op.value("registerTime", "").toString();

        selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("jobNumber", jobNumber);
        selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("phoneNumber", phoneNumber);
        selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("registerTime", registerTime);
        selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("errCodeSec", errCode);
        selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("userName", userName);
        selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("keysList", list);
    }
    return true;
}

bool CHMMqttCommand::onLoginAccountAnswer(const QVariantMap &op)
{
    if(selfObj->selfViewCommand->currentIndex != 22)
    {
        return true;
    }
    QVariantList list = op.value("data").toList();
    int errCode = op.value("errCode", 0).toInt();
    if(errCode != 0)
    {
        QString errMsg = op.value("msg", "").toString();
        selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("errMsg", errMsg);
        selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("errCodeSec", errCode);

    }
    else
    {
        QString userName = op.value("userName", "").toString();
        QString jobNumber = op.value("jobNumber", "").toString();
        QString phoneNumber = op.value("phoneNumber", "").toString();
        QString registerTime = op.value("registerTime", "").toString();


        selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("jobNumber", jobNumber);
        selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("phoneNumber", phoneNumber);
        selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("registerTime", registerTime);
        selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("errCodeSec", errCode);
        selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("userName", userName);
        selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("keysList", list);
    }
    return true;
}

bool CHMMqttCommand::onLoginDingAnswer(const QVariantMap &op)
{
    if(selfObj->selfViewCommand->currentIndex != 23)
    {
        return true;
    }
    QVariantList list = op.value("data").toList();
    int errCode = op.value("errCode", 0).toInt();
    if(errCode != 0)
    {
        QString errMsg = op.value("msg", "").toString();
        selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("errCodeSec", errCode);
        selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("errMsg", errMsg);
    }
    else
    {
        QString userName = op.value("userName", "").toString();
        QString jobNumber = op.value("jobNumber", "").toString();
        QString phoneNumber = op.value("phoneNumber", "").toString();
        QString registerTime = op.value("registerTime", "").toString();


        selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("jobNumber", jobNumber);
        selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("phoneNumber", phoneNumber);
        selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("registerTime", registerTime);
        selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("errCodeSec", errCode);
        selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("userName", userName);
        selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("keysList", list);
    }
    return true;
}

bool CHMMqttCommand::onLoginNfcAnswer(const QVariantMap &op)
{
    if(selfObj->selfViewCommand->currentIndex != 24)
    {
        return true;
    }
    QVariantList list = op.value("data").toList();
    int errCode = op.value("errCode", 0).toInt();
    if(errCode != 0)
    {
        QString errMsg = op.value("msg", "").toString();
        selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("errCodeSec", errCode);
        selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("errMsg", errMsg); 
    }
    else
    {
        QString userName = op.value("userName", "").toString();
        QString jobNumber = op.value("jobNumber", "").toString();
        QString phoneNumber = op.value("phoneNumber", "").toString();
        QString registerTime = op.value("registerTime", "").toString();


        selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("jobNumber", jobNumber);
        selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("phoneNumber", phoneNumber);
        selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("registerTime", registerTime);
        selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("errCodeSec", errCode);
        selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("userName", userName);
        selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("keysList", list);
    }
    return true;
}

bool CHMMqttCommand::onBorrowKeyAnswer(const QVariantMap &op)
{
    int errCode = op.value("errCode", 0).toInt();
    if(errCode != 0)
    {
        QString errMsg = op.value("msg", "").toString();
        selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("isBrowKeyCode", errCode);
        selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("errMsg", errMsg);
    }
    else
    {
        QVariantList list = op.value("data").toList();
        QString jobNumber = op.value("jobNumber", "").toString();
        QString phoneNumber = op.value("phoneNumber", "").toString();
        QString registerTime = op.value("registerTime", "").toString();
        registerTime = registerTime.insert(4, "-").insert(7, "-").insert(10, " ").insert(13, ":").insert(16, ":");
        QString userName = op.value("userName", "").toString();

        selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("isBrowKeyCode", errCode);
        selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("jobNumber", jobNumber);
        selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("phoneNumber", phoneNumber);
        selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("registerTime", registerTime);
        selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("userName", userName);
        selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("data", list);
    }
    return true;
}

bool CHMMqttCommand::onBorrowKeyInquireAnswer(const QVariantMap &op)
{
    QVariantList list = op.value("data").toList();
    int errCode = op.value("errCode", 0).toInt();
    QString errMsg = op.value("msg", "").toString();
    if(errCode !=0 )
    {         
        selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("errMsg", errMsg);
    }
    else
    {   
        selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("keysList", list);
    }
    selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("errCodeSec", errCode);
    return true;
}

bool CHMMqttCommand::onBorrowKeyInquireDAnswer(const QVariantMap &op)
{
    int errCode = op.value("errCode", -1).toInt();
    QString errMsg = op.value("msg", "").toString();
    QString tip = op.value("tip", "").toString();
    QString dateTime = op.value("datetime", "").toString();
    // 解析时间字符串
    QDateTime dateTimeFormat = QDateTime::fromString(dateTime, "yyyyMMddhhmmss");

    // 格式化为目标格式
    QString formattedTime = dateTimeFormat.toString("yyyy-MM-dd hh:mm:ss");
    QString person = op.value("personnel", "").toString();
    QString telephone = op.value("telephone", "").toString();
    QString pic = op.value("pic", "").toString();
    QString expersonnel = op.value("expersonnel", "").toString();
    QString expersonnelTel = op.value("expersonnelTel", "").toString();

    if(errCode !=0 )
    {
        selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("errCode", errCode);
        selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("errMsg", errMsg);
    }
    else
    {
        selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("tip", tip);
        selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("registerTime", formattedTime);
        selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("userName", person);
        selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("phoneNumber", telephone);
        selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("borrowFaceImg", pic);
        selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("expersonnel", expersonnel);
        selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("expersonnelTel", expersonnelTel);
    }
    return true;
}

bool CHMMqttCommand::onHmViewLogoutAnswer(const QVariantMap &op)
{

    int errCode = op.value("errCode", -1).toInt();
    QString errMsg = op.value("msg", "").toString(); 
    if(errCode !=0 )
    {
        selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("errMsg", errMsg);
    }
    else
    {
        selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("errCode", -11);
        selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("errCodeSec", -11);
        selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("conFaceErrCode", -11);
        selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("conFaceErrCodeSec", -11);
        selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("userName", "");
        selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("errMsg", "");
    }
    return true;
}

bool CHMMqttCommand::onOtherAuthorizationAnswer(const QVariantMap &op)
{
    int errCode = op.value("errCode", -1).toInt();
    QString errMsg = op.value("msg", "").toString();

    if(errCode !=0 )
    {
        selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("errMsg", errMsg);
        selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("errCode", errCode);
    }
    else
    {
        selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("errCode", errCode);
        selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("errCodeSec", -11);
    }
    return true;
}

bool CHMMqttCommand::onAuthorizationKeysAnswer(const QVariantMap &op)
{
    int errCode = op.value("errCode", -1).toInt();
    QString errMsg = op.value("msg", "").toString();
    QVariantList list = op.value("data").toList();
    if(errCode !=0 )
    {
        selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("errMsg", errMsg);
        selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("errCodeSec", errCode);
    }
    else
    {
        selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("errMsg", errMsg);
        selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("errCodeSec", errCode);
        selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("keysList", list);
    }
    return true;
}

bool CHMMqttCommand::onBorrowKeysAnswer(const QVariantMap &op)
{
    int errCode = op.value("errCode", -1).toInt();
    QString errMsg = op.value("msg", "").toString();

    if(errCode != 0 )
    {
        selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("errMsg", errMsg);
        selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("choiceKeyCode", errCode);
    }
    else
    {
        selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("choiceKeyCode", errCode);
    }
    return true;
}

bool CHMMqttCommand::onGrantFaceAnswer(const QVariantMap &op)
{
    if(selfObj->selfViewCommand->currentIndex != 2531)
    {
        return true;
    }
    int errCode = op.value("errCode", 0).toInt();
    if(errCode != 0)
    {
        QString errMsg = op.value("msg", "").toString();
        selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("errCodeSec", errCode);
        selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("errMsg", errMsg);       
    }
    else
    {
        QString userName = op.value("userName", "").toString();
        QVariantList list = op.value("data").toList();

        QString jobNumber = op.value("jobNumber", "").toString();
        QString phoneNumber = op.value("phoneNumber", "").toString();
        QString registerTime = op.value("registerTime", "").toString();

        selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("jobNumber", jobNumber);
        selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("phoneNumber", phoneNumber);
        selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("registerTime", registerTime);

        selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("errCodeSec", errCode);
        selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("userName", userName);
        selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("keysList", list);
    }
    return true;
}

bool CHMMqttCommand::onGrantAccountAnswer(const QVariantMap &op)
{
    if(selfObj->selfViewCommand->currentIndex != 2532)
    {
        return true;
    }
    int errCode = op.value("errCode", -1).toInt();
    QString errMsg = op.value("msg", "").toString();
    if(errCode !=0 )
    {
        selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("errMsg", errMsg);
        selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("errCodeSec", errCode);
    }
    else
    {
        selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("errCodeSec", errCode);
    }
    return true;
}

bool CHMMqttCommand::onGrantDingAnswer(const QVariantMap &op)
{
    if(selfObj->selfViewCommand->currentIndex != 2533)
    {
        return true;
    }
    int errCode = op.value("errCode", -1).toInt();
    QString errMsg = op.value("msg", "").toString();
    if(errCode !=0 )
    {
        selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("errMsg", errMsg);
        selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("errCodeSec", errCode);
    }
    else
    {
        selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("errCodeSec", errCode);
    }
    return true;
}

bool CHMMqttCommand::onGrantNfcAnswer(const QVariantMap &op)
{
    if(selfObj->selfViewCommand->currentIndex != 2534)
    {
        return true;
    }
    int errCode = op.value("errCode", -1).toInt();
    QString errMsg = op.value("msg", "").toString();
    if(errCode !=0 )
    {
        selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("errMsg", errMsg);
        selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("errCodeSec", errCode);
    }
    else
    {
        selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("errCodeSec", errCode);
    }
    return true;
}

bool CHMMqttCommand::onRelatedFaceAnswer(const QVariantMap &op)
{
    int errCode = op.value("errCode", -1).toInt();
    QString errMsg = op.value("msg", "").toString();
    if(errCode !=0 )
    {
        selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("errMsg", errMsg);
    }     
    selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("conFaceErrCodeSec", errCode);
    return true;
}

bool CHMMqttCommand::onRelatedPhoneAnswer(const QVariantMap &op)
{
    int errCode = op.value("errCode", -1).toInt();
    QString errMsg = op.value("msg", "").toString();
    if(errCode !=0 )
    {
        selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("errMsg", errMsg);
    }

    selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("errCode", errCode);

    return true;
}

bool CHMMqttCommand::onRelatedNfcAnswer(const QVariantMap &op)
{
    int errCode = op.value("errCode", -1).toInt();
    QString errMsg = op.value("msg", "").toString();
    if(errCode !=0 )
    {
        selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("errMsg", errMsg);
    }

    selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("errCode", errCode);

    return true;
}

bool CHMMqttCommand::onReturnAnswer(const QVariantMap &op)
{
//    int errCode = op.value("errCode", -1).toInt();
//    QString errMsg = op.value("msg", "").toString();
//    if(errCode !=0 )
//    {
//        selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("errMsg", errMsg);
//    }
//    else
//    {
//        selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("errCode", errCode);
//    }
    return true;
}

bool CHMMqttCommand::onTimeOutAnswer(const QVariantMap &op)
{
    int errCode = op.value("errCode", -1).toInt();
    QString errMsg = op.value("msg", "").toString();
    if(errCode !=0 )
    {
        selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("errMsg", errMsg);
    }
    else
    {
        selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("errCode", errCode);
    }
    return true;
}

bool CHMMqttCommand::onEnterOtherAuthorizationAnswer(const QVariantMap &op)
{
    return true;
}

bool CHMMqttCommand::onEnterLoginAccountAnswer(const QVariantMap &op)
{
    return true;
}

bool CHMMqttCommand::onGetKeyListAnswer(const QVariantMap &op)
{
    int errCode = op.value("errCode", -1).toInt();
    QString errMsg = op.value("msg", "").toString();
    QVariantList list = op.value("data").toList();
    if(errCode != 0)
    {
        selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("errMsg", errMsg);
    }
    else
    {
        selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("keysList", list);
    }
    selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("errCodeSec", errCode);

    return true;
}

/*
 * noface: -1
 * normal：1
 * offline：-2
 * online：2
*/


bool CHMMqttCommand::onNOFACE(const QVariantMap &op)
{
    QString errMsg = op.value("msg", "").toString();
//    selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("isOline", -1);
    selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("isMaintenance", -1);
    selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("errMsg", errMsg);
    return true;
}

bool CHMMqttCommand::onOFFLINE(const QVariantMap &op)
{
    QString errMsg = op.value("msg", "").toString();
    selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("isOline", -2);
    emit selfObj->selfViewCommand->selfView.context("HMStmView")->mySignal("offline");
    return true;
}

bool CHMMqttCommand::onONLINE(const QVariantMap &op)
{
    QString errMsg = op.value("msg", "").toString();
    selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("isOline", 2);
    emit selfObj->selfViewCommand->selfView.context("HMStmView")->mySignal("online");
    return true;
}

bool CHMMqttCommand::onNORMAL(const QVariantMap &op)
{
    QString errMsg = op.value("msg", "").toString();
    selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("isNormal", 1);
    selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("isMaintenance", -1);
    return true;
}

bool CHMMqttCommand::onMAINTENACNCEMODE(const QVariantMap &op)
{
    selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("isMaintenance", 1);
    return true;
}

bool CHMMqttCommand::onGetParamAnswer(const QVariantMap &op)
{
    int errCode = op.value("errCode", -1).toInt();
    if(errCode != 0)
    {
        QString errMsg = op.value("msg", "").toString();
        selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("errMsg", errMsg);
    }

    QVariantMap map = op.value("parameters").toMap();
    int maxBorrowKeys = map["MaxBorrowKeys"].toInt();
    selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("maxBorrowKeys", maxBorrowKeys);
    QRUrlBase = map["QRUrlBase"].toString();

//    QDateTime currentTime = QDateTime::currentDateTime();
//    QString now = currentTime.toString("yyyyMMddhhmmss");
//    selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("isRefreshCode", now);
    emit selfObj->selfViewCommand->selfView.context("HMStmView")->mySignal("refreshCode");
    return true;
}

bool CHMMqttCommand::onMaintenanceAnswer(const QVariantMap &op)
{     
    int errCode = op.value("errCode", -1).toInt();
    QString rfid = op.value("rfid").toString();
    if(rfid != "")
    {
        selfObj->selfViewCommand->selfView.context("HMStmView")->setRfid(rfid);
    }
    if(errCode != 0)
    {
        QString errMsg = op.value("msg", "").toString();
        selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("errCode", errCode);
        selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("errMsg", errMsg);
    }
    else
    {

        selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("errMsg", "");
        selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("errCode", errCode);
        QString test = op.value("test").toString();

//        qDebug()<<test;
    }
    return true;
}

bool CHMMqttCommand::onTakePhotoAnswer(const QVariantMap &op)
{
    int errCode = op.value("errCode", -1).toInt();
    QString errMsg = op.value("msg", "").toString();
    QString grantFace = op.value("picId", "").toString();
    selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("grantFaceImg", grantFace);
    if(errCode !=0 )
    {
        selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("errMsg", errMsg);
    }
    else
    {
        selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("errCode", errCode);
    }
    return true;
}

bool CHMMqttCommand::onGetQrCodeAnswer(const QVariantMap &op)
{
    int errCode = op.value("errCode", -1).toInt();
    QString errMsg = op.value("msg", "").toString();
//    if(errCode !=0 )
//    {
//        selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("errCode", errCode);
//        selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("errMsg", errMsg);
//    }
//    else
//    {
//        selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("errCode", errCode);
//    }
    return true;
}

bool CHMMqttCommand::onGetBackAnswer(const QVariantMap &op)
{
    int errCode = op.value("errCode", -1).toInt();
    if(errCode !=0 )
    {
        qDebug()<<"上一步错误";
    }
    return true;
}

bool CHMMqttCommand::onRfidWriteAnswer(const QVariantMap &op)
{
    if(selfObj->selfViewCommand->currentIndex != 271)
    {
        return true;
    }
    int errCode = op.value("errCode", -1).toInt();
    QString errMsg = op.value("msg", "").toString();
    QVariantList list = op.value("data").toList();
    if(errCode != 0)
    {
        selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("errMsg", errMsg);
    }
    else
    {
        selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("keysList", list);
    }
    selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("errCode", errCode);
    return true;
}

bool CHMMqttCommand::onRfidWriteKeysAnswer(const QVariantMap &op)
{
    if(selfObj->selfViewCommand->currentIndex != 271)
    {
        return true;
    }
    int errCode = op.value("errCode", -1).toInt();
    QString errMsg = op.value("msg", "").toString();
    if(errCode != 0)
    {
        selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("errMsg", errMsg);
    }

    selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("errCodeSec", errCode);
    return true;
}

bool CHMMqttCommand::onGetMeunAnswer(const QVariantMap &op)
{
    return true;
}

bool CHMMqttCommand::onGetMaintenanceListAnswer(const QVariantMap &op)
{
    int errCode = op.value("errCode", -1).toInt();
    QString errMsg = op.value("msg", "").toString();
    QVariantList list = op.value("data").toList();
    if(errCode != 0)
    {
        selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("errMsg", errMsg);
    }
    else
    {
        selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("keysList", list);
    }
    selfObj->selfViewCommand->selfView.context("HMStmView")->setFieldValue("errCodeSec", errCode);
    return true;
}






