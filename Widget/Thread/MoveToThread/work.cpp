#include "work.h"


Worker::~Worker()
{
    printf("work finishde...\n");
}

void Worker::doWork(const QString &parameter)
{
    for(int i=0; i < 10; i++){
        QThread::msleep(10);
        printf("%p...%d\n",QThread::currentThread(),i);
    }
}

Controller::Controller()
{
    Worker *worker = new Worker;
    worker->moveToThread(&workerThread);
    connect(&workerThread, &QThread::finished, worker, &QObject::deleteLater);
    connect(this, &Controller::operate, worker, &Worker::doWork);
    connect(worker, &Worker::resultReady, this, &Controller::handleResults);
    workerThread.start();
}

Controller::~Controller()
{
    workerThread.quit();
    workerThread.wait();
    printf("Controller finished...\n");
}

void Controller::handleResults(const QString &)
{

}
