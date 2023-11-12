#include "complex.h"

Complex::Complex()
{

}

Complex::Complex(int re, int im)
{
    this->_re = re;
    this->_im = im;
}

Complex::Complex(int re)
{
    this->_re = re;
    this->_im = 0;
}

Complex::Complex(std::string str)
{
    int i_pos = str.find("i");
    std::string realStr = str.substr(0, i_pos-2);
    std::string imStr = str.substr(i_pos + 1);
    this->_re = std::stod(realStr);
    this->_im = std::stod(imStr);
}

Complex Complex::abs()
{
    return Complex(std::sqrt(this->_re * this->_re + this->_im * this->_im));
}

Complex Complex::operator*(Complex c)
{
    Complex temp;
    temp._re = (this->_re * c._re) - (this->_im * c._im);
    temp._im = (this->_re * c._im) + (this->_im * c._re);
    return temp;
}

Complex Complex::operator+(Complex c)
{
    Complex temp;
    temp._re = this->_re + c._re;
    temp._im = this->_im + c._im;
    return temp;
}

Complex Complex::operator/(Complex c)
{
    Complex temp;
    temp._re = this->_re * c._re + this->_im * c._im;
    temp._im = this->_im * c._re - this->_re * c._im;
    temp._re /= c._re * c._re + c._im * c._im;
    temp._im /= c._re * c._re + c._im * c._im;
    return temp;
}

Complex Complex::operator-(Complex c)
{
    Complex temp;
    temp._re = this->_re - c._re;
    temp._im = this->_im - c._im;
    return temp;
}

bool Complex::operator==(Complex c)
{
    return (this->_re == c._re) && (this->_im == c._im);
}

bool Complex::operator>(Complex c)
{
    if(this->_im == 0 && c._im == 0)
    {
        return this->_re > c._re
    }
    return this->_re > c._re && this->_im > c._im;
}

bool Complex::operator!=(int i)
{
    return (this->_re != i) || (this->_im != 0);
}

Complex Complex::operator*=(Complex c)
{
    Complex temp = (*this) * c;
    this->_re = temp._re;
    this->_im = temp._im;
    return *this;
}

Complex Complex::operator-=(Complex c)
{
    Complex temp = (*this) - c;
    this->_re = temp._re;
    this->_im = temp._im;
    return *this;
}

Complex Complex::operator+=(Complex c)
{
    Complex temp = (*this) + c;
    this->_re = temp._re;
    this->_im = temp._im;
    return *this;
}

Complex Complex::operator=(Complex c)
{
    this->_re = c._re;
    this->_im = c._im;
    return *this;
}

Complex Complex::operator-()
{
    this->_re *= -1;
    this->_im *= -1;
    return *this;
}

Complex Complex::operator=(int i)
{
    this->_re = i;
    this->_im = 0;
    return *this;
}

std::ostream& operator<<(std::ostream& os, Complex c)
{
    os<<c._re<<"+"<<c._im<<"i";
    return os;
}

std::istream& operator>>(std::istream& is, Complex& c)
{
    is>>c._re>>c._im;
    return is;
}

QString& operator<<(QString& s, Complex r)
{
    QString str = QString::number(r._re) + "+" + QString::number(r._im) + "i";
    return str;
}
