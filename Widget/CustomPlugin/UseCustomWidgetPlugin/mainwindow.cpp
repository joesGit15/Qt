#include "mainwindow.h"

#include <QtWidgets>

#include <QtPlugins/analogclock.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QVBoxLayout* vlyt;
    vlyt = new QVBoxLayout;
    vlyt->addWidget(new AnalogClock(this));
    setLayout(vlyt);
}

MainWindow::~MainWindow()
{

}
