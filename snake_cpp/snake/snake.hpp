#ifndef __SNAKE_HPP__
#define __SNAKE_HPP__

#include <iostream>
#include <list>

#include "board.hpp"
#include "square.hpp"

enum Directions
{
    UP,
    RIGHT,
    DOWN,
    LEFT
};

class Snake
{

public:
    Snake(const std::pair<uint32_t, uint32_t> &head, int init_len = 3);
    void ChangeDirection(enum Directions direction);
    void EnlargeSnake();
    const std::list<std::pair<uint32_t, uint32_t>> &GetSnake();
    int UpdateSnakePos();

private:
    int m_length;
    std::list<std::pair<uint32_t, uint32_t>> m_snake;
    enum Directions m_direction;
};

#endif //__SNAKE_HPP__