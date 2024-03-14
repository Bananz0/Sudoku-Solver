#ifndef SODOKU_H
#define SODOKU_H
#include <vector>
#include <iostream>
#include <string>

class Sodoku
{
private:
    const int rows;
    const int cols;
    std::vector<std::vector<int>> sodokuGrid;
public:
    Sodoku();
    Sodoku(int row_n, int col_n);
    ~Sodoku();
    void InitializeGrid();
    void PopulateGrid(const std::vector<std::vector<int>> &GridIn);
    void PrintGrid();
    bool CheckGame();
};


#endif // SODOKU_H
