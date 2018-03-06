#include "widget.h"
#include "tcpserver.h"
#include "tcpclient.h"
#include "ui_widget.h"
#include <QColorDialog>
#include <QStringList>
#include <QProcess>
#include <QMessageBox>
#include <QHostInfo>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QScrollBar>
#include <QDateTime>
#include <QNetworkInterface>
#include <QFileDialog>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    resize(850,450);
    setWindowIcon(QIcon(":images/images/Q.ico"));
    setWindowTitle(tr("局域网聊天工具"));
    setMyLayout();//布局设置
    udpSocket = new QUdpSocket(this);
    port = 45454;
    udpSocket->bind(port,QUdpSocket::ShareAddress|QUdpSocket::ReuseAddressHint);
    connect(udpSocket,SIGNAL(readyRead()),this,SLOT(processPendingDatagrams()));
    sendMessage(NewParticipaint);
    connect(btnSendMessage,SIGNAL(clicked(bool)),this,SLOT(slotSendMessage()));
    connect(btnExit,SIGNAL(clicked(bool)),this,SLOT(slotbtnExit()));

    server = new TcpServer(this);
    connect(server,SIGNAL(sendFileName(QString)),this,SLOT(getFileName(QString)));

    connect(toolbtnsend,SIGNAL(clicked(bool)),this,SLOT(slotToolbtnSendClick()));
    connect(fontComboBox,SIGNAL(currentFontChanged(QFont)),this,SLOT(slotFontComBoxCurrentFontChange(QFont)));
    connect(combox,SIGNAL(currentIndexChanged(QString)),this,SLOT(slotComBoxCurrentIndexChanged(QString)));
    connect(toolbtnbold,SIGNAL(clicked(bool)),this,SLOT(slotToolBtnBoldClick(bool)));
    connect(toolbtnitalic,SIGNAL(clicked(bool)),this,SLOT(slotToolBtnItalicClick(bool)));
    connect(toolbtnunderline,SIGNAL(clicked(bool)),this,SLOT(slotToolBtnUnderlineClick(bool)));
    connect(toolbtncolor,SIGNAL(clicked(bool)),this,SLOT(slotToolBtnColorClick()));
    connect(toolbtnsave,SIGNAL(clicked(bool)),this,SLOT(slotToolBtnSaveClick()));
    connect(toolbtnclear,SIGNAL(clicked(bool)),this,SLOT(slotToolBtnClearClick()));
    connect(textEdit,SIGNAL(currentCharFormatChanged(QTextCharFormat)),this,SLOT(slotCurrentFormatChanged(QTextCharFormat)));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::newParticipaint(QString userName, QString localHostName, QString ipAddress)
{
    bool isEmpty = tableWidget->findItems(localHostName,Qt::MatchExactly).isEmpty();
    if(isEmpty)
    {
        QTableWidgetItem *user = new QTableWidgetItem(userName);
        QTableWidgetItem *host = new QTableWidgetItem(localHostName);
        QTableWidgetItem *ip = new QTableWidgetItem(ipAddress);

        tableWidget->insertRow(0);
        tableWidget->setItem(0,0,user);
        tableWidget->setItem(0,1,host);
        tableWidget->setItem(0,2,ip);

        textBrowser->setTextColor(Qt::gray);
        textBrowser->setCurrentFont(QFont("Times New Roman",10));
        textBrowser->append(tr("%1 上线!").arg(userName));
        labelUserNum->setText(tr("在线人数：%1").arg(tableWidget->rowCount()));
        sendMessage(NewParticipaint);
    }
}

void Widget::participantLeft(QString userName, QString localHostName, QString time)
{
    int rowNum = tableWidget->findItems(localHostName,Qt::MatchExactly).first()->row();
    tableWidget->removeRow(rowNum);
    textBrowser->setTextColor(Qt::gray);
    textBrowser->setCurrentFont(QFont("Times New Roman",10));
    textBrowser->append(tr("%1 于 %2 下线!").arg(userName).arg(time));
    labelUserNum->setText(tr("在线人数：%1").arg(tableWidget->rowCount()));
}

