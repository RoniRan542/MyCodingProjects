/*********************************************************
 * author: Ran Aharon Cohen                              *
 * reviewer: Mariana                                     *
 * date: 13.09.22                                        *
 * file: monitor & dllLoader test                                    *
 *********************************************************/
#include <iostream> //cout
#include <thread>   //this_thread

#include "DirMonitor.hpp"
#include "DynamicLoader.hpp"
using namespace std;
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

void foo(std::string path, DllLoader &dll)
{
    cout << "---- callback foo ----\n";
    cout << path << endl;

    dll.AddDll(path);
    cout << "---- dll open success ----\n";
}

void MonitorThread(DirMonitor &dmonitor)
{
    dmonitor.Run();
}

int main()
{
    cout << "---- DirMonitor ----\n";

    Phase1Test();

    return 0;
}

int Phase1Test()
{
    DllLoader *dll = new DllLoader;
    std::cout << "DllLoader was created" << std::endl;
    DirMonitor dmonitor("../temp", foo, dll);
    dmonitor.Run();
    std::this_thread::sleep_for(std::chrono::seconds(100));

    delete dll;

    return 0;
}