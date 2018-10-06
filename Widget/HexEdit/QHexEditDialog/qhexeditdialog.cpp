#include "qhexeditdialog.h"

#include <QtCore>
#include <QtWidgets>

QHexEditDialog::QHexEditDialog()
{
    setAcceptDrops( true );

    init();

    setCurrentFile("");
}

void QHexEditDialog::closeEvent(QCloseEvent *)
{
    writeSettings();
}

void QHexEditDialog::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasUrls()) {
        event->accept();
    }
}

void QHexEditDialog::dropEvent(QDropEvent *event)
{
    if (event->mimeData()->hasUrls()) {
        QList<QUrl> urls = event->mimeData()->urls();
        QString filePath = urls.at(0).toLocalFile();
        loadFile(filePath);
        event->accept();
    }
}

void QHexEditDialog::contextMenuEvent(QContextMenuEvent *event)
{
    _contextMenu->exec(event->globalPos());
}

void QHexEditDialog::about()
{
   QMessageBox::about(this, tr("About QHexEdit"), tr(""));
}

void QHexEditDialog::dataChanged()
{
    setWindowModified(_hexEdit->isModified());
}

void QHexEditDialog::open()
{
    QString fileName = QFileDialog::getOpenFileName(this);
    if (!fileName.isEmpty()) {
        loadFile(fileName);
    }
}

void QHexEditDialog::optionsAccepted()
{
    writeSettings();
    readSettings();
}

void QHexEditDialog::findNext()
{
    searchDialog->findNext();
}

bool QHexEditDialog::save()
{
    if (isUntitled) {
        return saveAs();
    } else {
        return saveFile(curFile);
    }
}

bool QHexEditDialog::saveAs()
{
    QString fileName;
    fileName = QFileDialog::getSaveFileName(this, tr("Save As"),
                                            curFile);
    if (fileName.isEmpty()){
        return false;
    }

    return saveFile(fileName);
}

void QHexEditDialog::saveSelectionToReadableFile()
{
    QString fileName;
    fileName = QFileDialog::getSaveFileName(this, tr("Save To Readable File"));
    if("" == fileName) {
        return;
    }

    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("QHexEdit"),
                             tr("Cannot write file %1:\n%2.")
                             .arg(fileName)
                             .arg(file.errorString()));
        return;
    }

    QApplication::setOverrideCursor(Qt::WaitCursor);
    file.write(_hexEdit->selectionToReadableString().toLatin1());
    QApplication::restoreOverrideCursor();
    _statusBar->showMessage(tr("File saved"), 2000);
}

void QHexEditDialog::saveToReadableFile()
{
    QString fileName;
    fileName = QFileDialog::getSaveFileName(this, tr("Save To Readable File"));
    if("" == fileName){
        return;
    }

    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("QHexEdit"),
                             tr("Cannot write file %1:\n%2.")
                             .arg(fileName)
                             .arg(file.errorString()));
        return;
    }

    QApplication::setOverrideCursor(Qt::WaitCursor);
    file.write(_hexEdit->toReadableString().toLatin1());
    QApplication::restoreOverrideCursor();
    _statusBar->showMessage(tr("File saved"), 2000);
}

void QHexEditDialog::setAddress(qint64 address)
{
    _lbAddress->setText(QString("%1").arg(address, 1, 16));
}

void QHexEditDialog::setOverwriteMode(bool mode)
{
    QSettings settings;
    settings.setValue("OverwriteMode", mode);

    if (mode) {
        _lbOverwriteMode->setText(tr("Overwrite"));
    } else {
        _lbOverwriteMode->setText(tr("Insert"));
    }
}

void QHexEditDialog::setSize(qint64 size)
{
#if 0
    lbSize->setText(QString("%1").arg(size));
#endif
}

void QHexEditDialog::showOptionsDialog()
{
    optionsDialog->show();
}

void QHexEditDialog::showSearchDialog()
{
    searchDialog->show();
}

