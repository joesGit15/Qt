#include "widget.h"
#include <QApplication>

#include <QtGui/QScreen>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Widget widget;

    QRect rect = QGuiApplication::primaryScreen()->availableGeometry();
    int w,h,x,y;
    w = rect.width() *0.8;
    h = rect.height()*0.8;

    widget.resize(w,h);

    x = rect.left() + (rect.width()-w )/2;
    y = rect.top()  + (rect.height()-h)/2;
    widget.move(x,y);

    widget.show();

    return a.exec();
}
