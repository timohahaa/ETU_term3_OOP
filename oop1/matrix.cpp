#include <iostream>
#include "matrix.h"

Matrix::Matrix()
{
    for(int i = 0; i < this->size; i++)
    {
        for(int j = 0; j < this->size; j++)
        {
            this->matrix[i][j] = 0;
        }
    }
}

void Matrix::edit()
{
    this->zero();
    std::cout<<"Enter matrix size (from 1 to 10): ";
    std::cin>>this->size;
    for(int i = 0; i < this->size; i++)
    {
        for(int j = 0; j < this->size; j++)
        {
            std::cout<<"Enter element at "<<i + 1<<"-"<<j+1<<" ";
            std::cin>>this->matrix[i][j];
        }
    }
}

number Matrix::calcDeterminand()
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

Matrix Matrix::transposed()
{
    Matrix trans = this->copy();
    for(int i = 0; i < size; i++)
    {
        for(int j = i; j < size; j++)
        {
            number temp = trans.matrix[i][j];
            trans.matrix[i][j] = trans.matrix[j][i];
            trans.matrix[j][i] = temp;
        }
    }
    return trans;
}

int Matrix::calcRank()
{
    int res = 0;
    number det = this->calcDeterminand();
    if(det != 0)
    {
        return this->size;
    }
    for(int i = 0; i < this->size; i++)
    {
        for(int j = 0; j < this->size; j++)
        {
            res = std::max(res, this->getMinor(i, j).calcRank());
        }
    }
    return res;
}

void Matrix::printMatrix()
{
    for(int i = 0; i < size; i++)
    {
        std::cout<<"| ";
        for(int j = 0; j < size; j++)
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
    temp.size = this->size;
    for(int i = 0; i < size; i++)
    {
        for(int j = 0; j < size; j++)
        {
            temp.matrix[i][j] = this->matrix[i][j];
        }
    }
    return temp;
}

void Matrix::zero()
{
    for(int i = 0; i < MAX_SIZE; i++)
    {
        for(int j = 0; j < MAX_SIZE; j++)
        {
            this->matrix[i][j] = 0;
        }
    }
}

Matrix Matrix::getMinor(int row, int col)
{
    int ofs_x = 0;
    int ofs_y = 0;
    Matrix temp;
    temp.size = this->size - 1;
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
