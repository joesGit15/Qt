#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>

class ImageProcessWidget;
QT_BEGIN_NAMESPACE
class QTabWidget;
class QWidget;
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    enum AppProcess{
        ImageProcess = 0,
        OtherProcess
    };

public:
    explicit MainWindow(QWidget *parent = 0);

protected:
    void showEvent(QShowEvent *) override;

private slots:
    void openFiles();
    void showImageProcessWidget();
    void showOtherWidget();

private:
    void initMenus();

private:
    QTabWidget*             _tabWidget        = 0;
    ImageProcessWidget*     _imageProcessWget = 0;
    QWidget*                _otherWidget      = 0;
};

#endif // MAINWINDOW_H
