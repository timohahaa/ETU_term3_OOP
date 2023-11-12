#include <iostream>
#include <QString>

#ifndef RATIONAL_H
#define RATIONAL_H


class Rational
{
public:
    Rational();
    Rational(int a, int b);
    Rational(int num);
    Rational(std::string str);
    Rational abs();
    friend std::ostream& operator<<(std::ostream& os, Rational r);
    friend std::istream& operator>>(std::istream& is, Rational& r);
    friend QString& operator<<(QString& s, Rational r);
    friend Rational operator>>(QString& s, Rational r);
    Rational operator*(Rational c);
    Rational operator+(Rational c);
    Rational operator-(Rational c);
    bool operator==(Rational c);
    bool operator!=(int i);
    bool operator>(Rational i);
    Rational operator*=(Rational c);
    Rational operator-=(Rational c);
    Rational operator+=(Rational c);
    Rational operator=(Rational c);
    Rational operator/(Rational c);
    Rational operator=(int i);
    Rational operator-();

private:
    int numerator = 1;
    int denominator = 1;

    void simplify();
};

#endif // RATIONAL_H
