/*************************************************
 *Name : Ran Aharon Cohen	 	    			 *
 *Date: 	14.07.22		            		 *
 *Description :implement the memcpy C function   *
 *************************************************/
#include <cassert> /* assert */
#include <cstring>
#include <cstdio>
#include <cstddef>
#include <iostream>

using namespace std;

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

enum status
{
    SUCCESS = 0,
    FALSE = 0,
    FAILURE = 1,
    TRUE = 1
};
static int ValCheck(int recieved_val, int expected_val, int line);

/* a simple solution O(n)*/
void *MyMemCpy(void *dest, const void *src, size_t n)
{
    char *dest_runner = (char *)dest;
    char *src_runner = (char *)src;

    assert(dest && src);

    while (n-- > 0)
    {
        *dest_runner++ = *src_runner++;
    }

    return dest;
}

int main(void)
{
    int result = 0;

    char str1[20] = {0};
    char str2[20] = {0};
    char str3[20] = {0};

    MyMemCpy(str1, "123456789", 5);
    result += ValCheck(strcmp(str1, "12345"), 0, __LINE__);
    cout << str1 << endl;
    MyMemCpy(str2, "123456789", 1);
    result += ValCheck(strcmp(str2, "1"), 0, __LINE__);
    cout << str2 << endl;
    MyMemCpy(str3, "123456789", 9);
    cout << str3 << endl;
    result += ValCheck(strcmp(str3, "123456789"), 0, __LINE__);
    RUNTEST(result);

    int a = 7;
    int *ptr = &a;

    cout << ptr << endl;
    cout << *ptr << endl;

    *(char *)&ptr = 1;

    cout << ptr << endl;
    cout << *ptr << endl;

    return 0;
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