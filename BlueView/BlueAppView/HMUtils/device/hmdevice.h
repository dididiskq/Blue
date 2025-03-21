#ifndef HMDEVICE_H
#define HMDEVICE_H

#include <QObject>
#include <QDebug>
#include "common/hmthread.h"
#include <QTimer>
class CHMThread;

class CHMDevice : public QObject
{
	Q_OBJECT
public:
    explicit CHMDevice(QObject* parent = 0);
    virtual ~CHMDevice();
    virtual bool processOp() = 0;
    virtual void sendOp(const QVariantMap &op);

     bool isSyncFlag();
     bool isUseSync();
     void setUseSync(bool s);
     void setSyncFlag(bool flag);

signals:
    void startTimer();
    //同步超时处理函数信号
    void setSyncOpertionOverTime();
    void stopTimer();

public slots:
    virtual void onSendOp(const QVariantMap &) = 0;
public:
    CHMThread *selfThread;

private:
    bool selfIsSync;//收发是否启用同步标志
    bool selfSyncFlag;//同步标志

    QTimer selfOverTimer;
};

#endif // HMDEVICE_H
