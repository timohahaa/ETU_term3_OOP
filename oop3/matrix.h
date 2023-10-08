#ifndef MATRIX_H
#define MATRIX_H

#include "number.h"

const int MAX_SIZE = 10;

class Matrix
{
public:
    Matrix();
    void edit();
    number calcDeterminand();
    number atIdx(int row, int col);
    Matrix transposed();
    int calcRank();
    void printMatrix();
    int getSize();
    void setSize(int s);
    void setAtIdx(number data, int row, int col);

private:
    int size = 3;
    number matrix[MAX_SIZE][MAX_SIZE]; //фиксированный размер, потому что в методичке об этом ни слова не сказанно
    Matrix copy();
    void zero();
    Matrix getMinor(int row, int col);

};

#endif // MATRIX_H
