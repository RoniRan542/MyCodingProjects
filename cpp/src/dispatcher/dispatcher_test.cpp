#include <iostream>

#include "dispatcher.hpp"
#include "../singleton/singleton.hpp"

using namespace ilrd;
class Point
{
public:
    Point(size_t x = 0, size_t y = 0);
    ~Point();
    void SetPoint(int x, int y);
    int GetX();
    int GetY();

private:
    size_t m_x;
    size_t m_y;
};

class Grid
{
public:
    Grid(size_t x = 100, size_t y = 100);
    ~Grid();
    void SetPoint(int x, int y);
    int GetPointX();
    int GetPointY();

private:
    friend class Singleton;
    const size_t m_xsize;
    const size_t m_ysize;
    Point mouse_cursor_position;
};

Grid::Grid(size_t x, size_t y) : m_xsize(x), m_ysize(y)
{
    // empty
}

Grid::~Grid()
{
    // empty
}

void Grid::SetPoint(int x, int y)
{
    mouse_cursor_position.SetPoint(x, y);
}

int Grid::GetPointX()
{
    return mouse_cursor_position.GetX();
}

int Grid::GetPointY()
{
    return mouse_cursor_position.GetY();
}

Point::Point(size_t x, size_t y) : m_x(x), m_y(y)
{
    // empty
}

Point::~Point()
{
    // empty
}

void Point::SetPoint(int x, int y)
{
    m_x += x;
    m_y += y;
}

int Point::GetX()
{
    return m_x;
}

int Point::GetY()
{
    return m_y;
}

class MouseEvent
{
public:
    MouseEvent(int horiz, int vertic);
    ~MouseEvent();
    void SetMove(int horiz, int vertic);
    int GetHorizontalMove() const;
    int GetVerticalMove() const;

private:
    int m_horizontal;
    int m_vertical;
};

MouseEvent::MouseEvent(int horiz, int vertic) : m_horizontal(horiz), m_vertical(vertic)
{
    // empty
}

MouseEvent::~MouseEvent()
{
    // empty
}

int MouseEvent::GetHorizontalMove() const
{
    return m_horizontal;
}

int MouseEvent::GetVerticalMove() const
{
    return m_vertical;
}

void MouseEvent::SetMove(int horiz, int vertic)
{
    m_horizontal = horiz;
    m_vertical = vertic;
}

void InvokeMove(const MouseEvent &e)
{
    Singleton<Grid>::GetInstance()->SetPoint(e.GetHorizontalMove(), e.GetVerticalMove());
    std::cout << "New position: x = " << Singleton<Grid>::GetInstance()->GetPointX()
              << ",y = " << Singleton<Grid>::GetInstance()->GetPointY() << std::endl;
}

void InvokeDir(const MouseEvent &e)
{
    std::string move;
    if (e.GetHorizontalMove() > 0)
    {
        move += "RIGHT :";
    }
    else if (e.GetVerticalMove() < 0)
    {
        move += "LEFT :";
    }
    else
    {
        move += "0 :";
    }

    if (e.GetVerticalMove() > 0)
    {
        move += " UP";
    }
    else if (e.GetVerticalMove() < 0)
    {
        move += " DOWN";
    }
    else
    {
        move += " 0";
    }

    std::cout << "Mouse Direction: " << move << std::endl;
}

void InvokeMove2(const MouseEvent &e)
{
    Singleton<Grid>::GetInstance()->SetPoint(e.GetHorizontalMove(), e.GetVerticalMove());
    std::cout << "New position: x = " << Singleton<Grid>::GetInstance()->GetPointX()
              << ",y = " << Singleton<Grid>::GetInstance()->GetPointY() << std::endl;
}

void PubDied()
{
    std::cout << "PubDied" << std::endl;
}

int main()
{
    Singleton<Grid>::GetInstance();
    Default_Listener<MouseEvent> listener(PubDied, InvokeMove);
    Default_Listener<MouseEvent> listener2(PubDied, InvokeDir);
    Default_Listener<MouseEvent> listener3(PubDied, InvokeDir);
    Dispatcher<MouseEvent> dispatcher;
    MouseEvent m_e1(7, 5);
    dispatcher.AddListener(&listener);
    dispatcher.Invoke(m_e1);
    MouseEvent m_e2(5, 7);
    dispatcher.Invoke(m_e2);
    dispatcher.AddListener(&listener2);
    MouseEvent m_e3(50, -3);
    dispatcher.Invoke(m_e3);
    Dispatcher<MouseEvent> dispatcher2;
    dispatcher2.AddListener(&listener);
    MouseEvent m_e4(-35, 22);
    dispatcher2.Invoke(m_e4);
    // dispatcher.RemoveListener(&listener);
    dispatcher2.Invoke(m_e1);
    return 0;
}
