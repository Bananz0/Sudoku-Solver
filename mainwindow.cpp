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

void MainWindow::on_StartGame_clicked()
{
    if (!isGameStarted) {
        isGameStarted = true;
        s->InitializeGrid();
        s->PopulateGrid(ParseText(fileText));
        s->PrintGrid();

    }
}

void MainWindow::on_openTextFile_clicked()
{
    //Adapted from QT4 Guides
    QFile sodokuText(":/Sample.txt");
    if (!sodokuText.open(QIODevice::ReadOnly)){
        QMessageBox::information(0,"info",sodokuText.errorString());
    }
    QTextStream sodokuTextIn(&sodokuText);
    fileText = sodokuTextIn.readAll().toStdString();
    QString qfileText = QString::fromStdString(fileText);
    ui->textBrowser->setText(qfileText);
}

void MainWindow::on_OpenFileDialog_clicked()
{
    QString sodokuTestAlt =  QFileDialog::getOpenFileName(this, tr("Open File"),
                                                         "/home",
                                                         tr("*.txt"));
    QFile sodokuText(sodokuTestAlt);
    if (!sodokuText.open(QIODevice::ReadOnly)){
        QMessageBox::information(0,"info",sodokuText.errorString());
    }
    QTextStream sodokuTextIn(&sodokuText);
    fileText = sodokuTextIn.readAll().toStdString();
    QString qfileText = QString::fromStdString(fileText);
    ui->textBrowser->setText(qfileText);

}

std::vector<std::vector<int>> MainWindow::ParseText(const std::string& input) {
    //Little help from AI and stack overflow
    std::vector<std::vector<int>> sodokuGridIn(9, std::vector<int>(9));

    int idx = 0;
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            sodokuGridIn[row][col] = input[idx] - '0';
            idx++;
        }
    }
    return sodokuGridIn;
}



void MainWindow::on_checkGame_clicked()
{

}

