#include <iostream>
#include "matrix.h"

Matrix::Matrix()
{
    number zero;
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            this->matrix[i][j] = zero;
        }
    }
}

void Matrix::edit()
{
    std::cout<<"Enter a11: ";
    std::cin >>this->matrix[0][0];
    std::cout<<"Enter a12: ";
    std::cin >>this->matrix[0][1];
    std::cout<<"Enter a13: ";
    std::cin >>this->matrix[0][2];
    std::cout<<"Enter a21: ";
    std::cin >>this->matrix[1][0];
    std::cout<<"Enter a22: ";
    std::cin >>this->matrix[1][1];
    std::cout<<"Enter a23: ";
    std::cin >>this->matrix[1][2];
    std::cout<<"Enter a31: ";
    std::cin >>this->matrix[2][0];
    std::cout<<"Enter a32: ";
    std::cin >>this->matrix[2][1];
    std::cout<<"Enter a33: ";
    std::cin >>this->matrix[2][2];
}

number Matrix::calcDeterminand()
{
    //просто 3х3 матрица, считаем втупую
    //главная диагональ и два треугольника
    number mainDiag = this->matrix[0][0]*this->matrix[1][1]*this->matrix[2][2];
    number mainTriangle1 = this->matrix[0][1]*this->matrix[1][2]*this->matrix[2][0];
    number mainTriangle2 = this->matrix[1][0]*this->matrix[2][1]*this->matrix[0][2];
    //побочная диагональ и два треугольника
    number sideDiag = this->matrix[0][2]*this->matrix[1][1]*this->matrix[2][0];
    number sideTriangle1 = this->matrix[0][1]*this->matrix[1][0]*this->matrix[2][2];
    number sideTriangle2 = this->matrix[0][0]*this->matrix[2][1]*this->matrix[1][2];

    number det = mainDiag + mainTriangle1 + mainTriangle2 - sideDiag - sideTriangle1 - sideTriangle2;
    return det;
}

Matrix Matrix::transposed()
{
    Matrix trans = this->copy();
    for(int i = 0; i < 3; i++)
    {
        for(int j = i; j < 3; j++)
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
    number zero;
    //опять же, потому что матрица 3х3, можем посчитать втупую
    Matrix m = this->copy();
    //из 2-й вычитаем 1-ю
    number firstEl = m.matrix[1][0];
    m.matrix[1][0] *= m.matrix[0][0];
    m.matrix[1][1] *= m.matrix[0][0];
    m.matrix[1][2] *= m.matrix[0][0];
    m.matrix[1][0] -= m.matrix[0][0] * firstEl;
    m.matrix[1][1] -= m.matrix[0][1] * firstEl;
    m.matrix[1][2] -= m.matrix[0][2] * firstEl;
    //из 3-й вычитаем 1-ю
    firstEl = m.matrix[2][0];
    m.matrix[2][0] *= m.matrix[0][0];
    m.matrix[2][1] *= m.matrix[0][0];
    m.matrix[2][2] *= m.matrix[0][0];
    m.matrix[2][0] -= m.matrix[0][0] * firstEl;
    m.matrix[2][1] -= m.matrix[0][1] * firstEl;
    m.matrix[2][2] -= m.matrix[0][2] * firstEl;
    //из 3-й вычитаем 2-ю
    firstEl = m.matrix[2][1];
    m.matrix[2][1] *= m.matrix[1][1];
    m.matrix[2][2] *= m.matrix[1][1];
    m.matrix[2][1] -= m.matrix[1][1] * firstEl;
    m.matrix[2][2] -= m.matrix[1][2] * firstEl;

    if(this->matrix[0][0] == zero)
    {
        return 0;
    }
    if(this->matrix[1][1] == zero)
    {
        return 1;
    }
    if(this->matrix[2][2] == zero)
    {
        return 2;
    }
    return 3;
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
