#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
class QTabWidget;
class QDockWidget;
class QTextEdit;
class QTableView;
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    /** the index of @see _ltDocks */
    enum DockIdx{
        Main = 0,
        Info
    };

public:
    explicit MainWindow(QWidget *parent = 0);

protected:
    void showEvent(QShowEvent *event) override;

private slots:
    void StDatabaseConnectError(const QString &error);
    void StDatabaseConnectInfo(const QString &info);

private:
    void SetTableViewDefaultOpts(QTableView *tbv);

private:
    QTabWidget*             _tabWidget = 0;
    QList<QDockWidget*>     _ltDocks;

    QTextEdit*              _info = 0;

    QTableView*             _tbvDesc = 0;
    QTableView*             _tbvData = 0;
};

#endif // MAINWINDOW_H
