#include "hmmoduleini.h"
#include "HMUtils/hmutils.h"
#include <QDebug>

CHMModuleIni::CHMModuleIni(QObject *parent)
    : QObject(parent)
{
    selfCommonMap = getConfigCommon();
    selfPrefix = getSingleDeviceId(selfCommonMap); // 返回前缀
    selfDevId = getDeviceId(selfCommonMap) ;
    selfTopics = getTopics();
    selfMqttMap = getMqttMap();
    //获取主屏的宽高
    QString group = QString("HMView.%1").arg(0);
    winWidth = HMUtils::settingValue("width", group, "", "../ini/HMSle.ini").toInt();
    winHeight = HMUtils::settingValue("height", group, "", "../ini/HMSle.ini").toInt();
    //skq 1222
    // node_id = HMUtils::settingValue("nodeId", "mine", "nodeId is null", "/root/wrk/ysgmasterservice/bin/ini/keyMasterService.ini").toString();
    isUseShell = HMUtils::settingValue("isUseShell", "viewFlag", "1", "../ini/HMSle.ini").toInt();

}

CHMModuleIni::~CHMModuleIni()
{

}

QVariantMap CHMModuleIni::getConfigCommon()
{
    QVariantMap op;

    int lineId = HMUtils::settingValue("lineid", "Sle", 0, "../ini/HMSle.ini").toInt();
    int stationId = HMUtils::settingValue("stationid", "Sle", 0, "../ini/HMSle.ini").toInt();
//    int sletype = 0x13;
    int sletype = HMUtils::settingValue("sletype", "Sle", 0, "../ini/HMSle.ini").toString().toInt();
    int sleId = HMUtils::settingValue("sleid", "Sle", 0, "../ini/HMSle.ini").toString().toInt();
    QString prefix = HMUtils::settingValue("prefix", "Sle", "", "../ini/HMSle.ini").toString();




    HMUtils::log() << "getConfigCommon:" << "lineId:" << lineId
              << ",stationId:" << stationId
                 << ",sletype:" << sletype
                    << ",sleId:" << sleId
                       << ",prefix:" << prefix
              <<  HMLog::endl;

    op["lineid"] = lineId;
    op["stationid"] = stationId;
    op["sletype"] = sletype;
    op["sleid"] = sleId;
    op["prefix"] = prefix;
    return op;
}

QString CHMModuleIni::getSingleDeviceId(const QVariantMap &common)
{
    int lineId = common.value("lineid", 0).toInt();
    int stationId = common.value("stationid", 0).toInt();
    int sleType = common.value("sletype", 0).toInt();
    int sleId = common.value("sleid", 0).toInt();
    QString prefix = common.value("prefix", 0).toString();

//    QString num = QString("%1%2%3%4%5/")
//            .arg(prefix)
//            .arg(lineId, 2, 10, QChar('0'))
//            .arg(stationId, 2, 10, QChar('0'))
//            .arg(sleType, 2, 16, QChar('0'))
//            .arg(sleId, 2, 16, QChar('0'))
//            ;
    QString num = QString("%1%2%3%4%5/")
            .arg(prefix)
            .arg(lineId, 2, 10, QChar('0'))
            .arg(stationId, 2, 10, QChar('0'))
            .arg(sleType, 2, 16, QChar('0'))
            .arg(sleId, 2, 16, QChar('0'))
            ;
    qDebug()<<num;
    return num;
}

QString CHMModuleIni::getDeviceId(const QVariantMap &common)
{
    int lineId = common.value("lineid", 0).toInt();
    int stationId = common.value("stationid", 0).toInt();
    int sleType = common.value("sletype", 0).toInt();
    int sleId = common.value("sleid", 0).toInt();

    QString num = QString("%1%2%3%4")
            .arg(sleType, 2, 16, QChar('0'))
            .arg(lineId, 2, 10, QChar('0'))
            .arg(stationId, 2, 10, QChar('0'))
            .arg(sleId, 2, 16, QChar('0'))
            ;


    return num;
}


QString CHMModuleIni::getStationId(const QVariantMap &common)
{
    int lineId = common.value("lineid", 0).toInt();
    int stationId = common.value("stationid", 0).toInt();

    QString num = QString("%1%2")
            .arg(lineId, 2, 10, QChar('0'))
            .arg(stationId, 2, 10, QChar('0'))
            ;


    return num;
}

QString CHMModuleIni::getDeviceId()
{
    return selfDevId;
}

