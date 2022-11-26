

#include <iostream>

#include "snake.hpp"

Snake::Snake(const Square &head, int init_len,
             uint32_t block_len) : m_length(init_len), m_block_len(block_len), m_direction(RIGHT)
{
    std::pair<uint32_t, uint32_t> lower_point = head.GetDLPoint();
    std::pair<uint32_t, uint32_t> upper_point = head.GetURPoint();
    for (size_t i = 0; i < m_length; ++i, lower_point.first += m_block_len, upper_point.first += m_block_len)
    {
        m_snake.push_front(Square(lower_point, upper_point));
    }
}

std::list<Square> &Snake::GetSnake()
{
    return m_snake;
}

void Snake::ChangeDirection(enum Directions direction)
{
}

void Snake::EnlargeSnake()
{
}