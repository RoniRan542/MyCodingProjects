#ifndef __BOARD_HPP__
#define __BOARD_HPP__

#include <iostream>
#include <vector>

#include "square.hpp"

class Board
{
public:
    explicit Board(uint32_t block_width, uint32_t block_height, uint32_t window_width, uint32_t window_height);
    std::vector<std::vector<Square>> &GetBoard();

private:
    void Init(uint32_t block_width, uint32_t block_height, uint32_t window_width, uint32_t window_height);
    std::vector<std::vector<Square>> board_squares_2d;
};

#endif // __BOARD_HPP__