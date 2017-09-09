#include <QApplication>
#include "imageprocesswidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ImageProcessWidget w;
    w.show();

    return a.exec();
}
