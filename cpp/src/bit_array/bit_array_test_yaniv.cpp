#include <cstring>  /* memcpy, strlen, for my test classes */

#include "bit_array.hpp"
#include "test.hpp" /* my testing header. it is located in ../include */

#define PRINT std::cout
#define END std::endl

const bool g_on = 1;
const bool g_off = 0;

void CtorDtorTest();
int SetGetTest();
int TestPhaseOne();
void PhaseOneQuestion();
int TestBoolSquareBrackets();
int TestFlipBit();
int TestFlipAll();
int TestEqual();
int TestCount();
int TestToString();
int TestSetAll();
int TestOr();
int TestAnd();
int TestXor();

using namespace ilrd;

template <size_t N>
void Print(BitArray<N> &arr);

int main()
try
{
    CtorDtorTest();
    RunTest(SetGetTest());
    RunTest(TestBoolSquareBrackets());
    RunTest(TestFlipBit());
    RunTest(TestFlipAll());
    RunTest(TestPhaseOne());
    PhaseOneQuestion();
    RunTest(TestEqual());
    RunTest(TestCount());
    RunTest(TestToString());
    RunTest(TestSetAll());
    RunTest(TestOr());
    RunTest(TestAnd());
    RunTest(TestXor());

    return 0;
}
catch (const std::exception &e)
{
    std::cerr << e.what() << '\n';
}

void CtorDtorTest()
{
    PRINT << "Ctor Dtor test" << END;
    BitArray<3> a;
    BitArray<8> b;
    BitArray<21> c;

    BitArray<3> aa = a;
    // BitArray<3> ab = b; conversion from ‘BitArray<8>’ to non-scalar type ‘BitArray<3>’ requested
    BitArray<8> bb(b);
    // BitArray<8> bc(c); fails at compilation
}

int SetGetTest()
{
    int status = 0; // updated via macro TEST
    BitArray<21> a;

    TEST(g_off, a.Get(0));
    TEST(g_off, a.Get(17));
    TEST(g_off, a.Get(8));
    TEST(g_off, a.Get(16));

    a.Set(0, 1);
    a.Set(17, 1);
    a.Set(8, 1);
    a.Set(16, 1);

    TEST(g_on, a.Get(0));
    TEST(g_on, a.Get(17));
    TEST(g_on, a.Get(8));
    TEST(g_on, a.Get(16));

    a.Set(16, 1);
    TEST(g_on, a.Get(16));

    a.Set(0, 0);
    a.Set(17, 0);
    a.Set(8, 0);
    a.Set(16, 0);

    TEST(g_off, a.Get(0));
    TEST(g_off, a.Get(17));
    TEST(g_off, a.Get(8));
    TEST(g_off, a.Get(16));

    a.Set(0, 0);
    TEST(g_off, a.Get(0));

    return status;
}

int TestPhaseOne()
{
    int status = 0; // updated via macro TEST
    BitArray<21> a;
    BitArray<21> h;
    BitArray<21> g;

    const BitArray<21> b;

    h.FlipAll();
    g[3] = h[3];
    TEST(g_on, g.Get(3));

    for (int i = 0; i < 21; ++i)
    {
        if (a[1])
        {
            status += 1;
        }
    }

    a.FlipAll();

    for (int i = 0; i < 21; ++i)
    {
        if (a[1])
        {
            status += 0;
        }
    }


    Print(a);

    for (int i = 0; i < 21; ++i)
    {
        if (i % 2)
        {
            TEST(g_on, a.Get(i));
            TEST(g_off, b.Get(i));
            a[i] = b[i];
            TEST(g_off, a.Get(i));
        }
    }

    Print(a);

    for (int i = 0; i < 21; ++i)
    {
        if (!(i % 2))
        {
            TEST(g_on, a.Get(i));
            a[i] = false;
            TEST(g_off, a.Get(i));
        }
    }

    Print(a);

    return status;
}

void PhaseOneQuestion()
{
    BitArray<21> a;
    const BitArray<21> b;

    if (!(b[1]))
    {
        PRINT << "calling [] with const calls bool returning [] operator" << END;
    }

    if (!(a[1]))
    {
        PRINT << "calling [] with non const builds a BitHandler and calls bool operator" << END;
    }
}

int TestBoolSquareBrackets()
{
    int status = 0; // updated via macro TEST
    const BitArray<21> a;
    BitArray<21> b;

    TEST(g_off, a[0]);
    TEST(g_off, a[17]);
    TEST(g_off, a[8]);
    TEST(g_off, a[16]);

    return status;
}

int TestFlipBit()
{
    int status = 0; // updated via macro TEST
    BitArray<21> a;

    TEST(g_off, a.Get(0));
    TEST(g_off, a.Get(17));
    TEST(g_off, a.Get(8));
    TEST(g_off, a.Get(16));

    a.Flip(0);
    a.Flip(17);
    a.Flip(8);
    a.Flip(16);

    TEST(g_on, a.Get(0));
    TEST(g_on, a.Get(17));
    TEST(g_on, a.Get(8));
    TEST(g_on, a.Get(16));

    a.Flip(0);
    a.Flip(17);
    a.Flip(8);
    a.Flip(16);

    TEST(g_off, a.Get(0));
    TEST(g_off, a.Get(17));
    TEST(g_off, a.Get(8));
    TEST(g_off, a.Get(16));

    return status;
}

