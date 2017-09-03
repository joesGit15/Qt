#include "tablewidget.h"
#include "itemdelegate.h"

#include <QtWidgets/QScrollBar>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTableWidgetItem>
#include <QtWidgets/QAbstractItemView>

#include <QtCore/QFileInfo>

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
    QStringList labelsText;
    labelsText << tr("Thumnail") << tr("Text") << tr("Checked");
    setHorizontalHeaderLabels(labelsText);

    int fixed = 100;
    setColumnWidth(Thumnail,fixed);
    setColumnWidth(Checked,fixed);

    ThumnailItemDelegate* thumnailDelegate = new ThumnailItemDelegate(this);
    setItemDelegateForColumn(Thumnail,thumnailDelegate);
    CheckedItemDelegate* checkedDelegate = new CheckedItemDelegate(this);
    setItemDelegateForColumn(Checked,checkedDelegate);

    QHeaderView* headerView = horizontalHeader();
    headerView->setSectionResizeMode(Thumnail,QHeaderView::Fixed);
    headerView->setSectionResizeMode(Text,    QHeaderView::Stretch);
    headerView->setSectionResizeMode(Checked, QHeaderView::Fixed);

    headerView = verticalHeader();
    headerView->setSectionResizeMode(QHeaderView::Fixed);

    setSelectionMode(QAbstractItemView::NoSelection);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void TableWidget::AddRows(const QStringList &paths)
{
   for(const QString &path:paths) {
       AddRow(path);
   }
}

void TableWidget::AddRow(const QString &path)
{
    Q_ASSERT("" != path);

    int row,w;
    /** img and thumnail are NULL */
    QImage img;
    QSize srcSize;
    QPixmap thumnail;
    QString fileByteSize;

    row = rowCount();
    insertRow(row);
    QTableWidgetItem* item = 0;

    item = new QTableWidgetItem(QVariant::Pixmap);
    w = columnWidth(Thumnail);
    img = ReadImage(path);
    if(!img.isNull()){
        srcSize = img.size();
        img = img.scaled(w,w,Qt::KeepAspectRatio);
        thumnail = QPixmap::fromImage(img);
    }
    item->setData(Qt::UserRole,thumnail);
    setItem(row,Thumnail,item);

    int k = 1024;
    int m = k*1024;
    int g = m*1024;

    QFileInfo info(path);
    if(info.size() < k){
        fileByteSize = QString("%1 bytes").arg(info.size());
    }else if(info.size() < m){
        fileByteSize = QString("%1 K").arg(info.size()/k);
    }else if(info.size() < g){
        fileByteSize = QString("%1 M").arg(info.size()/m);
    }else{
        fileByteSize = QString("%1 G").arg(info.size()/g);
    }

    QString text;
    text = QString("File: %1\nWxH: %2x%3\nSize:%4")
            .arg(path).arg(srcSize.width()).arg(srcSize.height())
            .arg(fileByteSize);

    item = new QTableWidgetItem(QVariant::String);
    item->setData(Qt::DisplayRole,text);
    item->setFlags(item->flags() & (~Qt::ItemIsEditable));
    setItem(row,Text,item);

    item = new QTableWidgetItem(QVariant::Bool);
    item->setData(Qt::UserRole,true);
    setItem(row,Checked,item);

    int h = columnWidth(Thumnail);
    setRowHeight(row,h);
}
