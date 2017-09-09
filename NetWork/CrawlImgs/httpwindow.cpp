#include <QtWidgets>
#include <QtNetwork>
#include <QUrl>

#include "httpwindow.h"

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

    _defaultFileLineEdit = new QLineEdit(defaultFileName,this);

    _downloadDirectoryLineEdit = new QLineEdit;
    QString downloadDirectory = QStandardPaths::writableLocation(QStandardPaths::TempLocation);
    if (downloadDirectory.isEmpty() || !QFileInfo(downloadDirectory).isDir()){
        downloadDirectory = QDir::currentPath();
    }
    _downloadDirectoryLineEdit->setText(QDir::toNativeSeparators(downloadDirectory));

    _downloadButton = new QPushButton(tr("Download"),this);
    _downloadButton->setDefault(true);

    QPushButton *quitButton = new QPushButton(tr("Quit"));
    quitButton->setAutoDefault(false);

    QFormLayout *formLayout = new QFormLayout;
    formLayout->addRow(tr("&URL:"), _urlLineEdit);
    formLayout->addRow(tr("&Download directory:"), _downloadDirectoryLineEdit);
    formLayout->addRow(tr("Default &file:"), _defaultFileLineEdit);

    QSpacerItem* spaceitem = new QSpacerItem(0,0,QSizePolicy::Ignored,
                                             QSizePolicy::MinimumExpanding);

    QDialogButtonBox *buttonBox = new QDialogButtonBox;
    buttonBox->addButton(_downloadButton, QDialogButtonBox::ActionRole);
    buttonBox->addButton(quitButton, QDialogButtonBox::RejectRole);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(formLayout);
    mainLayout->addItem(spaceitem);
    mainLayout->addWidget(buttonBox);

    connect(_urlLineEdit, &QLineEdit::textChanged,
            this, &HttpWindow::StEnableDownloadButton);

    connect(&_qnam, &QNetworkAccessManager::authenticationRequired,
            this, &HttpWindow::StAuthenticationRequired);
#ifndef QT_NO_SSL
    connect(&_qnam, &QNetworkAccessManager::sslErrors,
            this, &HttpWindow::StSslErrors);
#endif
    connect(_downloadButton, &QAbstractButton::clicked,
            this, &HttpWindow::StDownloadFile);
    connect(quitButton, &QAbstractButton::clicked,
            this, &QWidget::close);
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

    QString fileName = newUrl.fileName();
    if (fileName.isEmpty()){
        fileName = _defaultFileLineEdit->text().trimmed();
    }

    if (fileName.isEmpty()){
        fileName = defaultFileName;
    }

    QString downloadDirectory;
    downloadDirectory = QDir::cleanPath(_downloadDirectoryLineEdit->text().trimmed());
    if (!downloadDirectory.isEmpty() && QFileInfo(downloadDirectory).isDir()){
        fileName.prepend(downloadDirectory + '/');
    }

    if (QFile::exists(fileName)) {
        QString title,text;
        title = tr("Overwrite Existing File");
        text = tr("There already exists a file called %1 in the current directory. Overwrite?").arg(fileName);
        QMessageBox::StandardButton btn;
        btn = QMessageBox::question(this,title,text,QMessageBox::Yes|QMessageBox::No, QMessageBox::No);
        if (btn == QMessageBox::No){
            return;
        }

        QFile::remove(fileName);
    }

    _file = OpenFileForWrite(fileName);
    if (!_file){
        return;
    }

    _downloadButton->setEnabled(false);

    StartRequest(newUrl);
}

QFile *HttpWindow::OpenFileForWrite(const QString &fileName)
{
    QScopedPointer<QFile> file(new QFile(fileName));
    if (!file->open(QIODevice::WriteOnly)) {
        QMessageBox::information(this, tr("Error"),
                                 tr("Unable to save the file %1: %2.")
                                 .arg(QDir::toNativeSeparators(fileName),
                                      file->errorString()));
        return Q_NULLPTR;
    }
    return file.take();
}

void HttpWindow::StCancelDownload()
{
    _httpRequestAborted = true;
    _reply->abort();
    _downloadButton->setEnabled(true);
}

void HttpWindow::StHttpFinished()
{
    QFileInfo fi;
    if (_file) {
        fi.setFile(_file->fileName());
        _file->close();
        delete _file;
        _file = Q_NULLPTR;
    }

    if (_httpRequestAborted) {
        _reply->deleteLater();
        _reply = Q_NULLPTR;
        return;
    }

    if (_reply->error()) {
        QFile::remove(fi.absoluteFilePath());
#if 0
        _statusLabel->setText(tr("Download failed:\n%1.").arg(_reply->errorString()));
#endif
        _downloadButton->setEnabled(true);
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
            _downloadButton->setEnabled(true);
            return;
        }
        _file = OpenFileForWrite(fi.absoluteFilePath());
        if (!_file) {
            _downloadButton->setEnabled(true);
            return;
        }
        StartRequest(redirectedUrl);
        return;
    }
#if 0
    QString dir = QDir::toNativeSeparators(fi.absolutePath());
    QString text = tr("Downloaded %1 bytes to %2\nin\n%3")
            .arg(fi.size())
            .arg(fi.fileName(),QDir::toNativeSeparators(fi.absolutePath()));
    _statusLabel->setText(text);

    if (_launchCheckBox->isChecked())
        QDesktopServices::openUrl(QUrl::fromLocalFile(fi.absoluteFilePath()));
#endif
    _downloadButton->setEnabled(true);
}

void HttpWindow::StHttpReadyRead()
{
    // this slot gets called every time the QNetworkReply has new data.
    // We read all of its new data and write it into the file.
    // That way we use less RAM than when reading it at the finished()
    // signal of the QNetworkReply
    if (_file)
        _file->write(_reply->readAll());
}

void HttpWindow::StEnableDownloadButton()
{
    _downloadButton->setEnabled(!_urlLineEdit->text().isEmpty());
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
