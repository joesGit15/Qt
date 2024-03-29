#ifndef GENERATEBIGFILEWGT_H
#define GENERATEBIGFILEWGT_H

#include <QWidget>

class QSpinBox;
class QLineEdit;

class GenerateBigFileWgt : public QWidget
{
    Q_OBJECT
public:
    explicit GenerateBigFileWgt(QWidget *parent = 0);

signals:
    void sigGenerateOk(const QString &filename);

private:
    void slotBtnBeginClicked();

private:
    QSpinBox*  _sboxBaseNum;
    QSpinBox*  _sboxStep;
    QSpinBox*  _sboxCount;

    QLineEdit* _ledit;
};

#endif // GENERATEBIGFILEWGT_H
