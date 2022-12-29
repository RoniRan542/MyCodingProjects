#include <iostream>
#include <cstdlib>

#include "grid.hpp"

Grid::Grid()
{
    Init();
}

void Grid::Init()
{
    uint32_t window_width = 960;
    uint32_t window_height = 960;
    uint32_t block_height = 120;
    uint32_t block_width = 120;
    grid_squares_2d.resize(8);
    for (size_t i = 0; i < 8; i++)
    {
        grid_squares_2d[i].resize(8);
    }

    std::pair<uint32_t, uint32_t> lower_point = {0, 0};
    std::pair<uint32_t, uint32_t> upper_point = {block_height, block_width};

    for (int i = 0; upper_point.first <= window_height; lower_point.first += block_height, upper_point.first += block_height, ++i)
    {
        for (int j = 0; upper_point.second <= window_width; lower_point.second += block_width, upper_point.second += block_width, ++j)
        {
            grid_squares_2d[i][j] = Square(upper_point, lower_point);
        }
        lower_point.second = 0;
        upper_point.second = block_height;
    }
}

std::vector<std::vector<Square>> &Grid::GetGrid()
{
    return grid_squares_2d;
}
