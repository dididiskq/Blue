#include "hmutils.h"
#include "hmprotocol.h"

CHMProtocal::CHMProtocal(QObject *parent) :
    QObject(parent)
{

}

CHMProtocal::~CHMProtocal()
{

}

QVariantMap CHMProtocal::getStatus()
{
    return  this->status;
}


















