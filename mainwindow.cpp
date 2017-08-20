#include "mainwindow.h"

#include "./module_editorFactory_widget/editorfactorwidget.h"
#include "./module_colorViewModelDelegate/colorlistviewwidget.h"

#include <QtWidgets/QApplication>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QGridLayout>
#include <QtCore/QTime>

#include <QtGui/QScreen>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle(tr("Qt App"));
    ColorListViewWidget* colorList = new ColorListViewWidget(this);
    EditorFactorWidget* editorFactorWgt = new EditorFactorWidget(this);

    QTabWidget* tabWget = new QTabWidget(this);
    tabWget->addTab(colorList,tr("Color List"));
    tabWget->addTab(editorFactorWgt,tr("EditorFactor"));
    tabWget->setCurrentIndex(1);

    QWidget* wget = new QWidget(this);
    setCentralWidget(wget);

    QGridLayout* glyt = new QGridLayout;
    glyt->addWidget(tabWget);
    wget->setLayout(glyt);

    srand(QTime::currentTime().msec());
}

void MainWindow::showEvent(QShowEvent *)
{
    QSize s = QApplication::primaryScreen()->size();
    int w = s.width() * 0.8;
    int h = s.height() * 0.8;
    resize(w,h);
    int x = (s.width() - w)/2;
    int y = (s.height() - h)/2;
    move(x,y);
}
