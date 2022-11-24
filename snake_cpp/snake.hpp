#include <iostream>

enum Directions
{
    Up,
    Right,
    Down,
    Left
};

class Snake
{

public:
    Snake(int init_len, float x = 0, float y = 0);
    void ChangeDirection(enum Directions direction);
    void EnlargeSnake();
    ~Snake();

private:
    int m_length;
    std::pair<float, float> m_position;
    enum Directions m_direction;
};

Snake::Snake(int init_len, float x, float y)
{
}

Snake::~Snake()
{
}
