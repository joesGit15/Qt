#include <QApplication>
#include "editorfactorwidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    EditorFactorWidget w;
    w.show();

    return a.exec();
}
