#ifndef __GRID_HPP__
#define __GRID_HPP__

#include <iostream>
#include <vector>

#include "square.hpp"

class Grid
{
public:
    explicit Grid();
    std::vector<std::vector<Square>> &GetGrid();

private:
    void Init();
    std::vector<std::vector<Square>> grid_squares_2d;
};

#endif // __GRID_HPP__