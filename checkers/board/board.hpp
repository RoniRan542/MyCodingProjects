#ifndef __BOARD_HPP__
#define __BOARD_HPP__

#include <iostream>
#include <vector>

#include "square.hpp"
#include "board_square.hpp"

class Board
{
public:
    Board();
    std::vector<std::vector<BoardSquare>> &GetBoard();
    int IsValidChoice(BoardSquare &src, enum PlayerId plyr);
    int MoveIfValid(BoardSquare &src, BoardSquare &dest,
                    enum PlayerId plyr, int pawn_id);

private:
    void Init();

    void Move(BoardSquare &src, BoardSquare &dest,
              enum PlayerId plyr, int pawn_id);
    void Kill(BoardSquare &other);
    std::vector<std::vector<BoardSquare>> board_squares_2d;
};

#endif // __BOARD_HPP__