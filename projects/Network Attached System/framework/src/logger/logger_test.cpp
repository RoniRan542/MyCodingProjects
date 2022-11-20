/*********************************************************
 * author: Ran Aharon Cohen                              *
 * reviewer:                                             *
 * date: 19.09.22                                        *
 * file: logger        test                              *
 *********************************************************/
#include <iostream> //cout
#include <ctime>

using namespace std;

#include "../singleton/singleton.hpp"
#include "logger.hpp"

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

const std::string currentDateTime()
{
    time_t now = time(0);
    struct tm tstruct;
    char buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

    return buf;
}

int main()
{
    cout << "---- LOGGER ----\n";

    Phase1Test();
    Phase2Test();

    return 0;
}

int Phase1Test()
{
    cout << "\n-- Phase 1 --\n";
    int result = 0;

    Singleton<Logger>::GetInstance()->SetPath("log.txt");
    std::string user_input;
    std::getline(std::cin, user_input);
    while (user_input != "exit")
    {
        Singleton<Logger>::GetInstance()->Log(user_input);
        std::getline(std::cin, user_input);
    }

    RUNTEST(result);

    return 0;
}

int Phase2Test()
{

    cout << "\n-- Phase 2 --\n";
    int result = 0;
    std::cout << "==========" << currentDateTime() << "==========\n";
    std::cout << "==========" << currentDateTime() << "==========\n";
    std::cout << "==========" << currentDateTime() << "==========\n";
    Singleton<Logger>::GetInstance()->Log("Phase first log");
    std::cout << "==========" << currentDateTime() << "==========\n";
    std::cout << "==========" << currentDateTime() << "==========\n";
    std::cout << "==========" << currentDateTime() << "==========\n";

    Singleton<Logger>::GetInstance()->Log("Phase second log");
    std::cout << "==========" << currentDateTime() << "==========\n";
    std::cout << "==========" << currentDateTime() << "==========\n";
    std::cout << "==========" << currentDateTime() << "==========\n";

    Singleton<Logger>::GetInstance()->Log("Phase third log");
    std::cout << "==========" << currentDateTime() << "==========\n";
    std::cout << "==========" << currentDateTime() << "==========\n";
    std::cout << "==========" << currentDateTime() << "==========\n";

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
