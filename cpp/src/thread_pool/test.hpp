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
size_t g_error_counter = 0;

#define TEST(expected, recieved) (status += CmpV(expected, recieved, __FILE__, __LINE__))
#define PRINT std::cout
#define END std::endl

// colors
#define DEFAULT ("\x1b[0m") <<
#define PURPLE ("\x1b[0;35m") <<
#define RED ("\x1b[1;31m") <<
#define YELLOW ("\x1b[0;33m") <<
#define GREEN ("\x1b[0;32m") <<
#define BLUE ("\x1b[0;34m") <<
#define CYAN ("\x1b[0;36m") <<

template <typename T>
bool CmpV(T expected_val, T recieved_val, const char *file, int line)
{
    if (recieved_val != expected_val)
    {
        PRINT << RED "FAIL " << DEFAULT "in file: " << YELLOW file
              << DEFAULT ", line: " << YELLOW line << END;
        PRINT << DEFAULT "expected " << CYAN expected_val
              << DEFAULT ", recieved " << PURPLE recieved_val
              << DEFAULT std::endl;
        ++g_error_counter;
        return FAIL;
    }
    return SUCCESS;
}

template <>
bool CmpV<const char *>(const char *expected_val, const char *recieved_val, const char *file, int line)
{
    if (strcmp(recieved_val, expected_val))
    {
        PRINT << RED "FAIL " << DEFAULT "in file: " << YELLOW file
              << DEFAULT ", line: " << YELLOW line << END;
        PRINT << DEFAULT "expected " << CYAN expected_val
              << DEFAULT ", recieved " << PURPLE recieved_val
              << DEFAULT std::endl;
        ++g_error_counter;
        return FAIL;
    }
    return SUCCESS;
}

void RunTest(bool test)
{
    if (!(test))
    {
        PRINT << GREEN "Kudos" << DEFAULT END;
    }
    else
    {
        PRINT << RED "Fix me hooman :(" << DEFAULT END;
    }
}

void TestSummerize()
{
    if (!(g_error_counter))
    {
        PRINT << PURPLE "So long and thanks for all the fish" << DEFAULT END;
    }
    else
    {
        PRINT << RED "Error count: " << g_error_counter << DEFAULT END;
    }
}