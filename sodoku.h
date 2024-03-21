#ifndef SODOKU_H
#define SODOKU_H
#include <QVector>

class Sodoku
{
private:
    const int rows;
    const int cols;
    QVector<QVector<int>> sodokuGrid;
public:
    Sodoku();
    Sodoku(int row_n, int col_n);
    ~Sodoku();
    void InitializeGrid();
    void PopulateGrid(const QVector<QVector<int>> &GridIn);
    QVector<QVector<int>> getGrid();
    int getValue(int a,int b);
    void PrintGrid();
    bool CheckGame();
    void setValue(int a, int b, int valIn);
};


#endif // SODOKU_H
