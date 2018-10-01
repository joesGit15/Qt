#include "generatebigfilewgt.h"

#include <QtWidgets>

QString Convert(uint32_t u32Num)
{
    char szHex[11];
    sprintf(szHex,"0x%08X",u32Num);
    return QString(szHex);
}

QString Convert(uint64_t u64ByteSize)
{
    char szBuffer[50];
    uint8_t uLevel = 0;

    QString text;

    while(u64ByteSize > 1024){
        u64ByteSize /= 1024;
        uLevel++;
    }

    switch (uLevel) {
    case 0:
        szBuffer[0] = '\0';
        break;///bytes
    case 1:
        sprintf(szBuffer,"%liKB",u64ByteSize);
        break;///K
    case 2:
        sprintf(szBuffer,"%liMB",u64ByteSize);
        break;///M
    case 3:
        sprintf(szBuffer,"%liGB",u64ByteSize);
        break;///G
    default:
        szBuffer[0] = '\0';
        break;
    }

    text = QString(szBuffer);
    return text;
}

GenerateBigFileWgt::GenerateBigFileWgt(QWidget *parent)
    : QWidget(parent)
{
    QLabel* lbl;
    QSpinBox* sbox;
    QHBoxLayout *hlyt;
    QPushButton *btn;

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
    sbox->setValue(1024*100);
    hlyt->addWidget(lbl);
    hlyt->addWidget(sbox);

    hlyt->addStretch(1);

    btn = new QPushButton(tr("Begin..."),this);
    connect(btn,&QPushButton::clicked,
            this,&GenerateBigFileWgt::slotBtnBeginClicked);
    hlyt->addWidget(btn);

    setLayout(hlyt);
}

void GenerateBigFileWgt::slotBtnBeginClicked()
{
    int nRet;
    uint64_t u64ByteSize;

    uint32_t nBase,nStep,nCount;

    QFile file;
    QString text,filename,tmpText;

    nBase  = _sboxBaseNum->value();
    nStep  = _sboxStep->value();
    nCount = _sboxCount->value();
    if(0 == nCount){
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
    filename += "/a.bin";

    file.setFileName(filename);
    if(!file.open(QIODevice::WriteOnly)){
        QMessageBox::information(this,tr("Information"),file.errorString(),
                                 QMessageBox::Ok);
        return;
    }
    QDataStream out(&file);

    QProgressDialog progress("Generate files...", "Abort", 0, nCount, this);
    progress.setWindowModality(Qt::WindowModal);

    for (uint32_t i = 0; i < nCount; i++) {
        nBase += nStep;
        out << nBase;

        text = tr("Total Count %1 -> %2").arg(nCount - i).arg(i);
        progress.setLabelText(text);

        progress.setValue(i);
        if (progress.wasCanceled()) {
            break;
        }
    }

    progress.setValue(nCount);
    file.close();

    emit sigGenerateOk(filename);
}
