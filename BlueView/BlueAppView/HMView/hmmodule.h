#ifndef HMMODULE_H
#define HMMODULE_H
#include <QObject>
// #include "HMUtils/device/hmmqttclient.h"
#include "hmmoduleini.h"
#include "hmmqttcommand.h"
#include "hmviewcommand.h"
#include "QVariantMap"
#include "HMUtils/common/hmregister.h"
#include "HMUtils/common/hmmodulebasics.h"
#include"BmsController.h"
// #include "HMUtils/network/hmudp.h"
// #include <QMediaPlayer>
#include<QProcess>
class CHMMqttCommand;
class CHMViewCommand;
class BmsController;
// The CHMModule class
class CHMModule: public CHMModuleBasics
{
    Q_OBJECT
public:
    explicit CHMModule(QObject *parent = 0);
    ~CHMModule();
    void doProcessOp(const QVariantMap &op);
    bool start();
    void stop();
//    void textDeome();  // 调试一些测试信息
    void initConnectSlots();
public slots:
    void test(QVariantMap& parameters, QVariant &result);

    void playVoices(const QString path);

public:
    CHMModuleIni selfIni;               // 配置文件
    CHMMqttCommand *selfMqttCommand;    // 通讯助手
    CHMViewCommand *selfViewCommand;    // 界面文件
    BmsController *selfBmsCommand;
    CHMRegister selfRegister;           // 注册器

    // HMUdp selfUdp;
    // QMediaPlayer *mediaPlayer;
    QProcess* aplayProcess; // 用于管理 aplay 进程
};

#endif // HMMODULE_H
