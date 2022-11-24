#include <iostream>
#include <vector>

class Square
{
public:
    Square();
    Square(std::pair<float, float> down_left, std::pair<float, float> up_right);
    std::pair<float, float> GetDLPoint() const;
    std::pair<float, float> GetURPoint() const;

private:
    std::pair<float, float> m_down_left;
    std::pair<float, float> m_up_right;
};

class Board
{
public:
    Board(uint32_t block_width, uint32_t block_height, uint32_t window_width, uint32_t window_height);
    std::vector<std::vector<Square>> &GetBoard();

private:
    void Init(uint32_t block_width, uint32_t block_height, uint32_t window_width, uint32_t window_height);
    std::vector<std::vector<Square>> board_squares_2d;
};
