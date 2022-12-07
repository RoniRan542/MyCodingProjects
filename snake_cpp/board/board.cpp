#include <iostream>
#include <list>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <ctime>

#include "board.hpp"

Board::Board(uint32_t block_width, uint32_t block_height, uint32_t window_width, uint32_t window_height)
{
    Init(block_width, block_height, window_width, window_height);
    m_block_width = block_width;
}

void Board::Init(uint32_t block_width, uint32_t block_height, uint32_t window_width, uint32_t window_height)
{
    uint32_t actual_window_width = (window_width / block_width) * block_width;
    uint32_t actual_window_height = (window_height / block_height) * block_height;
    board_squares_2d.resize((window_width / block_width));
    for (int i = 0; i < (window_width / block_width); i++)
    {
        board_squares_2d[i].resize((window_height / block_height));
    }

    std::pair<uint32_t, uint32_t> lower_point = {0, 0};
    std::pair<uint32_t, uint32_t> upper_point = {block_height, block_width};

    for (int i = 0; upper_point.first <= actual_window_height; lower_point.first += block_height, upper_point.first += block_height, ++i)
    {
        for (int j = 0; upper_point.second <= actual_window_width; lower_point.second += block_width, upper_point.second += block_width, ++j)
        {
            board_squares_2d[i][j] = Square(upper_point, lower_point);
        }
        lower_point.second = 0;
        upper_point.second = block_height;
    }
}

std::vector<std::vector<Square>> &Board::GetBoard()
{
    return board_squares_2d;
}

void Board::SetFood(const std::list<std::pair<uint32_t, uint32_t>> &snake_list)
{
    std::size_t limit = board_squares_2d.size();
    std::srand(std::time(nullptr));
    uint32_t x = std::rand() % limit;
    uint32_t y = std::rand() % limit;

    while (std::find(snake_list.begin(), snake_list.end(), std::pair<uint32_t, uint32_t>(x, y)) != snake_list.end())
    {
        x = std::rand() % limit;
        y = std::rand() % limit;
        std::cout << x << " " << y << std::endl;
    }

    m_food = std::pair<uint32_t, uint32_t>(x, y);
}

std::pair<uint32_t, uint32_t> Board::GetFood()
{
    return m_food;
}