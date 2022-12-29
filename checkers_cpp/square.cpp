
#include "square.hpp"

Square::Square() : m_down_left({0, 0}), m_up_right({0, 0})
{
    // empty
}

Square::Square(std::pair<float, float> down_left, std::pair<float, float> up_right)
    : m_down_left(down_left), m_up_right(up_right)
{
    // empty
}

Square::Square(const Square &other) : m_down_left(other.GetDLPoint()), m_up_right(other.GetURPoint())
{
    // empty
}

Square &Square::operator=(const Square &other)
{
    m_down_left = other.GetDLPoint();
    m_up_right = other.GetURPoint();

    return *this;
}

std::pair<float, float> Square::GetDLPoint() const
{
    return m_down_left;
}

std::pair<float, float> Square::GetURPoint() const
{
    return m_up_right;
}

Square::~Square()
{
    // empty
}