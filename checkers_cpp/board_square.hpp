#ifndef __BOARD_SQUARE_HPP__
#define __BOARD_SQUARE_HPP__

#include <iostream>

#include "pawn.hpp"

class BoardSquare
{
public:
    BoardSquare();
    BoardSquare(int x, int y);
    BoardSquare(const BoardSquare &other);
    BoardSquare &operator=(const BoardSquare &other);
    void SetXY(int x, int y);
    void SetPawn(Pawn pawn);
    void SetPlayer(PlayerId pid);
    void SetPawnId(int id);
    int GetX() const;
    int GetY() const;
    Pawn GetPawn();
    PlayerId GetPlayerId() const;
    int GetPawnID() const;
    ~BoardSquare();

private:
    int m_x;
    int m_y;
    Pawn m_pawn;
};

#endif // __BOARD_SQUARE_HPP__