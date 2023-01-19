#include <iostream>
#include <vector>

#ifndef SHAPE3D_HPP
#define SHAPE3D_HPP

class Shape3D
{
public:
    explicit Shape3D(double x = 0, double y = 0, double z = 0);
    Shape3D(const Shape3D &other);
    Shape3D &operator=(const Shape3D &other);
    virtual double CalculateVolume() const = 0;
    virtual double CalculateSurfaceArea() const = 0;
    virtual void Move(double dx, double dy, double dz) = 0;
    virtual void Resize(const std::vector<double> &args) = 0;
    virtual ~Shape3D();

protected:
    double _x, _y, _z;
};

Shape3D ::Shape3D(double x, double y, double z) : _x(x), _y(y), _z(z)
{
}

Shape3D ::Shape3D(const Shape3D &other)
{
    *this = other;
}

Shape3D &Shape3D::operator=(const Shape3D &other)
{
    _y = other._y;
    _x = other._x;
    _z = other._z;
}

Shape3D ::~Shape3D()
{
}

#endif // SHAPE3D_HPP