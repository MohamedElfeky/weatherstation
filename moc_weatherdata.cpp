/****************************************************************************
** Meta object code from reading C++ file 'weatherdata.h'
**
** Created: Wed May 14 13:12:34 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "weatherdata.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'weatherdata.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_WeatherData[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      22,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      11,       // signalCount

 // signals: signature, parameters, type, tag, flags
      22,   13,   12,   12, 0x05,
      50,   43,   12,   12, 0x05,
      80,   73,   12,   12, 0x05,
      99,   43,   12,   12, 0x05,
     132,  125,   12,   12, 0x05,
     151,   43,   12,   12, 0x05,
     190,  177,   12,   12, 0x05,
     223,  210,   12,   12, 0x05,
     243,   13,   12,   12, 0x05,
     268,   13,   12,   12, 0x05,
     294,   13,   12,   12, 0x05,

 // slots: signature, parameters, type, tag, flags
     315,   13,   12,   12, 0x0a,
     335,  125,   12,   12, 0x0a,
     365,  357,   12,   12, 0x0a,
     387,   13,   12,   12, 0x0a,
     409,   12,   12,   12, 0x0a,
     420,   13,   12,   12, 0x0a,
     435,   13,   12,   12, 0x0a,
     456,   13,   12,   12, 0x0a,
     478,   13,   12,   12, 0x0a,
     502,   13,   12,   12, 0x0a,
     527,   13,   12,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_WeatherData[] = {
    "WeatherData\0\0newValue\0valueChanged(double)\0"
    "newStr\0stringChanged(QString)\0newMax\0"
    "maxChanged(double)\0stringMaxChanged(QString)\0"
    "newMin\0minChanged(double)\0"
    "stringMinChanged(QString)\0isIncreasing\0"
    "valIncreasing(bool)\0isDecreasing\0"
    "valDecreasing(bool)\0alarmLowChanged(QString)\0"
    "alarmHighChanged(QString)\0"
    "alarmTriggered(bool)\0changeValue(double)\0"
    "setMinAllowed(double)\0newMaxl\0"
    "setMaxAllowed(double)\0setDefaultVal(double)\0"
    "resetVal()\0setAlarm(bool)\0"
    "setAlarmLow(QString)\0setAlarmHigh(QString)\0"
    "setValueString(QString)\0"
    "setOffsetString(QString)\0"
    "setOffsetNegString(QString)\0"
};

void WeatherData::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        WeatherData *_t = static_cast<WeatherData *>(_o);
        switch (_id) {
        case 0: _t->valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 1: _t->stringChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->maxChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 3: _t->stringMaxChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->minChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 5: _t->stringMinChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: _t->valIncreasing((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->valDecreasing((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: _t->alarmLowChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 9: _t->alarmHighChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 10: _t->alarmTriggered((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 11: _t->changeValue((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 12: _t->setMinAllowed((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 13: _t->setMaxAllowed((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 14: _t->setDefaultVal((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 15: _t->resetVal(); break;
        case 16: _t->setAlarm((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 17: _t->setAlarmLow((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 18: _t->setAlarmHigh((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 19: _t->setValueString((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 20: _t->setOffsetString((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 21: _t->setOffsetNegString((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData WeatherData::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject WeatherData::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_WeatherData,
      qt_meta_data_WeatherData, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &WeatherData::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *WeatherData::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *WeatherData::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_WeatherData))
        return static_cast<void*>(const_cast< WeatherData*>(this));
    return QObject::qt_metacast(_clname);
}

int WeatherData::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 22)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 22;
    }
    return _id;
}

// SIGNAL 0
void WeatherData::valueChanged(double _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void WeatherData::stringChanged(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void WeatherData::maxChanged(double _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void WeatherData::stringMaxChanged(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void WeatherData::minChanged(double _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void WeatherData::stringMinChanged(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void WeatherData::valIncreasing(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void WeatherData::valDecreasing(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void WeatherData::alarmLowChanged(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void WeatherData::alarmHighChanged(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void WeatherData::alarmTriggered(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}
QT_END_MOC_NAMESPACE
