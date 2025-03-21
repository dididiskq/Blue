#-------------------------------------------------
#
# Project created by QtCreator 20201022
#
#-------------------------------------------------

#QT += core gui qml quick xml
QT +=  gui qml quick core bluetooth multimedia svg
#webchannel webengine
qtHaveModule(multimedia):
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TARGET = HmViewApp
TEMPLATE = app

CONFIG += resources_big
CONFIG += C++17
#CONFIG += console



win32:CONFIG(release, debug|release): LIBS += -L$$PWD/QZXing/lib/ -lQZXing3
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/QZXing/lib/ -lQZXingd3

INCLUDEPATH += $$PWD/QZXing/include
DEPENDPATH += $$PWD/QZXing/include

CONFIG += qzxing_qml
CONFIG += qzxing_multimedia
# include(QZXingSrc/QZXing.pri)

msvc {
    QMAKE_CFLAGS += /utf-8
    QMAKE_CXXFLAGS += /utf-8
}

HMUTILS_HOME = ../
include($$HMUTILS_HOME/HMUtils/HMUtils.pri)

OBJECTS_DIR = ./build/$$TARGET/obj
MOC_DIR	= ./build/$$TARGET/moc
RCC_DIR = ./build/$$TARGET/rcc
UI_DIR  = ./build/$$TARGET/ui
DESTDIR	= ../



SOURCES += \
    BmsController.cpp \
    chmres.cpp \
    hmmodule.cpp \
    hmmoduleini.cpp \
    hmmqttcommand.cpp \
    hmview.cpp \
    hmviewcommand.cpp \
    main.cpp

HEADERS += \
    BmsController.h \
    chmres.h \
    hmmodule.h \
    hmmoduleini.h \
    hmmqttcommand.h \
    hmview.h \
    hmviewcommand.h


DISTFILES += \
    ../../ini/HMSle.ini \
    ../../ini/config.json \
    ../../views/HMStmView.qml  \
    ../../views/HMTest.qml  \
    ../../views/InitView.qml \
    ../../views/component/CamerView.qml \
    ../../views/component/DControl.qml \
    ../../views/component/DMessage.qml \
    ../../views/component/DParam.qml \
    ../../views/component/DParam1.qml \
    ../../views/component/DParam2.qml \
    ../../views/component/DParam3.qml \
    ../../views/component/DParam4.qml \
    ../../views/component/DParam5.qml \
    ../../views/component/DParam6.qml \
    ../../views/component/DRealTime.qml \
    ../../views/component/DevicePage.qml \
    ../../views/component/HMInformation.qml  \
    ../../views/component/HMCNCulture.qml  \
    ../../views/component/MainPage.qml \
    ../../views/component/MinePage.qml \
    ../../views/component/STabButton.qml \
    ../../views/js/HMJs.qml  \
    HM.ico \
    logo.rc
RC_FILE += logo.rc

contains(ANDROID_TARGET_ARCH,armeabi-v7a) {
    ANDROID_EXTRA_LIBS = \
        $$PWD/../HMUtils/lib/libqmqtt.so
}


















