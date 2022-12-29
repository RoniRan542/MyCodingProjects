#include <iostream>

#include "pawn.hpp"

Pawn::Pawn() : m_pawn_id(auto_pawn_id++), m_is_king(false)
{
}

Pawn::Pawn(int id) : m_pawn_id(id), m_is_king(false)
{
    // empty
}

int Pawn::GetPawnId() const
{
    return m_pawn_id;
}

bool Pawn::IsKing() const
{
    return m_is_king;
}

void Pawn::MakeKing()
{
    m_is_king = true;
}

/* Pawn::Pawn(std::pair<u_int32_t, u_int32_t> init_pos)
    : m_pos(init_pos)
{
    // empty
}
std::pair<u_int32_t, u_int32_t> Pawn::GetPosition() const
{
    return m_pos;
}

void Pawn::SetPosition(std::pair<u_int32_t, u_int32_t> new_pos)
{
    m_pos.first = new_pos.first;
    m_pos.second = new_pos.second;
}
*/
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