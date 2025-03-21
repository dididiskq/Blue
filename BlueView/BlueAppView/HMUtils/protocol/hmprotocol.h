#ifndef HMPROTOCOL_H
#define HMPROTOCOL_H

#include <QObject>
#include <QString>
#include <QVariantMap>
class CHMProtocal : public QObject
{
    Q_OBJECT
public:
    explicit CHMProtocal(QObject *parent = 0);
    virtual ~CHMProtocal();

    virtual QByteArray byte(const QVariant &v) = 0;
    virtual QVariantMap byte(const QVariant &v, int flag) = 0;

    virtual QVariantMap parse(const QByteArray& buf ) = 0;
    /**
     * @brief parse
     * @param buf 源数据
     * @param size 数据长度
     * @param result 0-保留数据 -1-移除size长度数据 >0解析成功返回事件并移除size长度数据
     */
    virtual QVariantMap parse(const QByteArray& buf, int& size, int& result) = 0;
    virtual QVariantMap getStatus();

protected:
    QVariantMap status;
};

#endif // HMPROTOCOL_H
