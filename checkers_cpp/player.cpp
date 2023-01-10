#include <iostream>
#include <vector>

#include "player.hpp"

Player::Player(Board &board, Color player_color, std::string name)
    : m_board(board), m_color(player_color), m_name(name)
{
    size_t count = 0;
    if (IsEqualColor(m_color, BLACK))
    {
        for (u_int32_t j = 0; j < 2; j++)
        {
            for (u_int32_t i = 0; i < 8; i++)
            {
                m_tools.push_back(Pawn(std::pair<u_int32_t, u_int32_t>(i, j)));
            }
        }
    }
    else
    {
        for (u_int32_t j = 6; j < 8; j++)
        {
            for (u_int32_t i = 0; i < 8; i++)
            {
                m_tools.push_back(Pawn(std::pair<u_int32_t, u_int32_t>(i, j)));
            }
        }
    }
    m_tools.resize(16);
}

std::vector<Pawn> Player::GetPawns() const
{
    return m_tools;
}

Color Player::GetColor() const
{
    return m_color;
}

void Player::MovePlayer(int row, int col)
{
    m_board.
}

// void Move(std::string pawn_id);
//  void Capture(std::string pawn_id, enum Direction move_dir);
//  std::list<Pawn> GetPawns(std::string id);
