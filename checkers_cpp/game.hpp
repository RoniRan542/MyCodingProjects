#ifndef __GAME_HPP__
#define __GAME_HPP__

#include <iostream>
#include <vector>
#include "/home/rani/raylib/src/raylib.h"

#include "board.hpp"
#include "player.hpp"
#include "pawn.hpp"

class Game
{
public:
    explicit Game(std::string p_name1 = "player 1", std::string p_name2 = "player 2");
    void StartGame();
    bool IsValidMove(Pawn pawn, std::pair<u_int32_t, u_int32_t>);
    Board GetBoard() const;
    std::vector<Player> GetPlayers() const;

private:
    std::vector<Player> m_players;
    Board m_board;
};

#endif // __GAEM_HPP__