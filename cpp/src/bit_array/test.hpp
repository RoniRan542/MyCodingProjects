/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                           Test utils
- language: c++
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#include <iostream> /* cout */
#include <cstring>  /* strcmp */

void RunTest(bool test);
template <typename V>
bool CmpV(V expected_val, V recieved_val, int line);
template <>
bool CmpV<const char *>(const char *expected_val, const char *recieved_val, int line);

enum ret_val
{
    SUCCESS = 0,
    EQUAL = 0,
    FALSE = 0,
    TRUE = 1,
    FAIL = 1
};

bool const g_false = 0;
bool const g_true = 1;

#define TEST(expected, recieved) (status += CmpV(expected, recieved, __LINE__))

// colors
#define L ("\x1b[0m") <<
#define P ("\x1b[0;35m") <<
#define R ("\x1b[1;31m") <<
#define Y ("\x1b[0;33m") <<
#define G ("\x1b[0;32m") <<
#define B ("\x1b[0;34m") <<
#define C ("\x1b[0;36m") <<

template <typename V>
bool CmpV(V expected_val, V recieved_val, int line)
{
    if (recieved_val != expected_val)
    {
        std::cout << Y "FAIL in line " << line << ": ";
        std::cout << L "expected " << B expected_val << L ", recieved " << P recieved_val << L std::endl;
        return 1;
    }
    return 0;
}

template <>
bool CmpV<const char *>(const char *expected_val, const char *recieved_val, int line)
{
    if (strcmp(recieved_val, expected_val))
    {
        std::cout << Y "FAIL in line " << line << ": ";
        std::cout << L "expected " << C expected_val << L ", recieved " << P recieved_val << L std::endl;
        return 1;
    }
    return 0;
}

void RunTest(bool test)
{
    if (!(test))
    {
        std::cout << G "Kudos" << L std::endl;
    }
    else
    {
        std::cout << R "Fix me hooman" << L std::endl;
    }
}