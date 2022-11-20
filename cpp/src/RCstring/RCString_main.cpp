
#include <iostream>
#include <cstring>

#include "RCString.hpp"

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
#define TEST(x, y) ValCheck(x, y, __LINE__)

using namespace std;
using namespace ilrd_RCString;

enum status
{
    SUCCESS,
    FAILURE
};

static int ValCheck(int recieved_val, int expected_val, int line);

int main()
{
    int result = SUCCESS;

    RCString s1("RoniRanCohen");
    RCString s2("RoniRan");

    result += ValCheck(strcmp(s1.RCstr(), "RoniRanCohen"), 0, __LINE__);
    result += ValCheck(s1.Length(), 12, __LINE__);
    result += ValCheck(strcmp(s2.RCstr(), "RoniRan"), 0, __LINE__);
    result += ValCheck(s2.Length(), 7, __LINE__);
    RCString s3(s1);
    result += ValCheck(strcmp(s3.RCstr(), "RoniRanCohen"), 0, __LINE__);
    s3 = s2;
    result += ValCheck(strcmp(s3.RCstr(), "RoniRan"), 0, __LINE__);

    result += ValCheck(s3[2], 'n', __LINE__);
    result += ValCheck(s3[2] = 'k', 'k', __LINE__);
    cout << s3 << "\n";
    cin >> s1; // insert ABCDE
    result += ValCheck(strcmp(s1.RCstr(), "ABCDE"), 0, __LINE__);

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