void Widget::sendMessage(MessageType type, QString serverAddress)
{
    QByteArray data;
    QDataStream out(&data,QIODevice::WriteOnly);
    QString localHostName = QHostInfo::localHostName();
    QString address = getIP();
    out << type << getUserName() << localHostName;

    switch(type)
    {
    case Message:
        if(textEdit->toPlainText() == "")
        {
            QMessageBox box(QMessageBox::Warning,tr("警告"),tr("发送内容不能为空"),QMessageBox::Ok);
            box.setWindowIcon(QIcon(":images/images/Q.ico"));
            box.exec();
            return;
        }
        out << address <<getMessage();
        textBrowser->verticalScrollBar()->setValue(textBrowser->verticalScrollBar()->maximum());
        break;
    case NewParticipaint:
        out << address;
        break;
    case ParticipantLeft:
        break;
    case FileName:
    {
        int row = tableWidget->currentRow();
        QString clicentAddress = tableWidget->item(row,2)->text();
        out << address << clicentAddress << fileName;
        break;
    }
    case Refuse:
        out << serverAddress;
        break;
    }
    udpSocket->writeDatagram(data,data.length(),QHostAddress::Broadcast,port);
}

void Widget::hasPendingFile(QString userName, QString serverAddress, QString clicentAddress, QString fileName)
{
    QString ipAddress = getIP();
    if(ipAddress == clicentAddress)
    {
        QMessageBox::StandardButton btn = QMessageBox::information(this,
                                                                   tr("接收文件"),tr("来自%1(%2)的文件：%3，是否接收?")
                                                                   .arg(userName)
                                                                   .arg(serverAddress)
                                                                   .arg(fileName),QMessageBox::Ok,QMessageBox::No);
        if( QMessageBox::Ok == btn)
        {
            QString name = QFileDialog::getSaveFileName(0,tr("保存文件"),fileName);
            if(!name.isEmpty())
            {
                TcpClient *client = new TcpClient(this);
                client->setFileName(name);
                client->setHostAddress(QHostAddress(serverAddress));
                client->show();
            }
            else
            {
                sendMessage(Refuse,serverAddress);
            }
        }
    }
}

