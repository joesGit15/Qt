#ifndef APPSETTINGS_H
#define APPSETTINGS_H
#include <QObject>

QT_BEGIN_NAMESPACE
class QSettings;
QT_END_NAMESPACE

class AppSettings : public QObject
{
public:
    explicit AppSettings(QObject *parent = 0);
    ~AppSettings();

    const QStringList &Urls() const;
    void AppendUrl(const QString &url);

private:
    QSettings*  _appSet = 0;
    QSettings*  _winSet = 0;

    QStringList _urls;
};

#endif // APPSETTINGS_H
