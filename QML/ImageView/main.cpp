#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "fileoperator.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<FileOperator>("Qt.User.FileOperator",1,0,"FileOperator");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
