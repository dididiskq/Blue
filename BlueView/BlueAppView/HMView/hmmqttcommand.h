#ifndef HMMQTTCOMMAND_H
#define HMMQTTCOMMAND_H

#include <QObject>
// #include "HMUtils/device/hmmqttclient.h"
#include "hmmoduleini.h"
#include "hmmodule.h"
#include "HMUtils/common/hmcommand.h"

class CHMModule;
class CHMMqttCommand: public CHMCommand
{
    Q_OBJECT
public:
    explicit CHMMqttCommand(QObject *parent = 0, const QString &name = "");
    ~CHMMqttCommand();
    void initMqttClient();
    virtual void processCommand(const QString &command, const QVariantMap &op, QVariant &result);
    virtual void initCommands();
    virtual bool isCommand(const QString& command);
    virtual void processOp(const QVariantMap &op);
    virtual void sendOp(const QVariantMap &op);
    virtual void onHeartbeatTimer();
    virtual void clearBuf();
    virtual void disConnect();
    // 虚函数，mqtt连接成功后调用
    virtual void connect();
    void appendCommand(const QVariantMap &op);
    // 接口方法
    bool onHandShake(const QVariantMap &op);  // 心跳命令
    bool onParamSetting(const QVariantMap &op);  // 设置参数


    bool onRegisterAnswer(const QVariantMap& op);
    bool onInquireAnswer(const QVariantMap& op);
//    bool onHaveFace(const QVariantMap& op);
    bool onInquireUserAnswer(const QVariantMap& op);
    bool onLoginAccountAnswer(const QVariantMap& op);
    bool onLoginDingAnswer(const QVariantMap& op);
    bool onLoginNfcAnswer(const QVariantMap& op);
    bool onBorrowKeyAnswer(const QVariantMap& op);
    bool onBorrowKeyInquireAnswer(const QVariantMap& op);
    bool onBorrowKeyInquireDAnswer(const QVariantMap& op);
    bool onHmViewLogoutAnswer(const QVariantMap& op);
    bool onOtherAuthorizationAnswer(const QVariantMap& op);
    bool onAuthorizationKeysAnswer(const QVariantMap& op);
    bool onBorrowKeysAnswer(const QVariantMap& op);
    bool onGrantFaceAnswer(const QVariantMap& op);
    bool onGrantAccountAnswer(const QVariantMap& op);
    bool onGrantDingAnswer(const QVariantMap& op);
    bool onGrantNfcAnswer(const QVariantMap& op);
    bool onRelatedFaceAnswer(const QVariantMap& op);
    bool onRelatedPhoneAnswer(const QVariantMap& op);
    bool onRelatedNfcAnswer(const QVariantMap& op);
    bool onReturnAnswer(const QVariantMap& op);
    bool onTimeOutAnswer(const QVariantMap& op);
    bool onEnterOtherAuthorizationAnswer(const QVariantMap& op);
    bool onEnterLoginAccountAnswer(const QVariantMap& op);
    bool onGetKeyListAnswer(const QVariantMap& op);
    bool onNOFACE(const QVariantMap& op);
    bool onOFFLINE(const QVariantMap& op);
    bool onONLINE(const QVariantMap& op);
    bool onNORMAL(const QVariantMap& op);
    bool onMAINTENACNCEMODE(const QVariantMap& op);
    bool onGetParamAnswer(const QVariantMap& op);
    bool onMaintenanceAnswer(const QVariantMap& op);
    bool onTakePhotoAnswer(const QVariantMap& op);
    bool onGetQrCodeAnswer(const QVariantMap& op);
    bool onGetBackAnswer(const QVariantMap& op);
    bool onRfidWriteAnswer(const QVariantMap& op);
    bool onRfidWriteKeysAnswer(const QVariantMap& op);
    bool onGetMeunAnswer(const QVariantMap& op);
    bool onGetMaintenanceListAnswer(const QVariantMap& op);

    QString QRUrlBase = "";
public slots:

signals:

private:
    CHMModule *selfObj;
    // CHMMqttClient *selfMqttClient;
    QString name;
    typedef bool (CHMMqttCommand::*func)(const QVariantMap &op);  //定义数据类型，
    QMap<QString, CHMMqttCommand::func> selfCommands;
    int firstStart;

};

#endif // HMMQTTCOMMAND_H