void QHexEditDialog::init()
{
    setAttribute(Qt::WA_DeleteOnClose);

    _contextMenu = new QMenu(this);

    optionsDialog = new OptionsDialog(this);
    connect(optionsDialog, SIGNAL(accepted()), this, SLOT(optionsAccepted()));

    isUntitled = true;

    QVBoxLayout *vlyt;
    QStatusBar *&statusBar = _statusBar;

    /// hex edit
    _hexEdit  = new QHexEdit;
    statusBar = new QStatusBar(this);
    statusBar->setSizeGripEnabled(false);

    /// layout
    vlyt = new QVBoxLayout;
    vlyt->setMargin(0);
    vlyt->addWidget(_hexEdit);
    vlyt->addWidget(statusBar);
    setLayout(vlyt);

    connect(_hexEdit, SIGNAL(overwriteModeChanged(bool)), this, SLOT(setOverwriteMode(bool)));
    connect(_hexEdit, SIGNAL(dataChanged()), this, SLOT(dataChanged()));


    /// after new QHexEdit
    searchDialog = new SearchDialog(_hexEdit, this);

    initActions();
    initContextMenu(_contextMenu);
    initStatusBar(statusBar);

    readSettings();
#if 0
    setUnifiedTitleAndToolBarOnMac(true);
#endif
}

