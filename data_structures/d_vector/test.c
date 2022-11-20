#include <stddef.h> /*size_t*/
#include <stdio.h> /*printf*/
#include <string.h> /*strcmp*/

int TestSize_t(const char *str, size_t expected, size_t result)
{
	/*printf("%s\n" , str);*/
	(void)str;
	return !(expected == result);
}
int TestInt(const char *str, int expected, int result)
{
	/*printf("%s\n" , str);*/
	(void)str;
	return !(expected == result);
}
int TestDouble(const char *str, double expected, double result)
{
	/*printf("%s\n" , str);*/
	(void)str;
	return !(expected == result);
}
int TestChar(const char *str, char expected, char result)
{
	/*printf("%s\n" , str);*/
	(void)str;
	return !(expected == result);
}
int TestString(const char *str, char *expected, char *result)
{
	/*printf("%s\n" , str);*/
	(void)str;
	return !( strcmp(expected,result) );
}
