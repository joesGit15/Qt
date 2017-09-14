#include "widget.h"

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtCore/QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
}

Widget::~Widget()
{

}

void Widget::showEvent(QShowEvent *event)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    //db.setHostName("joe-sword");
    db.setHostName("localhost");
    db.setDatabaseName("sakila");
    db.setUserName("joe");
    db.setPassword("iamjoe");
    bool bOpenOk = db.open();
    if(!bOpenOk){
        qDebug() << db.lastError().text();
    }

    if(db.isOpen()){
        db.close();
    }
}
