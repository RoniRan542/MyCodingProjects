#ifndef __SQUARE_HPP__
#define __SQUARE_HPP__

#include <iostream>

class Square
{
public:
    Square();
    Square(std::pair<float, float> down_left, std::pair<float, float> up_right);
    Square(const Square &other);
    Square &operator=(const Square &other);
    std::pair<float, float> GetDLPoint() const;
    std::pair<float, float> GetURPoint() const;
    ~Square();

private:
    std::pair<float, float> m_down_left;
    std::pair<float, float> m_up_right;
};

#endif // __SQUARE_HPP__