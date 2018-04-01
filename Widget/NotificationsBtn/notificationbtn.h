#ifndef NOTIFICATIONBTN_H
#define NOTIFICATIONBTN_H

#include <QtWidgets/qabstractbutton.h>

class NotificationBtn : public QAbstractButton
{
public:
    NotificationBtn(QWidget* parent = 0);

public:
    void paintEvent(QPaintEvent *e) override;

    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;

    void keyPressEvent(QKeyEvent *e) override;
private:
    int   _num = 0;
    bool  _hover = false;

};

#endif // NOTIFICATIONBTN_H
