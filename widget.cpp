#include "widget.h"
#include "./module_editorFactory_widget/editorfactorwidget.h"
#include "./module_colorViewModelDelegate/colorlistviewwidget.h"

#include <QtWidgets/QApplication>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QGridLayout>
#include <QtCore/QTime>

#include <QtGui/QScreen>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    ColorListViewWidget* colorList = new ColorListViewWidget(this);
    EditorFactorWidget* editorFactorWgt = new EditorFactorWidget(this);

    QTabWidget* tabWget = new QTabWidget(this);
    tabWget->addTab(colorList,tr("Color List"));
    tabWget->addTab(editorFactorWgt,tr("EditorFactor"));
    tabWget->setCurrentIndex(1);

    QGridLayout* glyt = new QGridLayout;
    glyt->addWidget(tabWget);
    setLayout(glyt);


    srand(QTime::currentTime().msec());
}

Widget::~Widget()
{

}

void Widget::showEvent(QShowEvent *)
{
    QSize s = QApplication::primaryScreen()->size();
    int w = s.width() * 0.8;
    int h = s.height() * 0.8;
    resize(w,h);
    int x = (s.width() - w)/2;
    int y = (s.height() - h)/2;
    move(x,y);
}
