#ifndef HMSENDTHREAD_H
#define HMSENDTHREAD_H

#include <QObject>
#include <QString>
#include "hmthread.h"
#include <QVariantList>
#include <QTimer>
#include <QMutex>
#include "device/hmdevice.h"
class CHMDevice;

class CHMSendThread : public CHMThread
{
    Q_OBJECT
public:
    friend class CHMDevice;
    explicit CHMSendThread(QObject *parent = 0);
    ~CHMSendThread();
protected:
    void run();
private:
    CHMDevice *selfObj;
};

#endif // HMSENDTHREAD_H
