#include "hmini.h"
#include "hmutils.h"


CHMIni::CHMIni(QString &fileName, QObject *parent) :
    QObject(parent)
    , m_fileName(fileName)
{

}



CHMIni::~CHMIni()
{

}

QString CHMIni::getIni2String(const QString &name, const QString &group, const QVariant &defaultValue)
{
    QString value = HMUtils::settingValue(name, group, defaultValue, m_fileName).toString();
    return value;
}

int CHMIni::getIni2Dec(const QString &name, const QString &group, const QVariant &defaultValue)
{
    int value = HMUtils::settingValue(name, group, defaultValue, m_fileName).toInt();
    return value;
}

int CHMIni::getIni2Hex(const QString &name, const QString &group, const QVariant &defaultValue)
{
    int value = HMUtils::settingValue(name, group, defaultValue, m_fileName).toString().toInt(0, 16);
    return value;
}

void CHMIni::setIni(const QVariant &value, const QString &name, const QString &group)
{
    HMUtils::setSettingValue(value, name, group, m_fileName);
}



























