#ifndef HTTPWINDOW_H
#define HTTPWINDOW_H

#include <QtWidgets/QWidget>
#include <QtWidgets/QProgressDialog>

#include <QtNetwork/QNetworkAccessManager>
#include <QtCore/QUrl>

QT_BEGIN_NAMESPACE
class QFile;
class QLabel;
class QLineEdit;
class QPushButton;
class QSslError;
class QAuthenticator;
class QNetworkReply;
class QCheckBox;
QT_END_NAMESPACE

class HttpWindow : public QWidget
{
    Q_OBJECT

public:
    explicit HttpWindow(QWidget *parent = 0);

    void StartRequest(const QUrl &requestedUrl);

private slots:
    void StDownloadFile();
    void StCancelDownload();
    void StHttpFinished();
    void StHttpReadyRead();
    void StEnableDownloadButton();
    void StAuthenticationRequired(QNetworkReply*,QAuthenticator *);
#ifndef QT_NO_SSL
    void StSslErrors(QNetworkReply*,const QList<QSslError> &errors);
#endif

private:
    QFile *OpenFileForWrite(const QString &fileName);

private:
    QLineEdit*      _urlLineEdit    = 0;
    QPushButton*    _downloadButton = 0;

    QLineEdit*      _defaultFileLineEdit        = 0;
    QLineEdit*      _downloadDirectoryLineEdit  = 0;

    QUrl _url;
    QFile*                  _file       = 0;
    QNetworkReply*          _reply      = 0;
    QNetworkAccessManager   _qnam;
    bool _httpRequestAborted    = false;
};

class ProgressDialog : public QProgressDialog
{
    Q_OBJECT

public:
    explicit ProgressDialog(const QUrl &url, QWidget *parent = 0);

public slots:
   void StNetworkReplyProgress(qint64 bytesRead, qint64 totalBytes);
};
#endif
