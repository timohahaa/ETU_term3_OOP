#ifndef SQUAREMATRIX_H
#define SQUAREMATRIX_H

#include "matrix.h"



class SquareMatrix : public Matrix
{
public:
    SquareMatrix();
    SquareMatrix(Matrix mat);
    number calcDeterminand();
    int getSize();
    void setSize(int s);

private:
    int size = 3;

    SquareMatrix getMinor(int row, int col);
};

#endif // SQUAREMATRIX_H
