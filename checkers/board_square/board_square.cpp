
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

void BoardSquare::SetXY(int x, int y)
{
    m_x = x;
    m_y = y;
}

void BoardSquare::SetPawn(Pawn pawn)
{
    m_pawn = pawn;
}

void BoardSquare::SetPlayer(PlayerId pid)
{
    m_pawn.SetPlayerId(pid);
}

void BoardSquare::SetPawnId(int id)
{
    m_pawn.SetPawnId(id);
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

Pawn BoardSquare::GetPawn()
{
    return m_pawn;
}

PlayerId BoardSquare::GetPlayerId() const
{
    return m_pawn.GetPlayerId();
}

int BoardSquare::GetPawnID() const
{
    return m_pawn.GetPawnId();
}

BoardSquare::~BoardSquare()
{
    // empty
}