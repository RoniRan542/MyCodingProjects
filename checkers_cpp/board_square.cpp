
#include "board_square.hpp"

BoardSquare::BoardSquare() : m_x(0), m_y(0), m_plyr(PlayerId::VOID)
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

void BoardSquare::SetXY(int x, int y)
{
    m_x = x;
    m_y = y;
}

void BoardSquare::SetPlayer(PlayerId pid)
{
    m_plyr = pid;
}

void BoardSquare::SetPawnId(int id)
{
    m_pawn_id = id;
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