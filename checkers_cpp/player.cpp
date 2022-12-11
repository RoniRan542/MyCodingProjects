#include <iostream>
#include <vector>

#include "player.hpp"

Player::Player(Color player_color, std::string name) : m_color(player_color), m_name(name)
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

void Player::Move()
{
    std::string pawn;
    std::string pos;
    std::cout << "choose pawn: \n";
    std::getline(std::cin, pawn);
    std::cout << "move to new position: \n";
    std::getline(std::cin, pos);
    static int i = 3;
    m_tools[2].SetPosition(std::pair<u_int32_t, u_int32_t>(i % 8, 4));
    ++i;
}
// void Move(std::string pawn_id);
//  void Capture(std::string pawn_id, enum Direction move_dir);
//  std::list<Pawn> GetPawns(std::string id);
