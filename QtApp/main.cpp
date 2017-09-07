#include <QApplication>
#ifdef joe
#include "NetWork/CrawlImg/httpwindow.h"
#else
#include "mainwindow.h"
#endif

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
#ifdef joe
    HttpWindow w;
    w.show();
#else
    MainWindow w;
    w.show();
#endif
    return a.exec();
}
