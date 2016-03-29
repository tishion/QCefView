/****************************************************************************
** Meta object code from reading C++ file 'QCefView.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../inc/QCefView.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QCefView.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_QCefView_t {
    QByteArrayData data[7];
    char stringdata0[76];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QCefView_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QCefView_t qt_meta_stringdata_QCefView = {
    {
QT_MOC_LITERAL(0, 0, 8), // "QCefView"
QT_MOC_LITERAL(1, 9, 21), // "processQCefUrlRequest"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 3), // "url"
QT_MOC_LITERAL(4, 36, 23), // "processQCefQueryRequest"
QT_MOC_LITERAL(5, 60, 9), // "QCefQuery"
QT_MOC_LITERAL(6, 70, 5) // "query"

    },
    "QCefView\0processQCefUrlRequest\0\0url\0"
    "processQCefQueryRequest\0QCefQuery\0"
    "query"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QCefView[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   24,    2, 0x09 /* Protected */,
       4,    1,   27,    2, 0x09 /* Protected */,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, 0x80000000 | 5,    6,

       0        // eod
};

void QCefView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QCefView *_t = static_cast<QCefView *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->processQCefUrlRequest((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->processQCefQueryRequest((*reinterpret_cast< QCefQuery(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QCefQuery >(); break;
            }
            break;
        }
    }
}

const QMetaObject QCefView::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_QCefView.data,
      qt_meta_data_QCefView,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *QCefView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QCefView::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_QCefView.stringdata0))
        return static_cast<void*>(const_cast< QCefView*>(this));
    return QWidget::qt_metacast(_clname);
}

int QCefView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
