#ifndef MATRIX_H
#define MATRIX_H

#include "number.h"

const int MAX_SIZE = 10;

class Matrix
{
public:
    Matrix();
    void edit();
    number atIdx(int row, int col);
    Matrix transposed();
    int calcRank();
    void printMatrix();
    int getRowCount();
    int getColumnCount();
    void setRowCount(int i);
    void setColumnCount(int i);
    void setAtIdx(number data, int row, int col);

protected:
    int rows = 3;

    number matrix[MAX_SIZE][MAX_SIZE];

private:
    int cols = 3;
    Matrix copy();
    void zero();
};

#endif // MATRIX_H
