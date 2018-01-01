#include <QApplication>
#include <QQmlApplicationEngine>

#include "fileoperator.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    /** ~/.config/ */
    app.setOrganizationName("WT_Group");
    app.setOrganizationDomain("WT.com");
    app.setApplicationName("ImageView");
    app.setApplicationVersion("1.0");

    qmlRegisterType<FileOperator>("Qt.User.FileOperator",1,0,"FileOperator");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
