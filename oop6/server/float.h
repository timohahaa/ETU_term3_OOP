#include <iostream>
#include <QString>

#ifndef FLOAT_H
#define FLOAT_H

class Float
{
public:
    Float();
    Float(int re);
    Float(std::string str);
    Float abs();
    friend std::ostream& operator<<(std::ostream& os, Float c);
    friend std::istream& operator>>(std::istream& is, Float& c);
    friend QString& operator<<(QString& s, Float r);
    Float operator*(Float c);
    Float operator+(Float c);
    Float operator/(Float c);
    Float operator-(Float c);
    bool operator==(Float c);
    bool operator>(Float c);
    bool operator!=(int i);
    Float operator*=(Float c);
    Float operator-=(Float c);
    Float operator+=(Float c);
    Float operator-();
    Float operator=(Float c);
    Float operator=(int i);

private:
    double num;
};


#endif // FLOAT_H
