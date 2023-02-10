#include <iostream>
#include <vector>

#include "player.hpp"

Player::Player(Board &board, Color player_color, std::string name, PlayerId player_id)
    : m_board(board), m_color(player_color), m_name(name), m_pid(player_id)
{
    size_t count = 0;
}

Color Player::GetColor() const
{
    return m_color;
}
int Player::ChoosePawn(BoardSquare &pawn_src)
{
    return m_board.IsValidChoice(pawn_src, m_pid);
}

int Player::MovePlayer(BoardSquare &src, BoardSquare &dest)
{
    return m_board.MoveIfValid(src, dest, m_pid, src.GetPawnID());
}