int TestFlipAll()
{
    int status = 0; // updated via macro TEST
    BitArray<21> a;

    for (int i = 0; i < 21; ++i)
    {
        TEST(g_off, a.Get(i));
    }

    Print(a);
    a.FlipAll();

    for (int i = 0; i < 21; ++i)
    {
        TEST(g_on, a.Get(i));
    }

    Print(a);
    return status;
}

int TestEqual()
{
    int status = 0; // updated via macro TEST

    BitArray<21> a;
    BitArray<21> b;

    TEST(g_true, a == b);
    TEST(g_false, a != b);

    a.Set(5, 1);

    TEST(g_false, a == b);
    TEST(g_true, a != b);

    a.Set(5, 0);

    TEST(g_true, a == b);
    TEST(g_false, a != b);

    return status;
}

int TestCount()
{
    int status = 0; // updated via macro TEST

    BitArray<21> a;
    BitArray<9> b;

    TEST(0LU, a.Count());
    PRINT << "count " << END;
    a.FlipAll();
    Print(a);
    TEST(21LU, a.Count());

    b.FlipAll();
    TEST(9LU, b.Count());

    return status;
}

int TestToString()
{
    int status = 0; // updated via macro TEST

    BitArray<9> b;
    b.FlipAll();
    BitArray<21> a;
    a.Set(1, 1);
    a.Set(19, 1);

    std::string a_str = a.ToString();
    std::string b_str = b.ToString();

    std::string a_str_test = "010000000000000000010";
    std::string b_str_test = "111111111";

    TEST(a_str_test, a_str);
    TEST(b_str_test, b_str);

    TEST(a_str_test.size(), a_str.size());
    TEST(b_str_test.size(), b_str.size());

    return status;
}

int TestSetAll()
{
    int status = 0; // updated via macro TEST
    BitArray<21> a;

    for (int i = 0; i < 21; ++i)
    {
        TEST(g_off, a.Get(i));
    }

    a.SetAll(1);
    for (int i = 0; i < 21; ++i)
    {
        TEST(g_on, a.Get(i));
    }
    Print(a);

    a.SetAll(0);
    for (int i = 0; i < 21; ++i)
    {
        TEST(g_off, a.Get(i));
    }
    Print(a);

    return status;
}

int TestOr()
{
    int status = 0; // updated via macro TEST
    BitArray<6> a;
    BitArray<6> b;

    a.Set(0, 1);
    a.Set(1, 1);
    a.Set(2, 1);
    a.Set(3, 1);

    b |= a;

    for (int i = 0; 6 > i; ++i)
    {
        if(i < 4)
        {
            TEST(g_on, a.Get(i));
        }
        else
        {
            TEST(g_off, a.Get(i));
        }
    }

    a.FlipAll();
    b |= a;

    for (int i = 0; 6 > i; ++i)
    {
        if (i < 4)
        {
            TEST(g_off, a.Get(i));
        }
        else
        {
            TEST(g_on, a.Get(i));
        }
    }

    return status;
}

int TestAnd()
{
    int status = 0; // updated via macro TEST
    BitArray<6> a;
    BitArray<6> b;

    b.FlipAll();
    a.Set(0, 1);
    a.Set(1, 1);
    a.Set(2, 1);
    a.Set(3, 1);

    b &= a;
    Print(b);

    for (int i = 0; 6 > i; ++i)
    {
        if (i < 4)
        {
            TEST(g_on, a.Get(i));
        }
        else
        {
            TEST(g_off, a.Get(i));
        }
    }

    a.Set(5, 1);
    a.Set(4, 1);
    a.Set(0, 0);
    a.Set(1, 0);

    b &= a;
    Print(b);
    TEST(g_off, b.Get(0));
    TEST(g_off, b.Get(1));
    TEST(g_on, b.Get(2));
    TEST(g_on, b.Get(3));
    TEST(g_off, b.Get(4));
    TEST(g_off, b.Get(5));

    return status;
}

int TestXor()
{
    int status = 0; // updated via macro TEST
    BitArray<6> a;
    BitArray<6> b;

    a.Set(0, 1);
    a.Set(1, 1);
    a.Set(2, 1);
    a.Set(3, 1);

    b ^= a;
    Print(b);

    for (int i = 0; 6 > i; ++i)
    {
        if (i < 4)
        {
            TEST(g_on, a.Get(i));
        }
        else
        {
            TEST(g_off, a.Get(i));
        }
    }

    b ^= b;
    Print(b);
    for (int i = 0; 6 > i; ++i)
    {
        TEST(g_off, b.Get(i));
    }

    return status;
    }

    template <size_t N>
    void Print(BitArray<N> &arr)
{
    for (size_t i = 0; i < N; ++i)
    {
        PRINT << arr.Get(i) << " ";
    }
    PRINT << END;
}
