#ifndef DATABASECONNECT_H
#define DATABASECONNECT_H

#include <QWidget>
#include <QtSql/QSqlDatabase>

QT_BEGIN_NAMESPACE
class QLineEdit;
class QComboBox;
class QSqlQueryModel;
class QSqlTableModel;
QT_END_NAMESPACE

class DatabaseConnect : public QWidget
{
    Q_OBJECT

public:
    DatabaseConnect(QWidget *parent = 0);
    ~DatabaseConnect();

    inline QSqlQueryModel* TableDescModel(){
        return _tbDescModel;
    }
    inline QSqlTableModel* TableDataModel(){
        return _tbDataModel;
    }

signals:
    void SigError(const QString &srror);
    void SigInfo(const QString &info);

    void SigTableDescModelUpdate();
    void SigTableDataModelUpdate();

protected:
    void showEvent(QShowEvent *event) override;

private slots:
    void StConnectDatabase();

    void StSelectedDatabaseChanged(const QString &database);
    void StSelectedTableChanged(const QString &table);

private:
    QSqlDatabase    _db;

    QLineEdit*      _hostname   = 0;
    QLineEdit*      _username   = 0;
    QLineEdit*      _userpwd    = 0;

    QComboBox*      _databases  = 0;
    QComboBox*      _tables     = 0;

    QSqlQueryModel* _tbDescModel = 0;
    QSqlTableModel* _tbDataModel = 0;
};

#endif // DATABASECONNECT_H
