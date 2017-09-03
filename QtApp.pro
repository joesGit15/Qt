#-------------------------------------------------
# Project created by QtCreator 2017-08-12T07:52:15
#-------------------------------------------------

QT       += core gui network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app
TARGET = QtApp
VERSION = 00.00.01

CONFIG(debug,debug|release){
    DEFINES += joe
}else{

}

linux {
    DESTDIR = ./target
    MOC_DIR = ./tmp/Moc
    OBJECTS_DIR = ./tmp/Obj
}

SOURCES += main.cpp\
    mainwindow.cpp \
    ModelView/editorFactory_widget/editorfactorwidget.cpp \
    ModelView/editorFactory_widget/colorlisteditor.cpp \
    ModelView/editorFactory_widget/coloritemdelegate.cpp \
    ModelView/colorViewModelDelegate/listmodel.cpp \
    ModelView/colorViewModelDelegate/listitemdelegate.cpp \
    ModelView/colorViewModelDelegate/colorlistviewwidget.cpp \
    imageProcess/module_previewlist/styleditemdelegate.cpp \
    imageProcess/module_previewlist/progressdialog.cpp \
    imageProcess/module_previewlist/listwidget.cpp \
    imageProcess/imageprocesswidget.cpp \
    ModelView/tableWidgetThumnail/tablewidget.cpp \
    ModelView/tableWidgetThumnail/thumnailWidget.cpp \
    ModelView/tableWidgetThumnail/itemdelegate.cpp \
    NetWork/CrawlImg/httpwindow.cpp

HEADERS  += mainwindow.h \
    ModelView/editorFactory_widget/editorfactorwidget.h \
    ModelView/editorFactory_widget/colorlisteditor.h \
    ModelView/editorFactory_widget/coloritemdelegate.h \
    ModelView/colorViewModelDelegate/listmodel.h \
    ModelView/colorViewModelDelegate/listitemdelegate.h \
    ModelView/colorViewModelDelegate/colorlistviewwidget.h \
    imageProcess/module_previewlist/styleditemdelegate.h \
    imageProcess/module_previewlist/progressdialog.h \
    imageProcess/module_previewlist/listwidget.h \
    imageProcess/imageprocesswidget.h \
    ModelView/tableWidgetThumnail/tablewidget.h \
    ModelView/tableWidgetThumnail/thumnailWidget.h \
    ModelView/tableWidgetThumnail/itemdelegate.h \
    NetWork/CrawlImg/httpwindow.h

RESOURCES += \
    res.qrc

FORMS += \
    NetWork/CrawlImg/authenticationdialog.ui
