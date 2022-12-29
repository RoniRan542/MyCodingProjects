#ifndef __BOARD_HPP__
#define __BOARD_HPP__

#include <iostream>
#include <vector>

#include "square.hpp"

class Board
{
public:
    explicit Board();
    std::vector<std::vector<Square>> &GetBoard();
    int Move(const Square &src, const Square &dest,
             enum PlayerId plyr, std::vector<char> id_vec);
    int IsValidMove(const Square &src, const Square &dest,
                    enum PlayerId plyr, std::vector<char> id_vec);

private:
    void Init();
    std::vector<std::vector<Square>> board_squares_2d;
};

#endif // __BOARD_HPP__