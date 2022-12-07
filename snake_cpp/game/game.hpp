#ifndef __SNAKE_GAME_HPP__
#define __SNAKE_GAME_HPP__

#include <iostream>

#include "snake.hpp"
#include "board.hpp"

enum Level
{
    BEGINNER,
    MEDIUM,
    HARD
};

class Game
{
public:
    Game(float screenWidth = 960, float screenHeight = 960, enum Level level = BEGINNER);
    Game(const Game &other) = delete;
    Game(Game &&) = delete;
    const Game &operator=(const Game &other) = delete;
    const Game &operator=(Game &&) = delete;
    void StartGame();
    ~Game();

private:
    Board *m_board;
    Snake *m_snake;
    float m_screenWidth;
    float m_screenHeight;
    enum Level m_level;
};

#endif //__SNAKE_GAME_HPP__