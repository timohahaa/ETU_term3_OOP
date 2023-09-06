#include <iostream>
#include "matrix.h"

Matrix::Matrix()
{
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            this->matrix[i][j] = 0;
        }
    }
}

void Matrix::edit()
{
    
}

number Matrix::calcDeterminand()
{
    //просто 3х3 матрица, считаем втупую
    return this->matrix[0][0]*this->matrix[1][1]*this->matrix[2][2] +
    this->matrix[0][1]*this->matrix[1][2]*this->matrix[2][0] +
    this->matrix[1][0]*this->matrix[2][1]*this->matrix[0][2] -
    this->matrix[0][2]*this->matrix[1][1]*this->matrix[2][0] -
    this->matrix[0][1]*this->matrix[1][0]*this->matrix[2][2] -
           this->matrix[0][0]*this->matrix[2][1]*this->matrix[1][2];
}

Matrix Matrix::transposed()
{
    Matrix temp = this->copy();
    for(int i = 0; i < 3; i++)
    {
        for(int j = i; j < 3; j++)
        {
            temp.matrix[i][j] = temp.matrix[j][i];
        }
    }
    return temp;
}

int Matrix::calcRank()
{
    //опять же, потому что матрица 3х3, можем посчитать втупую

}

void Matrix::printMatrix()
{
    for(int i = 0; i < 3; i++)
    {
        std::cout<<"| ";
        for(int j = 0; j < 3; j++)
        {
            std::cout<<this->matrix[i][j]<< " ";
        }
        std::cout<<"|";
        std::cout<<std::endl;
    }
}

Matrix Matrix::copy()
{
    Matrix temp;
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            temp.matrix[i][j] = this->matrix[i][j];
        }
    }
    return temp;
}
