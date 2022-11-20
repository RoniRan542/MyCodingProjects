
#include <iostream>
#include <cstring>
#include <list>

#include "shapes.hpp"

#define RUNTEST(test)                                          \
    {                                                          \
        if (0 == test)                                         \
        {                                                      \
            cout << "\x1b[0;32m\x1b[1m\x1b[7m\x1b[5m" << endl; \
            cout << "OK" << endl;                              \
            cout << "\x1b[0m" << endl;                         \
        }                                                      \
        else                                                   \
        {                                                      \
            cout << "\x1b[1;31m\x1b[1m\x1b[7m\x1b[5m" << endl; \
            cout << "Test Failed" << endl;                     \
            cout << "\x1b[0m" << endl;                         \
        }                                                      \
    }

using namespace std;
using namespace ilrd;

enum status
{
    SUCCESS,
    FAILURE
};

static int ValCheck(int recieved_val, int expected_val, int line);

static void PrintList(list<const Shape *> &shape_list)
{

    list<const Shape *>::iterator iter = shape_list.begin();

    while (iter != shape_list.end())
    {
        (*iter)->Draw();
        ++iter;
    }
}

int main()
{
    int result = SUCCESS;

    list<const Shape *> shape_list;
    Line l[4];
    Square s[4];
    Rectangle r[4];
    Circle c[4];

    for (size_t i = 0; i < 4; ++i)
    {
        shape_list.push_back(&l[i]);
        shape_list.push_back(&s[i]);
        shape_list.push_back(&r[i]);
        shape_list.push_back(&c[i]);
    }

    for (size_t i = 0; i < 4; ++i)
    {
        l[i].Move(i * 10);
        s[i].Move(i * 10);
        r[i].Move(i * 10);
        c[i].Move(i * 10);
    }

    PrintList(shape_list);
    RUNTEST(result);

    return result;
}

static int ValCheck(int recieved_val, int expected_val, int line)
{
    if (recieved_val != expected_val)
    {
        cout << "----------------FAIL line " << line << "----------------\n " << endl;
        cout << "got " << recieved_val << ", when wanted " << expected_val << "\n " << endl;

        return 1;
    }
    return 0;
}
