#include <QString>
#include <QVariant>
#include <QDir>
#include <QQuickView>
#include <QQuickItem>
#include "hmview.h"
#include "HMUtils/common/hmlog.h"
#include "HMUtils/hmutils.h"

CHMView::CHMView(QObject *parent) : QObject(parent)
{
    init();
}

CHMView::~CHMView()
{

}

void CHMView::setName(const QString &name)
{
    this->name = name;
}

QQuickView* CHMView::view(const QString &objectName)
{
    QQuickView *view = NULL;
    if (objectName.isEmpty()) // 默认返回第一个
    {
        Q_ASSERT(!views.isEmpty());
        view = views.first();
        return view;
    }
    else
    {
        if(!views.contains(objectName))
        {
            view = new QQuickView;
            views[objectName] = view;
            return view;
        }
    }

    view = views.value(objectName, NULL);

    if (view == NULL)
    {
        view = new QQuickView;
        views[objectName] = view;
    }

    return view;
}

HMViewContext *CHMView::context(const QString &viewName)
{
    HMViewContext* context = NULL;

    if (viewName.isEmpty())
    {
        context = contexts.first();
        return context;
    }

    context = contexts.value(viewName, NULL);

    if (context == NULL)
    {
        context = new HMViewContext;
        contexts[viewName] = context;

        initContext(context);
    }

    return context;
}

void CHMView::onViewInvoke(const QString &method, const QVariant &parameters, QVariant &result)
{
    Q_UNUSED(method);
    Q_UNUSED(parameters);
    Q_UNUSED(result);
    QVariantMap values = parameters.toMap();
    values["name"] = this->name;
    values["command"] = method;
    emit this->updateCommand(values, result);

}

bool CHMView::initContext(HMViewContext *context)
{
    Q_ASSERT(context != NULL);
    context->setFieldValue("test", "hello word!");

    return true;
}

void CHMView::init()
{

}

bool CHMView::initViews()
{
    int count = HMUtils::settingValue("count", "HMView", 0, "HMSle.ini").toInt();
    HMUtils::log() << "界面数量:" << count << HMLog::endl;;
    for (int i = 0; i < count; i++)
    {
        QString group = QString("HMView.%1").arg(i);
        QString name = HMUtils::settingValue("name", group, "", "HMSle.ini").toString();
        QString source = HMUtils::settingValue("source", group, "", "HMSle.ini").toString();

        int left = HMUtils::settingValue("left", group, "", "HMSle.ini").toInt();
        int top = HMUtils::settingValue("top", group, "", "HMSle.ini").toInt();
        int width = HMUtils::settingValue("width", group, "", "HMSle.ini").toInt();
        int height = HMUtils::settingValue("height", group, "", "HMSle.ini").toInt();
        if (name.isEmpty() || source.isEmpty())
        {
            HMUtils::log() << "name 为空， 资源为空" << HMLog::endl;
            return false;
        }

        QString qrc = "";
#if defined(Q_OS_WIN32)
        if(USERES)
            qrc = QString("qrc%1%2").arg(ABS_PATH).arg(source);
        else
            qrc = QString("%1%2").arg(ABS_PATH).arg(source);
#elif defined(Q_OS_LINUX)
        if(USERES)
            qrc = QString("qrc%1%2").arg(ABS_PATH).arg(source);
        else
            qrc = QString("%1%2").arg(ABS_PATH).arg(source);
#endif
        QString info = QString("group:%1, name:%2, source:%3")
                .arg(group).arg(name).arg(qrc);

        HMUtils::log() <<  info << HMLog::endl;

        QQuickView *v = view(name);
        HMViewContext *c = context(name);
        Q_ASSERT(v != NULL);
        Q_ASSERT(c != NULL);

        // 注册自定义图像提供者到 QML 引擎0227
//        QQmlEngine *engine = v->engine();
//        if (engine) {
//            // 添加提供者，providerId 为 "qrcode"
//            engine->addImageProvider("qrcode", new QRCodeImageProvider());
//        }

        connect(c, SIGNAL(viewInvoke(QString,QVariant,QVariant&)), SLOT(onViewInvoke(QString,QVariant,QVariant&)));
        v->setResizeMode(QQuickView::SizeRootObjectToView);
        v->rootContext()->setContextProperty(name+"Context", c);

        v->setSource(QUrl(qrc));
        v->setObjectName(name);
#define QT_DEBUG
//        v->setFlags(Qt::FramelessWindowHint|Qt::Window);
#ifndef QT_DEBUG

#endif

        v->setGeometry(left,top,width,height);
        v->show();
    }

    return true;
}



