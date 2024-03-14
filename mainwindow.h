#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QBrush>
#include <QPen>
#include <QPixmap>
#include <QWidget>
#include <QMouseEvent>
#include <map>


#include "sodoku.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QVector<QVector<int>> ParseText(QString& input);
    Sodoku *s = new Sodoku;

private slots:
    void on_StartGame_clicked();
    void on_openTextFile_clicked();
    void on_openFileDialog_clicked();
    void on_checkGame_clicked();

private:
    bool isGameStarted = false;
    bool isGameComplete = false;
    QString fileText;
    Ui::MainWindow *ui;

protected:
    void paintEvent(QPaintEvent *event);
    void mouseReleaseEvent(QMouseEvent * event);
};
#endif // MAINWINDOW_H
