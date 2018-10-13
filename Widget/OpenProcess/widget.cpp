#include "widget.h"

#include <QtWidgets>

#define DEFAULT_URL "https://google.com/"
#define DEFAULT_FOLDER "C:\\"
#define DEFAULT_SOFT "notepad.exe"
#define DEFAULT_FILE "D:\\"
#define DEFAULT_FILESOFT "explorer"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *vlyt;
    QHBoxLayout *hlyt;
    QLineEdit *lineEdit;
    QPushButton *btn;

    vlyt = new QVBoxLayout;

    /** 打开网址 */
    lineEdit = new QLineEdit(this);
    _leditUrl = lineEdit;
    lineEdit->setPlaceholderText(tr("Input http url..."));
    lineEdit->setText(DEFAULT_URL);
    btn = new QPushButton(tr("Open Url"),this);
    connect(btn,&QPushButton::clicked,this,&Widget::StOpenUrl);
    hlyt = new QHBoxLayout;
    hlyt->addWidget(lineEdit,1);
    hlyt->addWidget(btn);
    vlyt->addLayout(hlyt);

    /** 打开文件夹 */
    lineEdit = new QLineEdit(this);
    _leditFolder = lineEdit;
    lineEdit->setPlaceholderText(tr("Input one folder..."));
    lineEdit->setText(DEFAULT_FOLDER);
    btn = new QPushButton(tr("Open folder"),this);
    connect(btn,&QPushButton::clicked,this,&Widget::StOpenFolder);
    hlyt = new QHBoxLayout;
    hlyt->addWidget(lineEdit,1);
    hlyt->addWidget(btn);
    vlyt->addLayout(hlyt);

    /** 打开软件 */
    lineEdit = new QLineEdit(this);
    _leditSoft = lineEdit;
    lineEdit->setPlaceholderText(tr("Input one exe path..."));
    lineEdit->setText(DEFAULT_SOFT);
    btn = new QPushButton(tr("Open soft"),this);
    connect(btn,&QPushButton::clicked,this,&Widget::StOpenSoft);
    hlyt = new QHBoxLayout;
    hlyt->addWidget(lineEdit,1);
    hlyt->addWidget(btn);
    vlyt->addLayout(hlyt);

    /** 打开文件和软件 */
    hlyt = new QHBoxLayout;
    lineEdit = new QLineEdit(this);
    _leditFile = lineEdit;
    lineEdit->setPlaceholderText(tr("Input one file..."));
    lineEdit->setText(DEFAULT_FILE);
    hlyt->addWidget(lineEdit,1);

    lineEdit = new QLineEdit(this);
    _leditFileSoft = lineEdit;
    lineEdit->setPlaceholderText(tr("Input one exe path..."));
    lineEdit->setText(DEFAULT_FILESOFT);
    hlyt->addWidget(lineEdit,1);

    btn = new QPushButton(tr("Open File"),this);
    connect(btn,&QPushButton::clicked,this,&Widget::StOpenFile);
    hlyt->addWidget(btn);
    vlyt->addLayout(hlyt);

    vlyt->addStretch(1);
    setLayout(vlyt);
}

Widget::~Widget()
{

}

void Widget::StOpenUrl()
{
    QString url;
    url = _leditUrl->text().trimmed();
    QDesktopServices::openUrl(QUrl(url));
}

void Widget::StOpenFolder()
{
    QString folder;
    folder = _leditFolder->text().trimmed();

    /** 两种方式 */
#if 1
    QString url;
    url = "file:///" + folder;
    QDesktopServices::openUrl(QUrl(url));
#else
    QString command;
    command = "explorer " + folder;
    QProcess::execute(command);
#endif
}

void Widget::StOpenSoft()
{
    QString softName;
    softName = _leditSoft->text().trimmed();
    QProcess::execute(softName);
}

void Widget::StOpenFile()
{
    QString filePath,softPath,command;
    filePath = _leditFile->text().trimmed();
    softPath = _leditFileSoft->text().trimmed();
    command = softPath + " " + filePath;
    QProcess::execute(command);
}
