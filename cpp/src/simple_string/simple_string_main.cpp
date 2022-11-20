
#include <iostream>
#include <cstring>

#include "simple_string.hpp"
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

int main()
{
    int result = SUCCESS;

    String s1("RoniRanCohen");
    String s2("RoniRan");

    result += ValCheck(strcmp(s1.Cstr(), "RoniRanCohen"), 0, __LINE__);
    result += ValCheck(s1.Length(), 12, __LINE__);
    result += ValCheck(strcmp(s2.Cstr(), "RoniRan"), 0, __LINE__);
    result += ValCheck(s2.Length(), 7, __LINE__);

    String s3;
    result += ValCheck(strcmp(s3.Cstr(), ""), 0, __LINE__);
    result += ValCheck(s3.Length(), 0, __LINE__);
    s3 = s1;
    result += ValCheck(strcmp(s3.Cstr(), s1.Cstr()), 0, __LINE__);
    result += ValCheck(s3.Length(), s1.Length(), __LINE__);

    result += ValCheck(s3 == s2, 0, __LINE__);
    result += ValCheck(s3 == s1, 1, __LINE__);
    result += ValCheck(s3 > s2, 1, __LINE__);
    result += ValCheck(s3 < s2, 0, __LINE__);
    result += ValCheck("123" > s2, 0, __LINE__);
    result += ValCheck("123" < s2, 1, __LINE__);
    result += ValCheck("123" == s2, 0, __LINE__);
    result += ValCheck("RoniRanCohen" == s1, 1, __LINE__);

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
