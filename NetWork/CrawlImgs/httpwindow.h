#ifndef HTTPWINDOW_H
#define HTTPWINDOW_H

#include <QtWidgets/QWidget>

#include <QtCore/QUrl>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkAccessManager>

class AppSettings;
QT_BEGIN_NAMESPACE
class QComboBox;
class QPushButton;
class QSslError;
class QAuthenticator;
class QTextBrowser;
QT_END_NAMESPACE

class HttpWindow : public QWidget
{
    Q_OBJECT

public:
    explicit HttpWindow(QWidget *parent = 0);

    void StartRequest(const QUrl &requestedUrl);

private slots:
    void StReplyError(QNetworkReply::NetworkError code);

    void StDownloadFile();
    void StHttpFinished();
    void StHttpReadyRead();

    void StClearTextBrowser();

private:
    void BeginToCrawl();

private:
    QComboBox*      _cbBoxUrl    = 0;
    QComboBox*      _cbBoxReg    = 0;

    AppSettings*    _appSet      = 0;
    QTextBrowser*   _textBrowser = 0;
    QPushButton*    _btnDownload = 0;

    QNetworkAccessManager   _qnam;

    QString         _regHtml;
    QString         _regImg;

    int             _urlId;
    QStringList     _urls;
};

#endif
