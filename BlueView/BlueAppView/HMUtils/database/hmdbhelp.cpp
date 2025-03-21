#include "hmdbhelp.h"
#include <QDateTime>
#include "HMUtils/hmutils.h"

#include <QUuid>

#include <QTime>
#include <QApplication>
#include <QCryptographicHash>

QMutex * HMDBHelp::mutex = new QMutex;

HMDBHelp::HMDBHelp(QObject *parent) : QObject(parent)
{
}

HMDBHelp::HMDBHelp(const QString &dbFileName, QObject *parent) : QObject(parent)
{
    if(!log.isOpen())
    {
        QString fileName = dbFileName.mid(dbFileName.lastIndexOf("/")+1);
        fileName = fileName.left(fileName.lastIndexOf("."));
        fileName += ".log";
        log.open(fileName);
    }
    open(dbFileName);
}

HMDBHelp::HMDBHelp(
		const QString &host,
		int port,
		const QString &database,
		const QString &uid,
		const QString &pwd,
		const QString &driver,
		QObject *parent
		) : QObject(parent)
{
	open(host, port, database, uid, pwd, driver);
}

HMDBHelp::~HMDBHelp()
{
    if (isOpen())
	{
		close();
	}
}

QString HMDBHelp::databaseName()
{
	if (connectionName().isEmpty())
        return QString("");

	return connectionName();
}

QString HMDBHelp::connectionName()
{
	return databaseConnectionName;
}


void HMDBHelp::setConnectionName(const QString &name)
{
	databaseConnectionName = name;
}

bool HMDBHelp::checkConnection()
{
    mutex->tryLock(0xFFFFFFFF);

	if (lastSqlError.type() == QSqlError::ConnectionError)
	{
        log << "db conn error, ["
                                     << lastSqlError.type() << "] "
                                     << lastSqlError.text() << HMLog::endl;

        log << "reconnect to host" << HMLog::endl;
		if (QSqlDatabase::database(connectionName()).open())
		{
            log << "reconnect success" << HMLog::endl;
		}
		else
		{
            log << "reconnect fail" << HMLog::endl;
		}
	}

    bool okay = QSqlDatabase::database(connectionName()).isOpen();

    mutex->unlock();

    return okay;
}

bool HMDBHelp::isOpen()
{
    mutex->tryLock(0xFFFFFFFF);

//	mutex.lock();
	QSqlDatabase db = QSqlDatabase::database(connectionName());
//	mutex.unlock();

    bool okay = db.isOpen();

    mutex->unlock();

    return okay;
}



bool
HMDBHelp::open(
		const QString &host,
		int port,
		const QString &database,
		const QString &uid,
		const QString &pwd,
		const QString &driver
		)
{
    if (!mutex->tryLock(0xFFFFFFFF))
        return false;
//    QMutexLocker locker(mutex);

	if (log.isOpen())
		log.close();

	QSqlDatabase db = QSqlDatabase::database(connectionName());

	if (db.isOpen())
	{
        mutex->unlock();
		close();
	}

	QString md5 = QCryptographicHash::hash(QUuid::createUuid().toByteArray(), QCryptographicHash::Md5).toHex();

	setConnectionName(md5);

//	log.open("db." + connectionName());
    log.open("db.log");

	db = QSqlDatabase::addDatabase(driver, connectionName());

	if (!db.isValid())
	{
		lastSqlError = db.lastError();
		log << "open fail, " << db.lastError().text() << HMLog::endl;

        mutex->unlock();
        close();
		return false;
	}

	db.setConnectOptions("MYSQL_OPT_RECONNECT=1;");
	db.setHostName(host);
	db.setPort(port);
	db.setUserName(uid);
	db.setPassword(pwd);
	db.setDatabaseName(database);

	if (!db.open())
	{
		lastSqlError = db.lastError();
		log << "open fail, " << db.lastError().text() << HMLog::endl;

        mutex->unlock();
        close();
		return false;
	}

	lastSqlError = db.lastError();

    bool okay = db.isOpen();

    mutex->unlock();

    return okay;
}

