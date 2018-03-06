#include "tcpclient.h"
#include "ui_tcpclient.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>
TcpClient::TcpClient(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TcpClient)
{
    ui->setupUi(this);
    setWindowTitle(tr("接收端"));
    resize(350,180);
    mySetLayout();
    totalBytes = 0;
    bytesReceived = 0;
    fileNameSize = 0;
    tcpClient = new QTcpSocket(this);
    tcpport = 6666;
    connect(tcpClient,SIGNAL(readyRead()),this,SLOT(readMessage()));
    connect(tcpClient,SIGNAL(error(QAbstractSocket::SocketError)),
            this,SLOT(disPlayError(QAbstractSocket::SocketError)));
    connect(btnCancel,SIGNAL(clicked(bool)),this,SLOT(slotBtnCancel()));
    connect(btnClose,SIGNAL(clicked(bool)),this,SLOT(slotBtnClose()));
}

TcpClient::~TcpClient()
{
    delete ui;
}

void TcpClient::mySetLayout()
{
    label = new QLabel;
    QFont ft;
    ft.setBold(true);
    ft.setPointSize(12);
    label->setFont(ft);
    label->setAlignment(Qt::AlignHCenter);
    label->setText(tr("等待接收文件... ..."));
    progressBar = new QProgressBar;
    progressBar->setValue(0);
    btnCancel = new QPushButton(tr("取消"));
    btnClose = new QPushButton(tr("关闭"));
    QHBoxLayout *hblayout = new QHBoxLayout;
    hblayout->addWidget(btnCancel);
    hblayout->addWidget(btnClose);
    hblayout->setSpacing(20);
    QVBoxLayout *vblayout = new QVBoxLayout(this);
    vblayout->addWidget(label);
    vblayout->addWidget(progressBar);
    vblayout->addLayout(hblayout);
}

void TcpClient::setFileName(QString fileName)
{
    loadFile = new QFile(fileName);
}

void TcpClient::setHostAddress(QHostAddress address)
{
    hostAddress = address;
    newConnect();
}

void TcpClient::closeEvent(QCloseEvent *event)
{
    slotBtnClose();
}

void TcpClient::readMessage()
{
    QDataStream in(tcpClient);
    in.setVersion(QDataStream::Qt_5_0);
    float usetime = time.elapsed();
    if(bytesReceived <= sizeof(qint64)*2)
    {
        if( (tcpClient->bytesAvailable() >= sizeof(qint64)*2) && (0 == fileNameSize))
        {
            in>>totalBytes>>fileNameSize;
            bytesReceived += sizeof(qint64)*2;
        }
        if( (tcpClient->bytesAvailable() >= fileNameSize) && (0 != fileNameSize))
        {
            in>>fileName;
            bytesReceived += fileNameSize;
            if(!loadFile->open(QFile::WriteOnly))
            {
                QMessageBox::warning(this,tr("应用程序"),tr("无法读取文件%1;\n%2").arg(fileName).arg(loadFile->errorString()));
                return;
            }
            else
            {
                return;
            }
        }
        if( bytesReceived < totalBytes)
        {
            bytesReceived += tcpClient->bytesAvailable();
            inBlock = tcpClient->readAll();
            inBlock.resize(0);
        }

        progressBar->setMaximum(totalBytes);
        progressBar->setValue(bytesReceived);

        double speed = bytesReceived/usetime;
        label->setText(tr("已接收%1MB(%2MB/S)\n"
                          "共%3MB 已用时： %4秒\n"
                          "估计剩余%5秒。")
                       .arg(bytesReceived/(1024*1024))
                       .arg(speed*1000/(1024*1024),0,'f',2)
                       .arg(totalBytes/(1024*1024))
                       .arg(usetime/1000,0,'f',0)
                       .arg(totalBytes/speed/1000 - usetime/1000,0,'f',0));
        if(totalBytes == bytesReceived)
        {
            loadFile->close();
            tcpClient->close();
            label->setText(tr("接收文件%1完毕").arg(fileName));
        }
    }
}

void TcpClient::disPlayError(QAbstractSocket::SocketError socketError)
{
    switch(socketError)
    {
        case QAbstractSocket::RemoteHostClosedError:break;
        default : qDebug()<<tcpClient->errorString();
    }
}

void TcpClient::newConnect()
{
    blockSize = 0;
    tcpClient->abort();
    tcpClient->connectToHost(hostAddress,tcpport);
    time.start();
}

void TcpClient::slotBtnCancel()
{
    tcpClient->abort();
    if(loadFile->isOpen())
    {
        loadFile->close();
    }
}

void TcpClient::slotBtnClose()
{
    tcpClient->abort();
    if(loadFile->isOpen())
    {
        loadFile->close();
    }
    close();
}
