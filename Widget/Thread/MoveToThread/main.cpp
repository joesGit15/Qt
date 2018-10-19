#include <QCoreApplication>
#include "work.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QString text;
    Controller controller;
#if 0
    {
        Controller controller1;
        controller1.operate(text);
        controller1.operate(text);//排队
        QThread::msleep(2000);
    }
#endif
    controller.operate(text);//线程排队
    controller.operate(text);//线程排队
    QThread::msleep(3000);
    controller.operate(text);
    QThread::msleep(3000);

    return 0;
    //return a.exec();
}
