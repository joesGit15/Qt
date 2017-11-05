#include "httpwindow.h"
#include "appsettings.h"

#include <QtWidgets/QComboBox>
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QDialogButtonBox>

#include <QtCore/QTimer>
#include <QtCore/QRegularExpression>
#include <QtCore/QRegularExpressionMatch>
#include <QtCore/QRegularExpressionMatchIterator>

#include <QtNetwork/QAuthenticator>
#include <QtNetwork/QNetworkRequest>

HttpWindow::HttpWindow(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle(tr("HTTP"));
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

#ifndef QT_NO_SSL
    const QString defaultUrl = "https://www.qt.io/";
#else
    const QString defaultUrl = "http://www.qt.io/";
#endif

    _appSet = new AppSettings(this);

    _cbBoxUrl = new QComboBox(this);
    _cbBoxUrl->setEditable(true);
    const QStringList urls = _appSet->Urls();
    if(urls.isEmpty()){
        _cbBoxUrl->addItem(defaultUrl);
    }else{
        for(int i=urls.count()-1; i>=0; i--){
            _cbBoxUrl->addItem(urls.at(i));
        }
    }

    _regHtml = "(https?|ftp|file)://[-A-Za-z0-9+&@#/%?=~_|!:,.;]+[-A-Za-z0-9+&@#/%=~_|](/|\.html)";
    _regImg  = "(https?|ftp|file)://[-A-Za-z0-9+&@#/%?=~_|!:,.;]+[-A-Za-z0-9+&@#/%=~_|]\.(jpg|png)";

    QStringList regs;
    regs << "(https?|ftp|file)://[-A-Za-z0-9+&@#/%?=~_|!:,.;]+[-A-Za-z0-9+&@#/%=~_|]"
         << _regHtml << _regImg;

    _cbBoxReg = new QComboBox(this);
    _cbBoxReg->setEnabled(false);
    _cbBoxReg->setEditable(true);
    for(const QString& reg:regs){
        _cbBoxReg->addItem(reg);
    }

    QFormLayout *formLayout = new QFormLayout;
    formLayout->addRow(tr("&URL:"), _cbBoxUrl);
    formLayout->addRow(tr("&Reg:"), _cbBoxReg);

    QPushButton* btnClear = new QPushButton(tr("Clear"),this);
    _btnDownload = new QPushButton(tr("Download"),this);
    QHBoxLayout* hlyt = new QHBoxLayout;
    hlyt->addStretch(1);
    hlyt->addWidget(btnClear);
    hlyt->addWidget(_btnDownload);

    _textBrowser = new QTextBrowser(this);

    QVBoxLayout *uivlyt = new QVBoxLayout(this);
    uivlyt->addLayout(formLayout);
    uivlyt->addLayout(hlyt);
    uivlyt->addWidget(_textBrowser);

    connect(btnClear,&QPushButton::clicked,
           this,&HttpWindow::StClearTextBrowser);
    connect(_btnDownload, &QAbstractButton::clicked,
            this, &HttpWindow::StDownloadFile);
}

void HttpWindow::StDownloadFile()
{
    const QString urlSpec = _cbBoxUrl->currentText().trimmed();
    if (urlSpec.isEmpty()){
        return;
    }

    const QUrl newUrl = QUrl::fromUserInput(urlSpec);
    if (!newUrl.isValid()) {
        QString text = tr("Invalid URL: %1: %2").arg(urlSpec, newUrl.errorString());
        QMessageBox::information(this, tr("Error"),text);
        return;
    }

    _appSet->AppendUrl(urlSpec);
    if(-1 == _cbBoxUrl->findText(urlSpec)){
        _cbBoxUrl->addItem(urlSpec);
    }

    _urlId = 0;
    _urls.append(urlSpec);
    QTimer::singleShot(100,this,&HttpWindow::BeginToCrawl);
}

void HttpWindow::BeginToCrawl()
{
    if(_urlId >= _urls.count()){
        _textBrowser->append("End Crawl");
        return;
    }

    QString url;
    QUrl newUrl;
    for(int i=_urlId; i<_urls.count(); i++){
        url = _urls.at(i);
        _urlId++;
        newUrl = QUrl::fromUserInput(url);
        if (newUrl.isValid()) {
            break;
        }
    }

    if(!newUrl.isValid()){
        return;
    }

    _textBrowser->append(tr("------------------%1-------------------").arg(_urlId));
    StartRequest(newUrl);
}

void HttpWindow::StartRequest(const QUrl &requestedUrl)
{
    QNetworkReply *reply = _qnam.get(QNetworkRequest(requestedUrl));
    connect(reply,
            static_cast<void (QNetworkReply::*)(QNetworkReply::NetworkError)>(&QNetworkReply::error),
            this,&HttpWindow::StReplyError);
    connect(reply, &QNetworkReply::finished,
            this, &HttpWindow::StHttpFinished);
    connect(reply, &QIODevice::readyRead,
            this, &HttpWindow::StHttpReadyRead);
}

void HttpWindow::StReplyError(QNetworkReply::NetworkError code)
{
    QString error;
    error = tr("Reply Error Code:%1").arg(code);
    _textBrowser->append(error);

    QObject* obj = sender();
    obj->deleteLater();
}

void HttpWindow::StHttpFinished()
{
    QObject* obj = sender();
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(obj);
    QUrl url = reply->url();

    if (reply->error()) {
        reply->deleteLater();
        return;
    }

    QVariant redirectionTarget;
    redirectionTarget = reply->attribute(QNetworkRequest::RedirectionTargetAttribute);

    reply->deleteLater();
    if(redirectionTarget.isNull()){
        return;
    }

    QUrl redirectedUrl;
    redirectedUrl = url.resolved(redirectionTarget.toUrl());
    StartRequest(redirectedUrl);
}

void HttpWindow::StHttpReadyRead()
{
    QObject* obj = sender();
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(obj);

    QRegularExpression re;
    QByteArray htmlContent;
    QRegularExpressionMatch match;
    QRegularExpressionMatchIterator i;

    htmlContent = reply->readAll();
    re.setPattern(_regHtml);
    i = re.globalMatch(QString(htmlContent));
    while(i.hasNext()){
        match = i.next();
        if(_urls.count() > 50){
            break;
        }
        _urls.append(match.captured());
    }

    re.setPattern(_regImg);
    i = re.globalMatch(QString(htmlContent));
    while(i.hasNext()){
        match = i.next();
        _textBrowser->append(match.captured());
    }

    QScrollBar* bar = _textBrowser->verticalScrollBar();
    int max = bar->maximum();
    bar->setValue(max);

    QTimer::singleShot(3000,this,&HttpWindow::BeginToCrawl);
}

void HttpWindow::StClearTextBrowser()
{
    _textBrowser->clear();
}