bool Widget::saveFile(const QString &fileName)
{
    QFile file(fileName);
    if(!file.open(QFile::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(this,tr("保存文件"),tr("无法保存文件%1:\n%2").arg(fileName).arg(file.errorString()));
        return false;
    }
    QTextStream out(&file);
    out<<textBrowser->toPlainText();
    return true;
}

void Widget::closeEvent(QCloseEvent *event)
{
    sendMessage(ParticipantLeft);
    QWidget::closeEvent(event);
}

QString Widget::getIP()
{
    QList<QHostAddress> list = QNetworkInterface::allAddresses();
    foreach(QHostAddress address,list)
    {
        if(QAbstractSocket::IPv4Protocol == address.protocol())
        {
            return address.toString();
        }
    }
    return 0;
}

QString Widget::getUserName()
{
    QStringList envVariables;
    envVariables << "USERNAME.*"<<"USER.*"<<"USERDOMAIN.*"<<"HOSTNAME.*"<<"DOMAINNAME.*";
    QStringList environment = QProcess::systemEnvironment();
    foreach(QString string,envVariables)
    {
        int index = environment.indexOf(QRegExp(string));
        if(index != -1)
        {
            QString strtemp = environment.at(index);//为什么这2句不能合并呢？
            QStringList stringList = strtemp.split('=');
            if(stringList.size() == 2)
            {
                return stringList.at(1);
                break;
            }
        }
    }
    return "unknown";
}

QString Widget::getMessage()
{
    QString msg = textEdit->toHtml();
    textEdit->clear();
    textEdit->setFocus();
    return msg;
}

void Widget::setMyLayout()
{
    QVBoxLayout *vboxLayout_talk = new QVBoxLayout;//聊天框布局

    textBrowser = new QTextBrowser(this);
    vboxLayout_talk->addWidget(textBrowser);//add textBrowser

    fontComboBox = new QFontComboBox(this);
    combox = new QComboBox(this);
    QStringList fontSize;
    for(int i=9;i<30;++i)
    {
        fontSize.append(QString::number(i));
    }
    combox->addItems(fontSize);
    combox->setCurrentIndex(3);

    QHBoxLayout * hboxLayout_toolbtn = new QHBoxLayout;//start_hboxLayout

    setAllToolbtn();//自定义
    hboxLayout_toolbtn->addWidget(fontComboBox);
    hboxLayout_toolbtn->addWidget(combox);

    hboxLayout_toolbtn->addWidget(toolbtnbold);
    hboxLayout_toolbtn->addWidget(toolbtnitalic);
    hboxLayout_toolbtn->addWidget(toolbtnunderline);
    hboxLayout_toolbtn->addWidget(toolbtncolor);
    hboxLayout_toolbtn->addWidget(toolbtnsend);
    hboxLayout_toolbtn->addWidget(toolbtnsave);
    hboxLayout_toolbtn->addWidget(toolbtnclear);

    vboxLayout_talk->addLayout(hboxLayout_toolbtn);//add hboxLayout_toolbtn
    textEdit = new QTextEdit(this);
    vboxLayout_talk->addWidget(textEdit);//add textEdit

    tableWidget = new QTableWidget(this);
    setTableWidget();//自定义
    QHBoxLayout *hboxLaytablewidget = new QHBoxLayout();//tableWidget布局
    hboxLaytablewidget->addLayout(vboxLayout_talk);
    hboxLaytablewidget->addWidget(tableWidget);

    btnSendMessage = new QPushButton(tr("发送"));

    labelUserNum = new QLabel(tr("在线用户:%1人").arg(0));
    btnExit = new QPushButton(tr("退出"));
    QHBoxLayout *layout_status = new QHBoxLayout;
    layout_status->setSpacing(120);
    layout_status->addWidget(btnSendMessage);
    layout_status->addWidget(labelUserNum);
    layout_status->addWidget(btnExit);

    QVBoxLayout *layout_out = new QVBoxLayout(this);
    layout_out->addLayout(hboxLaytablewidget);
    layout_out->addLayout(layout_status);
    setLayout(layout_out);
}

void Widget::setAllToolbtn()
{
    toolbtnbold = new QToolButton(this);
    toolbtnclear = new QToolButton(this);
    toolbtncolor = new QToolButton(this);
    toolbtnitalic = new QToolButton(this);
    toolbtnsave = new QToolButton(this);
    toolbtnsend = new QToolButton(this);
    toolbtnunderline = new QToolButton(this);
    setToolBtn(toolbtnbold);//自定义
    toolbtnbold->setIcon(QIcon(":/images/images/bold.png"));
    toolbtnbold->setToolTip(tr("加粗"));
    toolbtnbold->setCheckable(true);
    setToolBtn(toolbtnclear);
    toolbtnclear->setIcon(QIcon(":/images/images/clear.png"));
    toolbtnclear->setToolTip(tr("清空聊天记录"));
    setToolBtn(toolbtncolor);
    toolbtncolor->setIcon(QIcon(":/images/images/color.png"));
    toolbtncolor->setToolTip(tr("设置字体颜色"));
    setToolBtn(toolbtnitalic);
    toolbtnitalic->setIcon(QIcon(":/images/images/italic.png"));
    toolbtnitalic->setToolTip(tr("倾斜"));
    toolbtnitalic->setCheckable(true);
    setToolBtn(toolbtnsave);
    toolbtnsave->setIcon(QIcon(":/images/images/save.png"));
    toolbtnsave->setToolTip(tr("保存聊天记录"));
    setToolBtn(toolbtnsend);
    toolbtnsend->setIcon(QIcon(":/images/images/send.png"));
    toolbtnsend->setToolTip(tr("传输文件"));
    setToolBtn(toolbtnunderline);
    toolbtnunderline->setIcon(QIcon(":/images/images/under.png"));
    toolbtnunderline->setToolTip(tr("下划线"));
    toolbtnunderline->setCheckable(true);

}

void Widget::setTableWidget()
{
    tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableWidget->setShowGrid(false);
    tableWidget->insertColumn(0);
    tableWidget->insertColumn(1);
    tableWidget->insertColumn(2);
    tableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem(tr("用户名")));
    tableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem(tr("主机名")));
    tableWidget->setHorizontalHeaderItem(2, new QTableWidgetItem(tr("IP")));
}

