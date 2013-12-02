/****************************************************************************
** Meta object code from reading C++ file 'qwave2.h'
**
** Created: Thu Sep 19 18:51:49 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "qwave2.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qwave2.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MyWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      10,    9,    9,    9, 0x0a,
      23,    9,    9,    9, 0x0a,
      39,    9,    9,    9, 0x0a,
      55,    9,    9,    9, 0x0a,
      62,    9,    9,    9, 0x0a,
      71,    9,    9,    9, 0x0a,
      85,    9,    9,    9, 0x0a,
     101,   92,    9,    9, 0x0a,
     142,    9,    9,    9, 0x0a,
     158,  156,    9,    9, 0x08,
     187,  184,    9,    9, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MyWidget[] = {
    "MyWidget\0\0addSndFile()\0removeSndFile()\0"
    "browseSndFile()\0play()\0repeat()\0"
    "pauseResume()\0stop()\0beg,dur,\0"
    "changeSelection(double,double,Waveform*)\0"
    "setSpeed(int)\0,\0setTime(Waveform*,double)\0"
    "id\0on_devicesComboBox_IndexChanged(QString)\0"
};

void MyWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MyWidget *_t = static_cast<MyWidget *>(_o);
        switch (_id) {
        case 0: _t->addSndFile(); break;
        case 1: _t->removeSndFile(); break;
        case 2: _t->browseSndFile(); break;
        case 3: _t->play(); break;
        case 4: _t->repeat(); break;
        case 5: _t->pauseResume(); break;
        case 6: _t->stop(); break;
        case 7: _t->changeSelection((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< Waveform*(*)>(_a[3]))); break;
        case 8: _t->setSpeed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->setTime((*reinterpret_cast< Waveform*(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 10: _t->on_devicesComboBox_IndexChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MyWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MyWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_MyWidget,
      qt_meta_data_MyWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MyWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MyWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MyWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MyWidget))
        return static_cast<void*>(const_cast< MyWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int MyWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
