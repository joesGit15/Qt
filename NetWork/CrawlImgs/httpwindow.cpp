#include "httpwindow.h"

#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QDialogButtonBox>

#include <QtCore/QDir>
#include <QtCore/QFileInfo>
#include <QtCore/QStandardPaths>
#include <QtCore/QRegularExpression>
#include <QtCore/QRegularExpressionMatch>
#include <QtCore/QRegularExpressionMatchIterator>

#include <QtNetwork/QAuthenticator>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>

#ifndef QT_NO_SSL
static const char defaultUrl[] = "https://www.qt.io/";
#else
static const char defaultUrl[] = "http://www.qt.io/";
#endif

static const char defaultFileName[] = "index.html";

HttpWindow::HttpWindow(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle(tr("HTTP"));
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

    _urlLineEdit = new QLineEdit(defaultUrl,this);
    _urlLineEdit->setClearButtonEnabled(true);

    _btnDownload = new QPushButton(tr("Download"),this);
    _btnDownload->setDefault(true);

    QFormLayout *formLayout = new QFormLayout;
    formLayout->addRow(tr("&URL:"), _urlLineEdit);

    _textBrowser = new QTextBrowser(this);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(formLayout);
    mainLayout->addWidget(_textBrowser);
    mainLayout->addWidget(_btnDownload);

    connect(_urlLineEdit, &QLineEdit::textChanged,
            this, &HttpWindow::StEnableDownloadButton);

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
    connect(_reply, &QNetworkReply::finished,
            this, &HttpWindow::StHttpFinished);
    connect(_reply, &QIODevice::readyRead,
            this, &HttpWindow::StHttpReadyRead);

    ProgressDialog *progressDialog = new ProgressDialog(_url, this);
    progressDialog->setAttribute(Qt::WA_DeleteOnClose);

    connect(progressDialog, &QProgressDialog::canceled,
            this, &HttpWindow::StCancelDownload);
    connect(_reply, &QNetworkReply::downloadProgress,
            progressDialog, &ProgressDialog::StNetworkReplyProgress);
    connect(_reply, &QNetworkReply::finished,
            progressDialog, &ProgressDialog::hide);

    progressDialog->show();
}

void HttpWindow::StDownloadFile()
{
    const QString urlSpec = _urlLineEdit->text().trimmed();
    if (urlSpec.isEmpty()){
        return;
    }

    const QUrl newUrl = QUrl::fromUserInput(urlSpec);
    if (!newUrl.isValid()) {
        QString text = tr("Invalid URL: %1: %2").arg(urlSpec, newUrl.errorString());
        QMessageBox::information(this, tr("Error"),text);
        return;
    }

    _btnDownload->setEnabled(false);
    StartRequest(newUrl);
}

void HttpWindow::StCancelDownload()
{
    _httpRequestAborted = true;
    _reply->abort();
    _btnDownload->setEnabled(true);
}

void HttpWindow::StHttpFinished()
{
    if (_httpRequestAborted) {
        _reply->deleteLater();
        _reply = Q_NULLPTR;
        return;
    }

    if (_reply->error()) {
        _btnDownload->setEnabled(true);
        _reply->deleteLater();
        _reply = Q_NULLPTR;
        return;
    }

    const QVariant redirectionTarget = _reply->attribute(QNetworkRequest::RedirectionTargetAttribute);

    _reply->deleteLater();
    _reply = Q_NULLPTR;

    if (!redirectionTarget.isNull()) {
        const QUrl redirectedUrl = _url.resolved(redirectionTarget.toUrl());
        if (QMessageBox::question(this, tr("Redirect"),
                                  tr("Redirect to %1 ?").arg(redirectedUrl.toString()),
                                  QMessageBox::Yes | QMessageBox::No) == QMessageBox::No) {
            _btnDownload->setEnabled(true);
            return;
        }

        StartRequest(redirectedUrl);
        return;
    }

    _btnDownload->setEnabled(true);
}

void HttpWindow::StHttpReadyRead()
{
    QRegularExpressionMatch match;
    QRegularExpression re("(https?|ftp|file)://[-A-Za-z0-9+&@#/%?=~_|!:,.;]+[-A-Za-z0-9+&@#/%=~_|]");
    QRegularExpressionMatchIterator i = re.globalMatch(QString(_reply->readAll()));

    while(i.hasNext()){
        match = i.next();
        _textBrowser->append(match.captured());
    }
}

void HttpWindow::StEnableDownloadButton()
{
    _btnDownload->setEnabled(!_urlLineEdit->text().isEmpty());
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

ProgressDialog::ProgressDialog(const QUrl &url, QWidget *parent)
  : QProgressDialog(parent)
{
    setWindowTitle(tr("Download Progress"));
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    setLabelText(tr("Downloading %1.").arg(url.toDisplayString()));
    setMinimum(0);
    setValue(0);
    setMinimumDuration(0);
}

void ProgressDialog::StNetworkReplyProgress(qint64 bytesRead, qint64 totalBytes)
{
    setMaximum(totalBytes);
    setValue(bytesRead);
}
