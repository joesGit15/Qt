#include "generatebigfilewgt.h"

#include "../basefun.h"

#ifdef DEBUG
#include <time.h>
#endif

#include <QtWidgets>

GenerateBigFileWgt::GenerateBigFileWgt(QWidget *parent)
    : QWidget(parent)
{
    QLabel* lbl;
    QSpinBox* sbox;
    QHBoxLayout *hlyt;
    QPushButton *btn;
    QLineEdit *ledit;

    hlyt = new QHBoxLayout;

    lbl  = new QLabel(tr("Base number:"),this);
    sbox = new QSpinBox(this);
    _sboxBaseNum = sbox;
    sbox->setRange(0,100);
    sbox->setSingleStep(10);
    hlyt->addWidget(lbl);
    hlyt->addWidget(sbox);

    lbl  = new QLabel(tr("Step:"),this);
    sbox = new QSpinBox(this);
    _sboxStep = sbox;
    sbox->setRange(0,100);
    sbox->setSingleStep(10);
    sbox->setValue(1);

    hlyt->addWidget(lbl);
    hlyt->addWidget(sbox);

    lbl  = new QLabel(tr("Generate count:"),this);
    sbox = new QSpinBox(this);
    _sboxCount = sbox;

    /* 2147483647 * 4bytes ~= 8G */
    sbox->setRange(0,INT_MAX);
    sbox->setSingleStep(10);
    sbox->setValue(256*1024);
    hlyt->addWidget(lbl);
    hlyt->addWidget(sbox);

    lbl = new QLabel(tr("Filename:"),this);
    ledit = new QLineEdit(this);
    _ledit = ledit;
    ledit->setPlaceholderText(tr("binary file name:a.bin"));
    hlyt->addWidget(lbl);
    hlyt->addWidget(ledit);

    btn = new QPushButton(tr("Begin..."),this);
    connect(btn,&QPushButton::clicked,
            this,&GenerateBigFileWgt::slotBtnBeginClicked);
    hlyt->addWidget(btn);

    setLayout(hlyt);
}

#if 1
//12738- should in thread to work
void GenerateBigFileWgt::slotBtnBeginClicked()
{
    int nRet;
    uint64_t u64ByteSize;

    uint32_t nBase,nStep,nCount;

    QFile file;
    QString text,tmpText,filename;

    nBase  = _sboxBaseNum->value();
    nStep  = _sboxStep->value();
    nCount = _sboxCount->value();
    if(0 == nCount){
        return;
    }

    if("" == _ledit->text().trimmed()){
        return;
    }

    //0x00000000 -> 0xFFFFFFFF by step
    u64ByteSize = nCount * sizeof(uint32_t);

    text = tr("Base:%1 Step:%2 Count:%3, will generate %4bytes file.")
            .arg(Convert(nBase)).arg(Convert(nStep)).arg(nCount).arg(u64ByteSize);

    tmpText = Convert(u64ByteSize);
    if("" != tmpText){
        text += tr("about %1").arg(tmpText);
    }

    nRet = QMessageBox::information(this,tr("Information"),text,
                                    QMessageBox::Ok,QMessageBox::Cancel);
    if(QMessageBox::Cancel == nRet) {
        return;
    }

    filename = QCoreApplication::applicationDirPath();
    filename += "/";
    filename += _ledit->text().trimmed();

    file.setFileName(filename);

#ifdef DEBUG
    clock_t t;
    t = clock();
#endif

    if(!file.open(QIODevice::WriteOnly)){
        QMessageBox::information(this,tr("Information"),file.errorString(),
                                 QMessageBox::Ok);
        return;
    }

    QDataStream out(&file);
    for (uint32_t i = 0; i < nCount; i++) {
        nBase += nStep;
        out << nBase;
    }
    file.close();

#ifdef DEBUG
    qDebug("%li", clock() - t);
#endif

    emit sigGenerateOk(filename);
}
#endif
