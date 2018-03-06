#ifndef TCPCLIENT_H
#define TCPCLIENT_H
#include <QTime>
#include <QFile>
#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QProgressBar>
#include <QTcpSocket>
#include <QHostAddress>
namespace Ui {
class TcpClient;
}

class TcpClient : public QDialog
{
    Q_OBJECT

public:
    explicit TcpClient(QWidget *parent = 0);
    ~TcpClient();
    void mySetLayout();
    void setFileName(QString fileName);
    void setHostAddress(QHostAddress address);
protected:
    void closeEvent(QCloseEvent *event);
private:
    Ui::TcpClient *ui;
    QLabel *label;
    QProgressBar *progressBar;
    QPushButton *btnCancel;
    QPushButton *btnClose;

    QTcpSocket *tcpClient;
    QHostAddress hostAddress;
    QString fileName;
    QFile *loadFile;
    qint64 totalBytes;
    qint64 bytesReceived;
    qint64 fileNameSize;
    qint16 tcpport;
    qint16 blockSize;
    QTime time;
    QByteArray inBlock;
private slots:
    void readMessage();
    void disPlayError(QAbstractSocket::SocketError socketError);
    void newConnect();
    void slotBtnCancel();
    void slotBtnClose();
};

#endif // TCPCLIENT_H
