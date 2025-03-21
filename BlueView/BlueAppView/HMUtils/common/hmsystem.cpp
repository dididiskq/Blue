#include "hmsystem.h"
#include <QDebug>

CHMSystem::CHMSystem(QObject *parent)
    : QObject(parent)
{
    process = new QProcess(this);
    setProcessChannelMode(QProcess::MergedChannels);
    //读命令行数据
    connect(process,SIGNAL(readyRead()),this,SLOT(read_data()));
    //读命令行标准数据（兼容）
    connect(process,SIGNAL(readyReadStandardOutput()),this,SLOT(read_data()));
    //命令行错误处理
    connect(process,SIGNAL(errorOccurred(QProcess::ProcessError)),this,SLOT(error_process()));
    //命令行结束处理
    connect(process,SIGNAL(finished(int)),this,SLOT(finished_process()));
    start("cmd.exe");
}

CHMSystem::~CHMSystem()
{
    process->close();
    delete process;
    process = NULL;
    // qDebug() << "end Process" << endl;
}

void CHMSystem::start(const QString &cmd, const QStringList &list)
{
    process->start(cmd, list);
}

void CHMSystem::start(const QString &cmd)
{
    process->start(cmd);
}

void CHMSystem::setProcessChannelMode(QProcess::ProcessChannelMode mode)
{
    process->setProcessChannelMode(mode);
}

void CHMSystem::write_cmd(const QString &cmd)
{
    /* 转为char*并写入 */
    QByteArray qbarr = cmd.toLatin1();
    char *ch = qbarr.data();
    qint64 len = cmd.length();
    process->write(ch, len);

    /* 信息输出 */
    // qDebug() << "Success:write_cmd：" << cmd << endl;
}

void CHMSystem::read_data()
{
    /* 接收数据 */
    QByteArray bytes = process->readAll();

    /* 显示 */
    QString msg = QString::fromLocal8Bit(bytes);
    /* 信息输出 */
    // qDebug() << "Success:read_data:" << msg << endl;
}

void CHMSystem::finished_process()
{
    /* 接收数据 */
    int flag = process->exitCode();

    /* 信息输出 */
    // qDebug() << "Success:finishedProcess():" << flag << endl;
}

void CHMSystem::error_process()
{
    int err_code  = process->exitCode();
    QString err = process->errorString();

    /* 信息输出 */
    // qDebug() << "Success:error_process():" << err << err_code<< endl;
}








