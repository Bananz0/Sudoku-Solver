#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QDebug>
#include <QTextStream>
#include <QMessageBox>
#include <QDesktopServices>
#include <QTimer>
#include <wiringPi.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    QFile sodokuText(":/Sample.txt");
    if (!sodokuText.open(QIODevice::ReadOnly)){
        QMessageBox::information(0,"info",sodokuText.errorString());
    }
    QTextStream sodokuTextIn(&sodokuText);
    fileText = sodokuTextIn.readAll();

    s->InitializeGrid();
    //s->PrintGrid();


    ui->setupUi(this);
    setMinimumSize(450,600);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    //PEN
    QPen pen;
    painter.setPen(pen);
    painter.setRenderHint(QPainter::TextAntialiasing);
    pen.setWidth(4);

    //FONT
    QFont font;
    font.setPixelSize(30);
    font.setBold(1);
    font.setFamily("Bauhaus 93");
    painter.setFont(font);

    //OPACITY
    painter.setOpacity(.9);

    // Calculate the available drawing area
    int width = this->width();
    int height = this->height();

    // Calculate offsets to center the content
    int contentWidth = 442; // Width of your drawn grid and lines
    int contentHeight = 450; // Height of your drawn grid and lines


    // Calculate the center points of the widget and the content
    int centerX = width / 2;
    int centerY = height / 2;
    int contentCenterX = contentWidth / 2;
    int contentCenterY = contentHeight / 2;
    int offsetX = centerX - contentCenterX;
    int offsetY = centerY - contentCenterY;

    // Calculate scaling factors to fit content within the widget
    double scaleX = (double)width / contentWidth;
    double scaleY = (double)height / contentHeight;
    double scale = qMin(scaleX, scaleY);


    painter.translate(offsetX + 15 , offsetY - 50);
    painter.scale(scale, scale);

    //painter.translate(-contentCenterX, -contentCenterY);

    //Line Loop
    for (int i = 0; i < 10; i++){
        QPoint p1(0,40+i*(450/10)), p2(400,40+i*(450/10));
        QPoint p3(i*(450/10),42), p4(i*(450/10),442);

        //seting pen thicccness
        pen.setWidth((i % 3 == 0) ? 6 : 4);
        //pen coloour
        i % 2? pen.setColor(Qt::blue) : pen.setColor(Qt::red);
        if (i == 9) pen.setColor(Qt::black);
        if (i == 6) pen.setColor(Qt::black);
        if (i == 3) pen.setColor(Qt::black);
        if (i == 0) pen.setColor(Qt::black);


        painter.setPen(pen);
        painter.drawLine(p1, p2);
        painter.drawLine(p3, p4);
    }

    for (int j = 0; j < 9; j++) {
        for (int i = 0; i < 9; i++) {
            int value = s->getValue(j, i);
            i % 2 ? painter.setPen(Qt::red) : painter.setPen(Qt::green);
            QString text = QString::number(value);
            if (text == '9') painter.setPen(Qt::black);
            if (text == '6') painter.setPen(Qt::black);
            if (text == '4') painter.setPen(Qt::black);
            if (text == '2') painter.setPen(Qt::black);


            QRect cellRect(15 + i * (400 / 9), 80 + j * (400 / 9), 50, 20);
            if (cellRect.contains(clickedPos)) {
                text = QString::number(clickedValue);
            }

            if (text == '0') {
                painter.setPen(Qt::darkYellow);
            } else {
                painter.drawText(15 + i * (400 / 9), 80 + j * (400 / 9), text);
            }
        }
    }
}


// In mainwindow.cpp
void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    // Get click position
    clickedPos = event->pos();
    qDebug() << "Mouse x " << event->position() << " Mouse y " << event->position();

    // Find the clicked cell
    int row = -1, col = -1;
    for (int j = 0; j < 9; j++) {
        for (int i = 0; i < 9; i++) {
            QRect cellRect(15 + i * (400 / 9), 80 + j * (400 / 9), 50, 20);
            if (cellRect.contains(clickedPos)) {
                row = j;
                col = i;
                break;
            }
        }
        if (row != -1 && col != -1) break;
    }

    // If a cell was clicked, increment the clickedValue and update the grid value
    if (row != -1 && col != -1) {
        clickedValue = (clickedValue % 9) + 1;
        s->setValue(row, col, clickedValue);
    }

    s->PrintGrid();

    update(); // Trigger a repaint
}

