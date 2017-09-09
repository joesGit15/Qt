#include "progressdialog.h"

#include <QtWidgets/QPushButton>
#include <QtWidgets/QProgressBar>
#include <QtGui/QCloseEvent>

ProgressDialog::ProgressDialog(const QString& text,int maxNum, QWidget *parent)
    :QProgressDialog(parent)
{
    setWindowTitle(tr("进度窗体"));
    setLabelText(text);

    setCancelButtonText(tr(""));

    setRange(0,maxNum);
    setMinimumDuration(3000);

    setWindowModality(Qt::WindowModal);

    disconnect(this,SIGNAL(canceled()),this,SLOT(cancel()));

    /** (QLabel(), QProgressBar(), QTimer(), QPushButton(), QShortcut()) */
    QPushButton *cancelBtn = (QPushButton *)children()[3];
    cancelBtn->setHidden(true);
}

void ProgressDialog::UpdateValue()
{
    int val = value();
    val++;
    setValue(val);
}

void ProgressDialog::closeEvent(QCloseEvent *event)
{
    /** ignore X button */
    event->ignore();
}
