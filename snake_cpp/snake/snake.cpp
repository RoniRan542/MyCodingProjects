

#include <iostream>
#include <exception>
#include <algorithm>

#include "snake.hpp"

Snake::Snake(const std::pair<uint32_t, uint32_t> &head, int init_len) : m_length(init_len), m_direction(RIGHT)
{
    for (size_t i = 0; i < m_length; ++i)
    {
        m_snake.push_back(std::pair<uint32_t, uint32_t>(head.first - i, head.second));
    }
}

const std::list<std::pair<uint32_t, uint32_t>> &Snake::GetSnake()
{
    return m_snake;
}

int Snake::UpdateSnakePos()
{
    std::pair<uint32_t, uint32_t> new_section;
    std::pair<uint32_t, uint32_t> head = m_snake.front();
    if (RIGHT == m_direction)
    {
        if ((head.first + 1) % 16 == 0)
        {
            throw std::runtime_error("GAME OVER! \n");
        }

        new_section.first = (head.first + 1);
        new_section.second = (head.second);
    }
    else if (LEFT == m_direction)

    {
        if (((head.first) == 0))
        {
            throw std::runtime_error("GAME OVER! \n");
        }
        new_section.first = (head.first - 1);
        new_section.second = (head.second);
    }
    else if (DOWN == m_direction)
    {

        if ((head.second + 1) % 16 == 0)
        {
            throw std::runtime_error("GAME OVER! \n");
        }
        new_section.first = (head.first);
        new_section.second = (head.second + 1);
    }
    if (UP == m_direction)
    {
        if ((head.second) == 0)
        {
            throw std::runtime_error("GAME OVER! \n");
        }

        new_section.first = (head.first);
        new_section.second = (head.second - 1);
    }

    if (std::find(m_snake.begin(), m_snake.end(), std::pair<uint32_t, uint32_t>(new_section.first, new_section.second)) != m_snake.end())
    {
        throw std::runtime_error("GAME OVER! \n");
    }

    m_snake.push_front(new_section);
    m_snake.pop_back();

    return 0;
}

void Snake::ChangeDirection(enum Directions direction)
{
    m_direction = direction;
}

void Snake::EnlargeSnake()
{
    m_snake.push_back(m_snake.back());
}