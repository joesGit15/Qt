#include "DatabaseConnect.h"

#include <QtSql/QSqlError>

#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QFrame>

#include <QtSql/QSqlQuery>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlRecord>
#include <QtSql/QSqlQueryModel>
#include <QtSql/QSqlTableModel>

#include <QtCore/QDebug>

DatabaseConnect::DatabaseConnect(QWidget *parent)
    : QWidget(parent)
{
    _db = QSqlDatabase::addDatabase("QMYSQL");

    _tbDescModel = new QSqlQueryModel(this);
    _tbDataModel = new QSqlTableModel(this,_db);

    _hostname = new QLineEdit(this);
    _hostname->setPlaceholderText(tr("localhost"));
    _username = new QLineEdit(this);
    _userpwd  = new QLineEdit(this);
    _userpwd->setEchoMode(QLineEdit::Password);

    QPushButton* btnConnect = new QPushButton(tr("Open"),this);

    _databases = new QComboBox(this);
    _databases->setEditable(false);
    _databases->setSizeAdjustPolicy(QComboBox::AdjustToContents);

    _tables = new QComboBox(this);
    _tables->setEditable(false);
    _tables->setSizeAdjustPolicy(QComboBox::AdjustToContents);

    QPushButton* btnUse = new QPushButton(tr("Use Selected"),this);
    btnUse->setMinimumWidth(100);

    /** left formlayout */
    QFormLayout* lflyt = new QFormLayout;
    lflyt->addRow(tr("&Hostname"),_hostname);
    lflyt->addRow(tr("&Username"),_username);
    lflyt->addRow(tr("&password"),_userpwd);
    lflyt->addRow(tr(""),btnConnect);

    /** center formlayout */
    QFormLayout* cflyt = new QFormLayout;
    cflyt->addRow(tr("&Databases"),_databases);
    cflyt->addRow(tr("&Tables"),_tables);
    cflyt->addRow(tr(""),btnUse);

    QFrame* vline = new QFrame(this);
    vline->setFrameShape(QFrame::VLine);

    QHBoxLayout* hlyt = new QHBoxLayout;
    hlyt->addLayout(lflyt);
    hlyt->addWidget(vline);
    hlyt->addLayout(cflyt);
    hlyt->addStretch(1);

    setLayout(hlyt);

    connect(btnConnect,&QPushButton::clicked,
            this,&DatabaseConnect::StConnectDatabase);

    connect(_databases,&QComboBox::currentTextChanged,
            this,&DatabaseConnect::StSelectedDatabaseChanged);
    connect(_tables,&QComboBox::currentTextChanged,
            this,&DatabaseConnect::StSelectedTableChanged);
}

DatabaseConnect::~DatabaseConnect()
{
    if(_db.isOpen()){
        _db.close();
    }
}

void DatabaseConnect::showEvent(QShowEvent *event)
{
    (void)event;
}

void DatabaseConnect::StConnectDatabase()
{
    QObject* obj = sender();
    QPushButton* btn = qobject_cast<QPushButton*>(obj);

    disconnect(_databases,&QComboBox::currentTextChanged,
            this,&DatabaseConnect::StSelectedDatabaseChanged);

    if(btn->text() == tr("Open")){
        QString str;
        str = _hostname->text().trimmed();
        _db.setHostName(str);

        str = _username->text().trimmed();
        _db.setUserName(str);

        str = _userpwd->text().trimmed();
        _db.setPassword(str);
        if(!_db.open()){
            emit SigError(_db.lastError().text());
        }else{
            emit SigInfo(tr("Open Database OK"));
            btn->setText(tr("Close"));
        }

        /** show databases; */
        QSqlQuery query;
        QString database;
        if(!query.exec("show databases")){
            emit SigError(query.lastError().text());
            goto _END;
        }

        _databases->clear();
        while(query.next()){
            database = query.value(0).toString();
            _databases->addItem(database);
        }

        if(database != ""){
            StSelectedDatabaseChanged(database);
            _databases->setCurrentText(database);
        }

        goto _END;
    }

    if(btn->text() == tr("Close")){
        _db.close();
        emit SigInfo(tr("Close Database OK"));
        btn->setText(tr("Open"));

        goto _END;
    }

_END:
    connect(_databases,&QComboBox::currentTextChanged,
            this,&DatabaseConnect::StSelectedDatabaseChanged);
}

void DatabaseConnect::StSelectedDatabaseChanged(const QString &database)
{
    Q_ASSERT(database != "");

    QSqlQuery query;
    QString table,sql;

    disconnect(_tables,&QComboBox::currentTextChanged,
            this,&DatabaseConnect::StSelectedTableChanged);

    /** use database; */
    sql = QString("use %1").arg(database);
    if(!query.exec(sql)){
        goto _ERROR;
    }

    /** show tables*/
    if(!query.exec("show tables")){
        goto _ERROR;
    }

    _tables->clear();
    while(query.next()){
        table = query.value(0).toString();
        _tables->addItem(table);
    }

    if(table != ""){
        StSelectedTableChanged(table);
        _tables->setCurrentText(table);
    }

    goto _END;

_ERROR:
    emit SigError(query.lastError().text());

_END:
    connect(_tables,&QComboBox::currentTextChanged,
            this,&DatabaseConnect::StSelectedTableChanged);
}

void DatabaseConnect::StSelectedTableChanged(const QString &table)
{
    Q_ASSERT(table != "");

    QString sql;
    QSqlQuery query;

    /** desc tablename */
    sql = QString("desc %1").arg(table);
    if(!query.exec(sql)){
        emit SigError(query.lastError().text());
        return;
    }

    _tbDescModel->setQuery(query);

    /** select * from tablename; */
    _tbDataModel->setTable(table);
    _tbDataModel->select();

    /** show processlist; */
}
