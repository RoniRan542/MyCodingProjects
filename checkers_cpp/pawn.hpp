#ifndef __PAWN_HPP__
#define __PAWN_HPP__

#include <iostream>

class Pawn
{
public:
    explicit Pawn();
    explicit Pawn(std::pair<u_int32_t, u_int32_t> init_pos);
    // virtual void GoToPos(u_int32_t x, u_int32_t y);
    std::pair<u_int32_t, u_int32_t> GetPosition() const;
    //  virtual void Capture(enum Direction dir);

private:
    std::pair<u_int32_t, u_int32_t> m_pos;
};

#endif // __PAWN_HPP__