#include <QGuiApplication>
#include "hmmodule.h"
#include "HMUtils/common/hmlog.h"
#include "HMUtils/hmutils.h"
#include <QZXing.h>
#include<QImage>

int main(int argc, char *argv[])
{
    //开始解码
    // QImage img("file.png");
    // if (img.isNull())
    // {
    //     qCritical() << "Error: Image file not loaded!";
    //     return -1;
    // }

    // // QImage converted = img.convertToFormat(QImage::Format_RGB32);
    // QZXing decoder;
    // //QR Code二维码
    // decoder.setDecoder(QZXing::DecoderFormat_QR_CODE);
    // //可选设置，赋值自文档demo
    // decoder.setSourceFilterType(QZXing::SourceFilter_ImageNormal);
    // decoder.setTryHarderBehaviour(QZXing::TryHarderBehaviour_ThoroughScanning |
    //                               QZXing::TryHarderBehaviour_Rotate);
    // QString info = decoder.decodeImage(img);
    // qDebug()<<info;

    // QZXing::registerTypes();

    QCoreApplication::setAttribute(Qt::AA_UseOpenGLES);

#if defined(Q_OS_LINUX)

#else
//    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QCoreApplication::setAttribute(Qt::AA_ShareOpenGLContexts );

    QGuiApplication a(argc, argv);  // 主线程
//    CHMModule module;
    std::unique_ptr<CHMModule> module(new CHMModule());
    if( !module->start())
    {
        return 1;
    }


    int ret = a.exec();
    module->stop();



    return ret;
}

/*
// 假设 ABS_PATH 已经定义
#define ABS_PATH "../"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // 创建日志对象
    HMLog *log = new HMLog(QString("%1log/example.log").arg(ABS_PATH));

    // 打开日志文件
    log->open(QString("%1log/example.log").arg(ABS_PATH), "Example Log: ", true, 1024 * 1024 * 100);

    // 检查日志文件是否已打开
    if (log->isOpen()) {
        qDebug() << "Log file opened successfully.";
    } else {
        qDebug() << "Failed to open log file.";
    }

    // 写入日志
    *log << "This is a test log message." << HMLog::endl;
    *log << "Another test log message with number: " << 12345 << HMLog::endl;
    *log << "Test with QByteArray: " << QByteArray("Hello, World!") << HMLog::endl;
    *log << "Test with QVariantMap: " << QVariantMap{{"key", "value"}} << HMLog::endl;
    *log << "Test with QVariantList: " << QVariantList{"item1", "item2"} << HMLog::endl;
    *log << "Test with QStringList: " << QStringList{"item1", "item2"} << HMLog::endl;

    // 关闭日志文件
    log->close();

    delete log;

    return a.exec();
}

*/