void QHexEditDialog::initActions()
{
    QAction *&openAct = _openAct;
    openAct = new QAction(QIcon(":/images/open.png"), tr("&Open..."), this);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip(tr("Open an existing file"));
    connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

    QAction *&saveAct = _saveAct;
    saveAct = new QAction(QIcon(":/images/save.png"), tr("&Save"), this);
    saveAct->setShortcuts(QKeySequence::Save);
    saveAct->setStatusTip(tr("Save the document to disk"));
    connect(saveAct, SIGNAL(triggered()), this, SLOT(save()));

    QAction *&saveAsAct = _saveAsAct;
    saveAsAct = new QAction(tr("Save &As..."), this);
    saveAsAct->setShortcuts(QKeySequence::SaveAs);
    saveAsAct->setStatusTip(tr("Save the document under a new name"));
    connect(saveAsAct, SIGNAL(triggered()), this, SLOT(saveAs()));

    QAction *&saveReadable = _saveReadable;
    saveReadable = new QAction(tr("Save &Readable..."), this);
    saveReadable->setStatusTip(tr("Save document in readable form"));
    connect(saveReadable, SIGNAL(triggered()), this, SLOT(saveToReadableFile()));

    QAction *&saveSelectionReadable = _saveSelectionReadable;
    saveSelectionReadable = new QAction(tr("&Save Selection Readable..."), this);
    saveSelectionReadable->setStatusTip(tr("Save selection in readable form"));
    connect(saveSelectionReadable, SIGNAL(triggered()), this, SLOT(saveSelectionToReadableFile()));


    QAction *&undoAct = _undoAct;
    undoAct = new QAction(QIcon(":/images/undo.png"), tr("&Undo"), this);
    undoAct->setShortcuts(QKeySequence::Undo);
    connect(undoAct, SIGNAL(triggered()), _hexEdit, SLOT(undo()));

    QAction *&redoAct = _redoAct;
    redoAct = new QAction(QIcon(":/images/redo.png"), tr("&Redo"), this);
    redoAct->setShortcuts(QKeySequence::Redo);
    connect(redoAct, SIGNAL(triggered()), _hexEdit, SLOT(redo()));


    QAction *&findAct = _findAct;
    findAct = new QAction(QIcon(":/images/find.png"), tr("&Find/Replace"), this);
    findAct->setShortcuts(QKeySequence::Find);
    findAct->setStatusTip(tr("Show the Dialog for finding and replacing"));
    connect(findAct, SIGNAL(triggered()), this, SLOT(showSearchDialog()));

    QAction *&findNextAct = _findNextAct;
    findNextAct = new QAction(tr("Find &next"), this);
    findNextAct->setShortcuts(QKeySequence::FindNext);
    findNextAct->setStatusTip(tr("Find next occurrence of the searched pattern"));
    connect(findNextAct, SIGNAL(triggered()), this, SLOT(findNext()));


    QAction *&optionsAct = _optionsAct;
    optionsAct = new QAction(tr("&Options"), this);
    optionsAct->setStatusTip(tr("Show the Dialog to select applications options"));
    connect(optionsAct, SIGNAL(triggered()), this, SLOT(showOptionsDialog()));


    QAction *&aboutAct = _aboutAct;
    aboutAct = new QAction(tr("&About"), this);
    aboutAct->setStatusTip(tr("Show the application's About box"));
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

    QAction *&aboutQtAct = _aboutQtAct;
    aboutQtAct = new QAction(tr("About &Qt"), this);
    aboutQtAct->setStatusTip(tr("Show the Qt library's About box"));
    connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));


    QAction *&exitAct = _exitAct;
    exitAct = new QAction(tr("E&xit"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    exitAct->setStatusTip(tr("Exit the application"));
    connect(exitAct, SIGNAL(triggered()), qApp, SLOT(closeAllWindows()));
}

void QHexEditDialog::initContextMenu(QMenu *menu)
{
    menu->addAction(_openAct);
    menu->addAction(_saveAct);
    menu->addAction(_saveAsAct);
    menu->addAction(_saveReadable);
    menu->addAction(_saveSelectionReadable);
    menu->addSeparator();

    menu->addAction(_undoAct);
    menu->addAction(_redoAct);

    menu->addSeparator();

    menu->addAction(_findAct);
    menu->addAction(_findNextAct);

    menu->addAction(_optionsAct);

    menu->addSeparator();

    menu->addAction(_aboutAct);
    menu->addAction(_aboutQtAct);

    menu->addSeparator();
    menu->addAction(_exitAct);
}

void QHexEditDialog::initStatusBar(QStatusBar *statusBar)
{
    /// Address Label
    QLabel *&lbAddressName = _lbAddressName;
    lbAddressName = new QLabel(this);
    lbAddressName->setText(tr("Address:"));
    statusBar->addPermanentWidget(lbAddressName);

    QLabel *&lbAddress = _lbAddress;
    lbAddress = new QLabel(this);
    lbAddress->setFrameShape(QFrame::Panel);
    lbAddress->setFrameShadow(QFrame::Sunken);
    lbAddress->setMinimumWidth(70);
    statusBar->addPermanentWidget(lbAddress);
    connect(_hexEdit, SIGNAL(currentAddressChanged(qint64)), this, SLOT(setAddress(qint64)));

    /// Size Label
    QLabel *&lbSizeName = _lbSizeName;
    lbSizeName = new QLabel(this);
    lbSizeName->setText(tr("Size:"));
    statusBar->addPermanentWidget(lbSizeName);

    QLabel *&lbSize = _lbSize;
    lbSize = new QLabel(this);
    lbSize->setFrameShape(QFrame::Panel);
    lbSize->setFrameShadow(QFrame::Sunken);
    lbSize->setMinimumWidth(70);
    statusBar->addPermanentWidget(lbSize);
    connect(_hexEdit, SIGNAL(currentSizeChanged(qint64)), this, SLOT(setSize(qint64)));

    /// Overwrite Mode Label
    QLabel *&lbOverwriteModeName = _lbOverwriteModeName;
    lbOverwriteModeName = new QLabel(this);
    lbOverwriteModeName->setText(tr("Mode:"));
    statusBar->addPermanentWidget(lbOverwriteModeName);

    QLabel *&lbOverwriteMode = _lbOverwriteMode;
    lbOverwriteMode = new QLabel(this);
    lbOverwriteMode->setFrameShape(QFrame::Panel);
    lbOverwriteMode->setFrameShadow(QFrame::Sunken);
    lbOverwriteMode->setMinimumWidth(70);
    statusBar->addPermanentWidget(lbOverwriteMode);

    setOverwriteMode(_hexEdit->overwriteMode());
    statusBar->showMessage(tr("Ready"), 2000);
}

#if 0
void QHexEditDialog::createActions()
{
    openAct = new QAction(QIcon(":/images/open.png"), tr("&Open..."), this);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip(tr("Open an existing file"));
    connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

    saveAct = new QAction(QIcon(":/images/save.png"), tr("&Save"), this);
    saveAct->setShortcuts(QKeySequence::Save);
    saveAct->setStatusTip(tr("Save the document to disk"));
    connect(saveAct, SIGNAL(triggered()), this, SLOT(save()));

    saveAsAct = new QAction(tr("Save &As..."), this);
    saveAsAct->setShortcuts(QKeySequence::SaveAs);
    saveAsAct->setStatusTip(tr("Save the document under a new name"));
    connect(saveAsAct, SIGNAL(triggered()), this, SLOT(saveAs()));

    saveReadable = new QAction(tr("Save &Readable..."), this);
    saveReadable->setStatusTip(tr("Save document in readable form"));
    connect(saveReadable, SIGNAL(triggered()), this, SLOT(saveToReadableFile()));

    exitAct = new QAction(tr("E&xit"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    exitAct->setStatusTip(tr("Exit the application"));
    connect(exitAct, SIGNAL(triggered()), qApp, SLOT(closeAllWindows()));

    undoAct = new QAction(QIcon(":/images/undo.png"), tr("&Undo"), this);
    undoAct->setShortcuts(QKeySequence::Undo);
    connect(undoAct, SIGNAL(triggered()), hexEdit, SLOT(undo()));

    redoAct = new QAction(QIcon(":/images/redo.png"), tr("&Redo"), this);
    redoAct->setShortcuts(QKeySequence::Redo);
    connect(redoAct, SIGNAL(triggered()), hexEdit, SLOT(redo()));

    saveSelectionReadable = new QAction(tr("&Save Selection Readable..."), this);
    saveSelectionReadable->setStatusTip(tr("Save selection in readable form"));
    connect(saveSelectionReadable, SIGNAL(triggered()), this, SLOT(saveSelectionToReadableFile()));

    aboutAct = new QAction(tr("&About"), this);
    aboutAct->setStatusTip(tr("Show the application's About box"));
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

    aboutQtAct = new QAction(tr("About &Qt"), this);
    aboutQtAct->setStatusTip(tr("Show the Qt library's About box"));
    connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

    findAct = new QAction(QIcon(":/images/find.png"), tr("&Find/Replace"), this);
    findAct->setShortcuts(QKeySequence::Find);
    findAct->setStatusTip(tr("Show the Dialog for finding and replacing"));
    connect(findAct, SIGNAL(triggered()), this, SLOT(showSearchDialog()));

    findNextAct = new QAction(tr("Find &next"), this);
    findNextAct->setShortcuts(QKeySequence::FindNext);
    findNextAct->setStatusTip(tr("Find next occurrence of the searched pattern"));
    connect(findNextAct, SIGNAL(triggered()), this, SLOT(findNext()));

    optionsAct = new QAction(tr("&Options"), this);
    optionsAct->setStatusTip(tr("Show the Dialog to select applications options"));
    connect(optionsAct, SIGNAL(triggered()), this, SLOT(showOptionsDialog()));
}
#endif

#if 0
void QHexEditDialog::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);
    fileMenu->addAction(saveAsAct);
    fileMenu->addAction(saveReadable);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    editMenu = menuBar()->addMenu(tr("&Edit"));
    editMenu->addAction(undoAct);
    editMenu->addAction(redoAct);
    editMenu->addAction(saveSelectionReadable);
    editMenu->addSeparator();
    editMenu->addAction(findAct);
    editMenu->addAction(findNextAct);
    editMenu->addSeparator();
    editMenu->addAction(optionsAct);
    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);
}
#endif

