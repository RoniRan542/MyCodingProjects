#ifndef __PAWN_HPP__
#define __PAWN_HPP__

#include <iostream>

enum PlayerId
{

    ONE,
    TWO,
    VOID

};

class Pawn
{
public:
    explicit Pawn(int id = -1, bool is_king = false, PlayerId pid = PlayerId::VOID);
    explicit Pawn(int pawn_id);
    int GetPawnId() const;
    PlayerId GetPlayerId() const;
    void SetPawnId(int id);
    void SetPlayerId(PlayerId player_id);
    void MakeKing();
    bool IsKing() const;

private:
    int m_pawn_id;
    bool m_is_king;
    PlayerId m_pid;
};

#endif // __PAWN_HPP__