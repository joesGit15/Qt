#ifndef WORK_H
#define WORK_H

#include <QObject>
#include <QThread>

class Worker : public QObject
{
    Q_OBJECT

    ~Worker();

public slots:
    void doWork(const QString &parameter);

signals:
    void resultReady(const QString &result);
};

class Controller : public QObject
{
    Q_OBJECT
    QThread workerThread;

public:
    Controller();
    ~Controller();

public slots:
    void handleResults(const QString &);

signals:
    void operate(const QString &);
};

#endif // WORK_H
