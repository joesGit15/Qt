#include "audiowidget.h"

#include <QtMultimedia/qaudioinput.h>
#include <QtMultimedia/qaudiodeviceinfo.h>

#include <QtCharts/qchart.h>
#include <QtCharts/qchartview.h>
#include <QtCharts/qvalueaxis.h>
#include <QtCharts/qlineseries.h>

#include <QtWidgets/qboxlayout.h>

#include "xyseriesiodevice.h"

AudioWidget::AudioWidget(QWidget *parent)
    : QWidget(parent)
{
    setObjectName("Audio Widget");

    QChart* chart = new QChart;
    _chart = chart;

    QChartView *chartView = new QChartView(chart);
    chartView->setMinimumSize(800, 600);

    QLineSeries* series = new QLineSeries;
    _series = series;
    chart->addSeries(series);

    QValueAxis *axisX = new QValueAxis;
    axisX->setRange(0, 2000);
    axisX->setLabelFormat("%g");
    axisX->setTitleText("Samples");

    QValueAxis *axisY = new QValueAxis;
    axisY->setRange(-10, 10);
    axisY->setTitleText("Audio level");
    chart->setAxisX(axisX, series);
    chart->setAxisY(axisY, series);
    chart->legend()->hide();
    chart->setTitle("Data from the microphone");

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(chartView);
    setLayout(mainLayout);

    QAudioFormat formatAudio;
    formatAudio.setSampleRate(8000);
    formatAudio.setChannelCount(1);
    formatAudio.setSampleSize(8);
    formatAudio.setCodec("audio/pcm");
    formatAudio.setByteOrder(QAudioFormat::LittleEndian);
    formatAudio.setSampleType(QAudioFormat::UnSignedInt);

    QAudioDeviceInfo inputDevices = QAudioDeviceInfo::defaultInputDevice();
    _audioInput = new QAudioInput(inputDevices,formatAudio, this);

    _device = new XYSeriesIODevice(_series, this);
    _device->open(QIODevice::WriteOnly);

    _audioInput->start(_device);
}

AudioWidget::~AudioWidget()
{
    _audioInput->stop();
    _device->close();
}
