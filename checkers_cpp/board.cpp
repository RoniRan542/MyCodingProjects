#include <iostream>
#include <cstdlib>
#include <math.h>
#include "board.hpp"

Board::Board()
{
    Init();
}

void Board::Init()
{
    int counter = 0;
    board_squares_2d.resize(8, std::vector<BoardSquare>(8));
    for (size_t i = 0; i < 8; i++)
    {
        for (size_t j = 0; j < 8; j++)
        {
            board_squares_2d[i][j].SetXY(i, j);

            if (i < 3)
            {

                if ((i % 2) == 0)
                {
                    if (j % 2 == 0)
                    {
                        board_squares_2d[i][j].SetPlayer(PlayerId::ONE);
                        board_squares_2d[i][j].SetPawnId(counter++);
                    }
                }
                else
                {
                    if (j % 2 == 1)
                    {
                        board_squares_2d[i][j].SetPlayer(PlayerId::ONE);
                        board_squares_2d[i][j].SetPawnId(counter++);
                    }
                }
            }
            else if (i > 4)
            {
                if ((i % 2) == 1)
                {
                    if (j % 2 == 1)
                    {
                        board_squares_2d[i][j].SetPlayer(PlayerId::TWO);
                        board_squares_2d[i][j].SetPawnId(counter++);
                    }
                }
                else
                {
                    if (j % 2 == 0)
                    {
                        board_squares_2d[i][j].SetPlayer(PlayerId::TWO);
                        board_squares_2d[i][j].SetPawnId(counter++);
                    }
                }
            }
        }
    }
}

void Board::Move(BoardSquare &src, BoardSquare &dest,
                 enum PlayerId plyr, int pawn_id)
{
    dest.SetPawn(src.GetPawn());
    src.SetPawn(Pawn());
}

int Board::MoveIfValid(BoardSquare &src, BoardSquare &dest,
                       enum PlayerId plyr, int pawn_id)
{
    // check if the pawn belongs ro this player:
    std::cout << "src player id: " << src.GetPlayerId() << std::endl;
    std::cout << "actual player id: " << plyr << std::endl;
    if (src.GetPlayerId() != plyr)
    {
        return -1;
    }
    // check if dest is empty:
    std::cout << "dest pawn id: " << dest.GetPawn().GetPawnId() << std::endl;
    if (dest.GetPawn().GetPawnId() != -1)
    {
        return -1;
    }
    // check if move is consistent
    if (abs(dest.GetX() - src.GetX()) != 1 || abs(dest.GetY() - src.GetY()) != 1)
    {
        if (abs(dest.GetX() - src.GetX()) != 2 && abs(dest.GetY() - src.GetY()) != 2)
        {
            BoardSquare &mid_square = board_squares_2d[src.GetX() + 1][src.GetY() + 1];

            if (mid_square.GetPlayerId() != plyr &&
                mid_square.GetPlayerId() != PlayerId::VOID)
            {
                Move(src, dest, plyr, pawn_id);
                Kill(mid_square);
                return 1;
            }
            else
            {
                return -1;
            }
        }
        else
        {
            return -1;
        }
    }
}

void Board::Kill(BoardSquare &other)
{
    other.SetPawn(Pawn());
}

std::vector<std::vector<BoardSquare>> &Board::GetBoard()
{
    return board_squares_2d;
}
