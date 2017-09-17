#include "mainwindow.h"
#include <QApplication>
#include <QtGui/QScreen>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow window;

    QRect rect = QGuiApplication::primaryScreen()->availableGeometry();

    int w,h,x,y;
    w = rect.width() *0.8;
    h = rect.height()*0.8;

    window.resize(w,h);

    x = rect.left() + (rect.width()-w )/2;
    y = rect.top()  + (rect.height()-h)/2;
    window.move(x,y);

    window.show();

    return a.exec();
}
