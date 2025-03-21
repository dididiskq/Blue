#ifndef HMSYSTEM_H
#define HMSYSTEM_H
#include <QObject>
#include <QVariantMap>
#include <QProcess>

class CHMSystem: public QObject  // 定义一个类
{
    Q_OBJECT
public:
    explicit CHMSystem(QObject *parent = 0);
    ~CHMSystem();

    void start(const QString& cmd, const QStringList& list);
    void start(const QString& cmd);
    void setProcessChannelMode(QProcess::ProcessChannelMode mode);

signals:
    void readyReadStandardOutput(const QByteArray &data);
    void readyReadStandardError(const QByteArray &data);

public slots:
    void write_cmd(const QString &cmd);
    void read_data();
    void finished_process();
    void error_process();

private:
    QProcess *process;
};

#endif // HMSYSTEM_H
