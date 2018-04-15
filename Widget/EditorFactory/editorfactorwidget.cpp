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

/** editor factor */
#include <QtWidgets/QComboBox>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QDoubleSpinBox>

#include <QtWidgets/QTimeEdit>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDateTimeEdit>

#include <QtWidgets/QLabel>

#include <QtWidgets/QLineEdit>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QPlainTextEdit>


#include <QtWidgets/QItemEditorFactory>
#include <QtWidgets/QItemEditorCreator>
#include <QtWidgets/QItemEditorCreatorBase>
#include <QtWidgets/QStandardItemEditorCreator>

#include <QtGui/QColor>

EditorFactorWidget::EditorFactorWidget(QWidget *parent)
    : QWidget(parent)
{
    QItemEditorFactory *factor = new QItemEditorFactory;
///! [0]
    QItemEditorCreatorBase* editor;

    /** Customize editor for QColor */
    editor = new QStandardItemEditorCreator<ColorListEditor>();
    factor->registerEditor(QVariant::Color,editor);

    /** add Bool editor as QComboBox */
    editor = new QStandardItemEditorCreator<QComboBox>();
    factor->registerEditor(QVariant::Bool,editor);

    editor = new QStandardItemEditorCreator<QDoubleSpinBox>();
    factor->registerEditor(QVariant::Double,editor);

    /** int or unsigned int */
    editor = new QStandardItemEditorCreator<QSpinBox>();
    factor->registerEditor(QVariant::Int,editor);

    editor = new QStandardItemEditorCreator<QTimeEdit>();
    factor->registerEditor(QVariant::Time,editor);

    editor = new QStandardItemEditorCreator<QDateEdit>();
    factor->registerEditor(QVariant::Date,editor);

    editor = new QStandardItemEditorCreator<QDateTimeEdit>();
    factor->registerEditor(QVariant::DateTime,editor);

    editor = new QStandardItemEditorCreator<QLabel>();
    factor->registerEditor(QVariant::Pixmap,editor);

    /** add QString editor as QPlainTextEdit, default editor is QLineEdit */
    editor = new QStandardItemEditorCreator<QPlainTextEdit>();
    factor->registerEditor(QVariant::String,editor);

    /** Both new and existing delegates will use the new factory */
    /** All the default editor will remove*/
    QItemEditorFactory::setDefaultFactory(factor);
///! [0]

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
    _tableWget->blockSignals(true);

    int row = _tableWget->rowCount();
    _tableWget->insertRow(row);

    QStringList colorNames = QColor::colorNames();
    int idx = rand()%colorNames.size();
    QString cloName = colorNames[idx];

    QColor clo(cloName);
    QTableWidgetItem* item = 0;

    item = new QTableWidgetItem(QVariant::String);
    item->setData(Qt::DisplayRole,cloName);
    /** set item can not to edit */
    item->setFlags(item->flags() & (~Qt::ItemIsEditable));
    //item->setData(Qt::BackgroundRole,clo);
    _tableWget->setItem(row,Color_Name,item);

    item = new QTableWidgetItem(QVariant::String);
    QString text = tr("R=%1 G=%2 B=%3 A=%4").
            arg(clo.red()).arg(clo.green()).arg(clo.blue()).arg(clo.alpha());
    item->setData(Qt::DisplayRole,text);
    item->setFlags(item->flags() & (~Qt::ItemIsEditable));
    _tableWget->setItem(row,Color_Rgba,item);

    item = new QTableWidgetItem(QVariant::String);
    item->setData(Qt::DisplayRole,clo.name());
    item->setFlags(item->flags() & (~Qt::ItemIsEditable));
    _tableWget->setItem(row,Color_Hex,item);

    item = new QTableWidgetItem(QVariant::Color);
    item->setData(Qt::DisplayRole,clo);
    _tableWget->setItem(row,Color_Color,item);

    _tableWget->scrollToBottom();

    _tableWget->blockSignals(false);
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
