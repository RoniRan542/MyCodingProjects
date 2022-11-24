
#include "board.hpp"

Square::Square() : m_down_left({0, 0}), m_up_right({0, 0})
{
    // empty
}

Square::Square(std::pair<float, float> down_left, std::pair<float, float> up_right)
    : m_down_left(down_left), m_up_right(up_right)
{
    // empty
}

Board::Board(uint32_t block_width, uint32_t block_height, uint32_t window_width, uint32_t window_height)
{
    Init(block_width, block_height, window_width, window_height);
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
