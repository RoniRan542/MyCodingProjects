#include <iostream> //cout
#include <string>   //std::string
#include <cstring>  //strlen(), strcmp()

using namespace std;

#include "bit_array.hpp"

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

int main()
{
    BitArray<20> bit_arr;
    BitArray<20> bit_arr2;
    bit_arr2.SetAll(true);
    bit_arr |= bit_arr2;
    cout << bit_arr.Get(0) << endl;
    cout << bit_arr.Get(1) << endl;
    cout << bit_arr.Get(2) << endl;
    cout << bit_arr.Get(3) << endl;
    cout << bit_arr.Get(4) << endl;
    cout << bit_arr.Get(5) << endl;
    cout << bit_arr.Get(6) << endl;
    cout << bit_arr.Get(8) << endl;
    cout << bit_arr.Get(7) << endl;
    cout << bit_arr.Get(9) << endl;

    bit_arr2.SetAll(false);
    bit_arr &= bit_arr2;
    cout << bit_arr.Get(0) << endl;
    cout << bit_arr.Get(1) << endl;
    cout << bit_arr.Get(2) << endl;
    cout << bit_arr.Get(3) << endl;
    cout << bit_arr.Get(4) << endl;
    cout << bit_arr.Get(5) << endl;
    cout << bit_arr.Get(6) << endl;
    cout << bit_arr.Get(8) << endl;
    cout << bit_arr.Get(7) << endl;
    cout << bit_arr.Get(9) << endl;

    bit_arr2.SetAll(true);
    cout << "\n"
         << (bit_arr == bit_arr2) << endl;
    cout << (bit_arr != bit_arr2) << "\n"
         << endl;
    bit_arr ^= bit_arr2;
    cout << bit_arr.Get(0) << endl;
    cout << bit_arr.Get(1) << endl;
    cout << bit_arr.Get(2) << endl;
    cout << bit_arr.Get(3) << endl;
    cout << bit_arr.Get(4) << endl;
    cout << bit_arr.Get(5) << endl;
    cout << bit_arr.Get(6) << endl;
    cout << bit_arr.Get(8) << endl;
    cout << bit_arr.Get(7) << endl;
    cout << bit_arr.Get(9) << endl;
    /* bit_arr[0] = false;
    bit_arr[6] = false; */
    cout << bit_arr.Count() << endl;
    cout << bit_arr.ToString() << endl;
    /* cout << bit_arr.Get(0) << endl;
    cout << bit_arr.Get(1) << endl;
    bit_arr[0] = true;
    bit_arr[1] = true;
    cout << bit_arr.Get(0) << endl;
    cout << bit_arr.Get(1) << endl;
    bit_arr[0] = false;

    cout << bit_arr.Get(0) << endl;

    bit_arr[0] = bit_arr[1];
    cout << bit_arr.Get(0) << endl;

    bit_arr.SetAll(true);
    cout << bit_arr.Get(5) << endl;
    cout << bit_arr.Get(6) << endl;
    cout << bit_arr.Get(8) << endl;
    cout << bit_arr.Get(7) << endl;

    bit_arr.SetAll(false);
    cout << "\n\n"
         << endl;
    cout << bit_arr.Get(0) << endl;
    cout << bit_arr.Get(1) << endl;
    cout << bit_arr.Get(2) << endl;
    cout << bit_arr.Get(3) << endl;
    cout << bit_arr.Get(4) << endl;
    cout << bit_arr.Get(5) << endl;
    cout << bit_arr.Get(6) << endl;
    cout << bit_arr.Get(8) << endl;
    cout << bit_arr.Get(7) << endl;
    cout << bit_arr.Get(9) << endl;
    bit_arr[7] = true;
    bit_arr[9] = true;
    bit_arr.FlipAll();
    cout << "\n\n"
         << endl;
    cout << bit_arr.Get(0) << endl;
    cout << bit_arr.Get(1) << endl;
    cout << bit_arr.Get(2) << endl;
    cout << bit_arr.Get(3) << endl;
    cout << bit_arr.Get(4) << endl;
    cout << bit_arr.Get(5) << endl;
    cout << bit_arr.Get(6) << endl;
    cout << bit_arr.Get(7) << endl;
    cout << bit_arr.Get(8) << endl;
    cout << bit_arr.Get(9) << endl; */

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