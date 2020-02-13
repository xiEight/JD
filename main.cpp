#include "mainwindow.h"
#include "glscene.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    glScene scene;
    scene.show();
    return a.exec();
}
