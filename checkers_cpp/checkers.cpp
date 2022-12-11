#include <thread>
#include <chrono>

#include "board.hpp"
#include "game.hpp"
#include "square.hpp"
#include "player.hpp"

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 960;
    const int screenHeight = 960;
    InitWindow(screenWidth, screenHeight, "Damka");

    Game game;
    Board board = game.GetBoard();
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
    // make players
    // make

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
        size_t counter = 0;
        for (auto const &player : game.GetPlayers())
        {
            std::cout << counter++ << std::endl;
            auto color = player.GetColor();
            for (auto const &pawn : player.GetPawns())
            {
                std::pair<u_int32_t, u_int32_t> coordinates = pawn.GetPosition();
                DrawCircle(bo[coordinates.first][coordinates.second].GetDLPoint().first + 60,
                           bo[coordinates.first][coordinates.second].GetDLPoint().second + 60, 55, CLITERAL(color));
            }
        }
        /*
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
                } */
        EndMode2D();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}