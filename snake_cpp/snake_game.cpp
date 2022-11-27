#include "/home/rani/raylib/src/raylib.h"
#include "board.hpp"
#include "square.hpp"
#include "snake.hpp"

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1000;
    const int screenHeight = 1000;

    InitWindow(screenWidth, screenHeight, "Snake");

    Board board(60, 60, screenWidth, screenHeight);
    bool alternate = false;
    std::vector<std::vector<Square>> bo(board.GetBoard());
    Snake snake(std::pair<uint32_t, uint32_t>(7, 7), 3);
    board.SetFood(snake.GetSnake());
    SetTargetFPS(10);
    Camera2D camera;
    camera.offset.x = 0;
    camera.offset.y = 0;
    camera.target.x = 60;
    camera.target.y = 60;
    camera.rotation = 0;
    camera.zoom = 1;

    int i = 0, j = 0;

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(LIGHTGRAY);

        BeginMode2D(camera);

        /*         for (const std::vector<Square> &vector : bo)
                {
                    for (const Square &blk : vector)
                    {
                        Rectangle rec = {(blk.GetDLPoint()).first, (blk.GetDLPoint()).second, 60, 60};
                        DrawRectangleRec(rec, LIGHTGRAY);
                    }
                } */
        /* bool m_is_eaten; */
        std::list<std::pair<uint32_t, uint32_t>> snake_list = snake.GetSnake();
        std::list<std::pair<uint32_t, uint32_t>>::iterator snake_it = snake_list.begin();

        for (; snake_it != snake_list.end(); snake_it++)
        {
            Rectangle rec = {bo[snake_it->first][snake_it->second].GetDLPoint().first, bo[snake_it->first][snake_it->second].GetDLPoint().second, 60, 60};
            DrawRectangleRec(rec, BLACK);
        }

        Rectangle rec = {bo[board.GetFood().first][board.GetFood().second].GetDLPoint().first, bo[board.GetFood().first][board.GetFood().second].GetDLPoint().second, 60, 60};
        DrawRectangleRec(rec, GREEN);

        EndMode2D();

        EndDrawing();

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
    }

    CloseWindow();

    return 0;
}