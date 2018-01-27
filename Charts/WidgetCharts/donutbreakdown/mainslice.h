#ifndef MAINSLICE_H
#define MAINSLICE_H

#include <QtCharts/qpieslice.h>

namespace QtCharts {
    class QPieSeries;
}
using namespace QtCharts;

class MainSlice : public QPieSlice
{
    Q_OBJECT
public:
    MainSlice(QPieSeries *breakdownSeries, QObject *parent = 0);

    QPieSeries *breakdownSeries() const;

    void setName(QString name);
    QString name() const;

public slots:
    void updateLabel();

private:
    QString _name;
    QPieSeries *_breakdownSeries;
};

#endif // MAINSLICE_H
