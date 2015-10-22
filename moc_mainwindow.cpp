/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created: Wed Oct 8 12:26:03 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      11,   25,   25,   25, 0x08,
      26,   25,   25,   25, 0x08,
      40,   25,   25,   25, 0x08,
      54,   76,   25,   25, 0x08,
      83,   76,   25,   25, 0x08,
     102,   76,  121,   25, 0x08,
     129,   25,   25,   25, 0x08,
     145,  175,   25,   25, 0x0a,
     186,   25,   25,   25, 0x0a,
     211,   25,   25,   25, 0x0a,
     229,   76,   25,   25, 0x0a,
     257,  280,   25,   25, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0setHostname()\0\0startParser()\0"
    "globalReset()\0baroListVals(QString)\0"
    "newVal\0outputTime(double)\0formatTime(double)\0"
    "QString\0setRefPosHere()\0"
    "computeBaroCorrection(double)\0newAirTemp\0"
    "computeInitialDistance()\0computeDistance()\0"
    "computeDistanceStr(QString)\0"
    "setPositionAlarm(bool)\0newState\0"
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->setHostname(); break;
        case 1: _t->startParser(); break;
        case 2: _t->globalReset(); break;
        case 3: _t->baroListVals((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->outputTime((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 5: { QString _r = _t->formatTime((*reinterpret_cast< double(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 6: _t->setRefPosHere(); break;
        case 7: _t->computeBaroCorrection((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 8: _t->computeInitialDistance(); break;
        case 9: _t->computeDistance(); break;
        case 10: _t->computeDistanceStr((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 11: _t->setPositionAlarm((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MainWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
