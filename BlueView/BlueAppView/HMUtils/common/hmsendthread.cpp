#include "hmsendthread.h"
#include <QDebug>

CHMSendThread::CHMSendThread(QObject *parent) :
    CHMThread(parent)
{
    selfObj = (CHMDevice*)parent;
}

CHMSendThread::~CHMSendThread()
{

}


void CHMSendThread::run()
{ 
     while (selfRunning)
     {
//         operationLock();
         if(!this->selfObj->processOp()){
              msleep(10);
         }
//         operationUnlock();
     }
}
































