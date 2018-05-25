/****************************************************************************
** Meta object code from reading C++ file 'sderrickloadcapacitymainwin.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../sderrickloadcapacitymainwin.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sderrickloadcapacitymainwin.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SDerrickLoadCapacityMainWin_t {
    QByteArrayData data[18];
    char stringdata0[250];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SDerrickLoadCapacityMainWin_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SDerrickLoadCapacityMainWin_t qt_meta_stringdata_SDerrickLoadCapacityMainWin = {
    {
QT_MOC_LITERAL(0, 0, 27), // "SDerrickLoadCapacityMainWin"
QT_MOC_LITERAL(1, 28, 28), // "on_click_export_word_trigger"
QT_MOC_LITERAL(2, 57, 0), // ""
QT_MOC_LITERAL(3, 58, 30), // "on_actionOpenOriFile_triggered"
QT_MOC_LITERAL(4, 89, 23), // "on_actionExit_triggered"
QT_MOC_LITERAL(5, 113, 25), // "on_wComputeButton_clicked"
QT_MOC_LITERAL(6, 139, 29), // "getLinearExtrapolationGUIParm"
QT_MOC_LITERAL(7, 169, 22), // "getLoadCapacityGUIParm"
QT_MOC_LITERAL(8, 192, 7), // "alloc3d"
QT_MOC_LITERAL(9, 200, 8), // "float***"
QT_MOC_LITERAL(10, 209, 1), // "l"
QT_MOC_LITERAL(11, 211, 1), // "m"
QT_MOC_LITERAL(12, 213, 1), // "n"
QT_MOC_LITERAL(13, 215, 6), // "free3d"
QT_MOC_LITERAL(14, 222, 4), // "temp"
QT_MOC_LITERAL(15, 227, 7), // "alloc2d"
QT_MOC_LITERAL(16, 235, 7), // "float**"
QT_MOC_LITERAL(17, 243, 6) // "free2d"

    },
    "SDerrickLoadCapacityMainWin\0"
    "on_click_export_word_trigger\0\0"
    "on_actionOpenOriFile_triggered\0"
    "on_actionExit_triggered\0"
    "on_wComputeButton_clicked\0"
    "getLinearExtrapolationGUIParm\0"
    "getLoadCapacityGUIParm\0alloc3d\0float***\0"
    "l\0m\0n\0free3d\0temp\0alloc2d\0float**\0"
    "free2d"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SDerrickLoadCapacityMainWin[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x0a /* Public */,
       3,    0,   65,    2, 0x0a /* Public */,
       4,    0,   66,    2, 0x0a /* Public */,
       5,    0,   67,    2, 0x0a /* Public */,
       6,    0,   68,    2, 0x0a /* Public */,
       7,    0,   69,    2, 0x0a /* Public */,
       8,    3,   70,    2, 0x0a /* Public */,
      13,    3,   77,    2, 0x0a /* Public */,
      15,    2,   84,    2, 0x0a /* Public */,
      17,    2,   89,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Bool,
    QMetaType::Bool,
    0x80000000 | 9, QMetaType::Int, QMetaType::Int, QMetaType::Int,   10,   11,   12,
    QMetaType::Void, 0x80000000 | 9, QMetaType::Int, QMetaType::Int,   14,   10,   11,
    0x80000000 | 16, QMetaType::Int, QMetaType::Int,   11,   12,
    QMetaType::Void, 0x80000000 | 16, QMetaType::Int,   14,   11,

       0        // eod
};

void SDerrickLoadCapacityMainWin::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SDerrickLoadCapacityMainWin *_t = static_cast<SDerrickLoadCapacityMainWin *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_click_export_word_trigger(); break;
        case 1: _t->on_actionOpenOriFile_triggered(); break;
        case 2: _t->on_actionExit_triggered(); break;
        case 3: _t->on_wComputeButton_clicked(); break;
        case 4: { bool _r = _t->getLinearExtrapolationGUIParm();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 5: { bool _r = _t->getLoadCapacityGUIParm();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 6: { float*** _r = _t->alloc3d((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< float****>(_a[0]) = _r; }  break;
        case 7: _t->free3d((*reinterpret_cast< float***(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 8: { float** _r = _t->alloc2d((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< float***>(_a[0]) = _r; }  break;
        case 9: _t->free2d((*reinterpret_cast< float**(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObject SDerrickLoadCapacityMainWin::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_SDerrickLoadCapacityMainWin.data,
      qt_meta_data_SDerrickLoadCapacityMainWin,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *SDerrickLoadCapacityMainWin::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SDerrickLoadCapacityMainWin::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_SDerrickLoadCapacityMainWin.stringdata0))
        return static_cast<void*>(const_cast< SDerrickLoadCapacityMainWin*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int SDerrickLoadCapacityMainWin::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
