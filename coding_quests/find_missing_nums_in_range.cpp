/*************************************************
 *Name : Ran Aharon Cohen	 	    			 *
 *Date: 	19.07.22		            		 *
 *Description : print missing numbers in array   *
 *within the range input     					 *
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

void FindMissingNumbersInRange(int *arr, size_t len, int *range)
{
    size_t i = 0;
    size_t offset = 0;
    int *lut = NULL;

    assert(arr && range);

    lut = new int[range[1] - range[0]];
    offset = 0 - range[0];

    for (i = 0; i < len; i++)
    {
        ++lut[offset + arr[i]];
    }

    for (i = range[0]; i < (size_t)(1 + range[1] - range[0]); ++i)
    {
        if (0 == lut[i + offset])
        {
            cout << " " << i;
        }
    }
    cout << "\n";

    delete[] lut;
    lut = 0;
}

int main(void)
{
    int result = 0;
    int arr[] = {1, 4, 5, 6, 8, 9, 13, 44};
    int range[] = {0, 44};

    FindMissingNumbersInRange(arr, 8, range);

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