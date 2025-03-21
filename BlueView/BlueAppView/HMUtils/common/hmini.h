#ifndef HMINI_H
#define HMINI_H

#include <QObject>
#include <QString>


class CHMIni : public QObject
{
    Q_OBJECT
public:
    explicit CHMIni(QString &fileName, QObject *parent = 0);
    virtual ~CHMIni();
    QString getIni2String(
            const QString &name,
            const QString &group,
            const QVariant &defaultValue
            );
    int getIni2Dec(
            const QString &name,
            const QString &group,
            const QVariant &defaultValue
            );
    int getIni2Hex(
            const QString &name,
            const QString &group,
            const QVariant &defaultValue
            );

    void setIni(
            const QVariant &value,
                const QString &name,
                const QString &group
            );


private:
    QString m_fileName;
};

#endif // HMINI_H
