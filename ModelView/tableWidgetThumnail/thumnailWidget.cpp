#include "thumnailWidget.h"
#include "tablewidget.h"

#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QPushButton>

ThumnailWidget::ThumnailWidget(QWidget *parent)
    : QWidget(parent)
{
    _tableWget = new TableWidget(this);

    QPushButton* btnOpen = new QPushButton(tr("Open Images"),this);

    QHBoxLayout* hlyt = new QHBoxLayout;
    hlyt->addWidget(btnOpen);
    hlyt->addStretch(1);

    QVBoxLayout* vlyt = new QVBoxLayout;
    vlyt->addWidget(_tableWget,1);
    vlyt->addLayout(hlyt);

    setLayout(vlyt);

    connect(btnOpen,&QPushButton::clicked,
            this,&ThumnailWidget::StOpenImages);
}

void ThumnailWidget::StOpenImages()
{
    QString path = ":/png/imgs/tmp.jpg";
    _tableWget->AddRow(path);
}
