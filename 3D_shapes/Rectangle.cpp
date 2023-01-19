#include <iostream>
#include "3DShape.hpp"

using namespace std;

class Rectangle : public Shape3D
{

public:
    Rectangle(double width, double height, double depth);
    virtual double CalculateVolume() const;
    virtual double CalculateSurfaceArea() const;
    virtual void Move(double dx, double dy, double dz);
    virtual void Resize(vector<double> args);
    virtual ~Rectangle();

private:
    double _width;
    double _height;
    double _depth;
};

Rectangle::Rectangle(double width, double height, double depth)
    : _width(width), _height(height), _depth(depth)
{
    // empty
}

double Rectangle::CalculateVolume() const
{
    return _width * _height * _depth;
}

double Rectangle::CalculateSurfaceArea() const
{
    return 2 * (_width * _height + _height * _depth + _width * _depth);
}

void Rectangle::Move(double dx, double dy, double dz)
{
    _x = dx;
    _y = dy;
    _z = dz;
}

void Rectangle::Resize(vector<double> args)
{
    vector<double>::iterator i = args.begin();

    _width += *i++;
    _height += *i++;
    _depth += *i;
}

Rectangle::~Rectangle()
{
}
