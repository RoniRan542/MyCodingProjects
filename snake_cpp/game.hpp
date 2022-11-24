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
    Game(enum Level level = BEGINNER);
    void StartGame();

    ~Game();

private:
    Snake *m_snake;
    Board *m_board;
};

Game::Game(enum Level level)
{
}

Game::~Game()
{
}
