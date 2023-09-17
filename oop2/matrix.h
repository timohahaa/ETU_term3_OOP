#ifndef MATRIX_H
#define MATRIX_H

#include "number.h"

class Matrix
{
public:
    Matrix();
    void edit();
    number calcDeterminand();
    Matrix transposed();
    int calcRank();
    void printMatrix();

private:
    number matrix[3][3]; //фиксированный размер, потому что в методичке об этом ни слова не сказанно
    Matrix copy();

};

#endif // MATRIX_H
