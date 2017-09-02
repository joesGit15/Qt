#include "tablewidget.h"
#include "itemdelegate.h"

#include <QtWidgets/QScrollBar>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTableWidgetItem>

#include <QtGui/QImageReader>

static QImage ReadImage(const QString &imgPath)
{
    QImage img;
    QImageReader reader;

    reader.setFileName(imgPath);
    reader.setDecideFormatFromContent(true);

    if(reader.canRead()){
        img = reader.read();
    }

    return img;
}

TableWidget::TableWidget(QWidget *parent)
    :QTableWidget(0,3,parent)
{
    ThumnailItemDelegate* thumnailDelegate = new ThumnailItemDelegate(this);
    setItemDelegateForColumn(Thumnail,thumnailDelegate);
    CheckedItemDelegate* checkedDelegate = new CheckedItemDelegate(this);
    setItemDelegateForColumn(Checked,checkedDelegate);

    QStringList labelsText;
    labelsText << tr("Thumnail") << tr("Text") << tr("Checked");
    setHorizontalHeaderLabels(labelsText);
    setSelectionBehavior(QAbstractItemView::SelectRows);

    int fixed = 100;
    setColumnWidth(Thumnail,fixed);
    setColumnWidth(Checked,fixed);

    QHeaderView* headerView = horizontalHeader();
    headerView->setSectionResizeMode(Thumnail,QHeaderView::Fixed);
    headerView->setSectionResizeMode(Text,    QHeaderView::Stretch);
    headerView->setSectionResizeMode(Checked, QHeaderView::Fixed);

    headerView = verticalHeader();
    headerView->setSectionResizeMode(QHeaderView::Fixed);

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void TableWidget::AddRow(const QString &path)
{
    Q_ASSERT("" != path);

    int row,w;
    /** img and thumnail are NULL */
    QImage img;
    QPixmap thumnail;

    row = rowCount();
    insertRow(row);

    QTableWidgetItem* item = 0;

    item = new QTableWidgetItem(QVariant::Pixmap);
    setItem(row,Thumnail,item);
    w = columnWidth(Thumnail);
    img = ReadImage(path);
    if(!img.isNull()){
        img = img.scaled(w,w,Qt::KeepAspectRatio);
        thumnail = QPixmap::fromImage(img);
    }
    item->setData(Qt::UserRole,thumnail);

    item = new QTableWidgetItem(QVariant::String);
    setItem(row,Text,item);

    item = new QTableWidgetItem(QVariant::Bool);
    setItem(row,Checked,item);
    if(row%2 == 0){
        item->setData(Qt::UserRole,true);
    }else{
        item->setData(Qt::UserRole,false);
    }

    int h = columnWidth(Thumnail);
    setRowHeight(row,h);
}
