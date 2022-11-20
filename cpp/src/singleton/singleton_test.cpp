/*********************************************************
 * author: Ran Aharon Cohen                              *
 * reviewer: Andrei                                        *
 * date: 13.09.22                                        *
 * file: factory test                              *
 *********************************************************/
#include <iostream> //cout
#include <thread>   //cout
using namespace std;

#include "singleton.hpp"
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
int Phase2Test();
int Phase3Test();

class Base
{
private:
    int _x;

public:
    Base() : _x(5545) {}
    Base(int x) : _x(x) {}
    void Print() { std::cout << _x << "\n"; }
};

class Base2
{
private:
    double _x;

public:
    Base2() : _x(4.999) {}
    Base2(double x) : _x(x) {}
    void Print() { std::cout << _x << "\n"; }
};

class Derived : public Base
{
private:
    double _x;

public:
    Derived() : _x(4.999) {}
    Derived(double x) : _x(x) {}
    void PrintDouble() { std::cout << _x << "\n"; }
};

void Task1()
{
    std::cout << "Task1" << std::endl;
    Singleton<Base>::GetInstance()->Print();
    // b1 = Singleton<Base>::GetInstance();
}

void Task3()
{
    std::cout << "Task3" << std::endl;

    for (size_t i = 0; i < 5; ++i)
    {
        Singleton<Base>::GetInstance()->Print();
    }

    Singleton<Base>::DestroySingleton();
}

void Task2()
{
    std::cout << "Task2" << std::endl;

    Singleton<Base2>::GetInstance()->Print();
    Singleton<Base2>::DestroySingleton();
    // b2 = Singleton<Base2>::GetInstance();
}

int main()
{
    cout << "---- SINGLETON ----\n";

    // Phase1Test();
    //  Phase2Test();
    Phase3Test();
    return 0;
}

int Phase2Test()
{

    cout << "\n-- Phase 2 --\n";
    int result = 0;

    Singleton<Base>::GetInstance()->Print();
    Singleton<Base2>::GetInstance()->Print();
    Singleton<Base>::DestroySingleton();
    Singleton<Base2>::DestroySingleton();

    Singleton<Base>::GetInstance();
    Singleton<Base2>::GetInstance();

    RUNTEST(result);

    return 0;
}

int Phase1Test()
{

    cout << "\n-- Phase 1 --\n";
    int result = 0;

    std::thread thread1 = std::thread(Task1);
    std::thread thread2 = std::thread(Task2);
    std::thread thread3 = std::thread(Task3);

    thread1.join();
    thread2.join();
    thread3.join();

    RUNTEST(result);

    return 0;
}

int Phase3Test()
{

    cout << "\n-- Phase 3 --\n";
    int result = 0;
    Singleton<Base>::GetInstance()->Print();
    Singleton<Derived>::GetInstance()->PrintDouble();
    Singleton<Derived>::GetInstance()->Print();
    Singleton<Base>::DestroySingleton();
    Singleton<Derived>::DestroySingleton();

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
