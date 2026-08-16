#include "P6.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    P6 w;
    w.show();

    w.resize(192,108);
    w.setWindowTitle("DIGIDOKU: Digital Sodoku");
    w.show();

    return a.exec();
}
