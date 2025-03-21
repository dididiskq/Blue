#ifndef HMCOM_H
#define HMCOM_H

#include <QObject>
#include <QDebug>
#include <QSerialPort>
#include "protocol/hmprotocol.h"
#include "hmdevice.h"
class CHMCom : public CHMDevice
{
	Q_OBJECT
public:
    /**
     * @brief CHMCom
     * @param ini 串口配置
     * @param name 串口名称
     * @param protocal 串口协议
     * @param parent
     */
    explicit CHMCom(const QVariantMap &ini, const QString & name="", CHMProtocal *protocal=0, QObject* parent = 0);
    virtual ~CHMCom();
    /**
     * @brief open
     * @return true-串口打开成功
     */
    bool open();
    bool close();
    CHMProtocal *getProtocal();
    /**
     * @brief write
     * @param op
     * @return 写入串口字节数量
     */
    int write(const QVariantMap &op);
    /**
     * @brief clearBuf
     * 清空串口缓存
     */
    void clearBuf();
    //线程处理函数
    virtual bool processOp();

public slots:
    /**
     * @brief readyReadSlot
     * 串口读写事件槽
     */
    void readyReadSlot();
    //实体发送函数
    void onSendOp(const QVariantMap &op);
signals:
    void sendMsg(QVariantMap &op, QVariant&);

private:
    QSerialPort selfPort;//串口对象
    QVariantMap selfIni;//串口配置文件
    CHMProtocal *selfProtocal;//串口协议
    QByteArray selfArray;//串口缓存
    QString selfName;//串口名字
};

#endif // HMCOM_H
