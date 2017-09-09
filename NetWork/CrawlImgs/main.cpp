#include <QApplication>
#include "httpwindow.h"

#include <QtGui/QScreen>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    HttpWindow widget;

    QRect rect = QGuiApplication::primaryScreen()->availableGeometry();
    int w,h,x,y;
    w = rect.width() *0.5;
    h = rect.height()*0.2;

    widget.resize(w,h);

    x = rect.left() + (rect.width()-w )/2;
    y = rect.top()  + (rect.height()-h)/2;
    widget.move(x,y);

    widget.show();

    return a.exec();
}
