#include "tcpserver.h"
#include "ui_tcpserver.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QFileDialog>
TcpServer::TcpServer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TcpServer)
{
    ui->setupUi(this);
    setWindowTitle(tr("发送端"));
    setFixedSize(350,180);
    layoutTcpServer();

    tcpport = 6666;
    tcpServer = new QTcpServer(this);
    connect(tcpServer,SIGNAL(newConnection()),this,SLOT(sendMessage()));
    connect(btnOpen,SIGNAL(clicked(bool)),this,SLOT(btnOpenClick()));
    connect(btnClose,SIGNAL(clicked(bool)),this,SLOT(btnCloseClick()));
    connect(btnSend,SIGNAL(clicked(bool)),this,SLOT(btnSendClick()));

    initServer();
}

TcpServer::~TcpServer()
{
    delete ui;
}

void TcpServer::layoutTcpServer()
{
    label = new QLabel;
    QFont ft;
    ft.setBold(true);
    ft.setPointSize(12);
    label->setFont(ft);
    label->setAlignment(Qt::AlignHCenter);
    label->setText(tr("请选择要发送的文件!"));
    progressBar = new QProgressBar;
    progressBar->setValue(0);
    btnOpen = new QPushButton(tr("打开"));
    btnSend = new QPushButton(tr("发送"));
    btnClose = new QPushButton(tr("关闭"));
    //btnClose->setEnabled(false);
    btnSend->setEnabled(false);

    QHBoxLayout *hblayout = new QHBoxLayout;
    hblayout->addWidget(btnOpen);
    hblayout->addWidget(btnSend);
    hblayout->addWidget(btnClose);

    QVBoxLayout *vblayout = new QVBoxLayout(this);
    vblayout->addWidget(label);
    vblayout->addWidget(progressBar);
    vblayout->addLayout(hblayout);
    setLayout(vblayout);
}

void TcpServer::initServer()
{
    payloadSize = 64 * 1024;
    totalBytes = 0;
    bytesWritten = 0;
    bytesToWrite = 0;
    tcpServer->close();
}

void TcpServer::refused()
{
    tcpServer->close();
    label->setText(tr("对方决绝接收!!!"));
}

void TcpServer::closeEvent(QCloseEvent *)
{
    btnCloseClick();
}

void TcpServer::sendMessage()
{
    btnSend->setEnabled(false);
    clientConnection = tcpServer->nextPendingConnection();
    connect(clientConnection,SIGNAL(bytesWritten(qint64)),this,SLOT(updateClientProgress(qint64)));
    label->setText(tr("开始传送文件%1").arg(theFileName));
    loadFile = new QFile(fileName);
    if(!loadFile->open(QFile::ReadOnly))
    {
        QMessageBox::warning(this,tr("应用程序"),tr("无法读取文件%1:\n%2").arg(fileName).arg(loadFile->errorString()));
        return;
    }
    totalBytes = loadFile->size();
    QDataStream sendout(&outBlock,QIODevice::WriteOnly);
    sendout.setVersion(QDataStream::Qt_5_0);
    time.start();
    QString currentFile = fileName.right(fileName.size()-fileName.lastIndexOf('/')-1);
    sendout<<qint64(0)<<qint64(0)<<currentFile;
    totalBytes += outBlock.size();
    sendout.device()->seek(0);
    sendout<<totalBytes<<qint64(outBlock.size()-sizeof(qint64)*2);
    bytesToWrite = totalBytes - clientConnection->write(outBlock);
    outBlock.resize(0);
}

void TcpServer::updateClientProgress(qint64 numBytes)
{
    qApp->processEvents();
    bytesWritten += (int)numBytes;
    if(bytesToWrite > 0)
    {
        outBlock = loadFile->read(qMin(bytesToWrite,payloadSize));
        bytesToWrite -= (int)clientConnection->write(outBlock);
        outBlock.resize(0);
    }
    else
    {
        loadFile->close();
    }

    progressBar->setMinimum(bytesWritten);
    progressBar->setMaximum(totalBytes);

    float useTime = time.elapsed();
    double speed = bytesWritten / useTime;
    label->setText(tr("已经发送%1MB(%2MB/s)\n共%3MB，已用时%4秒\n估计剩余时间：%5秒")
                   .arg(bytesWritten/(1024*1024))
                   .arg(speed*1000/(1024*1024),0,'f',2)
                   .arg(totalBytes/(1024*1024))
                   .arg(useTime/1000,0,'f',0)
                   .arg(totalBytes/speed/1000 - useTime/1000,0,'f',0));
    if(bytesWritten == totalBytes)
    {
        loadFile->close();
        tcpServer->close();
        label->setText(tr("传送文件%1成功!").arg(theFileName));
    }
}

void TcpServer::btnOpenClick()
{
    fileName = QFileDialog::getOpenFileName(this,tr("选择文件"));
    if(!fileName.isEmpty())
    {
        theFileName = fileName.right(fileName.size() - fileName.lastIndexOf('/')-1);
        label->setText(tr("要传送的文件为%1").arg(theFileName));
        btnOpen->setEnabled(false);
        btnSend->setEnabled(true);
    }
}

void TcpServer::btnCloseClick()
{
    if(tcpServer->isListening())
    {
        tcpServer->close();
        if(loadFile->isOpen())
        {
            loadFile->close();
        }
        clientConnection->close();
    }
    close();
}

void TcpServer::btnSendClick()
{
    if(!tcpServer->listen(QHostAddress::Any,tcpport))
    {
        qDebug()<<tcpServer->errorString();
        close();
        return;
    }
    label->setText(tr("等待对方接收..."));
    emit sendFileName(theFileName);
}
