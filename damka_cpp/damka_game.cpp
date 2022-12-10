#include <thread>
#include <chrono>

#include "/home/rani/raylib/src/raylib.h"
#include "board.hpp"
#include "square.hpp"

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 960;
    const int screenHeight = 960;
    InitWindow(screenWidth, screenHeight, "Damka");

    Board board;
    bool alternate = false;
    std::vector<std::vector<Square>> bo(board.GetBoard());
    SetTargetFPS(2);
    Camera2D camera;
    camera.offset.x = -120;
    camera.offset.y = -120;
    camera.target.x = 0;
    camera.target.y = 0;
    camera.rotation = 0;
    camera.zoom = 1;

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(LIGHTGRAY);
        BeginMode2D(camera);

        for (size_t i = 0; i < 8; ++i)
        {
            for (size_t j = 0; j < 8; ++j)
            {
                Rectangle rec = {bo[i][j].GetDLPoint().first, bo[i][j].GetDLPoint().second, 120, 120};
                if (alternate == true)
                {
                    DrawRectangleRec(rec, WHITE);
                    alternate = false;
                }
                else
                {
                    DrawRectangleRec(rec, BROWN);
                    alternate = true;
                }
            }
            alternate = alternate == true ? false : true;
        }

        // std::cout << bo[i][j].GetDLPoint().first << ", " << bo[i][j].GetDLPoint().second << std::endl;

        for (size_t j = 0; j < 2; j++)
        {
            for (size_t i = 0; i < 8; i++)
            {
                DrawCircle(bo[i][j].GetDLPoint().first + 60, bo[i][j].GetDLPoint().second + 60, 55, BLACK);
            }
        }

        for (size_t j = 6; j < 8; j++)
        {
            for (size_t i = 0; i < 8; i++)
            {
                DrawCircle(bo[i][j].GetDLPoint().first + 60, bo[i][j].GetDLPoint().second + 60, 55, LIGHTGRAY);
            }
        }
        EndMode2D();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}