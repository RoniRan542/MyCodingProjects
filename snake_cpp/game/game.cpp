#include <iostream>
#include <thread>
#include <chrono>

#include "/home/rani/raylib/src/raylib.h"
#include "game.hpp"
#include "board.hpp"
#include "square.hpp"
#include "snake.hpp"

Game::Game(float screenWidth, float screenHeight, enum Level level)
    : m_board(new Board(60, 60, screenWidth, screenHeight)),
      m_snake(new Snake(std::pair<uint32_t, uint32_t>(7, 7), 3)),
      m_screenWidth(screenWidth),
      m_screenHeight(screenHeight),
      m_level(level)
{
    m_board->SetFood(m_snake->GetSnake());
}

void Game::StartGame()
{
    std::vector<std::vector<Square>> bo(m_board->GetBoard());
    InitWindow(m_screenWidth, m_screenHeight, "Snake");
    SetTargetFPS(10);
    Camera2D camera;
    camera.offset.x = -60;
    camera.offset.y = -60;
    camera.target.x = 0;
    camera.target.y = 0;
    camera.rotation = 0;
    camera.zoom = 1;

    while (!WindowShouldClose())
    {
        try
        {
            std::list<std::pair<uint32_t, uint32_t>> snake_list = m_snake->GetSnake();
            std::list<std::pair<uint32_t, uint32_t>>::iterator snake_it = snake_list.begin();

            if (IsKeyPressed(KEY_UP))
            {
                m_snake->ChangeDirection(UP);
            }
            else if (IsKeyPressed(KEY_DOWN))
            {
                m_snake->ChangeDirection(DOWN);
            }
            else if (IsKeyPressed(KEY_LEFT))
            {
                m_snake->ChangeDirection(LEFT);
            }
            else if (IsKeyPressed(KEY_RIGHT))
            {
                m_snake->ChangeDirection(RIGHT);
            }

            m_snake->UpdateSnakePos();
            snake_list = m_snake->GetSnake();
            if (snake_list.front() == m_board->GetFood())
            {
                m_snake->EnlargeSnake();
                m_board->SetFood(snake_list);
            }

            BeginDrawing();
            ClearBackground(BLUE);

            BeginMode2D(camera);
            for (; snake_it != snake_list.end(); snake_it++)
            {
                Rectangle rec = {bo[snake_it->first][snake_it->second].GetDLPoint().first, bo[snake_it->first][snake_it->second].GetDLPoint().second, 60, 60};
                DrawRectangleRec(rec, BLACK);
            }

            Rectangle rec = {bo[m_board->GetFood().first][m_board->GetFood().second].GetDLPoint().first, bo[m_board->GetFood().first][m_board->GetFood().second].GetDLPoint().second, 60, 60};
            DrawRectangleRec(rec, GREEN);

            EndMode2D();

            EndDrawing();
        }
        catch (const std::exception &e)
        {
            BeginDrawing();
            ClearBackground(BLUE);

            BeginMode2D(camera);
            DrawText("GAME OVER! ", (m_screenWidth * 2) / 7, m_screenHeight / 2, 80, DARKPURPLE);
            EndMode2D();

            EndDrawing();
            std::this_thread::sleep_for(std::chrono::seconds(1));
            exit(0);
        }
    }
}

Game::~Game()
{
    delete m_board;
    m_board = 0;
    delete m_snake;
    m_snake = 0;
}