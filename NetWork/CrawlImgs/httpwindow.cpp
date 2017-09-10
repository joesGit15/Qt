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

    QStringList regs;
    regs << "(https?|ftp|file)://[-A-Za-z0-9+&@#/%?=~_|!:,.;]+[-A-Za-z0-9+&@#/%=~_|]";
    _cbBoxReg = new QComboBox(this);
    _cbBoxReg->setEditable(true);
    for(const QString& reg:regs){
        _cbBoxReg->addItem(reg);
    }

    QFormLayout *formLayout = new QFormLayout;
    formLayout->addRow(tr("&URL:"), _cbBoxUrl);
    formLayout->addRow(tr("&Reg:"), _cbBoxReg);

    _btnDownload = new QPushButton(tr("Download"),this);
    QHBoxLayout* hlyt = new QHBoxLayout;
    hlyt->addStretch(1);
    hlyt->addWidget(_btnDownload);

    _textBrowser = new QTextBrowser(this);

    QVBoxLayout *uivlyt = new QVBoxLayout(this);
    uivlyt->addLayout(formLayout);
    uivlyt->addLayout(hlyt);
    uivlyt->addWidget(_textBrowser);

    connect(&_qnam, &QNetworkAccessManager::authenticationRequired,
            this, &HttpWindow::StAuthenticationRequired);
#ifndef QT_NO_SSL
    connect(&_qnam, &QNetworkAccessManager::sslErrors,
            this, &HttpWindow::StSslErrors);
#endif
    connect(_btnDownload, &QAbstractButton::clicked,
            this, &HttpWindow::StDownloadFile);
}

void HttpWindow::StartRequest(const QUrl &requestedUrl)
{
    _url = requestedUrl;
    _httpRequestAborted = false;

    _reply = _qnam.get(QNetworkRequest(_url));
    connect(_reply,
            static_cast<void (QNetworkReply::*)(QNetworkReply::NetworkError)>(&QNetworkReply::error),
            this,&HttpWindow::StReplyError);
    connect(_reply, &QNetworkReply::finished,
            this, &HttpWindow::StHttpFinished);
    connect(_reply, &QIODevice::readyRead,
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

    StartRequest(newUrl);
}

void HttpWindow::StCancelDownload()
{
    _httpRequestAborted = true;
    _reply->abort();
}

void HttpWindow::StHttpFinished()
{
    if (_httpRequestAborted || _reply->error()) {
        _reply->deleteLater();
        _reply = 0;
        return;
    }

    QVariant redirectionTarget;
    redirectionTarget = _reply->attribute(QNetworkRequest::RedirectionTargetAttribute);

    _reply->deleteLater();
    _reply = 0;

    if(redirectionTarget.isNull()){
        return;
    }

    QUrl redirectedUrl;
    redirectedUrl = _url.resolved(redirectionTarget.toUrl());
    QString msg = tr("Redirect to %1 ?").arg(redirectedUrl.toString());

    QMessageBox::StandardButton sbtn;
    sbtn = QMessageBox::question(this,tr("Redirect"),msg,QMessageBox::Yes|QMessageBox::No);
    if (sbtn == QMessageBox::Yes) {
        StartRequest(redirectedUrl);
    }
}

void HttpWindow::StHttpReadyRead()
{
    QString regStr = _cbBoxReg->currentText().trimmed();

    QRegularExpressionMatch match;
    QRegularExpression re(regStr);
    QRegularExpressionMatchIterator i = re.globalMatch(QString(_reply->readAll()));

    while(i.hasNext()){
        match = i.next();
        _textBrowser->append(match.captured());
    }
    QScrollBar* bar = _textBrowser->verticalScrollBar();
    int max = bar->maximum();
    bar->setValue(max);
}

void HttpWindow::StAuthenticationRequired(QNetworkReply*,QAuthenticator *authenticator)
{
#if 0
    Ui::Dialog ui;
    QDialog authenticationDialog;
    ui.setupUi(&authenticationDialog);

    authenticationDialog.adjustSize();
    ui.siteDescription->setText(tr("%1 at %2").arg(authenticator->realm(), _url.host()));

    ui.userEdit->setText(_url.userName());
    ui.passwordEdit->setText(_url.password());

    if (authenticationDialog.exec() == QDialog::Accepted) {
        authenticator->setUser(ui.userEdit->text());
        authenticator->setPassword(ui.passwordEdit->text());
    }
#endif
}

#ifndef QT_NO_SSL
void HttpWindow::StSslErrors(QNetworkReply*,const QList<QSslError> &errors)
{
    QString errorString;
    foreach (const QSslError &error, errors) {
        if (!errorString.isEmpty())
            errorString += '\n';
        errorString += error.errorString();
    }

    if (QMessageBox::warning(this, tr("SSL Errors"),
                             tr("One or more SSL errors has occurred:\n%1").arg(errorString),
                             QMessageBox::Ignore | QMessageBox::Abort) == QMessageBox::Ignore) {
        _reply->ignoreSslErrors();
    }
}
#endif