void MainWindow::on_StartGame_clicked()
{
    static bool isGameStarted = false;
    static bool isGameComplete = false;

    if (!isGameStarted && !isGameComplete) {
        // Begin Game state
        qDebug() << "Starting New Game:";
        s->InitializeGrid();
        s->PopulateGrid(ParseText(fileText));
        ui->StartGame->setText("Check Game");
        isGameStarted = true;
        update();
    } else if (isGameStarted && !isGameComplete) {
        // Check Game state
        qDebug() << "Checking Game Status:";
        bool isSodokuValid = s->CheckGame();
        if (isSodokuValid) {
            ui->StartGame->setText("Your Sodoku is Valid");

            QTimer::singleShot(2500, this, [=]() {
                // TRANSMIT THROUGH Pions //
                wiringPiSetup();

                //Set Pin 0 as output to signal start
                ui->StartGame->setText("Transmitting data over pin 1");
                qDebug() << "Initiating handshake";

                pinMode(0, OUTPUT);
                for (int i = 0; i < 5 ; i++){
                    digitalWrite(0, HIGH); delay(500) ;
                    digitalWrite(0, LOW); delay(500);
                }



                //Transmit data through pin1 //Stub funtion
                pinMode(1, OUTPUT);

                for (int j = 0; j < 9 ; j++){
                    for (int i=0; i < 9; i++){
                        for (int z = 0; i < s->getValue(j,i) ; z++){
                            digitalWrite(0, HIGH); delay(500) ;
                            digitalWrite(0, LOW); delay(500);
                        }
                        qDebug() << "Sent " << s->getValue(i,j) << " over pin 1";
                    }
                }

                //Set Pin2 as output to signal end
                qDebug() << "Finalizing transfer";
                pinMode(2, OUTPUT);
                for (int i = 0; i < 5 ; i++){
                    digitalWrite(0, HIGH); delay(500) ;
                    digitalWrite(0, LOW); delay(500);
                }
                ui->StartGame->setText("Transfer Complete!");
                qDebug() << "Transfer Complete";
            });

            isGameComplete = true;

            isGameComplete= false;
            isGameStarted = false;
            QTimer::singleShot(1500, this, [=]() {
                ui->StartGame->setText("Start new Game");
            });


        } else {
            isGameComplete = false;
            isGameStarted = false;
            ui->StartGame->setText("Your Sodoku is Invalid, Start New Game.");
            QTimer::singleShot(2500, this, [=]() {
                ui->StartGame->setText("Start new Game");
            });
        }
        update();
    } else if (isGameComplete) {
        // Game Complete state
        qDebug() << "Game Complete. Starting New Game.";
        s->InitializeGrid();
        s->PopulateGrid(ParseText(fileText));
        ui->StartGame->setText("Check Game");
        isGameStarted = true;
        isGameComplete = false;
        update();
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
    fileText = sodokuTextIn.readAll();
}

void MainWindow::on_actionFrom_File_triggered()
{
    QString sodokuTestAlt =  QFileDialog::getOpenFileName(this, tr("Open File"),
                                                         "/home",
                                                         tr("*.txt"));
    QFile sodokuText(sodokuTestAlt);
    if (!sodokuText.open(QIODevice::ReadOnly)){
        QMessageBox::information(0,"info",sodokuText.errorString());
    }
    QTextStream sodokuTextIn(&sodokuText);
    fileText = sodokuTextIn.readAll();
}
void MainWindow::on_openFileDialog_clicked()
{
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

void MainWindow::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
    update(); // Trigger a repaint
}

void MainWindow::on_actionOpen_triggered()
{
    //Adapted from QT4 Guides
    QFile sodokuText(":/Sample.txt");
    if (!sodokuText.open(QIODevice::ReadOnly)){
        QMessageBox::information(0,"info",sodokuText.errorString());
    }
    QTextStream sodokuTextIn(&sodokuText);
    fileText = sodokuTextIn.readAll();
}

void MainWindow::on_actionUnsolved_Game_triggered()
{
    //Adapted from QT4 Guides
    QFile sodokuText(":/Sample_unsolved.txt");
    if (!sodokuText.open(QIODevice::ReadOnly)){
        QMessageBox::information(0,"info",sodokuText.errorString());
    }
    QTextStream sodokuTextIn(&sodokuText);
    fileText = sodokuTextIn.readAll();
}

void MainWindow::on_actionSolved_Game_triggered()
{
    //Adapted from QT4 Guides
    QFile sodokuText(":/Sample.txt");
    if (!sodokuText.open(QIODevice::ReadOnly)){
        QMessageBox::information(0,"info",sodokuText.errorString());
    }
    QTextStream sodokuTextIn(&sodokuText);
    fileText = sodokuTextIn.readAll();
}

void MainWindow::on_actionSave_File_triggered()
{

}

void MainWindow::on_actionHelp_triggered()
{
    QString link = "https://www.youtube.com/watch?v=dQw4w9WgXcQ";
    QDesktopServices::openUrl(QUrl(link));
}

void MainWindow::on_actionCredits_triggered()
{
    QString link = "https://youtu.be/LDU_Txk06tM?si=pU71xuD08cFz5sy4&t=74";
    QDesktopServices::openUrl(QUrl(link));

}

void MainWindow::on_actionExit_Game_triggered()
{
    QApplication::closeAllWindows();
}

void MainWindow::on_actionSave_triggered()
{
    on_actionSave_as_triggered();
}


void MainWindow::on_actionSave_as_triggered()
{
    QString sodokuTestAlt =  QFileDialog::getSaveFileName(this, tr("Open File"),
                                                         "/home",
                                                         tr("*.txt"));
    QFile sodokuText(sodokuTestAlt);
    if (!sodokuText.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "Failed to open file for writing: " + sodokuText.errorString());
        return;
    }

    QTextStream out(&sodokuText);
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            out << s->getValue(row, col);
        }
    }

    sodokuText.close();
}


