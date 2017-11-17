#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "changecolor.h"

#include <QtCore/qdebug.h>
#include <QtWidgets/qpushbutton.h>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    /** find the Window qml object */
    QObject* window = 0;
    QList<QObject*> ltObjs = engine.rootObjects();
    for(QObject* &obj:ltObjs){
        if(obj->objectName() == "window"){
            window = obj;
            break;
        }
    }

    if(0 != window){
        new ChangeColor(window,&app);
    }

    /** find quit button to connect the quit signal */
    QObject* quitobj = window->findChild<QObject*>("quitbtn");
    if(0 != quitobj){
#if 0
        /** this way has error */
        QPushButton* btn = qobject_cast<QPushButton*>(quitobj);
        QObject::connect(btn,&QPushButton::clicked,
                         &app,&QGuiApplication::quit);
#else
        /** this connect is just compare string */
        QObject::connect(quitobj,SIGNAL(clicked()),&app,SLOT(quit()));
#endif
    }

    /**  */
    QObject* text = window->findChild<QObject*>("text");
    if(0 != text){
        /** return bool value */
        /** will return false, because text object => QQuickText, not has setText function */
        //QMetaObject::invokeMethod(text,"setText",Q_ARG(QString,"ha ha set text ok"));

        text->setProperty("color",QColor::fromRgb(255,0,0));
        bool bRet = QMetaObject::invokeMethod(text,"doLayout");
        qDebug() << "Text do layout:" << bRet;
    }

    return app.exec();
}
