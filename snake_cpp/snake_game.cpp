#include <thread>
#include <chrono>

#include "/home/rani/raylib/src/raylib.h"
#include "board.hpp"
#include "square.hpp"
#include "snake.hpp"

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 960;
    const int screenHeight = 960;

    InitWindow(screenWidth, screenHeight, "Snake");

    Board board(60, 60, screenWidth, screenHeight);
    bool alternate = false;
    std::vector<std::vector<Square>> bo(board.GetBoard());
    Snake snake(std::pair<uint32_t, uint32_t>(7, 7), 3);
    board.SetFood(snake.GetSnake());
    SetTargetFPS(10);
    Camera2D camera;
    camera.offset.x = -60;
    camera.offset.y = -60;
    camera.target.x = 0;
    camera.target.y = 0;
    camera.rotation = 0;
    camera.zoom = 1;

    int i = 0, j = 0;

    while (!WindowShouldClose())
    {
        try
        {
            std::list<std::pair<uint32_t, uint32_t>> snake_list = snake.GetSnake();
            std::list<std::pair<uint32_t, uint32_t>>::iterator snake_it = snake_list.begin();

            if (IsKeyPressed(KEY_UP))
            {
                snake.ChangeDirection(UP);
            }
            else if (IsKeyPressed(KEY_DOWN))
            {
                snake.ChangeDirection(DOWN);
            }
            else if (IsKeyPressed(KEY_LEFT))
            {
                snake.ChangeDirection(LEFT);
            }
            else if (IsKeyPressed(KEY_RIGHT))
            {
                snake.ChangeDirection(RIGHT);
            }

            snake.UpdateSnakePos();
            snake_list = snake.GetSnake();

            if (snake_list.front() == board.GetFood())
            {
                snake.EnlargeSnake();
                board.SetFood(snake_list);
            }

            BeginDrawing();
            ClearBackground(BLUE);

            BeginMode2D(camera);

            for (; snake_it != snake_list.end(); snake_it++)
            {
                Rectangle rec = {bo[snake_it->first][snake_it->second].GetDLPoint().first, bo[snake_it->first][snake_it->second].GetDLPoint().second, 60, 60};
                DrawRectangleRec(rec, BLACK);
            }

            Rectangle rec = {bo[board.GetFood().first][board.GetFood().second].GetDLPoint().first, bo[board.GetFood().first][board.GetFood().second].GetDLPoint().second, 60, 60};
            DrawRectangleRec(rec, GREEN);

            EndMode2D();

            EndDrawing();
        }
        catch (const std::exception &e)
        {
            BeginDrawing();
            ClearBackground(BLUE);

            BeginMode2D(camera);
            DrawText("GAME OVER! ", screenWidth / 3, screenHeight / 2, 80, DARKPURPLE);
            EndMode2D();

            EndDrawing();
            std::this_thread::sleep_for(std::chrono::seconds(1));
            exit(0);
        }
    }

    CloseWindow();

    return 0;
}