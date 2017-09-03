#include <QtWidgets>
#include <QtNetwork>
#include <QUrl>

#include "httpwindow.h"
#include "ui_authenticationdialog.h"

#ifndef QT_NO_SSL
static const char defaultUrl[] = "https://www.qt.io/";
#else
static const char defaultUrl[] = "http://www.qt.io/";
#endif
static const char defaultFileName[] = "index.html";

HttpWindow::HttpWindow(QWidget *parent)
    : QWidget(parent)
    , _statusLabel(new QLabel(tr("Please enter the URL of a file you want to download.\n\n"), this))
    , _urlLineEdit(new QLineEdit(defaultUrl))
    , _downloadButton(new QPushButton(tr("Download")))
    , _launchCheckBox(new QCheckBox("Launch file"))
    , _defaultFileLineEdit(new QLineEdit(defaultFileName))
    , _downloadDirectoryLineEdit(new QLineEdit)
    , _reply(Q_NULLPTR)
    , _file(Q_NULLPTR)
    , _httpRequestAborted(false)
{
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    setWindowTitle(tr("HTTP"));

    connect(&_qnam, &QNetworkAccessManager::authenticationRequired,
            this, &HttpWindow::StAuthenticationRequired);
#ifndef QT_NO_SSL
    connect(&_qnam, &QNetworkAccessManager::sslErrors,
            this, &HttpWindow::StSslErrors);
#endif

    QFormLayout *formLayout = new QFormLayout;
    _urlLineEdit->setClearButtonEnabled(true);
    connect(_urlLineEdit, &QLineEdit::textChanged,
            this, &HttpWindow::StEnableDownloadButton);
    formLayout->addRow(tr("&URL:"), _urlLineEdit);
    QString downloadDirectory = QStandardPaths::writableLocation(QStandardPaths::TempLocation);
    if (downloadDirectory.isEmpty() || !QFileInfo(downloadDirectory).isDir())
        downloadDirectory = QDir::currentPath();
    _downloadDirectoryLineEdit->setText(QDir::toNativeSeparators(downloadDirectory));
    formLayout->addRow(tr("&Download directory:"), _downloadDirectoryLineEdit);
    formLayout->addRow(tr("Default &file:"), _defaultFileLineEdit);
    _launchCheckBox->setChecked(true);
    formLayout->addRow(_launchCheckBox);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(formLayout);

    mainLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::Ignored, QSizePolicy::MinimumExpanding));

    _statusLabel->setWordWrap(true);
    mainLayout->addWidget(_statusLabel);

    _downloadButton->setDefault(true);
    connect(_downloadButton, &QAbstractButton::clicked, this, &HttpWindow::StDownloadFile);
    QPushButton *quitButton = new QPushButton(tr("Quit"));
    quitButton->setAutoDefault(false);
    connect(quitButton, &QAbstractButton::clicked, this, &QWidget::close);
    QDialogButtonBox *buttonBox = new QDialogButtonBox;
    buttonBox->addButton(_downloadButton, QDialogButtonBox::ActionRole);
    buttonBox->addButton(quitButton, QDialogButtonBox::RejectRole);
    mainLayout->addWidget(buttonBox);

    _urlLineEdit->setFocus();
}

void HttpWindow::StartRequest(const QUrl &requestedUrl)
{
    _url = requestedUrl;
    _httpRequestAborted = false;

    _reply = _qnam.get(QNetworkRequest(_url));
    connect(_reply, &QNetworkReply::finished, this, &HttpWindow::StHttpFinished);
    connect(_reply, &QIODevice::readyRead, this, &HttpWindow::StHttpReadyRead);

    ProgressDialog *progressDialog = new ProgressDialog(_url, this);
    progressDialog->setAttribute(Qt::WA_DeleteOnClose);
    connect(progressDialog, &QProgressDialog::canceled, this, &HttpWindow::StCancelDownload);
    connect(_reply, &QNetworkReply::downloadProgress, progressDialog, &ProgressDialog::StNetworkReplyProgress);
    connect(_reply, &QNetworkReply::finished, progressDialog, &ProgressDialog::hide);
    progressDialog->show();

    _statusLabel->setText(tr("Downloading %1...").arg(_url.toString()));
}

void HttpWindow::StDownloadFile()
{
    const QString urlSpec = _urlLineEdit->text().trimmed();
    if (urlSpec.isEmpty())
        return;

    const QUrl newUrl = QUrl::fromUserInput(urlSpec);
    if (!newUrl.isValid()) {
        QMessageBox::information(this, tr("Error"),
                                 tr("Invalid URL: %1: %2").arg(urlSpec, newUrl.errorString()));
        return;
    }

    QString fileName = newUrl.fileName();
    if (fileName.isEmpty())
        fileName = _defaultFileLineEdit->text().trimmed();
    if (fileName.isEmpty())
        fileName = defaultFileName;
    QString downloadDirectory = QDir::cleanPath(_downloadDirectoryLineEdit->text().trimmed());
    if (!downloadDirectory.isEmpty() && QFileInfo(downloadDirectory).isDir())
        fileName.prepend(downloadDirectory + '/');
    if (QFile::exists(fileName)) {
        if (QMessageBox::question(this, tr("Overwrite Existing File"),
                                  tr("There already exists a file called %1 in "
                                     "the current directory. Overwrite?").arg(fileName),
                                  QMessageBox::Yes|QMessageBox::No, QMessageBox::No)
            == QMessageBox::No)
            return;
        QFile::remove(fileName);
    }

    _file = OpenFileForWrite(fileName);
    if (!_file)
        return;

    _downloadButton->setEnabled(false);

    // schedule the request
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
    _statusLabel->setText(tr("Download canceled."));
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
        _statusLabel->setText(tr("Download failed:\n%1.").arg(_reply->errorString()));
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

    _statusLabel->setText(tr("Downloaded %1 bytes to %2\nin\n%3")
                         .arg(fi.size()).arg(fi.fileName(), QDir::toNativeSeparators(fi.absolutePath())));
    if (_launchCheckBox->isChecked())
        QDesktopServices::openUrl(QUrl::fromLocalFile(fi.absoluteFilePath()));
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