#if 0
void QHexEditDialog::createStatusBar()
{
    // Address Label
    lbAddressName = new QLabel();
    lbAddressName->setText(tr("Address:"));
    statusBar()->addPermanentWidget(lbAddressName);
    lbAddress = new QLabel();
    lbAddress->setFrameShape(QFrame::Panel);
    lbAddress->setFrameShadow(QFrame::Sunken);
    lbAddress->setMinimumWidth(70);
    statusBar()->addPermanentWidget(lbAddress);
    connect(hexEdit, SIGNAL(currentAddressChanged(qint64)), this, SLOT(setAddress(qint64)));

    // Size Label
    lbSizeName = new QLabel();
    lbSizeName->setText(tr("Size:"));
    statusBar()->addPermanentWidget(lbSizeName);
    lbSize = new QLabel();
    lbSize->setFrameShape(QFrame::Panel);
    lbSize->setFrameShadow(QFrame::Sunken);
    lbSize->setMinimumWidth(70);
    statusBar()->addPermanentWidget(lbSize);
    connect(hexEdit, SIGNAL(currentSizeChanged(qint64)), this, SLOT(setSize(qint64)));

    // Overwrite Mode Label
    lbOverwriteModeName = new QLabel();
    lbOverwriteModeName->setText(tr("Mode:"));
    statusBar()->addPermanentWidget(lbOverwriteModeName);
    lbOverwriteMode = new QLabel();
    lbOverwriteMode->setFrameShape(QFrame::Panel);
    lbOverwriteMode->setFrameShadow(QFrame::Sunken);
    lbOverwriteMode->setMinimumWidth(70);
    statusBar()->addPermanentWidget(lbOverwriteMode);
    setOverwriteMode(hexEdit->overwriteMode());

    statusBar()->showMessage(tr("Ready"), 2000);
}
#endif

