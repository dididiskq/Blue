#include "hmutils.h"
#include "hmstates.h"
// #include "database/hmdbhelp.h"
CHMStates::CHMStates(QObject *parent) :
    QObject(parent)
{
    stateCode = 0;
    getGtStatusConfig();

    name = "CHMStates_STATUS";
}



CHMStates::~CHMStates()
{

}

void CHMStates::runState(bool isAuto)
{
    CHMStates::func f = commands.value(stateCode);
    if (f!=NULL){
        (this->*f)(isAuto);
    }
}

void CHMStates::appendState(const QString &name, const QVariantMap &op)
{
    states[name] = op;
}

int CHMStates::setState(const QString &name, const QVariantMap & state, bool isCheck)
{
    int code = stateCode;
    if(states.contains(name)){
        if((isCheck) || (states[name] != state)){
            states[name] = state;
            code = processStates();
        }
    }
    else{
        states[name] = state;
        code = processStates();
    }
    return  code;
}

int CHMStates::processStates()
{
    int state = doStates();
    if(state != stateCode){
        qDebug() << "processStates" << state << ":" << stateCode << endl;
        stateCode = state;
        CHMStates::func f = this->commands.value(stateCode);
        if (f!=NULL){
            (this->*f)(false);
        }
    }
    return  state;
}

int CHMStates::doStates()
{
    int stateFlag = 0;
    foreach(QVariant t, statusPosTable){
        QVariantMap op = t.toMap();
        QString Name = op.value("Name", "").toString();
        int pos = op.value("Position").toInt();
        int isEnable = op.value("IsEnable").toInt();

        bool isInit = states.value("isInit", true).toBool();
        QVariantMap stop = states.value(Name, QVariantMap()).toMap();

        int iSt = stop.value("status", 2).toInt();
        int value = 0;

        if(!isInit) {
            value = 1;
        }
        else if (isEnable != 0){
            value = (iSt == 2 ? 1:0);
        }
        stateFlag = stateFlag | value << pos;

    }
    return stateFlag;
}

bool CHMStates::getGtStatusConfig()
{
    HMDBHelp dbhelper;
    QString dbName = "../data/HMGTStatus.db";

    if(!dbhelper.open(dbName))
    {
        qDebug() <<dbName <<  ":打开失败！" << endl;
        return false;
    }

    QSqlQueryModel queryModel;
    QString sqlStr = "select count(*) from sqlite_master where type='table' and name=?";
    if(!HMDBHelp(dbName).execQuery(queryModel, sqlStr, QVariantList() << "StatusPosTable"))
    {
       return false;
    }

    int row = queryModel.rowCount();//获得行数
    if(row == 0)
    {
        return false;
    }
    QSqlRecord record = queryModel.record(0);//获得一条记录
    QString fieldName = record.fieldName(0);
    int value = record.value(fieldName).toUInt();
    if(value == 0){
        return false;
    }

    sqlStr = "select count(*) from sqlite_master where type='table' and name=?";
    if(!HMDBHelp(dbName).execQuery(queryModel, sqlStr, QVariantList() << "StatusTable"))
    {
        return false;
    }
    row = queryModel.rowCount();//获得行数
    if(row == 0)
    {
        return false;
    }
    record = queryModel.record(0);//获得一条记录
    fieldName = record.fieldName(0);
    value = record.value(fieldName).toUInt();
    if(value == 0){
        return false;
    }

    sqlStr = QString("select * from StatusPosTable ;");
    QVariant var;
    bool ret = dbhelper.execQuery(var, sqlStr);
    if (ret){
        this->statusPosTable = var.toList();
    }

    sqlStr = QString("select * from StatusTable ;");
    var.clear();
    ret = dbhelper.execQuery(var, sqlStr);
    if (ret){
        this->statusTable = var.toList();
    }
    foreach(QVariant t, this->statusTable){
        QVariantMap op = t.toMap();
        int hex = 0;
        foreach(QString k, op.keys()){
            bool f = false;

            int pos = k.toInt(&f);
            if(f){
                int value = op.value(k).toInt();
                hex = hex | value << pos;
            }
        }
        stateModel[hex] = op.value("StatusValue").toInt();

    }


   dbhelper.close();
   return true;
}

void CHMStates::log(const QString &msg)
{
//    HMUtils::log(name) << msg << HMLog::endl;
//    qDebug().noquote() << msg << endl;
    Q_UNUSED(msg);
}



















