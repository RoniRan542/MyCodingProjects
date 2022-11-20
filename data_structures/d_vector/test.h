#ifndef __TEST_H__
#define __TEST_H__
#include <stddef.h>


int TestSize_t(const char *str, size_t expected, size_t result);
int TestInt(const char *str, int expected, int result);
int TestDouble(const char *str, double expected, double result);
int TestChar(const char *str, char expected, char result);
int TestString(const char *str, char *expected, char *result);


#endif /*__TEST_H__*/


