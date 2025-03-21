#include "hmdb.h"
#include <QDateTime>
// #include "hmdbhelp.h"


CHMDb::CHMDb(QObject *parent) : QObject(parent)
{

}

CHMDb::~CHMDb()
{

}

bool CHMDb::isTatbleExist(const QString &tableName, const QString &dbName)
{
    QSqlQueryModel queryModel;
    QString sqlStr = "select count(*) from sqlite_master where type='table' and name=?";
    bool ret = HMDBHelp(dbName).execQuery(queryModel, sqlStr, QVariantList() << tableName);
    if(!ret)
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
    return value != 0;
}

bool CHMDb::isColumnExist(const QString &columnName, const QString &tableName, const QString &dbName)
{
    QSqlQueryModel queryModel;
    QString sqlStr = "select sql from sqlite_master where type='table' and name=?";
    bool ret = HMDBHelp(dbName).execQuery(queryModel, sqlStr, QVariantList() << tableName);
    if(!ret)
    {
       return false;
    }

    int row = queryModel.rowCount();//获得行数
    if(row == 0)
    {
        return false;
    }
    QSqlRecord record = queryModel.record(0);//获得一条记录
    QString fieldName = record.value("sql").toString();

    if (!fieldName.contains(columnName))
    {
        return false;
    }
    return true;
}

bool CHMDb::insertOp(const QString& dbPathName,  const QVariantMap &op)
{
    QString dbName = dbPathName;

    QString sql = "INSERT INTO UDTable ";

    QString keys = "( ";
    QString v = "";
    QVariantList list;

    QVariantMap::const_iterator i = op.constBegin();
    while (i != op.constEnd()) {
        keys += i.key();
        keys += ", ";
        v += "?, ";
        list << i.value();
        ++i;
    }
    keys = keys.trimmed();
    keys = keys.left(keys.length()-1);
    sql += keys;
    sql += " ) VALUES ( ";

    v  = v.trimmed();
    v = v.left(v.length()-1);
    sql += v;
    sql += " );";
    bool bRet = HMDBHelp(dbName).execQuery(sql, list);
    return bRet;
}


