#ifndef __PLAYER_HPP__
#define __PLAYER_HPP__

#include <iostream>
#include <vector>

#include "/home/rani/raylib/src/raylib.h"
#include "pawn.hpp"
#include "board_square.hpp"
#include "board.hpp"

class Player
{
public:
    explicit Player(Board &board, Color player_color, std::string name, PlayerId player_id);
    int ChoosePawn(BoardSquare &pawn_src);
    int MovePlayer(BoardSquare &src, BoardSquare &dest);
    Color GetColor() const;

private:
    Board &m_board;
    std::string m_name;
    Color m_color;
    PlayerId m_pid;
};

static bool IsEqualColor(const Color c1, const Color c2)
{
    return c1.r == c2.r && c1.g == c2.g && c1.b == c2.b && c1.a == c2.a;
}

#endif //__PLAYER_HPP__