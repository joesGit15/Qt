#-------------------------------------------------
# Project created by QtCreator 2017-08-12T07:52:15
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = viewModel
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
    mainwindow.cpp \
    module_editorFactory_widget/editorfactorwidget.cpp \
    module_colorViewModelDelegate/colorlistviewwidget.cpp \
    module_colorViewModelDelegate/listmodel.cpp \
    module_colorViewModelDelegate/listitemdelegate.cpp \
    module_editorFactory_widget/colorlisteditor.cpp \
    module_editorFactory_widget/coloritemdelegate.cpp \
    module_imageProcess/imageprocesswidget.cpp

HEADERS  += mainwindow.h \
    module_editorFactory_widget/editorfactorwidget.h \
    module_colorViewModelDelegate/colorlistviewwidget.h \
    module_colorViewModelDelegate/listmodel.h \
    module_colorViewModelDelegate/listitemdelegate.h \
    module_editorFactory_widget/colorlisteditor.h \
    module_editorFactory_widget/coloritemdelegate.h \
    module_imageProcess/imageprocesswidget.h

RESOURCES += \
    res.qrc
