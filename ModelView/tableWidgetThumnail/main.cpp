#include <QApplication>

#include "thumnailWidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ThumnailWidget w;
    w.show();

    return a.exec();
}
