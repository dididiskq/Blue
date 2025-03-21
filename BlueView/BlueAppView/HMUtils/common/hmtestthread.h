#ifndef HMTESTTHREAD_H
#define HMTESTTHREAD_H

#include <QObject>
#include <QString>
#include "hmthread.h"
#include <QVariantList>
#include <QTimer>
#include <QMutex>
#include "hmmodulebasics.h"

class CHMModuleBasics;

/**
 * @brief The CHMTestThread class
 * 线程的基类，
 */
class CHMTestThread : public CHMThread
{
    Q_OBJECT
public:
    friend class CHMModuleBasics;
    explicit CHMTestThread(QObject *parent = 0);
    ~CHMTestThread();
protected:
    void run();

private:
    CHMModuleBasics *selfObj;
};

#endif // HMTESTTHREAD_H
