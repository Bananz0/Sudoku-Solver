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

    void on_actionOpen_triggered();

    void on_actionUnsolved_Game_triggered();

    void on_actionSolved_Game_triggered();

    void on_actionHelp_triggered();

    void on_actionSave_File_triggered();

    void on_actionCredits_triggered();

    void on_actionExit_Game_triggered();

private:
    bool isGameStarted = false;
    bool isGameComplete = false;
    bool isSodokuValid = false;
    QString fileText;
    Ui::MainWindow *ui;
    void resizeEvent(QResizeEvent *event);

protected:
    void paintEvent(QPaintEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
};
#endif // MAINWINDOW_H
