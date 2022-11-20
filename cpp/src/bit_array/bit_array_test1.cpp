#include <iostream> //cout
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

int Phase1Test();
int Phase2Test();

int main()
{
    cout << "---- Bit Array ----\n";

    Phase1Test();
    Phase2Test();

    return 0;
}

int Phase1Test()
{
    cout << "\n-- Phase 1 --\n";

    BitArray<6> b1;
    const BitArray<6> b2;
    BitArray<6> b3;
    int result = 0;

    b1[1] = true;
    result += TEST(1, 1 == b1[1]);

    b1[0] = b2[0];
    result += TEST(1, 0 == b1[0]);

    b3[0] = true;
    result += TEST(1, 1 == b3[0]);

    b1[0] = b3[0];
    result += TEST(1, 1 == b1[0]);

    RUNTEST(result);

    return 0;
}

int Phase2Test()
{
    cout << "\n-- Phase 2 --\n";

    cout << "\n-- == , != --\n";
    BitArray<6> b1;
    BitArray<6> b2;
    int result = 0;

    result += TEST(1, b1 == b2);
    result += TEST(0, b1 != b2);

    for (size_t i = 0; i < 6; i += 2)
    {
        b1[i] = true;
    }

    result += TEST(0, b1 == b2);
    result += TEST(1, b1 != b2);

    RUNTEST(result);

    cout << "\n-- Get() --\n";

    for (size_t i = 0; i < 6; i += 2)
    {
        result += TEST(1, b1[i]);
    }

    for (size_t i = 1; i < 6; i += 2)
    {
        result += TEST(0, b1[i]);
    }

    RUNTEST(result);

    cout << "\n-- Set() --\n";

    for (size_t i = 1; i < 6; i += 2)
    {
        b1.Set(i, 1);
    }

    for (size_t i = 1; i < 6; i += 2)
    {
        result += TEST(1, b1[i]);
    }

    for (size_t i = 1; i < 6; i += 2)
    {
        b1.Set(i, 0);
    }

    for (size_t i = 1; i < 6; i += 2)
    {
        result += TEST(0, b1[i]);
    }

    RUNTEST(result);

    cout << "\n-- SetAll() --\n";

    BitArray<6> b3;

    for (size_t i = 0; i < 6; ++i)
    {
        result += TEST(0, b3[i]);
    }

    b3.SetAll(true);

    for (size_t i = 0; i < 6; ++i)
    {
        result += TEST(true, b3[i]);
    }

    RUNTEST(result);

    cout << "\n-- Flip Bit --\n";

    b3.Flip(0);
    b3.Flip(1);

    result += TEST(0, b3[0]);
    result += TEST(0, b3[1]);

    b3.Flip(0);

    result += TEST(1, b3[0]);

    RUNTEST(result);

    cout << "\n-- Flip All --\n";

    BitArray<6> b4;

    for (size_t i = 1; i < 6; i += 2)
    {
        b4.Set(i, 1);
    }

    for (size_t i = 1; i < 6; i += 2)
    {
        result += TEST(1, b4[i]);
    }

    b4.FlipAll();

    for (size_t i = 1; i < 6; i += 2)
    {
        result += TEST(0, b4[i]);
    }

    for (size_t i = 0; i < 6; i += 2)
    {
        result += TEST(1, b4[i]);
    }

    RUNTEST(result);

    cout << "\n-- Count On Bits --\n";

    BitArray<10> b5;

    result += TEST(0, b5.Count());

    for (size_t i = 1; i < 10; i += 2)
    {
        b5.Set(i, 1);
    }

    result += TEST(5, b5.Count());

    b5.Set(1, 0);
    b5.Set(3, 0);

    result += TEST(3, b5.Count());

    b5.SetAll(1);

    result += TEST(10, b5.Count());

    RUNTEST(result);

    cout << "\n-- To String --\n";
    BitArray<10> b6;

    for (size_t i = 1; i < 10; i += 2)
    {
        b6.Set(i, 1);
    }

    cout << "b6 to string: " << b6.ToString() << endl;

    cout << "\n-- Or Operator --\n";

    b6 |= b5;

    cout << "b6 to string: " << b6.ToString() << endl;

    cout << "\n-- And Operator --\n";

    b5.SetAll(0);

    b6 &= b5;

    cout << "b6 to string: " << b6.ToString() << endl;

    cout << "\n-- Xor Operator --\n";

    b5.SetAll(1);

    b6 ^= b5;

    cout << "b6 to string: " << b6.ToString() << endl;

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
