#ifndef EDITORFACTORWIDGET_H
#define EDITORFACTORWIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QTableWidget;
class QTableWidgetItem;
QT_END_NAMESPACE

class EditorFactorWidget : public QWidget
{
    Q_OBJECT

    enum TableWidgetColumns{
        Color_Name = 0,
        Color_Rgba,
        Color_Hex,
        Color_Color,
    };
public:
    explicit EditorFactorWidget(QWidget *parent = 0);

protected:
    void showEvent(QShowEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void StAddRow();
    void StItemChanged(QTableWidgetItem* item);

private:
    void InitTableWidgetColumnWidth();

private:
    QTableWidget* _tableWget = 0;
};

#endif // EDITORFACTORWIDGET_H
