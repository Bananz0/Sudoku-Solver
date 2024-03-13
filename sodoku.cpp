#include "sodoku.h"

Sodoku::Sodoku() : rows(9), cols(9) {}
Sodoku::Sodoku(int row_n, int col_n): rows(row_n), cols(col_n){};
Sodoku::~Sodoku(){}

void Sodoku::InitializeGame(){
    for (int i = 0; i < rows ; i++){
        for (int j = 0; j < rows; j++){
            sodokuGrid[i][j] = 0;
        }
    }
}

