#ifndef __PLAYER_HPP__
#define __PLAYER_HPP__

#include <iostream>
#include <vector>

#include "/home/rani/raylib/src/raylib.h"
#include "pawn.hpp"

class Player
{
public:
    explicit Player(Color player_color, std::string name);
    std::vector<Pawn> GetPawns() const;
    Color GetColor() const;

private:
    std::vector<Pawn>
        m_tools;
    std::string m_name;
    Color m_color;
};

static bool IsEqualColor(const Color c1, const Color c2)
{
    return c1.r == c2.r && c1.g == c2.g && c1.b == c2.b && c1.a == c2.a;
}

#endif //__PLAYER_HPP__