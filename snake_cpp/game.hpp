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
    Game(float screenWidth, float screenHeight, enum Level level = BEGINNER);
    void StartGame();

    ~Game();

private:
    Board *m_board;
    Snake *m_snake;
    enum Level m_level;
};
