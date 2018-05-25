#include "sderrickloadcapacitymainwin.h"
#include <QApplication>
#include "salgo.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SDerrickLoadCapacityMainWin w;
    w.show();

    return a.exec();
}
