#ifndef WIDGET_H
#define WIDGET_H

#include <QtWidgets/QWidget>

namespace QtCharts {
    class QLineSeries;
    class QChart;
}
using namespace QtCharts;

class XYSeriesIODevice;

class QAudioInput;

class AudioWidget : public QWidget
{
    Q_OBJECT

public:
    AudioWidget(QWidget *parent = 0);
    ~AudioWidget();

private:
    QChart       *_chart = 0;
    QLineSeries *_series = 0;

    XYSeriesIODevice     *_device = 0;
    QAudioInput      *_audioInput = 0;
};

#endif // WIDGET_H
