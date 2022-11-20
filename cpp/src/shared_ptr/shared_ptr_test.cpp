#include <iostream> //cout
#include <string>   //std::string
#include <cstring>  //strlen(), strcmp()
using namespace std;

#include "shared_ptr.hpp"
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

class String
{
public:
    char str[10];
};

class Number
{
public:
    int num;
};

int main()
{
    cout << "---- Shared Pointer ----\n\n";

    int result = 0;

    /**************************************************************************/

    String *name = new String;
    memset(name->str, 0, strlen("hagar") + 1);
    strcpy(name->str, "hagar");

    cout << "-- CTOR --\n";
    SharedPtr<String> s_ptr1(name);

    result += strcmp("hagar", (*s_ptr1).str);
    result += strcmp("hagar", s_ptr1->str);
    result += strcmp("hagar", s_ptr1.GetPtr()->str);

    RUNTEST(result);

    /**************************************************************************/

    cout << "-- CCTOR --\n";
    SharedPtr<String> s_ptr2(s_ptr1);

    result += strcmp("hagar", (*s_ptr2).str);
    result += strcmp("hagar", s_ptr2->str);
    result += strcmp("hagar", s_ptr2.GetPtr()->str);

    RUNTEST(result);

    /**************************************************************************/

    cout << "-- OP = --\n";
    SharedPtr<String> s_ptr3 = s_ptr2;

    result += strcmp("hagar", (*s_ptr3).str);
    result += strcmp("hagar", s_ptr3->str);
    result += strcmp("hagar", s_ptr3.GetPtr()->str);

    String *last_name = new String;
    memset(last_name->str, 0, strlen("gur-arie") + 1);
    strcpy(last_name->str, "gur-arie");

    SharedPtr<String> s_ptr4(last_name);

    result += strcmp("gur-arie", (*s_ptr4).str);
    result += strcmp("gur-arie", s_ptr4->str);
    result += strcmp("gur-arie", s_ptr4.GetPtr()->str);

    s_ptr3 = s_ptr4;
    result += strcmp("gur-arie", (*s_ptr3).str);
    result += strcmp("gur-arie", s_ptr3->str);
    result += strcmp("gur-arie", s_ptr3.GetPtr()->str);

    RUNTEST(result);

    /**************************************************************************/

    cout << "-- OP == --\n";

    result += TEST(true, s_ptr1 == s_ptr2);
    result += TEST(true, s_ptr3 == s_ptr4);
    result += TEST(false, s_ptr1 == s_ptr3);
    result += TEST(false, s_ptr2 == s_ptr4);

    RUNTEST(result);

    /**************************************************************************/

    cout << "-- OP != --\n";

    result += TEST(true, s_ptr1 != s_ptr3);
    result += TEST(true, s_ptr2 != s_ptr4);
    result += TEST(false, s_ptr1 != s_ptr2);
    result += TEST(false, s_ptr3 != s_ptr4);

    RUNTEST(result);

    /**************************************************************************/

    Number *lucky_num = new Number;
    lucky_num->num = 7;

    SharedPtr<Number> s_ptr5(lucky_num);

    cout << "-- OP *, ->, getter() --\n";
    result += TEST(7, (*s_ptr5).num);
    result += TEST(7, s_ptr5->num);
    result += TEST(7, s_ptr5.GetPtr()->num);

    RUNTEST(result);

    /**************************************************************************/

    /*  cout << "-- CCTOR (class Y) --\n";

    RUNTEST(result);
  */

    /**************************************************************************/

    /*  cout << "-- OP = (class Y) --\n";

     s_ptr4 = s_ptr5;
     result += TEST(7, (*s_ptr4).num);
     result += TEST(7, s_ptr4->num);
     result += TEST(7, s_ptr4.GetPtr()->num);

    RUNTEST(result);

  */

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