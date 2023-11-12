#include <iostream>
#include "matrix.h"

Matrix::Matrix()
{
    for(int i = 0; i < this->rows; i++)
    {
        for(int j = 0; j < this->cols; j++)
        {
            this->matrix[i][j] = 0;
        }
    }
}

void Matrix::edit()
{
    this->zero();
    std::cout<<"Enter rows (from 1 to 10): ";
    std::cin>>this->rows;
    std::cout<<"Enter columns (from 1 to 10): ";
    std::cin>>this->cols;
    for(int i = 0; i < this->rows; i++)
    {
        for(int j = 0; j < this->cols; j++)
        {
            std::cout<<"Enter element at "<<i + 1<<"-"<<j+1<<" ";
            std::cin>>this->matrix[i][j];
        }
    }
}

number Matrix::atIdx(int row, int col)
{
    return this->matrix[row][col];
}

Matrix Matrix::transposed()
{
    Matrix trans = this->copy();
    for(int i = 0; i < MAX_SIZE; i++)
    {
        for(int j = i; j < MAX_SIZE; j++)
        {
            number temp = trans.matrix[i][j];
            trans.matrix[i][j] = trans.matrix[j][i];
            trans.matrix[j][i] = temp;
        }
    }
    trans.setRowCount(this->rows);
    trans.setColumnCount(this->cols);
    return trans;
}

int Matrix::calcRank()
{
    int i, j, k;
    int countSwaps = 1;
    Matrix c = this->copy();
    for (i = 0; i < this->rows; ++ i)
    {
        // находим строку с максимальным первым элементом
        int iMax = i;
        for (j = i + 1; j < this->rows; ++ j)
            if (c.matrix[j][i].abs() > c.matrix[iMax][i].abs())
            {
                iMax = j;
            }
        for (k = 0; k < this->cols; ++ k)
        {
            number temp = c.matrix[i][k];
            c.matrix[i][k] = c.matrix[iMax][k];
            c.matrix[iMax][k] = temp;
        }
        //countSwaps = - countSwaps * (i != iMax ? 1 : - 1);

        //  вычитаем текущую строку из всех остальных
        for (j = i + 1; j < this->rows; ++ j)
        {
            number q = -c.matrix[j][i] / c.matrix[i][i];
            for (k = this->cols - 1; k >= i; -- k)
            {
                c.matrix[j][k] += q * c.matrix[i][k];
            }
        }
    }
}

void Matrix::printMatrix()
{
    for(int i = 0; i < this->rows; i++)
    {
        std::cout<<"| ";
        for(int j = 0; j < this->cols; j++)
        {
            std::cout<<this->matrix[i][j]<< " ";
        }
        std::cout<<"|";
        std::cout<<std::endl;
    }
}

int Matrix::getRowCount()
{
    return this->rows;
}

int Matrix::getColumnCount()
{
    return this->cols;
}

void Matrix::setRowCount(int i)
{
    this->rows = i;
}

void Matrix::setColumnCount(int i)
{
    this->cols = i;
}

void Matrix::setAtIdx(number data, int row, int col)
{
    this->matrix[row][col] = data;
}

Matrix Matrix::copy()
{
    Matrix temp;
    temp.rows = this->rows;
    temp.cols = this->cols;
    for(int i = 0; i < this->rows; i++)
    {
        for(int j = 0; j < this->cols; j++)
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
