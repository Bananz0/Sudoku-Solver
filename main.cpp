#include "mainwindow.h"
#include <QApplication>

#include <QSplashScreen>
#include <QTimer>
#include <QIcon>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("SodokuSE");
    a.setApplicationVersion("1.0.0");

    QIcon icon(":/assets/icon.png");


    QSplashScreen *splash =new QSplashScreen;
    splash->setPixmap(QPixmap(":/assets/splash.png"));
    splash->show();

    MainWindow *w = new MainWindow;

    QTimer::singleShot(2500,splash,SLOT(close()));
    QTimer::singleShot(2500,w,SLOT(show()));

    w->setWindowTitle("SodokuSE: A new way to solve sodoku ineffeciently!");
    w->setWindowIcon(icon);



    //w.show();

    return a.exec();
}

