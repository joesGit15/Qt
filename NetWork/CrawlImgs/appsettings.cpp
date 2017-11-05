#include "appsettings.h"

#include <QtCore/QSettings>

AppSettings::AppSettings(QObject *parent):
    QObject(parent)
{
    QString file = "config.ini";
    _appSet = new QSettings(file,QSettings::IniFormat,this);

    _appSet->beginGroup("app");
    _appSet->setValue("organization_name","WT");
    _appSet->setValue("application_name","crawl");

    _winSet = new QSettings(file,QSettings::IniFormat,this);
    _winSet->beginGroup("window");

    QString url;
    int size = _winSet->beginReadArray("urls");
    for (int i = 0; i < size; ++i) {
        _winSet->setArrayIndex(i);
        url = _winSet->value("url","").toString();
        _urls.append(url);
    }
    _winSet->endArray();
}

AppSettings::~AppSettings()
{
    _winSet->beginWriteArray("urls");
    for(int i=0; i < _urls.count(); i++){
        _winSet->setArrayIndex(i);
        _winSet->setValue("url",_urls.at(i));
    }
    _winSet->endArray();
}

const QStringList &AppSettings::Urls() const
{
    return _urls;
}

void AppSettings::AppendUrl(const QString &url)
{
    if(!_urls.contains(url)){
        _urls.append(url);
    }
}
