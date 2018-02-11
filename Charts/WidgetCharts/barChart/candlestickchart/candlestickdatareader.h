#ifndef CANDLESTICKDATAREADER_H
#define CANDLESTICKDATAREADER_H

#include <QtCore/qtextstream.h>
#include <QtCharts/qcandlestickset.h>

using namespace QtCharts;

class CandlestickDataReader : public QTextStream
{
public:
    explicit CandlestickDataReader(QIODevice *device);

    void readFile(QIODevice *device);
    QCandlestickSet *readCandlestickSet();
};

#endif // CANDLESTICKDATAREADER_H
