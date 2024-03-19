#include <iostream>
#include "sodoku.h"

bool CheckSubGrid(QVector<QVector<int>>& sodokuGrid, int GridNumber);
bool CheckLines(QVector<QVector<int>>& sodokuGrid);

Sodoku::Sodoku() : rows(9), cols(9) {};
Sodoku::Sodoku(int row_n, int col_n) : rows(row_n), cols(col_n) {};
Sodoku::~Sodoku() {};

void Sodoku::InitializeGrid() {
    sodokuGrid.resize(rows, QVector<int>(cols, 0));
}
void Sodoku::PopulateGrid(const QVector<QVector<int>> &GridIn) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < rows; j++) {
            sodokuGrid[i][j] = GridIn[i][j];
        }
    }
}
bool Sodoku::CheckGame() {
    int check = 0;
    int check2 = 0;
    for (int i = 0; i < 9; i++) {
        check += CheckSubGrid(sodokuGrid, i);
    }
    check2 = CheckLines(sodokuGrid);
    std::cout << "The game is" << ((check + check2) == 10?" valid ": " invalid") << std::endl;
    //Check for both lines and subgrids
    return ((check + check2) == 10);
}
bool CheckSubGrid(QVector<QVector<int>>& sodokuGrid, int GridNumber) {
    int sum = 0;
    int StartColumn = (GridNumber / 3) * 3;
    int StartRow = (GridNumber % 3) * 3;
    for (int i = StartColumn; i < StartColumn + 3; i++) {
        for (int j = StartRow; j < StartRow + 3; j++) {
            sum += sodokuGrid[i][j];
        }
    }
    return sum == 45;
}
bool CheckLines(QVector<QVector<int>>& sodokuGrid) {
    int sum_horizontal = 0;
    int sum_vertical = 0;

    for (int j = 0; j < 9; j++) {
        for (int i = 0; i < 9; i++) {
            sum_horizontal += sodokuGrid[i][j];
            sum_vertical += sodokuGrid[j][i];
        }
    }
    return (sum_horizontal + sum_vertical) == 405 * 2;
}
void Sodoku::PrintGrid() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < rows; j++) {
            std::cout << sodokuGrid[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

QVector<QVector<int>> Sodoku::getGrid() {
    return sodokuGrid;
}

int Sodoku::getValue(int a, int b){
    return sodokuGrid[a][b];
}
