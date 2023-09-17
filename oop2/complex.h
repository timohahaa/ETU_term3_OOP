#include <iostream>

#ifndef COMPLEX_H
#define COMPLEX_H


class Complex
{
public:
    Complex();
    Complex(int re, int im);
    friend std::ostream& operator<<(std::ostream& os, Complex c);
    friend std::istream& operator>>(std::istream& is, Complex& c);
    Complex operator*(Complex c);
    Complex operator+(Complex c);
    Complex operator-(Complex c);
    bool operator==(Complex c);
    Complex operator*=(Complex c);
    Complex operator-=(Complex c);
    Complex operator=(Complex c);

private:
    double _re = 0;
    double _im = 0;
};

#endif // COMPLEX_H
