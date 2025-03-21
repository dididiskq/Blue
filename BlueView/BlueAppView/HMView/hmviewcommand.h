#ifndef HMVIEWCOMMAND_H
#define HMVIEWCOMMAND_H

#include <QObject>
#include <QTranslator>
#include <chmres.h>
#include "hmview.h"
#include "hmmoduleini.h"
#include "hmmodule.h"
#include "HMUtils/common/hmcommand.h"
#include <QZXing.h>
//#include "opencv2/opencv.hpp"
// #include <QSoundEffect>
// #include <QtConcurrent>
class CHMModule;
class CHMViewCommand: public CHMCommand
{
    Q_OBJECT
public:
    explicit CHMViewCommand(QObject *parent = 0, const QString &name = "");
    ~CHMViewCommand();
    bool initView();
    //  设置客显界面变量
    bool initViewVariable();
    void setLanguageView();
    virtual void processCommand(const QString &command, const QVariantMap &op, QVariant &result);
    virtual void initCommands();
    virtual bool isCommand(const QString& command);
    virtual void processOp(const QVariantMap &op);
    virtual void sendOp(const QVariantMap &op);
    virtual void clearBuf();
    virtual void onHeartbeatTimer();
    virtual void disConnect();
    virtual void connect();
    void appendCommand(const QVariantMap &op);




    bool onStartSearchBlue(const QVariantMap &op);
    bool onSendToBlue(const QVariantMap &op);
    bool onSendCodeData(const QVariantMap &op);
    bool onConnectBlue(const QVariantMap &op);

    void playAudio(const QString &filePath);
public:


public slots:
    void render_image(const QVariantMap);

    // 更新摄像头数据
//    void updateFrame();
//    QString imageToBase64( QImage image);

signals:
    void playVoice(const QString path);
    void startBle();
    void sendBlueSlot(const int type);
    void connectBlueSlot(const QString addr);
public:
    CHMModule *selfObj;
    CHMView selfView;                                             // 界面对象
    typedef bool (CHMViewCommand::*func)(const QVariantMap &op);  // 定义数据类型，
    QMap<QString, CHMViewCommand::func> selfCommands;
    bool imageReady = false;

    int currentIndex;
//    QImage m_currentFrame;    // 存储当前帧
//    cv::VideoCapture m_camera; // OpenCV 摄像头对象
//    QTimer m_updateTimer;      // 定时器，用于定期捕获帧
//    bool isSendCamera = true;
    int frameCount = 0;
    // QSoundEffect effect;  // 将 QSoundEffect 作为成员变量


};

#endif // HMVIEWCOMMAND_H
