#include <iostream>

#ifndef MATRIX_H
#define MATRIX_H

const int MAX_SIZE = 10;

template <class number>
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
    int rows;

    number matrix[MAX_SIZE][MAX_SIZE];

private:
    int cols;
    Matrix copy();
    void zero();
};

template <class number>
Matrix<number>::Matrix()
{
    this->rows = 3;
    this->cols = 3;
    for(int i = 0; i < this->rows; i++)
    {
        for(int j = 0; j < this->cols; j++)
        {
            this->matrix[i][j] = 0;
        }
    }
}

template <class number>
void Matrix<number>::edit()
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

template <class number>
number Matrix<number>::atIdx(int row, int col)
{
    return this->matrix[row][col];
}

template <class number>
Matrix<number> Matrix<number>::transposed()
{
    Matrix<number> trans = this->copy();
    for(int i = 0; i < MAX_SIZE; i++)
    {
        for(int j = i; j < MAX_SIZE; j++)
        {
            number temp = trans.matrix[i][j];
            trans.matrix[i][j] = trans.matrix[j][i];
            trans.matrix[j][i] = temp;
        }
    }
    trans.setRowCount(this->cols);
    trans.setColumnCount(this->rows);
    return trans;
}

template <class number>
int Matrix<number>::calcRank()
{
    int i, j, k;
    int countSwaps = 1;
    Matrix<number> c = this->copy();
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

template <class number>
void Matrix<number>::printMatrix()
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

template <class number>
int Matrix<number>::getRowCount()
{
    return this->rows;
}

template <class number>
int Matrix<number>::getColumnCount()
{
    return this->cols;
}

template <class number>
void Matrix<number>::setRowCount(int i)
{
    this->rows = i;
}

template <class number>
void Matrix<number>::setColumnCount(int i)
{
    this->cols = i;
}

template <class number>
void Matrix<number>::setAtIdx(number data, int row, int col)
{
    this->matrix[row][col] = data;
}

template <class number>
Matrix<number> Matrix<number>::copy()
{
    Matrix<number> temp;
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

template <class number>
void Matrix<number>::zero()
{
    for(int i = 0; i < MAX_SIZE; i++)
    {
        for(int j = 0; j < MAX_SIZE; j++)
        {
            this->matrix[i][j] = 0;
        }
    }
}

#endif // MATRIX_H
