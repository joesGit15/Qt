#include "mainwindow.h"
#include <QApplication>

#include "minmaxwidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

#if 1
    MinMaxWidget w;
    w.show();
#else
    MainWindow w;
    w.show();
#endif

    return a.exec();
}
