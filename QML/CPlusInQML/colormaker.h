#ifndef COLORMAKER_H
#define COLORMAKER_H

#include <QtCore/qobject.h>
#include <QtGui/qcolor.h>

class ColorMaker : public QObject
{
    Q_OBJECT

    Q_ENUMS(GenerateAlgorithm)

    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(QColor timeColor READ timeColor)

public:
    explicit ColorMaker(QObject *parent = 0);

    enum GenerateAlgorithm{
        RandomRGB = 0,
        RandomRed,
        RandomGreen,
        RandomBlue,
        LinearIncrease
    };

    inline QColor color() const{
        return _color;
    }

    void setColor(const QColor &color);
    QColor timeColor() const;

    Q_INVOKABLE inline GenerateAlgorithm algorithm() const{
        return _algorithm;
    }

    Q_INVOKABLE inline void setAlgorithm(GenerateAlgorithm algorithm){
        _algorithm = algorithm;
    }

signals:
    void colorChanged(const QColor &color);
    void currentTime(const QString &strTime);

public slots:
    void start();
    void stop();

protected:
    void timerEvent(QTimerEvent *event) override;

private:
    GenerateAlgorithm   _algorithm  = RandomRGB;
    QColor              _color      = QColor(Qt::black);
    int                 _colorTimer = 0;
};

#endif // COLORMAKER_H
