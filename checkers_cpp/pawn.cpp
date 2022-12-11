#include <iostream>

#include "pawn.hpp"

Pawn::Pawn()
{
}

Pawn::Pawn(std::pair<u_int32_t, u_int32_t> init_pos)
    : m_pos(init_pos)
{
    // empty
}
std::pair<u_int32_t, u_int32_t> Pawn::GetPosition() const
{
    return m_pos;
}
/* void Pawn::GoToPos(u_int32_t x, u_int32_t y)
{
    if (m_color == BLACK)
    {
        // going down
    }
    else
    {
        // going up
    }
} */