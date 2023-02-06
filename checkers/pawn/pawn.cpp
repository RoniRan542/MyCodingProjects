#include <iostream>

#include "pawn.hpp"

Pawn::Pawn(int id, bool is_king, PlayerId pid)
    : m_pawn_id(id), m_is_king(false), m_pid(pid)
{
    // empty
}

int Pawn::GetPawnId() const
{
    return m_pawn_id;
}

PlayerId Pawn::GetPlayerId() const
{
    return m_pid;
}

void Pawn::SetPawnId(int id)
{
    m_pawn_id = id;
}

void Pawn::SetPlayerId(PlayerId player_id)
{
    m_pid = player_id;
}

bool Pawn::IsKing() const
{
    return m_is_king;
}

void Pawn::MakeKing()
{
    m_is_king = true;
}
