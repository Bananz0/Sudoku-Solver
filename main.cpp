#include "mainwindow.h"

#include <QApplication>
#include <QLabel>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QLabel *label = new QLabel("Hello Qt!");




    label -> show();
    w.show();

    return a.exec();
}

void InitializeSodoku(){}

void StartSodoku(){

}
