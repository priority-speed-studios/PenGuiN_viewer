#include <QApplication>
#include <SFML/Graphics.hpp>
#include "header/mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc,argv);
    MainWindow w;
    w.show();
    return app.exec();
}
