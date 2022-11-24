#include <iostream>

#include "snake.hpp"

enum Level
{
    BEGINNER,
    MEDIUM,
    HARD
};

class Game
{
public:
    Game(enum Level level = BEGINNER);
    void StartGame();

    ~Game();

private:
    Snake *m_snake;
};

Game::Game(enum Level level)
{
}

Game::~Game()
{
}
