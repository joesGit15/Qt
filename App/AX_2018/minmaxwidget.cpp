#include "minmaxwidget.h"

#include <QtWidgets/qlabel.h>
#include <QtWidgets/qboxlayout.h>

#include <QtGui/qpainter.h>

MinMaxWidget::MinMaxWidget(QWidget *parent)
    : QWidget(parent)
{
    QLabel* lblMin = new QLabel(this);
    lblMin->setPixmap(QPixmap(":/res/min.png"));
    QLabel* lblMax = new QLabel(this);
    lblMax->setPixmap(QPixmap(":/res/max.png"));
    QLabel* lblClo = new QLabel(this);
    lblClo->setPixmap(QPixmap(":/res/close.png"));

    QHBoxLayout* hlyt = new QHBoxLayout;
    hlyt->addStretch(1);
    hlyt->addWidget(lblMin);
    hlyt->addWidget(lblMax);
    hlyt->addWidget(lblClo);
    setLayout(hlyt);

    setAttribute(Qt::WA_TranslucentBackground);
}

void MinMaxWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QPainterPath path(rect().topLeft());
    path.lineTo(rect().bottomRight());
    path.lineTo(rect().topRight());
    path.lineTo(rect().topLeft());
    painter.fillPath(path,QColor("#032d57"));
}
