#include "mainwindow.h"
#include <QApplication>
#include <QDir>


int main(int argc, char *argv[])
{
    QDir::setCurrent(FileHandler::FILE_DIRECTORY);
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
