#include "dialog.h"

#include "GenerateBigFile/generatebigfilewgt.h"
#include "ViewBigFile/viewbigfilewgt.h"

#include <QtWidgets>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle(tr("View the Big File"));

    QVBoxLayout* vlyt;
    vlyt = new QVBoxLayout;

    ViewBigFileWgt* viewWgt;
    GenerateBigFileWgt* generateWgt;

    generateWgt = new GenerateBigFileWgt(this);
    viewWgt     = new ViewBigFileWgt(this);

    vlyt->addWidget(generateWgt);
    vlyt->addWidget(viewWgt);

    setLayout(vlyt);

    connect(generateWgt,&GenerateBigFileWgt::sigGenerateOk,
            viewWgt,&ViewBigFileWgt::setFilename);
}

Dialog::~Dialog()
{

}
