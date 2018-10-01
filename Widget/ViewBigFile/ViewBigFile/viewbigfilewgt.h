#ifndef VIEWBIGFILEWGT_H
#define VIEWBIGFILEWGT_H

#include <QWidget>

class QLineEdit;
class QTextEdit;

class ViewBigFileWgt : public QWidget
{
    Q_OBJECT
public:
    explicit ViewBigFileWgt(QWidget *parent = 0);

    void setFilename(const QString &filename);

private:
    QLineEdit* _ledit;
    QTextEdit* _tedit;
};

#endif // VIEWBIGFILEWGT_H
