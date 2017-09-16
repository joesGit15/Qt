#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtSql/QSqlDatabase>

QT_BEGIN_NAMESPACE
class QLineEdit;
class QTextEdit;
class QComboBox;
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

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

    QTextEdit*      _data = 0;

    QComboBox*      _databases  = 0;
    QComboBox*      _tables     = 0;
};

#endif // WIDGET_H
