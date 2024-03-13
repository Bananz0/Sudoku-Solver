#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool gameStarted= false;
void MainWindow::on_StartGame_clicked()
{
    gameStarted = true;
    ui->gameStatus->setText("The game has started...");

}

