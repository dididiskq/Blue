/****************************************************************************
** Meta object code from reading C++ file 'ImageHandler.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../ImageHandler.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ImageHandler.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ImageHandler_t {
    const uint offsetsAndSize[18];
    char stringdata0[62];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_ImageHandler_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_ImageHandler_t qt_meta_stringdata_ImageHandler = {
    {
QT_MOC_LITERAL(0, 12), // "ImageHandler"
QT_MOC_LITERAL(13, 4), // "save"
QT_MOC_LITERAL(18, 0), // ""
QT_MOC_LITERAL(19, 8), // "imageObj"
QT_MOC_LITERAL(28, 4), // "path"
QT_MOC_LITERAL(33, 7), // "offsetX"
QT_MOC_LITERAL(41, 7), // "offsetY"
QT_MOC_LITERAL(49, 5), // "width"
QT_MOC_LITERAL(55, 6) // "height"

    },
    "ImageHandler\0save\0\0imageObj\0path\0"
    "offsetX\0offsetY\0width\0height"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ImageHandler[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    6,   44,    2, 0x0a,    1 /* Public */,
       1,    5,   57,    2, 0x2a,    8 /* Public | MethodCloned */,
       1,    4,   68,    2, 0x2a,   14 /* Public | MethodCloned */,
       1,    3,   77,    2, 0x2a,   19 /* Public | MethodCloned */,
       1,    2,   84,    2, 0x2a,   23 /* Public | MethodCloned */,

 // slots: parameters
    QMetaType::Void, QMetaType::QObjectStar, QMetaType::QString, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,    3,    4,    5,    6,    7,    8,
    QMetaType::Void, QMetaType::QObjectStar, QMetaType::QString, QMetaType::Int, QMetaType::Int, QMetaType::Int,    3,    4,    5,    6,    7,
    QMetaType::Void, QMetaType::QObjectStar, QMetaType::QString, QMetaType::Int, QMetaType::Int,    3,    4,    5,    6,
    QMetaType::Void, QMetaType::QObjectStar, QMetaType::QString, QMetaType::Int,    3,    4,    5,
    QMetaType::Void, QMetaType::QObjectStar, QMetaType::QString,    3,    4,

       0        // eod
};

void ImageHandler::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ImageHandler *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->save((*reinterpret_cast< QObject*(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const int(*)>(_a[3])),(*reinterpret_cast< const int(*)>(_a[4])),(*reinterpret_cast< const int(*)>(_a[5])),(*reinterpret_cast< const int(*)>(_a[6]))); break;
        case 1: _t->save((*reinterpret_cast< QObject*(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const int(*)>(_a[3])),(*reinterpret_cast< const int(*)>(_a[4])),(*reinterpret_cast< const int(*)>(_a[5]))); break;
        case 2: _t->save((*reinterpret_cast< QObject*(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const int(*)>(_a[3])),(*reinterpret_cast< const int(*)>(_a[4]))); break;
        case 3: _t->save((*reinterpret_cast< QObject*(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const int(*)>(_a[3]))); break;
        case 4: _t->save((*reinterpret_cast< QObject*(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObject ImageHandler::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_ImageHandler.offsetsAndSize,
    qt_meta_data_ImageHandler,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_ImageHandler_t
, QtPrivate::TypeAndForceComplete<ImageHandler, std::true_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QObject *, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<const int, std::false_type>, QtPrivate::TypeAndForceComplete<const int, std::false_type>, QtPrivate::TypeAndForceComplete<const int, std::false_type>, QtPrivate::TypeAndForceComplete<const int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QObject *, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<const int, std::false_type>, QtPrivate::TypeAndForceComplete<const int, std::false_type>, QtPrivate::TypeAndForceComplete<const int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QObject *, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<const int, std::false_type>, QtPrivate::TypeAndForceComplete<const int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QObject *, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<const int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QObject *, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>


>,
    nullptr
} };


const QMetaObject *ImageHandler::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ImageHandler::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ImageHandler.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int ImageHandler::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 5;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
