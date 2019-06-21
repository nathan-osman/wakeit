/****************************************************************************
** Meta object code from reading C++ file 'devicemodel.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../backend/src/devicemodel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'devicemodel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_DeviceModel_t {
    QByteArrayData data[19];
    char stringdata0[112];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DeviceModel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DeviceModel_t qt_meta_stringdata_DeviceModel = {
    {
QT_MOC_LITERAL(0, 0, 11), // "DeviceModel"
QT_MOC_LITERAL(1, 12, 5), // "error"
QT_MOC_LITERAL(2, 18, 0), // ""
QT_MOC_LITERAL(3, 19, 7), // "message"
QT_MOC_LITERAL(4, 27, 10), // "onFinished"
QT_MOC_LITERAL(5, 38, 4), // "load"
QT_MOC_LITERAL(6, 43, 4), // "save"
QT_MOC_LITERAL(7, 48, 3), // "add"
QT_MOC_LITERAL(8, 52, 4), // "data"
QT_MOC_LITERAL(9, 57, 6), // "update"
QT_MOC_LITERAL(10, 64, 3), // "idx"
QT_MOC_LITERAL(11, 68, 6), // "remove"
QT_MOC_LITERAL(12, 75, 5), // "index"
QT_MOC_LITERAL(13, 81, 4), // "wake"
QT_MOC_LITERAL(14, 86, 5), // "title"
QT_MOC_LITERAL(15, 92, 5), // "local"
QT_MOC_LITERAL(16, 98, 4), // "host"
QT_MOC_LITERAL(17, 103, 3), // "mac"
QT_MOC_LITERAL(18, 107, 4) // "port"

    },
    "DeviceModel\0error\0\0message\0onFinished\0"
    "load\0save\0add\0data\0update\0idx\0remove\0"
    "index\0wake\0title\0local\0host\0mac\0port"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DeviceModel[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   79,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   82,    2, 0x08 /* Private */,

 // methods: name, argc, parameters, tag, flags
       5,    0,   83,    2, 0x02 /* Public */,
       6,    0,   84,    2, 0x02 /* Public */,
       7,    1,   85,    2, 0x02 /* Public */,
       9,    2,   88,    2, 0x02 /* Public */,
      11,    1,   93,    2, 0x02 /* Public */,
      13,    1,   96,    2, 0x02 /* Public */,
      14,    1,   99,    2, 0x02 /* Public */,
      15,    1,  102,    2, 0x02 /* Public */,
      16,    1,  105,    2, 0x02 /* Public */,
      17,    1,  108,    2, 0x02 /* Public */,
      18,    1,  111,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,

 // slots: parameters
    QMetaType::Void,

 // methods: parameters
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::QJsonObject,    8,
    QMetaType::Void, QMetaType::Int, QMetaType::QJsonObject,   10,    8,
    QMetaType::Void, QMetaType::Int,   12,
    QMetaType::Void, QMetaType::Int,   12,
    QMetaType::QString, QMetaType::Int,   12,
    QMetaType::Bool, QMetaType::Int,   12,
    QMetaType::QString, QMetaType::Int,   12,
    QMetaType::QString, QMetaType::Int,   12,
    QMetaType::QString, QMetaType::Int,   12,

       0        // eod
};

void DeviceModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        DeviceModel *_t = static_cast<DeviceModel *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->error((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->onFinished(); break;
        case 2: { bool _r = _t->load();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 3: { bool _r = _t->save();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 4: _t->add((*reinterpret_cast< const QJsonObject(*)>(_a[1]))); break;
        case 5: _t->update((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QJsonObject(*)>(_a[2]))); break;
        case 6: _t->remove((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->wake((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: { QString _r = _t->title((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 9: { bool _r = _t->local((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 10: { QString _r = _t->host((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 11: { QString _r = _t->mac((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 12: { QString _r = _t->port((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (DeviceModel::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DeviceModel::error)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject DeviceModel::staticMetaObject = {
    { &QAbstractListModel::staticMetaObject, qt_meta_stringdata_DeviceModel.data,
      qt_meta_data_DeviceModel,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *DeviceModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DeviceModel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DeviceModel.stringdata0))
        return static_cast<void*>(this);
    return QAbstractListModel::qt_metacast(_clname);
}

int DeviceModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractListModel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void DeviceModel::error(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
