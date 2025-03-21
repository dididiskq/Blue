#ifndef HMMODULEINI_H
#define HMMODULEINI_H
#include <QObject>
#include <QVariantMap>
#include "HMUtils/common/hmini.h"

class CHMModuleIni: public QObject  // 定义一个类
{
    Q_OBJECT
public:
    explicit CHMModuleIni(QObject *parent = 0);
    ~CHMModuleIni();
    // 返回设备编号
    QString getDeviceId(const QVariantMap &common);
    QString getDeviceId();
    QString getStationId(const QVariantMap &common);
    QVariantMap initJsonConfig(const QString &filePath);
    QVariantMap readJsonConfig(const QString& filePath);
    bool writeJsonConfig(const QString &filePath, const QVariantMap& config);
private:
    QVariantMap getConfigCommon();
    // 获取通讯身份编号
    QString getSingleDeviceId(const QVariantMap &common);
    QStringList getTopics();
    QVariantMap getMqttMap();




public:
    QVariantMap selfCommonMap;
    QString selfPrefix;
    QStringList selfTopics;
    QVariantMap selfMqttMap;
    QStringList selfRevNames;
    QString selfModuelName;
    QString selfDevId;
    int winWidth;
    int winHeight;
    QString node_id;
    int isUseShell;
};

#endif // HMMODULEINI_H
