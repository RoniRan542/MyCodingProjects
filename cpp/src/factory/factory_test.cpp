/*********************************************************
 * author: Ran Aharon Cohen                              *
 * reviewer: Andrei                                        *
 * date: 13.09.22                                        *
 * file: factory test                              *
 *********************************************************/
#include <iostream> //cout
using namespace std;

#include "factory.hpp"
using namespace ilrd;

#define RUNTEST(test)                     \
    {                                     \
        if (0 == test)                    \
        {                                 \
            cout << "\x1b[0;32m\n";       \
            cout << "OK!\n\n";            \
            cout << "\x1b[0m";            \
        }                                 \
        else                              \
        {                                 \
            cout << "\x1b[1;31m";         \
            cout << "\nTest Failed!\n\n"; \
            cout << "\x1b[0m";            \
        }                                 \
    }
#define TEST(x, y) ValCheck(x, y, __LINE__)
static int ValCheck(double expected_val, double recieved_val, int line);

int Phase1Test();

class Base
{
private:
    int _x;

public:
    Base(int x) : _x(x) {}
    void Print() { std::cout << _x << "\n"; }
};

class Base2
{
private:
    double _x;

public:
    Base2(double x) : _x(x) {}
    void Print() { std::cout << _x << "\n"; }
};

Base *creator(const int &x)
{
    return new Base(x);
}

Base2 *creator2(const double &x)
{
    return new Base2(x);
}

int main()
{
    cout << "---- Thread Pool ----\n";

    Phase1Test();

    return 0;
}

int Phase1Test()
{

    cout << "\n-- Phase 1 --\n";
    int result = 0;

    std::string key("Base");

    Factory<Base, std::string, int> factory;

    factory.Add(key, creator);
    // factory.Add(key, creator);
    Base *b = factory.Create("Base", 7);
    Base *g = factory.Create("Base", 3.4);
    // Base *g = factory.Create("Baze", 7);
    b->Print(); // expect 7
    g->Print(); // expect 777

    Factory<Base2, std::string, double> factory2;
    factory2.Add("Base2:double", creator2);

    Base2 *d = factory2.Create("Base2:double", 2.7777);
    d->Print(); // expect 2.7777

    RUNTEST(result);

    return 0;
}

/******************************************************************************/

static int ValCheck(double expected_val, double recieved_val, int line)
{
    if (recieved_val != expected_val)
    {
        cout << "----------------FAIL line " << line << "----------------\n";
        cout << "got " << recieved_val << " when wanted " << expected_val << endl;
        return 1;
    }

    return 0;
}
