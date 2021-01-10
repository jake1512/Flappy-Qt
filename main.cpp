#include "mainwindow.h"
#include "common.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(IMG_ICON));
    MainWindow w;
    w.show();
    return a.exec();
}
