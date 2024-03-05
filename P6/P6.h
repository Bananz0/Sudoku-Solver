#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_P6.h"

class P6 : public QMainWindow
{
    Q_OBJECT

public:
    P6(QWidget *parent = nullptr);
    ~P6();

private:
    Ui::P6Class ui;
};
