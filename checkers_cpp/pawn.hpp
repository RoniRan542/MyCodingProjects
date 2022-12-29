#ifndef __PAWN_HPP__
#define __PAWN_HPP__

#include <iostream>

class Pawn
{
public:
    explicit Pawn();
    explicit Pawn(int pawn_id);
    int GetPawnId() const;
    void MakeKing();
    bool IsKing() const;
    // explicit Pawn(std::pair<u_int32_t, u_int32_t> init_pos);
    //  virtual void GoToPos(u_int32_t x, u_int32_t y);
    // std::pair<u_int32_t, u_int32_t> GetPosition() const;
    // void SetPosition(std::pair<u_int32_t, u_int32_t> new_pos);
    //  virtual void Capture(enum Direction dir);

private:
    // std::pair<u_int32_t, u_int32_t> m_pos;
    static int auto_pawn_id;
    const int m_pawn_id;
    bool m_is_king;
};

#endif // __PAWN_HPP__