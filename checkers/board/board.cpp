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
        std::cout << i << " [ ";

        for (size_t j = 0; j < 8; j++)
        {
            board_squares_2d[i][j].SetXY(i, j);
            std::cout << j << " ";
            if (j < 3)
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
            else if (j > 4)
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
        std::cout << "]\n"
                  << std::endl;
    }
}

void Board::Move(BoardSquare &src, BoardSquare &dest,
                 enum PlayerId plyr, int pawn_id)
{
    dest.SetPawn(src.GetPawn());
    src.SetPawn(Pawn());
}

int Board::IsValidChoice(BoardSquare &src, enum PlayerId plyr)
{
    if (src.GetPlayerId() != plyr)
    {
        return -1;
    }

    return 1;
}
int Board::MoveIfValid(BoardSquare &src, BoardSquare &dest,
                       enum PlayerId plyr, int pawn_id)
{

    // check if dest is empty:
    std::cout << "dest pawn id: " << dest.GetPawn().GetPawnId() << std::endl;
    if (dest.GetPawn().GetPawnId() != -1)
    {
        return -2;
    }

    // check if player moving forward not backwards
    if (plyr == PlayerId::ONE && (dest.GetY() - src.GetY() < 0))
    {
        return -5;
    }
    if (plyr == PlayerId::TWO && (dest.GetY() - src.GetY() > 0))
    {
        return -5;
    }

    // check if move isn't consistent
    if (abs(dest.GetX() - src.GetX()) != 1 || abs(dest.GetY() - src.GetY()) != 1)
    {
        if (abs(dest.GetX() - src.GetX()) == 2 && abs(dest.GetY() - src.GetY()) == 2)
        {
            std::cout << "mid_square x: " << src.GetX() + (dest.GetX() - src.GetX()) / 2 << std::endl;
            std::cout << "mid_square y: " << src.GetY() + (dest.GetX() - src.GetX()) / 2 << std::endl;

            BoardSquare &mid_square = board_squares_2d[src.GetX() + (dest.GetX() - src.GetX()) / 2][src.GetY() + (dest.GetY() - src.GetY()) / 2];
            std::cout << "mid_square.GetPlayerId(): " << mid_square.GetPlayerId() << std::endl;
            std::cout << "plyr: " << plyr << std::endl;
            if (mid_square.GetPlayerId() != plyr &&
                mid_square.GetPlayerId() != PlayerId::VOID)
            {
                Move(src, dest, plyr, pawn_id);
                Kill(mid_square);
                return 1;
            }
            else
            {
                std::cout << "error: " << -3 << std::endl;

                return -3;
            }
        }
        else
        {
            std::cout << "error: " << -4 << std::endl;
            return -4;
        }
    }
    else
    {
        Move(src, dest, plyr, pawn_id);
    }

    return 1;
}

void Board::Kill(BoardSquare &other)
{
    other.SetPawn(Pawn());
}

std::vector<std::vector<BoardSquare>> &Board::GetBoard()
{
    return board_squares_2d;
}
