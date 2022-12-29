#ifndef __BOARD_SQUARE_HPP__
#define __BOARD_SQUARE_HPP__

#include <iostream>

enum PlayerId
{
    ONE,
    TWO
};

class BoardSquare
{
public:
    BoardSquare();
    BoardSquare(int x, int y);
    BoardSquare(const BoardSquare &other);
    BoardSquare &operator=(const BoardSquare &other);
    int GetX() const;
    int GetY() const;
    PlayerId GetPlayerId() const;
    int GetPawnID() const;
    ~BoardSquare();

private:
    int m_x;
    int m_y;
    enum PlayerId m_plyr;
    int m_pawn_id;
};

#endif // __BOARD_SQUARE_HPP__