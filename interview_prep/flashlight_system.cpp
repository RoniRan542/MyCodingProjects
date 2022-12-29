// Design a system that controls a led with a key bord, with classes and the relationships

#include <iostream>

using namespace std;

enum State
{
    OFF,
    ON,
    BLINK
};

class Flashlight
{
public:
    Flashlight(enum State init_state) : m_state(init_state)
    {
    }
    void ChangeState(enum State state)
    {
        m_state = state;
    }

private:
    enum State m_state;
};

class Control
{
public:
    Control();
    void Listen()
    {
        while (1)
        {
            getline(cin, m_input);
            if (m_input == "on")
            {
                m_flash.ChangeState(ON);
                continue;
            }
            if (m_input == "off")
            {
                m_flash.ChangeState(OFF);
                continue;
            }
            if (m_input == "blink")
            {
                m_flash.ChangeState(BLINK);
                continue;
            }
        }
    }

private:
    Flashlight m_flash;
    string m_input;
};
