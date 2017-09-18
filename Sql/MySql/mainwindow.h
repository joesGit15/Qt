#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
class QMdiArea;
class QDockWidget;
class QTextEdit;
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
    QMdiArea*               _mdiArea = 0;
    QList<QDockWidget*>     _ltDocks;

    QTextEdit*              _info = 0;
};

#endif // MAINWINDOW_H
