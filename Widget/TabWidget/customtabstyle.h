#ifndef CUSTOMTABSTYLE_H
#define CUSTOMTABSTYLE_H

#include <QtWidgets/qproxystyle.h>
#include <QtWidgets/qtabbar.h>

class CustomTabStyle : public QProxyStyle
{
public:
    CustomTabStyle(QTabBar::Shape shape,QStyle *style = 0);
    void setTabBarShape();

    QSize sizeFromContents(ContentsType type, const QStyleOption *option,
                           const QSize &size, const QWidget *widget) const;

    void drawControl(ControlElement element, const QStyleOption *option,
                     QPainter *painter, const QWidget *widget) const;
private:
    QTabBar::Shape _shape;
};

#endif // CUSTOMTABSTYLE_H