void Widget::processPendingDatagrams()
{
    while(udpSocket->hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(udpSocket->pendingDatagramSize());
        udpSocket->readDatagram(datagram.data(),datagram.size());
        QDataStream in(&datagram,QIODevice::ReadOnly);
        int messageType;
        in >> messageType;
        QString userName,localHostName,ipAddress,message;
        QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
        switch(messageType)
        {
        case Message:
            in >> userName >> localHostName >> ipAddress >>message;
            textBrowser->setTextColor(Qt::blue);
            textBrowser->setCurrentFont(QFont("Times New Roman",12));
            textBrowser->append("["+userName+"]"+time);
            textBrowser->append(message);
            break;
        case NewParticipaint:
            in >>userName >>localHostName >>ipAddress;
            newParticipaint(userName,localHostName,ipAddress);
            break;
        case ParticipantLeft:
            in >> userName >> localHostName;
            participantLeft(userName,localHostName,time);
            break;
        case FileName:
        {
            in >> userName >> localHostName >> ipAddress;
            QString clientAddress,fileName;//fileName是不是重复定义
            in >> clientAddress >> fileName;
            hasPendingFile(userName,ipAddress,clientAddress,fileName);
            break;
        }
        case Refuse:
        {    in >> userName >> localHostName;
            QString serverAddress;
            in >> serverAddress;
            QString ipAddress = getIP();//ipAddress重复定义
            if(ipAddress == serverAddress)
            {
                server->refused();
            }
            break;
        }
        }
    }
}

void Widget::slotSendMessage()
{
    sendMessage(Message);
}

void Widget::getFileName(QString name)
{
    fileName = name;
    sendMessage(FileName);//FileName 枚举变量
}

void Widget::slotToolbtnSendClick()
{
    if(tableWidget->selectedItems().isEmpty())
    {
        QMessageBox box(QMessageBox::Warning,tr("选择用户"),tr("请先从用户列表选择要传送的用户!"));
        box.setWindowIcon(QIcon(":images/images/Q.ico"));
        box.exec();
        return;
    }
    server->show();
    server->initServer();
}

void Widget::slotFontComBoxCurrentFontChange(QFont f)
{
    textEdit->setFont(f);
    textEdit->setFocus();
}

void Widget::slotComBoxCurrentIndexChanged(QString size)
{
    textEdit->setFontPointSize(size.toDouble());
    textEdit->setFocus();
}

void Widget::slotToolBtnBoldClick(bool checked)
{
    if(checked)
    {
        textEdit->setFontWeight(QFont::Bold);
    }
    else
    {
        textEdit->setFontWeight(QFont::Normal);
    }
    textEdit->setFocus();
}

void Widget::slotToolBtnItalicClick(bool checked)
{
    textEdit->setFontItalic(checked);
    textEdit->setFocus();
}

void Widget::slotToolBtnUnderlineClick(bool checked)
{
    textEdit->setFontUnderline(checked);
    textEdit->setFocus();
}

void Widget::slotToolBtnColorClick()
{
    color = QColorDialog::getColor(color,this,tr("颜色选择"));
    if(color.isValid())
    {
        textEdit->setTextColor(color);
        textEdit->setFocus();
    }
}

void Widget::slotCurrentFormatChanged(const QTextCharFormat &format)
{
    fontComboBox->setCurrentFont(format.font());
    if(format.fontPointSize() < 9)
    {
        combox->setCurrentIndex(3);
    }
    else
    {
        combox->setCurrentIndex(combox->findText(QString::number(format.fontPointSize())));
    }
    toolbtnbold->setChecked(format.font().bold());
    toolbtnitalic->setChecked(format.font().italic());
    toolbtnunderline->setChecked(format.font().underline());
    color = format.foreground().color();
}

void Widget::slotToolBtnSaveClick()
{
    if(textBrowser->document()->isEmpty())
    {
        QMessageBox box(QMessageBox::Warning,tr("警告"),tr("聊天记录为空，无法保存!"));
        box.setWindowIcon(QIcon(":images/images/Q.ico"));
        box.exec();
    }
    else
    {
        QString fileName = QFileDialog::getSaveFileName(0,tr("保存聊天记录"),tr("聊天记录"),tr("文本(*.txt);;All File(*.*)"));
        if(!fileName.isEmpty())
        {
            saveFile(fileName);
        }
    }
}

void Widget::slotToolBtnClearClick()
{
    textBrowser->clear();
}

void Widget::slotbtnExit()
{
    close();
}
//set tool btn
void Widget::setToolBtn(QToolButton *btn)
{
    btn->resize(30,30);
    btn->setIconSize(QSize(22,22));
    btn->setAutoRaise(true);
}
