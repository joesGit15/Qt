#include "mainwindow.h"

#include "./module_editorFactory_widget/editorfactorwidget.h"
#include "./module_colorViewModelDelegate/colorlistviewwidget.h"
#include "./module_imageProcess/imageprocesswidget.h"

#include <QtWidgets/QApplication>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QGridLayout>

#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QTabWidget>

#include <QtCore/QTime>
#include <QtCore/QStandardPaths>

#include <QtGui/QScreen>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle(tr("Qt App"));

    initMenus();

    /** begin: image process widget */
    _imageProcessWget = new ImageProcessWidget(this);
    /** end: image process widget */

    /** begin: other widget */
    _otherWidget = new QWidget(this);
    ColorListViewWidget* colorList = new ColorListViewWidget(this);
    EditorFactorWidget* editorFactorWgt = new EditorFactorWidget(this);

    QTabWidget* tabWget = new QTabWidget(this);
    tabWget->addTab(colorList,tr("Color List"));
    tabWget->addTab(editorFactorWgt,tr("EditorFactor"));
    tabWget->setCurrentIndex(1);

    QGridLayout* glyt = new QGridLayout;
    glyt->addWidget(tabWget);
    _otherWidget->setLayout(glyt);
    srand(QTime::currentTime().msec());
    /** end: other widget */

    _tabWidget = new QTabWidget(this);
    setCentralWidget(_tabWidget);
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

void MainWindow::openFiles()
{
    QStringList filters;
    QString defaultDir = "";
    QFileDialog dlg(this);
    if("" == defaultDir){
        defaultDir = QStandardPaths::standardLocations(
                    QStandardPaths::PicturesLocation).first();
    }

    dlg.setDirectory(defaultDir);
    filters << "Image files(*.png *.jpg)"
            << "Text files(*.txt)"
            << "Any files(*)";
    dlg.setNameFilters(filters);
    dlg.setOption(QFileDialog::DontUseNativeDialog);
    if(QDialog::Accepted == dlg.exec()){
        //qDebug() << dlg.selectedFiles();
        if(filters[0] == dlg.selectedNameFilter()){

        }else{
            // other ...
        }
    }
}

void MainWindow::showImageProcessWidget()
{
    _tabWidget->addTab(_imageProcessWget,tr("Image Process"));
}

void MainWindow::showOtherWidget()
{
    _tabWidget->addTab(_otherWidget,tr("Other Process"));
}

void MainWindow::initMenus()
{
    QMenuBar* mBar = menuBar();
    QMenu* appMenu  = mBar->addMenu(tr("&App"));
    appMenu->addAction(tr("&Image Process"),
                        this,&MainWindow::showImageProcessWidget);
    appMenu->addAction(tr("&Other Process"),
                        this,&MainWindow::showOtherWidget);
    appMenu->addSeparator();
    appMenu->addAction(tr("Exit out"),
                        this,&MainWindow::close);

    QMenu* fileMenu = mBar->addMenu(tr("&File"));
    fileMenu->addAction(tr("&Open Files..."),
                        this,&MainWindow::openFiles,
                        QKeySequence::Open);
}
