/****************************************************************************
** Meta object code from reading C++ file 'serv.h'
**
** Created: Thu 22. May 16:23:45 2014
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../serv.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'serv.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_serv[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
       6,    5,    5,    5, 0x0a,
      18,    5,    5,    5, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_serv[] = {
    "serv\0\0myConnect()\0startRead()\0"
};

const QMetaObject serv::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_serv,
      qt_meta_data_serv, 0 }
};

const QMetaObject *serv::metaObject() const
{
    return &staticMetaObject;
}

void *serv::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_serv))
        return static_cast<void*>(const_cast< serv*>(this));
    return QObject::qt_metacast(_clname);
}

int serv::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: myConnect(); break;
        case 1: startRead(); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
