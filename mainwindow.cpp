#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QDebug>
#include <QTextStream>
#include <QMessageBox>


// mainwindow.cpp
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //setFixedSize(400,600);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::paintEvent(QPaintEvent *event)
{
    //Did not want to do this here
    QFile sodokuText(":/Sample.txt");
    if (!sodokuText.open(QIODevice::ReadOnly)){
        QMessageBox::information(0,"info",sodokuText.errorString());
    }
    QTextStream sodokuTextIn(&sodokuText);
    fileText = sodokuTextIn.readAll();

    s->InitializeGrid();
    s->PopulateGrid(ParseText(fileText));
    s->PrintGrid();
    //

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::TextAntialiasing);
    QPen pen;
    QFont font;
    font.setPixelSize(30);
    pen.setWidth(4);
    painter.setPen(pen);
    painter.setFont(font);
    painter.setOpacity(.5);


    // Calculate the available drawing area
    int width = this->width();
    int height = this->height();

    // Calculate offsets to center the content
    int contentWidth = 400; // Width of your drawn grid and lines
    int contentHeight = 450; // Height of your drawn grid and lines
    int offsetX = (width - contentWidth) / 2;
    int offsetY = (height - contentHeight) / 2;

    // Calculate scaling factors to fit content within the widget
    double scaleX = (double)width / 400.0; // Assuming max width of content is 400
    double scaleY = (double)height / 450.0; // Assuming max height of content is 450
    double scale = qMin(scaleX, scaleY); // Use the smaller scaling factor

    painter.translate(offsetX, offsetY);
    painter.scale(scale, scale);


    //Line Loop
    for (int i = 0; i < 10; i++){
        QPoint p1(0,40+i*(450/10)), p2(400,40+i*(450/10));
        QPoint p3(+i*(450/10),42), p4(i*(450/10),442);
        painter.drawLine(p1, p2);
        painter.drawLine(p3, p4);
    }

    //Grid Loop
    for (int j = 0; j < 9; j++) {
        for (int i = 0; i < 9; i++) {
            int value = s->getValue(j,i);
            QString text = QString::number(value);
            painter.drawText(15+i*(400/9),80+j*(400/9), text);
        }
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent * event)
{
    // get click position
    qDebug() << "Mouse x " << event->position() << " Mouse y " << event->position();
}

void MainWindow::on_StartGame_clicked()
{
    // if (!isGameStarted) {
    //     isGameStarted = true;
    //     s->InitializeGrid();
    //     s->PopulateGrid(ParseText(fileText));
    //     s->PrintGrid();
    // }
}

void MainWindow::on_openTextFile_clicked()
{
    // //Adapted from QT4 Guides
    // QFile sodokuText(":/Sample.txt");
    // if (!sodokuText.open(QIODevice::ReadOnly)){
    //     QMessageBox::information(0,"info",sodokuText.errorString());
    // }
    // QTextStream sodokuTextIn(&sodokuText);
    // fileText = sodokuTextIn.readAll();
}

void MainWindow::on_openFileDialog_clicked()
{
    // QString sodokuTestAlt =  QFileDialog::getOpenFileName(this, tr("Open File"),
    //                                                      "/home",
    //                                                      tr("*.txt"));
    // QFile sodokuText(sodokuTestAlt);
    // if (!sodokuText.open(QIODevice::ReadOnly)){
    //     QMessageBox::information(0,"info",sodokuText.errorString());
    // }
    // QTextStream sodokuTextIn(&sodokuText);
    // fileText = sodokuTextIn.readAll();

}

QVector<QVector<int>> MainWindow::ParseText(QString& input) {
    //Little help from AI and stack overflow
    QVector<QVector<int>> sodokuGridIn(9, QVector<int>(9));
    int idx = 0;
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            sodokuGridIn[row][col] = input[idx].digitValue();;
            idx++;
        }
    }
    return sodokuGridIn;
}

void MainWindow::on_checkGame_clicked()
{
    // if (!isGameComplete){
    //     isGameComplete= s->CheckGame();
    // }
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
    update(); // Trigger a repaint
}