QStringList CHMModuleIni::getTopics()
{
    QStringList topics;
    QString revName = HMUtils::settingValue("revName", "stmView", "", "../ini/HMSle.ini").toString();
    QString moduleName = HMUtils::settingValue("moduleName", "stmView", "", "../ini/HMSle.ini").toString();
    // revName = revName.remove(QRegExp("\\s"));

    QStringList revNames = revName.split('|');
    selfRevNames = revNames;
    selfModuelName = moduleName;
    foreach (QString name, revNames)
    {
        QString topic = selfPrefix + name + QString("/event/%1/#").arg(selfModuelName);
        QString topic1 = selfPrefix + name + "/event/handshake/#";
        topics << topic << topic1;
    }
//    QString topic = revName + QString("/event/%1").arg(selfModuelName);
//    QString topic1 = revName + "/event/handshake/#";
//    topics << topic << topic1;
    return  topics;
}

QVariantMap CHMModuleIni::getMqttMap()
{
    QVariantMap op;
    QString ip = HMUtils::settingValue("mqttip", "Sle", "127.0.0.1", "HMSle.ini").toString();
    HMUtils::log() << "mqtt:" << ip << HMLog::endl;
    int port = HMUtils::settingValue("mqttport", "Sle", 1883, "HMSle.ini").toInt();
    op["ip"] = ip;
    op["port"] = port;
    return  op;
}

QVariantMap CHMModuleIni::readJsonConfig(const QString &filePath)
{

       // QFile file(filePath);
       // if (!file.open(QIODevice::ReadOnly))
       // {
       //     qWarning() << "Cannot open file for reading:" << file.errorString();
       //     return QVariantMap();
       // }

       // QByteArray data = file.readAll();
       // file.close();

       // QJsonDocument doc = QJsonDocument::fromJson(data);
       // if (!doc.isObject())
       // {
       //     qWarning() << "JSON is not an object.";
       //     return QVariantMap();
       // }

       // QJsonObject obj = doc.object();
       QVariantMap t;
       return t;
}

bool CHMModuleIni::writeJsonConfig(const QString &filePath, const QVariantMap &config)
{

    // 检查目录是否存在，如果不存在则创建它
        // QFileInfo fileInfo(filePath);
        // QDir dir;
        // if (!dir.mkpath(fileInfo.absolutePath())) {
        //     qWarning() << "Failed to create directory:" << fileInfo.absolutePath();
        //     return false;
        // }

        // QFile file(filePath);
        // if (!file.open(QIODevice::WriteOnly)) {
        //     qWarning() << "Cannot open file for writing:" << file.errorString();
        //     return false;
        // }

        // QJsonObject obj = QJsonObject::fromVariantMap(config);
        // QJsonDocument doc(obj);
        // QByteArray data = doc.toJson();
        // if (file.write(data) == -1) {
        //     qWarning() << "Failed to write to file:" << file.errorString();
        //     file.close();
        //     return false;
        // }

        // file.close();
        return true;
}

QVariantMap CHMModuleIni::initJsonConfig(const QString &filePath)
{
    if(QFile::exists(filePath))
    {
        QVariantMap obj = readJsonConfig(filePath);
        //渲染界面
        return obj;
    }
    else
    {

        // 初始化QMap
        QMap<QString, QVariant> mp;

        // activities
        QVariantMap activitiesMap;
        activitiesMap.insert("delayTime", 2.0);

        QVariantList showList;
        showList << "1.jpg" << "2.jpg";
        activitiesMap.insert("showList", showList);

        //Cnc
        QVariantMap cNCultureMap;
        cNCultureMap.insert("delayTime", 2.0);

        QVariantList showList_;
        showList_ << "1.png" << "2.png";
        cNCultureMap.insert("showVideoAndImageList", showList_);

        //inform
        QVariantMap informationMap;
        informationMap.insert("pic", "4.png");

        //welcome
        QVariantMap welcomeMap;
        welcomeMap.insert("animationEnable", 1.0);
        welcomeMap.insert("pic", "1.png");

        // 将所有的子QVariantMap加入到最外层的QVariantMap中
        QVariantMap paramMap;
        paramMap.insert("Activities", activitiesMap);
        paramMap.insert("Background", "background.jpg");
        paramMap.insert("CNCulture", cNCultureMap);
        paramMap.insert("Information", informationMap);
        paramMap.insert("Welcome", welcomeMap);

        // 最外层QMap的初始化
        mp.insert("command", "param.setting");
        mp.insert("name", "hmStm");
        mp.insert("param", paramMap);


        //写默认配置文件
        if(writeJsonConfig(filePath, mp))
        {
//            QVariantMap obj = readJsonConfig(filePath);
            //渲染界面
            return mp;
        }
        else
        {
            qDebug()<<"writeJsonConfig error";
        }
    }
    return QVariantMap();
}














