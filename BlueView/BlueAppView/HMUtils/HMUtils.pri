#QT += gui core  network sql qml quick xml websockets multimedia quickwidgets
QT +=  sql qml quick

greaterThan(QT_MAJOR_VERSION, 5): QT += widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QT += quickwidgets

INCLUDEPATH += $$HMUTILS_HOME



SOURCES += \
    $$PWD/common/hmregister.cpp \
    $$PWD/common/hmsendthread.cpp \
    $$PWD/common/hmthread.cpp \
    $$PWD/common/hmtestthread.cpp \
    $$PWD/common/hmviewcontext.cpp \
    $$PWD/common/hmlog.cpp \
    $$PWD/common/hmcommand.cpp \
    $$PWD/common/hmmodulebasics.cpp \
    $$PWD/common/hmsystem.cpp \
    $$PWD/common/hmcrc.cpp \
    $$PWD/device/hmdevice.cpp \
    $$PWD/hmutils.cpp   \
    $$PWD/protocol/BMSProtocol.cpp \
    $$PWD/protocol/hmprotocol.cpp


HEADERS += \
    $$PWD/common/hmregister.h \
    $$PWD/common/hmsendthread.h \
    $$PWD/common/hmthread.h \
    $$PWD/common/hmtestthread.h \
    $$PWD/common/hmviewcontext.h \
    $$PWD/common/hmlog.h \
    $$PWD/common/hmcommand.h \
    $$PWD/common/hmmodulebasics.h \
    $$PWD/common/hmsystem.h \
    $$PWD/common/hmcrc.h \
    $$PWD/device/hmdevice.h \
    $$PWD/common/hmconfig.h \
    $$PWD/hmutils.h \
    $$PWD/device/mqtt/qmqtt.h \
    $$PWD/protocol/BMSProtocol.h \
    $$PWD/protocol/hmprotocol.h


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../HMUtils/lib/ -lQMQTT
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../HMUtils/lib/ -lQMQTT
else:unix:!macx: LIBS += -L$$PWD/../HMUtils/lib/ -lQMQTT


INCLUDEPATH += $$PWD/../HMUtils
DEPENDPATH += $$PWD/../HMUtils



#INCLUDEPATH += D:/software/Opencv4.6.0/opencv/build/include

#Debug: {
#    LIBS += -lD:/software/Opencv4.6.0/opencv/build/x64/vc15/lib/opencv_world460d
#}

#Release: {
#    LIBS += -lD:/software/Opencv4.6.0/opencv/build/x64/vc15/lib/opencv_world460
#}

