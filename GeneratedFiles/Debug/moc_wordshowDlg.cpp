/****************************************************************************
** Meta object code from reading C++ file 'wordshowDlg.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../wordshowDlg.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'wordshowDlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_wordshowDlg_t {
    QByteArrayData data[11];
    char stringdata0[155];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_wordshowDlg_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_wordshowDlg_t qt_meta_stringdata_wordshowDlg = {
    {
QT_MOC_LITERAL(0, 0, 11), // "wordshowDlg"
QT_MOC_LITERAL(1, 12, 22), // "on_click_pushButton_up"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 24), // "on_click_pushButton_next"
QT_MOC_LITERAL(4, 61, 25), // "on_click_pushButton_print"
QT_MOC_LITERAL(5, 87, 9), // "showEvent"
QT_MOC_LITERAL(6, 97, 11), // "QShowEvent*"
QT_MOC_LITERAL(7, 109, 11), // "resizeEvent"
QT_MOC_LITERAL(8, 121, 13), // "QResizeEvent*"
QT_MOC_LITERAL(9, 135, 11), // "eventFilter"
QT_MOC_LITERAL(10, 147, 7) // "QEvent*"

    },
    "wordshowDlg\0on_click_pushButton_up\0\0"
    "on_click_pushButton_next\0"
    "on_click_pushButton_print\0showEvent\0"
    "QShowEvent*\0resizeEvent\0QResizeEvent*\0"
    "eventFilter\0QEvent*"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_wordshowDlg[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x0a /* Public */,
       3,    0,   45,    2, 0x0a /* Public */,
       4,    0,   46,    2, 0x0a /* Public */,
       5,    1,   47,    2, 0x0a /* Public */,
       7,    1,   50,    2, 0x0a /* Public */,
       9,    2,   53,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6,    2,
    QMetaType::Void, 0x80000000 | 8,    2,
    QMetaType::Bool, QMetaType::QObjectStar, 0x80000000 | 10,    2,    2,

       0        // eod
};

void wordshowDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        wordshowDlg *_t = static_cast<wordshowDlg *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_click_pushButton_up(); break;
        case 1: _t->on_click_pushButton_next(); break;
        case 2: _t->on_click_pushButton_print(); break;
        case 3: _t->showEvent((*reinterpret_cast< QShowEvent*(*)>(_a[1]))); break;
        case 4: _t->resizeEvent((*reinterpret_cast< QResizeEvent*(*)>(_a[1]))); break;
        case 5: { bool _r = _t->eventFilter((*reinterpret_cast< QObject*(*)>(_a[1])),(*reinterpret_cast< QEvent*(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObject wordshowDlg::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_wordshowDlg.data,
      qt_meta_data_wordshowDlg,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *wordshowDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *wordshowDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_wordshowDlg.stringdata0))
        return static_cast<void*>(const_cast< wordshowDlg*>(this));
    return QDialog::qt_metacast(_clname);
}

int wordshowDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