#if 0
void QHexEditDialog::createToolBars()
{
    fileToolBar = addToolBar(tr("File"));
    fileToolBar->addAction(openAct);
    fileToolBar->addAction(saveAct);
    editToolBar = addToolBar(tr("Edit"));
    editToolBar->addAction(undoAct);
    editToolBar->addAction(redoAct);
    editToolBar->addAction(findAct);
}
#endif

void QHexEditDialog::loadFile(const QString &fileName)
{
    file.setFileName(fileName);
    if (!_hexEdit->setData(file)) {
        QMessageBox::warning(this, tr("QHexEdit"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(fileName)
                             .arg(file.errorString()));
        return;
    }
    setCurrentFile(fileName);
#if 0
    statusBar()->showMessage(tr("File loaded"), 2000);
#endif
}

void QHexEditDialog::readSettings()
{
    QSettings settings;
    QPoint pos = settings.value("pos", QPoint(200, 200)).toPoint();
    QSize size = settings.value("size", QSize(610, 460)).toSize();
    move(pos);
    resize(size);

    _hexEdit->setAddressArea(settings.value("AddressArea").toBool());
    _hexEdit->setAsciiArea(settings.value("AsciiArea").toBool());
    _hexEdit->setHighlighting(settings.value("Highlighting").toBool());
    _hexEdit->setOverwriteMode(settings.value("OverwriteMode").toBool());
    _hexEdit->setReadOnly(settings.value("ReadOnly").toBool());

    _hexEdit->setHighlightingColor(settings.value("HighlightingColor").value<QColor>());
    _hexEdit->setAddressAreaColor(settings.value("AddressAreaColor").value<QColor>());
    _hexEdit->setSelectionColor(settings.value("SelectionColor").value<QColor>());
    _hexEdit->setFont(settings.value("WidgetFont").value<QFont>());

    _hexEdit->setAddressWidth(settings.value("AddressAreaWidth").toInt());
    _hexEdit->setBytesPerLine(settings.value("BytesPerLine").toInt());
}

bool QHexEditDialog::saveFile(const QString &fileName)
{
    QString tmpFileName = fileName + ".~tmp";

    QApplication::setOverrideCursor(Qt::WaitCursor);
    QFile file(tmpFileName);
    bool ok = _hexEdit->write(file);
    if (QFile::exists(fileName))
        ok = QFile::remove(fileName);
    if (ok)
    {
        file.setFileName(tmpFileName);
        ok = file.copy(fileName);
        if (ok)
            ok = QFile::remove(tmpFileName);
    }
    QApplication::restoreOverrideCursor();

    if (!ok) {
        QMessageBox::warning(this, tr("QHexEdit"),
                             tr("Cannot write file %1.")
                             .arg(fileName));
        return false;
    }

    setCurrentFile(fileName);
#if 0
    statusBar()->showMessage(tr("File saved"), 2000);
#endif
    return true;
}

void QHexEditDialog::setCurrentFile(const QString &fileName)
{
    curFile = QFileInfo(fileName).canonicalFilePath();
    isUntitled = fileName.isEmpty();
    setWindowModified(false);
    if (fileName.isEmpty()) {
        setWindowFilePath("HexEdit");
    } else {
        setWindowFilePath(curFile + " - HexEdit");
    }
}

QString QHexEditDialog::strippedName(const QString &fullFileName)
{
    return QFileInfo(fullFileName).fileName();
}

void QHexEditDialog::writeSettings()
{
    QSettings settings;
    settings.setValue("pos", pos());
    settings.setValue("size", size());
}
