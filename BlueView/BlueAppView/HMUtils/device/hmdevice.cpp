#include "hmdevice.h"
#include <QDebug>
#include "hmutils.h"
#include <QThread>
#include "common/hmsendthread.h"

CHMDevice::CHMDevice(QObject* parent):
    QObject(parent)
  , selfIsSync(false)
  , selfSyncFlag(false)
{
    selfThread = new CHMSendThread(this);
    QObject::connect(selfThread, &CHMSendThread::deviceEvent
                     , this
                     , &CHMDevice::onSendOp
//                     , Qt::BlockingQueuedConnection
//                     , Qt::QueuedConnection
                     );

    selfThread->start();

    QObject::connect(&selfOverTimer
                     ,&QTimer::timeout
                     , this, [=]{
        // qDebug() << "接收超时" << endl;
        selfOverTimer.stop();
        setSyncFlag(false);
        emit setSyncOpertionOverTime();
    }
    );
    //开始发送命令
    QObject::connect(this, &CHMDevice::startTimer
                     , this
                     , [=]{
        selfOverTimer.stop();
        selfOverTimer.start(2000);
        qDebug() << "threadId: " << QThread::currentThreadId();
    }
    );
    //规定时间内收到应答
    QObject::connect(this, &CHMDevice::stopTimer
                     , this
                     , [=]{
        // qDebug() << "停止selfOverTimer.stop();" << endl;
        selfOverTimer.stop();
    }
    );
}

CHMDevice::~CHMDevice()
{
    selfThread->terminate();
}

void CHMDevice::sendOp(const QVariantMap &op)
{
    Q_UNUSED(op);
    this->selfThread->appendOp(op);
}

bool CHMDevice::isSyncFlag()
{
    return selfSyncFlag;
}

bool CHMDevice::isUseSync()
{
    return  selfIsSync;
}

void CHMDevice::setUseSync(bool s)
{
    selfIsSync = s;
}

void CHMDevice::setSyncFlag(bool flag)
{
    selfSyncFlag = flag;
}

