bool HMDBHelp::open(const QString &dbFileName)
{
    if (!mutex->tryLock(0xFFFFFFFF))
        return false;

//    QMutexLocker locker(mutex);
//	mutex.lock();
	QSqlDatabase db = QSqlDatabase::database(connectionName());
//	mutex.unlock();


//	log.open("db." + connectionName());
    if(!log.isOpen())
    {
        QString fileName = dbFileName.mid(dbFileName.lastIndexOf("/")+1);
        fileName = fileName.left(fileName.lastIndexOf("."));
        fileName += ".log";
        log.open(fileName);
    }

	if (db.isOpen())
	{
        mutex->unlock();
		close();
	}

    QString md5 = QCryptographicHash::hash(QUuid::createUuid().toByteArray(), QCryptographicHash::Md5).toHex();

    setConnectionName(dbFileName + "." + md5);
	db = QSqlDatabase::addDatabase("QSQLITE", connectionName());
	db.setDatabaseName(dbFileName);

	if (!db.open())
    {
		lastSqlError = db.lastError();
		log << "open fail, " << db.lastError().text() << HMLog::endl;

        mutex->unlock();
        close();
		return false;
	}

	lastSqlError = db.lastError();

    bool okay = db.isOpen();

    mutex->unlock();

    return okay;
}

void HMDBHelp::close()
{
    if (connectionName().isEmpty())
        return;

    if (!mutex->tryLock(0xFFFFFFFF))
        return;

//    QMutexLocker locker(mutex);
//	mutex.lock();

	QSqlDatabase::database(connectionName()).close();
	QSqlDatabase::removeDatabase(connectionName());

    setConnectionName("");

    mutex->unlock();
//	mutex.unlock();
}


bool HMDBHelp::recordIsExisted(const QString &tableName, const QString &keyName, const QVariant &keyValue)
{
    QString sql = "select * from " + tableName + " where " + keyName + "=?";

	QSqlQueryModel m;

	if (!execQuery(m, sql, QVariantList() << keyValue))
		return false;

//    QMutexLocker locker(mutex);

    if (!mutex->tryLock(0xFFFFFFFF))
    {
        return false;
    }

	if (m.rowCount() > 0)
	{
		m.query().clear();
		m.clear();

        mutex->unlock();
		return true;
	}

    mutex->unlock();

	return false;
}

int HMDBHelp::recordCount(const QString &fieldName, const QString &tableName, const QString &condition, const QVariantList &values)
{
    QString sql = "select count(" + fieldName + ") from " + tableName + " where " + condition;
	QSqlQuery q;

	if (!execQuery(q, sql, values))
		return -1;

//    QMutexLocker locker(mutex);

    if (!mutex->tryLock(0xFFFFFFFF))
    {
        return false;
    }

	if (!q.next())
	{
		q.clear();
        mutex->unlock();
		return 0;
	}

	QSqlRecord r = q.record();

	int count = r.value(0).toInt();

	q.clear();

    mutex->unlock();

	return count;
}

bool HMDBHelp::transaction()
{
	if (!checkConnection())
		return false;

//    QMutexLocker locker(mutex);

    if (!mutex->tryLock(0xFFFFFFFF))
    {
        return false;
    }

	QSqlDatabase db = QSqlDatabase::database(connectionName());

//	db.exec("start transaction");
    db.transaction();
	lastSqlError = db.lastError();
	if (lastSqlError.isValid())
    {
		lastSqlError = db.lastError();
        log << "transaction failed. [" << lastSqlError.type() << "] " << lastSqlError.text()
                << HMLog::endl;

        mutex->unlock();
        return false;
	}

    mutex->unlock();

    return true;
}

