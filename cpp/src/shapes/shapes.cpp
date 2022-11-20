
#include <iostream> //cout

#include "shapes.hpp" // shapes header file

using namespace std;

namespace ilrd
{
    Shape::Shape() : m_offset(0)
    {
        // empty
    }
    Shape::~Shape()
    {
        // empty
    }
    void Shape::Draw() const
    {
        for (size_t i = 0; i < m_offset; ++i)
        {
            cout << " ";
        }
    }

    void Shape::Move(size_t offset)
    {
        m_offset = offset;
    }

    void Line::Draw() const
    {
        Shape::Draw();
        cout << "Line\n";
    }

    void Circle::Draw() const
    {
        Shape::Draw();
        cout << "Circle\n";
    }

    void Rectangle::Draw() const
    {
        Shape::Draw();
        cout << "Rectangle\n";
    }

    void Square::Draw() const
    {
        Shape::Draw();
        cout << "Square\n";
    }
}
