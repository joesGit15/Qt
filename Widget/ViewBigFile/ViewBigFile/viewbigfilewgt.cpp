#include "viewbigfilewgt.h"
#include "../basefun.h"

#ifdef DEBUG
#include <time.h>
#endif

#include <QtWidgets>

ViewBigFileWgt::ViewBigFileWgt(QWidget *parent)
    : QWidget(parent)
{
    QHBoxLayout *hlyt;
    QVBoxLayout *vlyt;
    QPushButton *btn;
    QLineEdit *ledit;
    QPlainTextEdit *tedit;

    hlyt = new QHBoxLayout;

    ledit = new QLineEdit(this);
    _ledit = ledit;
    ledit->setReadOnly(true);
    ledit->setPlaceholderText(tr("default big binary file path"));

#ifdef LINUX_DEBUG
    ledit->setText("/home/joe/bin/a_10m.bin");
    ledit->setReadOnly(false);
#endif

    btn = new QPushButton(tr("Open file"));
    connect(btn,&QPushButton::clicked,
            this,&ViewBigFileWgt::slotBtnOpenClicked);

    hlyt->addWidget(ledit,1);
    hlyt->addWidget(btn);

    tedit = new QPlainTextEdit(this);
    _tedit = tedit;
    tedit->setReadOnly(true);

    vlyt = new QVBoxLayout;
    vlyt->addLayout(hlyt);
    vlyt->addWidget(tedit,1);
    setLayout(vlyt);
}

void ViewBigFileWgt::setFilename(const QString &filename)
{
    _ledit->setText(filename);
}

#if 1
void ViewBigFileWgt::slotBtnOpenClicked()
{
    QString filename;
    filename = _ledit->text().trimmed();
    if("" == filename){
        return;
    }

#ifdef DEBUG
    clock_t t;
    t = clock();
#endif

    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly)){
        QMessageBox::information(this,tr("Info"),file.errorString());
        return;
    }

    char szHex[12];
    QString text;
    uint32_t u32Val;
    QDataStream in(&file);
    text = "";
    QList<uint32_t> u32Datas;
    while(!in.atEnd()){
        in >> u32Val;
        //u32Datas.append(u32Val);
        sprintf(szHex,"0x%08X ",u32Val);
        text += QString(szHex);
    }
    file.close();

    _tedit->setPlainText(text);

#ifdef DEBUG
    //1446357
    qDebug("%li clock\n",clock() - t);
#endif
}
#else
void ViewBigFileWgt::slotBtnOpenClicked()
{
    QString filename;
    filename = _ledit->text().trimmed();
    if("" == filename){
        return;
    }

#ifdef DEBUG
    clock_t t;
    t = clock();
#endif

    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly)){
        QMessageBox::information(this,tr("Info"),file.errorString());
        return;
    }

    char szHex[12];
    QString text;
    uint32_t u32Val;
    QDataStream in(&file);
    text = "";
    QList<uint32_t> u32Datas;
    while(!in.atEnd()){
        in >> u32Val;
        //u32Datas.append(u32Val);
        sprintf(szHex,"0x%08X ",u32Val);
        text += QString(szHex);
    }
    file.close();

    _tedit->setPlainText(text);

#ifdef DEBUG
    //1446357
    qDebug("%li clock\n",clock() - t);
#endif
}
#endif