bool HMDBHelp::beginTransaction()
{
    if (!checkConnection())
        return false;

//	QMutexLocker locker(&mutex);

    if (!mutex->tryLock(0xFFFFFFFF))
        return false;


    QSqlDatabase db = QSqlDatabase::database(connectionName());

    db.exec("BEGIN TRANSACTION;");
    lastSqlError = db.lastError();
    if (lastSqlError.isValid())
    {
        lastSqlError = db.lastError();
        log << "transaction failed. [" << lastSqlError.type() << "] " << lastSqlError.text()
                << HMLog::endl;

        mutex->unlock();
        return false;
    }

    mutex->unlock();

    return true;
}

bool HMDBHelp::endTransaction()
{
    if (!checkConnection())
        return false;

    if (!mutex->tryLock(0xFFFFFFFF))
        return false;

//	QMutexLocker locker(&mutex);

    QSqlDatabase db = QSqlDatabase::database(connectionName());

    db.exec("END TRANSACTION;");
    lastSqlError = db.lastError();
    if (lastSqlError.isValid())
    {
        lastSqlError = db.lastError();
        log << "transaction failed. [" << lastSqlError.type() << "] " << lastSqlError.text()
                << HMLog::endl;

        mutex->unlock();
        return false;
    }

    mutex->unlock();

    return true;
}

bool HMDBHelp::rollbackSqlite3()
{
    if (!checkConnection())
        return false;

//    QMutexLocker locker(&mutex);

    if (!mutex->tryLock(0xFFFFFFFF))
        return false;

    QSqlDatabase db = QSqlDatabase::database(connectionName());

//    if (!db.rollback())
    db.exec("ROLLBACK;");
    lastSqlError = db.lastError();
    if (lastSqlError.isValid())
    {
        log << "rollback failed. [" << lastSqlError.type() << "] " << lastSqlError.text()
                << HMLog::endl;

        mutex->unlock();
        return false;
    }

    mutex->unlock();

    return true;

}

bool HMDBHelp::commit()
{
	if (!checkConnection())
		return false;

//    QMutexLocker locker(mutex);

    if (!mutex->tryLock(0xFFFFFFFF))
    {
        return false;
    }

	QSqlDatabase db = QSqlDatabase::database(connectionName());

//	if (!db.commit())
//	db.exec("commit");
    db.commit();
	lastSqlError = db.lastError();
	if (lastSqlError.isValid())
	{
        log << "commit failed. [" << lastSqlError.type() << "] " << lastSqlError.text()
                << HMLog::endl;

        mutex->unlock();
        return false;
	}

    mutex->unlock();

    return true;
}

bool HMDBHelp::rollback()
{
    if (!checkConnection())
        return false;

//    QMutexLocker locker(mutex);

    if (!mutex->tryLock(0xFFFFFFFF))
        return false;

    QSqlDatabase db = QSqlDatabase::database(connectionName());

//    if (!db.rollback())
//	db.exec("rollback");
    db.rollback();
	lastSqlError = db.lastError();
	if (lastSqlError.isValid())
    {
        log << "rollback failed. [" << lastSqlError.type() << "] " << lastSqlError.text()
                << HMLog::endl;

        mutex->unlock();

        return false;
    }

    mutex->unlock();

    return true;
}

