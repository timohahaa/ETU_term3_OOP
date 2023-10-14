#include "rational.h"
#include <QStringList>

Rational::Rational()
{

}

Rational::Rational(int a, int b)
{
    this->numerator = a;
    this->denominator = b;
    this->simplify();
}

Rational::Rational(int num)
{
    this->numerator = num;
    this->denominator = 1;
}

Rational::Rational(std::string str)
{
    // только строки вида знак-число-/-число
    // пример: -9/5 3/4
    int slashIdx = str.find("/");
    std::string numStr= str.substr(0,slashIdx);
    std::string denStr = str.substr(slashIdx + 1);
    int num = std::stoi(numStr);
    int den = std::stoi(denStr);
    this->numerator = num;
    this->denominator = den;
    this->simplify();
}

Rational Rational::operator*(Rational c)
{
    Rational temp;
    temp.numerator = this->numerator * c.numerator;
    temp.denominator = this->denominator * c.denominator;
    temp.simplify();
    return temp;
}

Rational Rational::operator+(Rational c)
{
    Rational temp;
    temp.numerator = this->numerator * c.denominator + this->denominator * c.numerator;
    temp.denominator = this->denominator * c.denominator;
    temp.simplify();
    return temp;
}

Rational Rational::operator-(Rational c)
{
    Rational temp;
    temp.numerator = this->numerator * c.denominator - this->denominator * c.numerator;
    temp.denominator = this->denominator * c.denominator;
    temp.simplify();
    return temp;
}

bool Rational::operator==(Rational c)
{
    return (this->numerator == c.numerator) && (this->denominator == c.denominator);
}

bool Rational::operator!=(int i)
{
    return (this->denominator != 1) || (this->numerator != i);
}

Rational Rational::operator*=(Rational c)
{
    Rational temp = (*this) * c;
    this->numerator = temp.numerator;
    this->denominator = temp.denominator;
    return (*this);
}

Rational Rational::operator-=(Rational c)
{
    Rational temp = (*this) - c;
    this->numerator = temp.numerator;
    this->denominator = temp.denominator;
    return (*this);
}

Rational Rational::operator+=(Rational c)
{
    Rational temp = (*this) + c;
    this->numerator = temp.numerator;
    this->denominator = temp.denominator;
    return (*this);
}

Rational Rational::operator=(Rational c)
{
    this->numerator = c.numerator;
    this->denominator = c.denominator;
    return *this;
}

Rational Rational::operator=(int i)
{
    this->numerator = i;
    this->denominator = 1;
    return *this;
}

void Rational::simplify()
{
    //сначала знаки
    if(this->denominator < 0)
    {
        this->numerator *= -1;
        this->denominator *= -1;
    }
    // теперь сокращаем дробь
    int MAX = std::max(this->denominator, std::abs(this->numerator));
    for(int i = MAX; i > 1; i--)
    {
        if(this->numerator % i == 0 && this->denominator % i == 0)
        {
            this->numerator /= i;
            this->denominator /= i;
        }
    }
}

std::ostream& operator<<(std::ostream& os, Rational r)
{
    os<<r.numerator<<"/"<<r.denominator;
    return os;
}

std::istream& operator>>(std::istream& is, Rational& r)
{
    is>>r.numerator>>r.denominator;
    return is;
}

QString& operator<<(QString& s, Rational r)
{
    s = QString::number(r.numerator) + "/" + QString::number(r.denominator);
    return s;
}

Rational operator>>(QString& s, Rational r)
{
    int num = s.split(QChar('/'), Qt::SkipEmptyParts)[0].toInt();
    int den = s.split(QChar('/'), Qt::SkipEmptyParts)[1].toInt();
    return Rational(num, den);
}





