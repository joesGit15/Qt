#include "customtabstyle.h"

#include <QtWidgets/qstyleoption.h>

CustomTabStyle::CustomTabStyle(QTabBar::Shape shape, QStyle *style)
    :QProxyStyle(style)
{
    _shape = shape;
}

QSize CustomTabStyle::sizeFromContents(QStyle::ContentsType type,
                                       const QStyleOption *option,
                                       const QSize &size,
                                       const QWidget *widget) const
{
    QSize s = QProxyStyle::sizeFromContents(type,option,size,widget);
    if(QStyle::CT_TabBarTab){
        s.transpose();
    }
    return s;
}

void CustomTabStyle::drawControl(QStyle::ControlElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const
{
    if (element == CE_TabBarTabLabel) {
        const QStyleOptionTab* tab = qstyleoption_cast<const QStyleOptionTab*>(option);
        if (tab != 0) {
            QStyleOptionTab opt(*tab);
            opt.shape = _shape;
            QProxyStyle::drawControl(element, &opt, painter, widget);
            return;
        }
    }

    QProxyStyle::drawControl(element, option, painter, widget);
}
