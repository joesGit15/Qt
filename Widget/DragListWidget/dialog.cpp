#include "dialog.h"
#include "ui_dialog.h"
#include "draglistitemdelegate.h"
#include <vector>

using namespace std;

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    Q_ASSERT(ui->listA->objectName() != "");
    Q_ASSERT(ui->listB->objectName() != "");
    Q_ASSERT(ui->listC->objectName() != "");
    Q_ASSERT(ui->listD->objectName() != "");

    ui->listA->setItemDelegate(new DragListItemDelegate);
    ui->listB->setItemDelegate(new DragListItemDelegate);
    ui->listC->setItemDelegate(new DragListItemDelegate);
    ui->listD->setItemDelegate(new DragListItemDelegate);

    vector<QListWidget*> ltArr;
    ltArr.push_back(ui->listA);
    ltArr.push_back(ui->listB);
    ltArr.push_back(ui->listC);
    ltArr.push_back(ui->listD);

    QString text;
    QListWidgetItem* item = 0;
    for(QListWidget* lt:ltArr){
        for(int i=0; i < 10; i++){
            item = new QListWidgetItem(lt);
            text = QString("%1 item %2").arg(lt->objectName()).arg(i);
            item->setText(text);
            item->setData(Qt::UserRole+1,rand()%256);
            item->setData(Qt::UserRole+2,rand()%256);
            item->setData(Qt::UserRole+3,rand()%256);
        }
    }

    ui->listA->setDragEnabled(true);
    ui->listA->setAcceptDrops(true);
    ui->listA->setDropIndicatorShown(true);
    ui->listA->setDefaultDropAction(Qt::MoveAction);

#define Test_A2B_B2A 1
#define Test_A2B 0

#if Test_A2B_B2A
    /** A and B can move to each other */
    ui->listB->setDragEnabled(true);
    ui->listB->setAcceptDrops(true);
    ui->listB->setDropIndicatorShown(true);
    ui->listB->setDefaultDropAction(Qt::MoveAction);

    ui->listA->appendDragSourceObjName(ui->listA->objectName());
    ui->listA->appendDragSourceObjName(ui->listB->objectName());

    ui->listB->appendDragSourceObjName(ui->listB->objectName());
    ui->listB->appendDragSourceObjName(ui->listA->objectName());
#elif Test_A2B
    /** A Can drag to B, B not */
    //ui->listB->setDragEnabled(true);
    ui->listB->setAcceptDrops(true);
    //ui->listB->setDropIndicatorShown(true);
    //ui->listB->setDefaultDropAction(Qt::MoveAction);
#endif

    ui->listC->setDragEnabled(true);
    ui->listC->setAcceptDrops(true);
    ui->listC->setDropIndicatorShown(true);
    ui->listC->setDefaultDropAction(Qt::MoveAction);
    ui->listC->appendDragSourceObjName(ui->listC->objectName());
}

Dialog::~Dialog()
{
    delete ui;
}
