#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDialog>

#include "../QHexEdit/qhexedit.h"
#include "optionsdialog.h"
#include "searchdialog.h"

QT_BEGIN_NAMESPACE
class QAction;
class QUndoStack;
class QLabel;
class QDragEnterEvent;
class QDropEvent;

class QMenu;
class QToolBar;
class QStatusBar;
QT_END_NAMESPACE

class QHexEditDialog : public QDialog
{
    Q_OBJECT

public:
    QHexEditDialog();

protected:
    void closeEvent(QCloseEvent *event);
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);
    void contextMenuEvent(QContextMenuEvent *event);

private slots:
    void about();
    void dataChanged();
    void open();
    void optionsAccepted();
    void findNext();
    bool save();
    bool saveAs();
    void saveSelectionToReadableFile();
    void saveToReadableFile();
    void setAddress(qint64 address);
    void setOverwriteMode(bool mode);
    void setSize(qint64 size);
    void showOptionsDialog();
    void showSearchDialog();

private:
    void init();
    void initActions();
    void initContextMenu(QMenu *menu);
    void initStatusBar(QStatusBar *statusBar);

#if 0
    void createActions();
    void createMenus();
    void createStatusBar();
    void createToolBars();
#endif

    void loadFile(const QString &fileName);
    void readSettings();
    bool saveFile(const QString &fileName);
    void setCurrentFile(const QString &fileName);
    QString strippedName(const QString &fullFileName);
    void writeSettings();

    QString curFile;
    QFile file;
    bool isUntitled;

#if 1
    QMenu *_contextMenu;

    QAction *_openAct;
    QAction *_saveAct;
    QAction *_saveAsAct;
    QAction *_saveReadable;
    QAction *_saveSelectionReadable;

    QAction *_undoAct;
    QAction *_redoAct;

    QAction *_findAct;
    QAction *_findNextAct;

    QAction *_optionsAct;

    QAction *_aboutAct;
    QAction *_aboutQtAct;

    QAction *_exitAct;
#else
    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *helpMenu;
    QAction *closeAct;
#endif

    QHexEdit *_hexEdit;
    OptionsDialog *optionsDialog;
    SearchDialog *searchDialog;

#if 0
    QLabel *lbAddress, *lbAddressName;
    QLabel *lbOverwriteMode, *lbOverwriteModeName;
    QLabel *lbSize, *lbSizeName;
#endif
};

#endif
