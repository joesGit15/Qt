#ifndef PROGRESSDIALOG_H
#define PROGRESSDIALOG_H

#include <QtWidgets/QProgressDialog>

QT_BEGIN_NAMESPACE
QT_END_NAMESPACE

class ProgressDialog : public QProgressDialog
{
public:
    explicit ProgressDialog(const QString &text, int maxNum, QWidget *parent = 0);
    void UpdateValue();

protected:
    void closeEvent(QCloseEvent *event) override;
};

#endif // PROGRESSDIALOG_H
