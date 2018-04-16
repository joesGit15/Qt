#include "mainwindow.h"

#include "minmaxwidget.h"

#include <QtWidgets/qboxlayout.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    Qt::WindowFlags flags;
    flags = Qt::Dialog | Qt::FramelessWindowHint;
    setWindowFlags(flags);

    QPalette plt = palette();
    QBrush br(QColor("#192b6b"));
    plt.setBrush(QPalette::Background,br);
    setPalette(plt);

    MinMaxWidget* widget = new MinMaxWidget(this);

    QHBoxLayout* hlyt = new QHBoxLayout;
    hlyt->addStretch(1);
    hlyt->addWidget(widget);

    QVBoxLayout* vlyt = new QVBoxLayout;
    vlyt->setMargin(0);
    vlyt->addLayout(hlyt);
    vlyt->addStretch(1);

    QWidget* centerWidget = new QWidget(this);
    centerWidget->setLayout(vlyt);
    setCentralWidget(centerWidget);
}

MainWindow::~MainWindow()
{

}
