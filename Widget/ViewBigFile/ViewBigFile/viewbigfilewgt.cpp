#include "viewbigfilewgt.h"

#include <QtWidgets>

ViewBigFileWgt::ViewBigFileWgt(QWidget *parent)
    : QWidget(parent)
{
    QHBoxLayout *hlyt;
    QVBoxLayout *vlyt;
    QPushButton *btn;
    QLineEdit *ledit;
    QTextEdit *tedit;

    hlyt = new QHBoxLayout;

    ledit = new QLineEdit(this);
    _ledit = ledit;
    ledit->setReadOnly(true);
    ledit->setPlaceholderText(tr("default big binary file path"));
    btn = new QPushButton(tr("Open file"));

    hlyt->addWidget(ledit,1);
    hlyt->addWidget(btn);

    tedit = new QTextEdit(this);
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
