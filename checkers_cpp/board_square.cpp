
#include "board_square.hpp"

BoardSquare::BoardSquare() : m_x(0), m_y(0)
{
    // empty
}

BoardSquare::BoardSquare(int x, int y) : m_x(x), m_y(y)
{
    // empty
}

BoardSquare::BoardSquare(const BoardSquare &other) : m_x(other.GetX()), m_y(other.GetY())
{
    // empty
}

BoardSquare &BoardSquare::operator=(const BoardSquare &other)
{
    m_x = other.GetX();
    m_y = other.GetY();

    return *this;
}

int BoardSquare::GetX() const
{
    return m_x;
}

int BoardSquare::GetY() const
{
    return m_y;
}

BoardSquare::~BoardSquare()
{
    // empty
}