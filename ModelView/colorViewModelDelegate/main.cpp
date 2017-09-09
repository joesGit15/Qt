#include <QApplication>
#include "colorlistviewwidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ColorListViewWidget w;
    w.show();

    return a.exec();
}
