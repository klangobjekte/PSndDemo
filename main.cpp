#include "playerdemo.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    MyWidget w;
    w.show();

    return a.exec();


}
