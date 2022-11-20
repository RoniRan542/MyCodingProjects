
#include <iostream>
#include <cmath>

#include "complex.hpp"

using namespace std;

namespace ilrd
{
    Complex::Complex(double real, double imaginary) : m_real(real), m_imaginary(imaginary)
    {
    }

    Complex &Complex::operator+=(const Complex &num)
    {
        m_real += num.GetReal();
        m_imaginary += num.GetImaginary();

        return *this;
    }

    Complex &Complex::operator-=(const Complex &num)
    {
        m_real -= num.GetReal();
        m_imaginary -= num.GetImaginary();

        return *this;
    }

    Complex &Complex::operator*=(const Complex &num)
    {
        m_real = m_real * num.GetReal() - m_imaginary * num.GetImaginary();
        m_imaginary = m_real * num.GetImaginary() + m_imaginary * num.GetReal();

        return *this;
    }

    Complex &Complex::operator/=(const Complex &num)
    {
        m_real = (m_real * num.GetReal()) + (m_imaginary * num.GetImaginary()) /
                                                (pow(num.GetReal(), 2) + pow(num.GetImaginary(), 2));
        m_imaginary = (m_imaginary * num.GetReal()) - (m_real * num.GetImaginary()) /
                                                          (pow(num.GetReal(), 2) + pow(num.GetImaginary(), 2));
        return *this;
    }

    double Complex::GetReal() const
    {
        return m_real;
    }

    double Complex::GetImaginary() const
    {
        return m_imaginary;
    }

    void Complex::SetReal(const double &num)
    {
        m_real = num;
    }

    void Complex::SetImaginary(const double &num)
    {
        m_imaginary = num;
    }

    const Complex operator+(const Complex &num1, const Complex &num2)
    {
        Complex temp(num1);

        return (temp += num2);
    }

    const Complex operator-(const Complex &num1, const Complex &num2)
    {
        Complex temp(num1);

        return (temp -= num2);
    }

    const Complex operator*(const Complex &num1, const Complex &num2)
    {
        Complex temp;
        double new_real = num1.GetReal() * num2.GetReal() - num1.GetImaginary() * num2.GetImaginary();
        double new_imag = num1.GetReal() * num2.GetImaginary() + num2.GetReal() * num1.GetImaginary();
        temp.SetReal(new_real);
        temp.SetImaginary(new_imag);

        return temp;
    }

    const Complex operator/(const Complex &num1, const Complex &num2)
    {
        Complex temp;
        double t_real = (num1.GetReal() * num2.GetReal()) + (num1.GetImaginary() * num2.GetImaginary()) /
                                                                (pow(num2.GetReal(), 2) + pow(num2.GetImaginary(), 2));
        double t_imag = (num1.GetImaginary() * num2.GetReal()) - (num1.GetReal() * num2.GetImaginary()) /
                                                                     (pow(num2.GetReal(), 2) + pow(num2.GetImaginary(), 2));
        temp.SetReal(t_real);
        temp.SetImaginary(t_imag);

        return temp;
    }

    bool operator==(const Complex &num1, const Complex &num2)
    {
        return num1.GetReal() == num2.GetReal() &&
               num1.GetImaginary() == num2.GetImaginary();
    }

    bool operator!=(const Complex &num1, const Complex &num2)
    {
        return !(num1 == num2);
    }
    std::ostream &operator<<(std::ostream &os, const Complex &num)
    {
        return os << "complex num: " << num.GetReal() << " + " << num.GetImaginary() << "i \n ";
    }
    std::istream &operator>>(std::istream &is, Complex &num)
    {
        double real = 0;
        double imaginary = 0;
        is >> real;
        is >> imaginary;
        num.SetReal(real);
        num.SetImaginary(imaginary);

        return is;
    }
}