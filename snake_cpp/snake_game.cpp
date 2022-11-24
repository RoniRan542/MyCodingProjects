#include "/home/rani/raylib/src/raylib.h"
#include "board.hpp"

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1000;
    const int screenHeight = 1000;

    InitWindow(screenWidth, screenHeight, "Snake");

    Board board(80, 80, screenWidth, screenHeight);
    bool alternate = false;
    std::vector<std::vector<Square>> bo(board.GetBoard());

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

        for (const std::vector<Square> &vector : bo)
        {
            for (const Square &blk : vector)
            {
                Rectangle rec = {blk.m_down_left.first, blk.m_down_left.second, 80, 80};
                if (alternate)
                {
                    DrawRectangleRec(rec, RED);
                    alternate = false;
                }
                else
                {
                    DrawRectangleRec(rec, BLUE);
                    alternate = true;
                }
            }
            if (alternate)
            {
                alternate = false;
            }
            else
            {
                alternate = true;
            }
        }

        EndMode2D();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}