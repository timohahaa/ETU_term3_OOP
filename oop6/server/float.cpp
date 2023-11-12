#include "float.h"

Float::Float()
{

}

Float::Float(int re)
{
    this->num= re;
}

Float::Float(std::string str)
{
    this->num = std::stod(str);
}

Float Float::abs()
{
    if(this->num > 0)
    {
        return *this;
    }
    return Float(-1 * this->num);
}

Float Float::operator*(Float c)
{
    Float temp;
    temp.num = this->num * c.num;
    return temp;
}

Float Float::operator+(Float c)
{
    Float temp;
    temp.num = this->num + c.num;
    return temp;
}

Float Float::operator/(Float c)
{
    Float temp;
    temp.num = this->num / c.num;
    return temp;
}

Float Float::operator-(Float c)
{
    Float temp;
    temp.num = this->num - c.num;
    return temp;
}

bool Float::operator==(Float c)
{
    return this->num == c.num;
}

bool Float::operator>(Float c)
{
    return this->num > c.num;
}

bool Float::operator!=(int i)
{
    return this->num != i;
}

Float Float::operator*=(Float c)
{
    Float temp = (*this) * c;
    this->num = temp.num;
    return *this;
}

Float Float::operator-=(Float c)
{
    Float temp = (*this) - c;
    this->num = temp.num;
    return *this;
}

Float Float::operator+=(Float c)
{
    Float temp = (*this) + c;
    this->num = temp.num;
    return *this;
}

Float Float::operator=(Float c)
{
    this->num = c.num;
    return *this;
}

Float Float::operator-()
{
    this->num *= -1;
    return *this;
}

Float Float::operator=(int i)
{
    this->num = i;
    return *this;
}

std::ostream& operator<<(std::ostream& os, Float c)
{
    os << c.num;
    return os;
}

std::istream& operator>>(std::istream& is, Float& c)
{
    is>>c.num;
    return is;
}

QString& operator<<(QString& s, Float r)
{
    QString str = QString::number(r.num);
    return str;
}
