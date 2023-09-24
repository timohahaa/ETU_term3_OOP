#include <iostream>

#ifndef COMPLEX_H
#define COMPLEX_H


class Complex
{
public:
    Complex();
    Complex(int re, int im);
    Complex(int re);
    friend std::ostream& operator<<(std::ostream& os, Complex c);
    friend std::istream& operator>>(std::istream& is, Complex& c);
    Complex operator*(Complex c);
    Complex operator+(Complex c);
    Complex operator-(Complex c);
    bool operator==(Complex c);
    bool operator!=(int i);
    Complex operator*=(Complex c);
    Complex operator-=(Complex c);
    Complex operator+=(Complex c);
    Complex operator=(Complex c);
    Complex operator=(int i);

private:
    double _re = 0;
    double _im = 0;
};

#endif // COMPLEX_H
