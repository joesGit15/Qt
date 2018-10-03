#ifndef VIEWBIGFILEWGT_H
#define VIEWBIGFILEWGT_H

#include <QWidget>

class QLineEdit;
class QPlainTextEdit;

class ViewBigFileWgt : public QWidget
{
    Q_OBJECT
public:
    explicit ViewBigFileWgt(QWidget *parent = 0);

    void setFilename(const QString &filename);

private slots:
    void slotBtnOpenClicked();

private:
    QLineEdit*      _ledit;
    QPlainTextEdit* _tedit;
};

#endif // VIEWBIGFILEWGT_H
