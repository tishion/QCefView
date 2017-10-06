/****************************************************************************
** Meta object code from reading C++ file 'CCefWindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "stdafx.h"
#include "../../CCefWindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CCefWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_CCefWindow_t {
    QByteArrayData data[23];
    char stringdata0[249];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CCefWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CCefWindow_t qt_meta_stringdata_CCefWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "CCefWindow"
QT_MOC_LITERAL(1, 11, 19), // "loadingStateChanged"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 9), // "isLoading"
QT_MOC_LITERAL(4, 42, 9), // "canGoBack"
QT_MOC_LITERAL(5, 52, 12), // "canGoForward"
QT_MOC_LITERAL(6, 65, 9), // "loadStart"
QT_MOC_LITERAL(7, 75, 7), // "loadEnd"
QT_MOC_LITERAL(8, 83, 14), // "httpStatusCode"
QT_MOC_LITERAL(9, 98, 9), // "loadError"
QT_MOC_LITERAL(10, 108, 9), // "errorCode"
QT_MOC_LITERAL(11, 118, 8), // "errorMsg"
QT_MOC_LITERAL(12, 127, 9), // "failedUrl"
QT_MOC_LITERAL(13, 137, 17), // "processUrlRequest"
QT_MOC_LITERAL(14, 155, 3), // "url"
QT_MOC_LITERAL(15, 159, 19), // "processQueryRequest"
QT_MOC_LITERAL(16, 179, 9), // "QCefQuery"
QT_MOC_LITERAL(17, 189, 5), // "query"
QT_MOC_LITERAL(18, 195, 18), // "invokeMethodNotify"
QT_MOC_LITERAL(19, 214, 9), // "browserId"
QT_MOC_LITERAL(20, 224, 7), // "frameId"
QT_MOC_LITERAL(21, 232, 6), // "method"
QT_MOC_LITERAL(22, 239, 9) // "arguments"

    },
    "CCefWindow\0loadingStateChanged\0\0"
    "isLoading\0canGoBack\0canGoForward\0"
    "loadStart\0loadEnd\0httpStatusCode\0"
    "loadError\0errorCode\0errorMsg\0failedUrl\0"
    "processUrlRequest\0url\0processQueryRequest\0"
    "QCefQuery\0query\0invokeMethodNotify\0"
    "browserId\0frameId\0method\0arguments"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CCefWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,   49,    2, 0x06 /* Public */,
       6,    0,   56,    2, 0x06 /* Public */,
       7,    1,   57,    2, 0x06 /* Public */,
       9,    3,   60,    2, 0x06 /* Public */,
      13,    1,   67,    2, 0x06 /* Public */,
      15,    1,   70,    2, 0x06 /* Public */,
      18,    4,   73,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool, QMetaType::Bool, QMetaType::Bool,    3,    4,    5,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, QMetaType::Int, QMetaType::QString, QMetaType::QString,   10,   11,   12,
    QMetaType::Void, QMetaType::QString,   14,
    QMetaType::Void, 0x80000000 | 16,   17,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::QString, QMetaType::QVariantList,   19,   20,   21,   22,

       0        // eod
};

void CCefWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CCefWindow *_t = static_cast<CCefWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->loadingStateChanged((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 1: _t->loadStart(); break;
        case 2: _t->loadEnd((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->loadError((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3]))); break;
        case 4: _t->processUrlRequest((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->processQueryRequest((*reinterpret_cast< const QCefQuery(*)>(_a[1]))); break;
        case 6: _t->invokeMethodNotify((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3])),(*reinterpret_cast< const QVariantList(*)>(_a[4]))); break;
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
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (CCefWindow::*_t)(bool , bool , bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CCefWindow::loadingStateChanged)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (CCefWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CCefWindow::loadStart)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (CCefWindow::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CCefWindow::loadEnd)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (CCefWindow::*_t)(int , const QString & , const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CCefWindow::loadError)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (CCefWindow::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CCefWindow::processUrlRequest)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (CCefWindow::*_t)(const QCefQuery & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CCefWindow::processQueryRequest)) {
                *result = 5;
                return;
            }
        }
        {
            typedef void (CCefWindow::*_t)(int , int , const QString , const QVariantList );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CCefWindow::invokeMethodNotify)) {
                *result = 6;
                return;
            }
        }
    }
}

const QMetaObject CCefWindow::staticMetaObject = {
    { &QWindow::staticMetaObject, qt_meta_stringdata_CCefWindow.data,
      qt_meta_data_CCefWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CCefWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CCefWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CCefWindow.stringdata0))
        return static_cast<void*>(const_cast< CCefWindow*>(this));
    return QWindow::qt_metacast(_clname);
}

int CCefWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWindow::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void CCefWindow::loadingStateChanged(bool _t1, bool _t2, bool _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CCefWindow::loadStart()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void CCefWindow::loadEnd(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void CCefWindow::loadError(int _t1, const QString & _t2, const QString & _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void CCefWindow::processUrlRequest(const QString & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void CCefWindow::processQueryRequest(const QCefQuery & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void CCefWindow::invokeMethodNotify(int _t1, int _t2, const QString _t3, const QVariantList _t4)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}
QT_END_MOC_NAMESPACE
