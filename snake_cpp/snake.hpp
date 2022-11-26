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
    Snake(const Square &head, int init_len = 3,
          uint32_t block_len = 80);
    void ChangeDirection(enum Directions direction);
    void EnlargeSnake();
    std::list<Square> &GetSnake();

private:
    int m_length;
    u_int32_t m_block_len;
    std::list<Square> m_snake;
    enum Directions m_direction;
};

#endif //__SNAKE_HPP__