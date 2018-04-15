#include "thumnailWidget.h"
#include "tablewidget.h"

#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QFileDialog>

#include <QtCore/QStandardPaths>

ThumnailWidget::ThumnailWidget(QWidget *parent)
    : QWidget(parent)
{
    _tableWget = new TableWidget(this);

    QPushButton* btnOpen = new QPushButton(tr("Open Images"),this);

    QHBoxLayout* hlyt = new QHBoxLayout;
    hlyt->addWidget(btnOpen);
    hlyt->addStretch(1);

    QVBoxLayout* vlyt = new QVBoxLayout;
    vlyt->addWidget(_tableWget,1);
    vlyt->addLayout(hlyt);

    setLayout(vlyt);

    connect(btnOpen,&QPushButton::clicked,
            this,&ThumnailWidget::StOpenImages);
}

void ThumnailWidget::StOpenImages()
{
    QStringList filters,paths;
    QFileDialog dlg(this);
    QString defaultDir = "";

    if("" == defaultDir){
        defaultDir = QStandardPaths::standardLocations(
                    QStandardPaths::PicturesLocation).first();
    }

    dlg.setDirectory(defaultDir);
    filters << "Image files(*.png *.jpg)"
            << "Any files(*)";
    dlg.setNameFilters(filters);
    dlg.setFileMode(QFileDialog::ExistingFiles);
    dlg.setOption(QFileDialog::DontUseNativeDialog);

    if(QDialog::Accepted == dlg.exec()){
        paths =dlg.selectedFiles();
        _tableWget->AddRows(paths);
    }
}
