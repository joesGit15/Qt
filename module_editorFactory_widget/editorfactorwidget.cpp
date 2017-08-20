#include "editorfactorwidget.h"
#include "colorlisteditor.h"
#include "coloritemdelegate.h"

#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTableWidgetItem>
#include <QtWidgets/QAbstractItemView>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>

#include <QtWidgets/QItemEditorFactory>
#include <QtWidgets/QItemEditorCreator>
#include <QtWidgets/QItemEditorCreatorBase>
#include <QtWidgets/QStandardItemEditorCreator>

#include <QtGui/QColor>

#include <QtCore/QDebug>

EditorFactorWidget::EditorFactorWidget(QWidget *parent)
    : QWidget(parent)
{
    QItemEditorFactory *factor = new QItemEditorFactory;
    QItemEditorCreatorBase* colorListCreator =
            new QStandardItemEditorCreator<ColorListEditor>();
    factor->registerEditor(QVariant::Color,colorListCreator);
    QItemEditorFactory::setDefaultFactory(factor);

    ColorItemDelegate* delegate = new ColorItemDelegate(this);

    _tableWget = new QTableWidget(0,4,this);
    _tableWget->setItemDelegateForColumn(3,delegate);

    _tableWget->horizontalHeader()->setStretchLastSection(true);
    _tableWget->setSelectionBehavior(QAbstractItemView::SelectRows);

    QTableWidgetItem* item = 0;
    item = new QTableWidgetItem(tr("Color Name"),QVariant::String);
    _tableWget->setHorizontalHeaderItem(Color_Name,item);
    item = new QTableWidgetItem(tr("Color Rgba"),QVariant::String);
    _tableWget->setHorizontalHeaderItem(Color_Rgba,item);
    item = new QTableWidgetItem(tr("Color Hex"),QVariant::String);
    _tableWget->setHorizontalHeaderItem(Color_Hex,item);
    item = new QTableWidgetItem(tr("Color Color"),QVariant::String);
    _tableWget->setHorizontalHeaderItem(Color_Color,item);

    QPushButton* btnAddRow = new QPushButton(tr("Add"),this);
    connect(btnAddRow,&QPushButton::clicked,
            this,&EditorFactorWidget::StAddRow);

    QHBoxLayout* hlyt = new QHBoxLayout;
    hlyt->addWidget(btnAddRow);
    hlyt->addStretch(1);

    QVBoxLayout* vlyt = new QVBoxLayout;
    vlyt->addWidget(_tableWget,1);
    vlyt->addLayout(hlyt);

    setLayout(vlyt);
}

void EditorFactorWidget::showEvent(QShowEvent *event)
{
    (void)event;
    InitTableWidgetColumnWidth();

    connect(_tableWget,&QTableWidget::itemChanged,
            this,&EditorFactorWidget::StItemChanged);
}

void EditorFactorWidget::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    InitTableWidgetColumnWidth();
}

void EditorFactorWidget::StAddRow()
{
    disconnect(_tableWget,&QTableWidget::itemChanged,
            this,&EditorFactorWidget::StItemChanged);

    int row = _tableWget->rowCount();
    _tableWget->insertRow(row);

    QStringList colorNames = QColor::colorNames();
    int idx = rand()%colorNames.size();
    QString cloName = colorNames[idx];

    QColor clo(cloName);
    QTableWidgetItem* item = 0;

    item = new QTableWidgetItem(QVariant::String);
    item->setData(Qt::DisplayRole,cloName);
    //item->setData(Qt::BackgroundRole,clo);
    _tableWget->setItem(row,Color_Name,item);

    item = new QTableWidgetItem(QVariant::String);
    QString text = tr("R=%1 G=%2 B=%3 A=%4").
            arg(clo.red()).arg(clo.green()).arg(clo.blue()).arg(clo.alpha());
    item->setData(Qt::DisplayRole,text);
    _tableWget->setItem(row,Color_Rgba,item);

    item = new QTableWidgetItem(QVariant::String);
    item->setData(Qt::DisplayRole,clo.name());
    _tableWget->setItem(row,Color_Hex,item);

    item = new QTableWidgetItem(QVariant::Color);
    item->setData(Qt::DisplayRole,clo);
    _tableWget->setItem(row,Color_Color,item);

    _tableWget->scrollToBottom();

    connect(_tableWget,&QTableWidget::itemChanged,
            this,&EditorFactorWidget::StItemChanged);
}

void EditorFactorWidget::StItemChanged(QTableWidgetItem *item)
{
    if(item->column() != Color_Color){
        return;
    }

    QString text;
    QStringList colorNames = QColor::colorNames();
    QColor clo = item->data(Qt::DisplayRole).value<QColor>();
    for(const QString &str:colorNames){
        if(clo == QColor(str)){
            text = str;
            break;
        }
    }

    int row = item->row();

    item = _tableWget->item(row,Color_Name);
    item->setData(Qt::DisplayRole,text);

    item = _tableWget->item(row,Color_Rgba);
    text = tr("R=%1 G=%2 B=%3 A=%4").
            arg(clo.red()).arg(clo.green()).arg(clo.blue()).arg(clo.alpha());
    item->setData(Qt::DisplayRole,text);

    item = _tableWget->item(row,Color_Hex);
    item->setData(Qt::DisplayRole,clo.name());
}

void EditorFactorWidget::InitTableWidgetColumnWidth()
{
    if(0 == _tableWget){
        return;
    }

    int count = _tableWget->columnCount();
    int viewWidth = _tableWget->width();
    int w = viewWidth/count;
    for(int i=0; i < count-1; i++){
        _tableWget->setColumnWidth(i,w);
    }
}