bool HMDBHelp::execQuery(QSqlQuery &query, const QString &sql, const QVariantList &values)
{
	if (!checkConnection())
		return false;

//    QMutexLocker locker(mutex);
    if (!mutex->tryLock(0xFFFFFFFF))
    {
        return false;
    }

	QSqlDatabase db = QSqlDatabase::database(connectionName());
	QSqlQuery q(db);

	query = q;

	if (!query.prepare(sql))
	{
		lastSqlError = query.lastError();
		log << "exec query prepare failed. [" << query.lastError().type() << "] " << query.lastError().text()
				<< HMLog::endl
				<< sql
				<< HMLog::endl;

        qDebug() << "exec query prepare failed. [" << query.lastError().type() << "] " << query.lastError().text()
                << endl
                << sql
                << HMLog::endl;

//        qDebug() << "exec query prepare failed. [" << query.lastError().type() << "] " << query.lastError().text()
//                << endl
//                << sql
//                << endl;


		query.clear();
        mutex->unlock();
		return false;
	}

	lastSqlError = query.lastError();

	foreach (QVariant value, values)
	{
		query.addBindValue(value);
	}

	if (!query.exec())
	{
		lastSqlError = query.lastError();
		log
				<< "exec query failed. [" << query.lastError().type() << "] " << query.lastError().text()
				<< HMLog::endl
				<< sql
				<< HMLog::endl;

        qDebug()
                << "exec query failed. [" << query.lastError().type() << "] " << query.lastError().text()
                << endl
                << sql
                << endl;

		query.clear();
        mutex->unlock();
		return false;
	}

	lastSqlError = query.lastError();

    mutex->unlock();
	return true;
}

bool HMDBHelp::execQuery(QVariant &var, const QString &sql, const QVariantList &values)
{
    QSqlQuery query;

	if (!execQuery(query,sql,values))
		return false;

    if (!mutex->tryLock(0xFFFFFFFF))
        return false;

//    QMutexLocker locker(mutex);
	QVariantList lst;

	while (query.next())
	{
		QSqlRecord r = query.record();

		QVariantMap m;

		for (int i = 0; i < r.count(); i++)
		{
			QSqlField f = r.field(i);
			m[f.name()] = f.value();
		}

		lst << m;
	}

	query.clear();

	var = lst;

    mutex->unlock();

	return true;
}

QSqlQuery HMDBHelp::call(const QString &produce, const QVariantList &parameters)
{
	if (!checkConnection())
		return QSqlQuery();

//    QMutexLocker locker(mutex);
    if (!mutex->tryLock(0xFFFFFFFF))
    {
        return QSqlQuery();
    }


	QString params;

	foreach (QVariant var, parameters)
	{
		QString parameter;

		switch (var.type())
		{
		case QVariant::Int:
		case QVariant::LongLong:
		case QVariant::UInt:
		case QVariant::ULongLong:
		case QVariant::Double:
			parameter = var.toString();
			break;
		case QVariant::String:
			parameter = "'" + var.toString() + "'";
			break;
		case QVariant::DateTime:
			parameter = "'" + var.toDateTime().toString("yyyy-MM-dd hh:mm:ss") + "'";
			break;
		case QVariant::Time:
			parameter = "'" + var.toTime().toString("hh:mm:ss") + "'";
			break;
		default:
			parameter = var.toString();
			break;
		}

		if (!params.isEmpty())
			params += ",";

		params += parameter;

	}

	QString sql = "call " + produce + "(" + params + ")";
//    qDebug() << " sql = " << sql << endl;

	QSqlQuery query = QSqlDatabase::database(connectionName()).exec(sql);

	lastSqlError = query.lastError();
	if (lastSqlError.isValid())
	{
        log << "call failed. ["
                                     << lastSqlError.type() << "] "
                                     << lastSqlError.text()
                                     << HMLog::endl
                                     << sql
                                     << HMLog::endl;
//        qDebug() << "call failed. ["
//                                     << lastSqlError.type() << "] "
//                                     << lastSqlError.text()
//                                     << endl
//                                     << sql
//                                     << endl;

		query.clear();

        mutex->unlock();
		return QSqlQuery();
	}

    mutex->unlock();

	return query;
}


