#ifndef TCPSERVER_H
#define TCPSERVER_H
#include <QTime>
#include <QDialog>
#include <QLabel>
#include <QProgressBar>
#include <QPushButton>
#include <QTcpServer>
#include <QTcpSocket>
#include <QFile>

namespace Ui {
class TcpServer;
}

class TcpServer : public QDialog
{
    Q_OBJECT

public:
    explicit TcpServer(QWidget *parent = 0);
    ~TcpServer();
    void layoutTcpServer();//用于外观布局
    void initServer();
    void refused();
protected:
    void closeEvent(QCloseEvent *);
private:
    Ui::TcpServer *ui;
    QLabel *label;
    QProgressBar *progressBar;
    QPushButton *btnOpen;
    QPushButton *btnSend;
    QPushButton *btnClose;

    qint16 tcpport;
    QTcpServer *tcpServer;
    QTcpSocket *clientConnection;
    qint64 totalBytes;
    qint64 bytesWritten;
    qint64 bytesToWrite;
    qint64 payloadSize;
    QByteArray outBlock;
    QString fileName;
    QString theFileName;
    QFile *loadFile;
    QTime time;
private slots:
    void sendMessage();
    void updateClientProgress(qint64 numBytes);
    void btnOpenClick();
    void btnCloseClick();
    void btnSendClick();
signals:
    void sendFileName(QString theFileName);
};

#endif // TCPSERVER_H
