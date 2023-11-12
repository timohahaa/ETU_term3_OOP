#include "squarematrix.h"

SquareMatrix::SquareMatrix() : Matrix()
{
}

SquareMatrix::SquareMatrix(Matrix mat) : Matrix()
{
    this->setSize(size);
    int size = mat.getRowCount();
    for(int i = 0; i < size; i++)
    {
        for(int j = 0; j < size; j++)
        {
            this->setAtIdx(mat.atIdx(i, j), i, j);
        }
    }
}

SquareMatrix SquareMatrix::getMinor(int row, int col)
{
    int ofs_x = 0;
    int ofs_y = 0;
    SquareMatrix temp;
    temp.setSize(this->size - 1);
    for(int i = 0; i < temp.size; i++)
    {
        if(i == row)
        {
            ofs_x = 1;
        }
        for(int j = 0; j < temp.size; j++)
        {
            if(j == col)
            {
                ofs_y = 1;
            }
            temp.matrix[i][j] = this->matrix[i+ofs_x][j+ofs_y];
        }
    }
    return temp;
}

number SquareMatrix::calcDeterminand()
{
    if(this->size == 1)
    {
        return this->matrix[0][0];
    }
    if(this->size == 2)
    {
        return this->matrix[0][0] * this->matrix[1][1] - this->matrix[0][1] * this->matrix[1][0];
    }
    if(this->size == 3)
    {
        return this->matrix[0][0]*this->matrix[1][1]*this->matrix[2][2] +
               this->matrix[0][1]*this->matrix[1][2]*this->matrix[2][0] +
               this->matrix[1][0]*this->matrix[2][1]*this->matrix[0][2] -
               this->matrix[0][2]*this->matrix[1][1]*this->matrix[2][0] -
               this->matrix[0][1]*this->matrix[1][0]*this->matrix[2][2] -
               this->matrix[0][0]*this->matrix[2][1]*this->matrix[1][2];
    }
    number res = 0;
    int sign = 1;
    for(int row = 0; row < this->size; row++)
    {
        if(sign == 1)
        {
            res += this->matrix[row][0] * this->getMinor(row, 0).calcDeterminand();
        }
        else
        {
            res -= this->matrix[row][0] * this->getMinor(row, 0).calcDeterminand();
        }
        sign *= -1;
    }
    return res;
}

int SquareMatrix::getSize()
{
    return this->rows;
}

void SquareMatrix::setSize(int s)
{
    this->setRowCount(s);
    this->setColumnCount(s);
}