bool HMDBHelp::execQuery(QSqlQueryModel &m, const QString &sql, const QVariantList &values)
{
	if (!checkConnection())
		return false;

    if (!mutex->tryLock(0xFFFFFFFF))
        return false;

//    QMutexLocker locker(mutex);
	QSqlQuery q(QSqlDatabase::database(connectionName()));

	if (!q.prepare(sql))
	{
		lastSqlError = q.lastError();

		log
				<< "exec query prepare failed. [" << q.lastError().type() << "] " << q.lastError().text()
				<< HMLog::endl
				<< sql
				<< HMLog::endl;

        qDebug()
                << "exec query prepare failed. [" << q.lastError().type() << "] " << q.lastError().text()
                << endl
                << sql
                << endl;

        mutex->unlock();
		return false;
	}

	lastSqlError = q.lastError();

	foreach (QVariant value, values)
	{
		q.addBindValue(value);
	}

    if (!q.exec())
    {

        lastSqlError = q.lastError();
        log
                << "exec query failed. [" << q.lastError().type() << "] " << q.lastError().text()
                << HMLog::endl
                << sql
                << HMLog::endl;
        qDebug()
                << "exec query failed. [" << q.lastError().type() << "] " << q.lastError().text()
                << endl
                << sql
                << endl;

        q.clear();

        mutex->unlock();
        return false;
    }

	m.setQuery(q);

	if(m.lastError().isValid())
	{
		lastSqlError = q.lastError();
		log
				<< "exec query model failed. [" << q.lastError().type() << "] " << m.lastError().text()
				<< HMLog::endl
				<< sql
				<< HMLog::endl;

        qDebug()
                << "exec query model failed. [" << q.lastError().type() << "] " << m.lastError().text()
                << endl
                << sql
                << endl;

		q.clear();
		m.clear();

        mutex->unlock();
		return false;
	}

	lastSqlError = q.lastError();

    while (m.canFetchMore())
	{
		m.fetchMore();
	}

    mutex->unlock();

	return true;
}

bool HMDBHelp::execQuery(const QString &sql, const QVariantList &values)
{
    if (!checkConnection())
    {
        return false;
    }

//    QMutexLocker locker(mutex);

    if (!mutex->tryLock(0xFFFFFFFF))
        return false;


//	mutex.lock();
	QSqlDatabase db = QSqlDatabase::database(connectionName());
	QSqlQuery q(db);
//	mutex.unlock();

	if (!values.isEmpty())
	{
		if (!q.prepare(sql))
		{
			lastSqlError = q.lastError();
            log << "exec query prepare failed. ["
                                         << q.lastError().type() << "] "
                                         << q.lastError().text()
                                         << HMLog::endl
                                         << sql
                                         << HMLog::endl;

//            qDebug() << "exec query prepare failed. ["
//                                         << q.lastError().type() << "] "
//                                         << q.lastError().text()
//                                         << endl
//                                         << sql
//                                         << endl;

			q.clear();

            mutex->unlock();
			return false;
		}

		lastSqlError = q.lastError();

		foreach (QVariant value, values)
		{
			q.addBindValue(value);
		}

		if (!q.exec())
		{
			lastSqlError = q.lastError();
            log << "exec query failed. ["
                                         << q.lastError().type() << "] "
                                         << q.lastError().text()
                                         << HMLog::endl
                                         << sql
                                         << HMLog::endl;

//            qDebug() << "exec query failed. ["
//                     << q.lastError().type() << "] "
//                     << q.lastError().text()
//                     << endl
//                     << sql
//                     << endl;

			q.clear();
            mutex->unlock();
			return false;
		}
	}
	else
	{
		if (!q.exec(sql))
		{
			lastSqlError = q.lastError();
            log << "exec query failed. ["
                                         << q.lastError().type() << "] "
                                         << q.lastError().text()
                                         << HMLog::endl
                                         << sql
                                         << HMLog::endl;
//            qDebug() << "exec query failed. ["
//                                         << q.lastError().type() << "] "
//                                         << q.lastError().text()
//                                         << endl
//                                         << sql
//                                         << endl;

			q.clear();

            mutex->unlock();
			return false;
		}
	}

	lastSqlError = q.lastError();
    mutex->unlock();

	return true;
}
