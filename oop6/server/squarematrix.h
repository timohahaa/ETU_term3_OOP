#ifndef SQUAREMATRIX_H
#define SQUAREMATRIX_H

#include "matrix.h"


template <class number>
class SquareMatrix : public Matrix<number>
{
public:
    SquareMatrix();
    SquareMatrix(Matrix<number> mat);
    number calcDeterminand();
    int getSize();
    void setSize(int s);

private:
    int size;

    SquareMatrix getMinor(int row, int col);
};



template <class number>
SquareMatrix<number>::SquareMatrix() : Matrix<number>()
{
    this->size = 3;
}

template <class number>
SquareMatrix<number>::SquareMatrix(Matrix<number> mat) : Matrix<number>()
{
    int size = mat.getRowCount();
    this->setSize(size);
    for(int i = 0; i < size; i++)
    {
        for(int j = 0; j < size; j++)
        {
            this->setAtIdx(mat.atIdx(i, j), i, j);
        }
    }
}

template <class number>
SquareMatrix<number> SquareMatrix<number>::getMinor(int row, int col)
{
    int ofs_x = 0;
    int ofs_y = 0;
    SquareMatrix<number> temp;
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

template <class number>
number SquareMatrix<number>::calcDeterminand()
{
    std::cout << "here f iter " << this->size << std::endl;
    if(this->size == 1)
    {
        std::cout<<"here " << this->matrix[0][0] << std::endl;
        return this->matrix[0][0];
    }
    if(this->size == 2)
    {
        std::cout<<"here 2" << std::endl;
        return this->matrix[0][0] * this->matrix[1][1] - this->matrix[0][1] * this->matrix[1][0];
    }
    if(this->size == 3)
    {
        std::cout<<"here 3" << std::endl;
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
    return number(8,1);
}

template <class number>
int SquareMatrix<number>::getSize()
{
    return this->rows;
}

template <class number>
void SquareMatrix<number>::setSize(int s)
{
    this->size = s;
    this->setRowCount(s);
    this->setColumnCount(s);
}

#endif // SQUAREMATRIX_H
