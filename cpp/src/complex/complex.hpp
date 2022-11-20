#ifndef __ILRD_RD12123_COMPLEX_HPP__
#define __ILRD_RD12123_COMPLEX_HPP__

#include <iosfwd> // lightest i/o library

namespace ilrd
{
    // complex numbers (a + bi): a(real part) + (b(imaginary part) * i(sqrt(-1))
    class Complex
    {
    public:
        Complex(double real = 0, double imaginary = 0); // non-explicit intentionally
        Complex &operator+=(const Complex &num);        //(x1+=x2)+=x3
        Complex &operator-=(const Complex &num);
        Complex &operator*=(const Complex &num);
        Complex &operator/=(const Complex &num);
        double GetReal() const;
        double GetImaginary() const;
        void SetReal(const double &num);
        void SetImaginary(const double &num);

    private:
        double m_real;
        double m_imaginary;
    };
    const Complex operator+(const Complex &num1, const Complex &num2);
    const Complex operator*(const Complex &num1, const Complex &num2);
    const Complex operator/(const Complex &num1, const Complex &num2);
    const Complex operator-(const Complex &num1, const Complex &num2);
    bool operator==(const Complex &num1, const Complex &num2);
    bool operator!=(const Complex &num1, const Complex &num2);
    std::ostream &operator<<(std::ostream &os, const Complex &num);
    std::istream &operator>>(std::istream &is, Complex &num);
}

#endif //__ILRD_RD12123_COMPLEX_HPP__