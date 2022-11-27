#ifndef __BOARD_HPP__
#define __BOARD_HPP__

#include <iostream>
#include <vector>
#include <list>

#include "square.hpp"

class Board
{
public:
    explicit Board(uint32_t block_width, uint32_t block_height, uint32_t window_width, uint32_t window_height);
    std::vector<std::vector<Square>> &GetBoard();
    void SetFood(const std::list<std::pair<uint32_t, uint32_t>> &snake_list);
    std::pair<uint32_t, uint32_t> GetFood();

private:
    void
    Init(uint32_t block_width, uint32_t block_height, uint32_t window_width, uint32_t window_height);
    std::vector<std::vector<Square>> board_squares_2d;
    std::pair<uint32_t, uint32_t> m_food;
    uint32_t m_block_width;
};

#endif // __BOARD_HPP__