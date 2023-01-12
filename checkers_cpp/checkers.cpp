#include <thread>
#include <chrono>

#include "board.hpp"
#include "game.hpp"
#include "square.hpp"
#include "player.hpp"
#include "grid.hpp"

int GameLoop(Game &game)
{
    while (!WindowShouldClose())
    {
        if (IsMouseButtonPressed(0))
        {
            Vector2 pos = GetMousePosition();
            // std::cout << pos.x / 120 << " " << pos.y / 120 << std::endl;
            std::cout << game.PlayTurn((pos.x / 120), (pos.y / 120)) << std::endl;
            /* if (game.PlayTurn((pos.x / 120), (pos.y / 120)) == -1)
            {
                continue;
            }
            else
            {
                continue;
            } */
        }
    }
}

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 960;
    const int screenHeight = 960;
    InitWindow(screenWidth, screenHeight, "Checkers");

    Game game;

    Grid grid;
    bool alternate = false;

    std::vector<std::vector<Square>> the_grid = grid.GetGrid();
    std::vector<std::vector<BoardSquare>> *bo = &game.GetBoard().GetBoard();
    SetTargetFPS(1);
    Camera2D camera;
    camera.offset.x = -120;
    camera.offset.y = -120;
    camera.target.x = 0;
    camera.target.y = 0;
    camera.rotation = 0;
    camera.zoom = 1;
    // make players
    // make
    std::thread thread(GameLoop, std::ref(game));

    // Define the camera to look into our 3d world
    Camera3D camera3 = {0};
    camera3.position = (Vector3){0.0f, 10.0f, 10.0f}; // Camera position
    camera3.target = (Vector3){0.0f, 0.0f, 0.0f};     // Camera looking at point
    camera3.up = (Vector3){0.0f, 1.0f, 0.0f};         // Camera up vector (rotation towards target)
    camera3.fovy = 45.0f;                             // Camera field-of-view Y
    camera3.projection = CAMERA_ORTHOGRAPHIC;         // Camera mode type

    Vector3 circle_position = {0.0f, 0.0f, 0.0f};
    Vector3 circle_position2 = {0.9f, 0.0f, 7.9f};
    Vector3 rotation_axis = {1, 1, 1};
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(LIGHTGRAY);

        BeginMode2D(camera);
        for (size_t i = 0; i < 8; ++i)
        {
            for (size_t j = 0; j < 8; ++j)
            {
                Rectangle rec = {the_grid[i][j].GetDLPoint().first, the_grid[i][j].GetDLPoint().second, 120, 120};
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

            for (size_t i = 0; i < 8; ++i)
            {
                for (size_t j = 0; j < 8; ++j)
                {
                    if ((*bo)[i][j].GetPawn().GetPawnId() != -1)
                    {
                        if ((*bo)[i][j].GetPawn().GetPlayerId() == PlayerId::ONE)
                        {
                            auto color = game.GetPlayers()[0].GetColor();
                            DrawCircle(the_grid[i][j].GetDLPoint().first + 60,
                                       the_grid[i][j].GetDLPoint().second + 60, 55, CLITERAL(color));
                        }
                        else
                        {
                            auto color = game.GetPlayers()[1].GetColor();
                            DrawCircle(the_grid[i][j].GetDLPoint().first + 60,
                                       the_grid[i][j].GetDLPoint().second + 60, 55, CLITERAL(color));
                        }
                    }
                }
            }
        }
        // game.PlayTurn();
        EndMode2D();
        /* BeginMode3D(camera3);
        DrawCylinder(circle_position, 2.5, 2.5, 0.6, 5, BLACK);
        DrawCylinderWires(circle_position, 2.5, 2.5, 0.6, 20, DARKGRAY);
        DrawCylinder(circle_position2, 2.5, 2.5, 0.6, 5, BLACK);
        DrawCylinderWires(circle_position2, 2.5, 2.5, 0.6, 20, DARKGRAY);
        EndMode3D(); */
        EndDrawing();
    }

    CloseWindow();
    thread.join();

    return 0;
}