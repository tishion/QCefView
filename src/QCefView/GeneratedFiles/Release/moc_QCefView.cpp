/****************************************************************************
** Meta object code from reading C++ file 'QCefView.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "stdafx.h"
#include "../../inc/QCefView.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QCefView.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_QCefView_t {
    QByteArrayData data[23];
    char stringdata0[255];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QCefView_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QCefView_t qt_meta_stringdata_QCefView = {
    {
QT_MOC_LITERAL(0, 0, 8), // "QCefView"
QT_MOC_LITERAL(1, 9, 21), // "onLoadingStateChanged"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 9), // "isLoading"
QT_MOC_LITERAL(4, 42, 9), // "canGoBack"
QT_MOC_LITERAL(5, 52, 12), // "canGoForward"
QT_MOC_LITERAL(6, 65, 11), // "onLoadStart"
QT_MOC_LITERAL(7, 77, 9), // "onLoadEnd"
QT_MOC_LITERAL(8, 87, 14), // "httpStatusCode"
QT_MOC_LITERAL(9, 102, 11), // "onLoadError"
QT_MOC_LITERAL(10, 114, 9), // "errorCode"
QT_MOC_LITERAL(11, 124, 8), // "errorMsg"
QT_MOC_LITERAL(12, 133, 9), // "failedUrl"
QT_MOC_LITERAL(13, 143, 16), // "onQCefUrlRequest"
QT_MOC_LITERAL(14, 160, 3), // "url"
QT_MOC_LITERAL(15, 164, 18), // "onQCefQueryRequest"
QT_MOC_LITERAL(16, 183, 9), // "QCefQuery"
QT_MOC_LITERAL(17, 193, 5), // "query"
QT_MOC_LITERAL(18, 199, 20), // "onInvokeMethodNotify"
QT_MOC_LITERAL(19, 220, 9), // "browserId"
QT_MOC_LITERAL(20, 230, 7), // "frameId"
QT_MOC_LITERAL(21, 238, 6), // "method"
QT_MOC_LITERAL(22, 245, 9) // "arguments"

    },
    "QCefView\0onLoadingStateChanged\0\0"
    "isLoading\0canGoBack\0canGoForward\0"
    "onLoadStart\0onLoadEnd\0httpStatusCode\0"
    "onLoadError\0errorCode\0errorMsg\0failedUrl\0"
    "onQCefUrlRequest\0url\0onQCefQueryRequest\0"
    "QCefQuery\0query\0onInvokeMethodNotify\0"
    "browserId\0frameId\0method\0arguments"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QCefView[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    3,   49,    2, 0x09 /* Protected */,
       6,    0,   56,    2, 0x09 /* Protected */,
       7,    1,   57,    2, 0x09 /* Protected */,
       9,    3,   60,    2, 0x09 /* Protected */,
      13,    1,   67,    2, 0x09 /* Protected */,
      15,    1,   70,    2, 0x09 /* Protected */,
      18,    4,   73,    2, 0x09 /* Protected */,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool, QMetaType::Bool, QMetaType::Bool,    3,    4,    5,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, QMetaType::Int, QMetaType::QString, QMetaType::QString,   10,   11,   12,
    QMetaType::Void, QMetaType::QString,   14,
    QMetaType::Void, 0x80000000 | 16,   17,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::QString, QMetaType::QVariantList,   19,   20,   21,   22,

       0        // eod
};

void QCefView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QCefView *_t = static_cast<QCefView *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onLoadingStateChanged((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 1: _t->onLoadStart(); break;
        case 2: _t->onLoadEnd((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->onLoadError((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3]))); break;
        case 4: _t->onQCefUrlRequest((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->onQCefQueryRequest((*reinterpret_cast< const QCefQuery(*)>(_a[1]))); break;
        case 6: _t->onInvokeMethodNotify((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3])),(*reinterpret_cast< const QVariantList(*)>(_a[4]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 5:
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
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
