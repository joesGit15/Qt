#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class QLineEdit;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void StOpenUrl();
    void StOpenFolder();
    void StOpenSoft();
    void StOpenFile();

private:
    QLineEdit*      _leditUrl;
    QLineEdit*      _leditFolder;
    QLineEdit*      _leditSoft;

    QLineEdit*      _leditFile;
    QLineEdit*      _leditFileSoft;
};

#endif // WIDGET_H
