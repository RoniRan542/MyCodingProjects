#include <stdio.h> /*printf*/
#include <stddef.h> /*size_t*/


#include "d_vector.h"


#define RUNTEST(test) {\
            if (0 == test)\
            {\
                printf("\x1b[0;32m");\
                printf("OK!\n\n");\
                printf("\x1b[0m");\
            }\
            else\
            {\
                printf("\x1b[1;31m");\
                printf("\nTest Failed!\n\n");\
                printf("\x1b[0m");\
            }\
        }


int TestVector_tInt();
int TestVector_tDouble();
int TestVector_tFloat();
int TestVector_tChar();
int TestVector_tString();
int TestSize_t(const char *str, size_t expected, size_t result);
int TestString(const char *str, char *expected, char *result);
int TestChar(const char *str, char expected, char result);
int TestDouble(const char *str, double expected, double result);
int TestInt(const char *str, int expected, int result);

int main()
{
    
	printf("----------------Test of Int vector----------------\n");
    RUNTEST(TestVector_tInt());
    printf("\n----------------Test of Double vector----------------\n");
	RUNTEST(TestVector_tDouble());
	printf("\n----------------Test of Float vector----------------\n");
	RUNTEST(TestVector_tFloat());
	printf("\n----------------Test of Char vector----------------\n");
	RUNTEST(TestVector_tChar());
	printf("\n----------------Test of String vector----------------\n");
	RUNTEST(TestVector_tString());

    return 0;
}

int TestVector_tInt()
{
	int num = 4;
	int num2 = 6;
	size_t capacity = 2;
	d_vector_t *vector_int  = DVectorCreate(sizeof(int) , capacity);
	int result = 0;
	 
	result += TestSize_t("size", 0 , DVectorSize(vector_int));
	RUNTEST(result);
	result += TestSize_t("capacity" , capacity , DVectorCapacity(vector_int));
	RUNTEST(result);
	result += TestInt("IsEmpty", 1 , DVectorIsEmpty(vector_int));
	RUNTEST(result);
	result += TestInt("PushBack", 0 , DVectorPushBack(vector_int , &num));
	RUNTEST(result);
	result += TestInt("GetElement", 4 , *(int *)DVectorGetElement(vector_int , 0));
	RUNTEST(result);
	result += TestInt("PushBack", 0 , DVectorPushBack(vector_int , &num2));
	RUNTEST(result);
	result += TestInt("GetElement", 6 , *(int *)DVectorGetElement(vector_int , 1));
	RUNTEST(result);
	result += TestInt("PushBack", 0 , DVectorPushBack(vector_int , &num));
	RUNTEST(result);
	result += TestInt("GetElement", 6 , *(int *)DVectorGetElement(vector_int , 1));
	RUNTEST(result);
	result += TestSize_t("size", 3 , DVectorSize(vector_int));
	RUNTEST(result);
	result += TestSize_t("capacity" , capacity*2 , DVectorCapacity(vector_int));
	RUNTEST(result);
	result += TestInt("PushBack", 0 , DVectorPushBack(vector_int , &num2));
	RUNTEST(result);
	result += TestInt("PushBack", 0 , DVectorPushBack(vector_int , &num));
	RUNTEST(result);
	result += TestSize_t("capacity" , capacity*4 , DVectorCapacity(vector_int));
	RUNTEST(result);
	result += TestSize_t("Reserve" , 0, DVectorReserve(vector_int , 4));
	RUNTEST(result);
	result += TestSize_t("capacity" , 6 , DVectorCapacity(vector_int));
	RUNTEST(result);
	result += TestInt("PopBack" , 0 , DVectorPopBack(vector_int));
	RUNTEST(result);
	result += TestInt("GetElement", 4 , *(int *)DVectorGetElement(vector_int , 4));
	RUNTEST(result);
	result += TestInt("PopBack" , 0 , DVectorPopBack(vector_int));
	RUNTEST(result);
	result += TestInt("PopBack" , 0 , DVectorPopBack(vector_int));
	RUNTEST(result);
	result += TestInt("PopBack" , 0 , DVectorPopBack(vector_int));
	RUNTEST(result);
	result += TestSize_t("size", 1 , DVectorSize(vector_int));
	RUNTEST(result);
	result += TestInt("IsEmpty", 0 , DVectorIsEmpty(vector_int));
	RUNTEST(result);
	result += TestSize_t("capacity" , 3 , DVectorCapacity(vector_int));
	RUNTEST(result);
	DVectorDestroy(vector_int);
	return result;
}

int TestVector_tDouble()
{
	double num = 4.0;
	double num2 = 6.0;
	size_t capacity = 2;
	d_vector_t *vector_double  = DVectorCreate(sizeof(double) , capacity);
	double result = 0;
	 
	result += TestSize_t("size", 0 , DVectorSize(vector_double));
	RUNTEST(result);
	result += TestSize_t("capacity" , capacity , DVectorCapacity(vector_double));
	RUNTEST(result);
	result += TestInt("IsEmpty", 1 , DVectorIsEmpty(vector_double));
	RUNTEST(result);
	result += TestInt("PushBack", 0 , DVectorPushBack(vector_double , &num));
	RUNTEST(result);
	result += TestDouble("GetElement", 4.0 , *(double *)DVectorGetElement(vector_double , 0));
	RUNTEST(result);
	result += TestInt("PushBack", 0 , DVectorPushBack(vector_double , &num2));
	RUNTEST(result);
	result += TestDouble("GetElement", 6.0 , *(double *)DVectorGetElement(vector_double , 1));
	RUNTEST(result);
	result += TestInt("PushBack", 0 , DVectorPushBack(vector_double , &num));
	RUNTEST(result);
	result += TestDouble("GetElement", 6.0 , *(double *)DVectorGetElement(vector_double , 1));
	RUNTEST(result);
	result += TestSize_t("size", 3 , DVectorSize(vector_double));		
	RUNTEST(result);
	result += TestSize_t("capacity" , capacity*2 , DVectorCapacity(vector_double));
	RUNTEST(result);
	result += TestInt("PushBack", 0 , DVectorPushBack(vector_double , &num2));
	RUNTEST(result);
	result += TestInt("PushBack", 0 , DVectorPushBack(vector_double , &num));
	RUNTEST(result);
	result += TestSize_t("capacity" , capacity*4 , DVectorCapacity(vector_double));
	RUNTEST(result);
	result += TestSize_t("Reserve" , 0, DVectorReserve(vector_double , 4));
	RUNTEST(result);
	result += TestSize_t("capacity" , 6.0 , DVectorCapacity(vector_double));
	RUNTEST(result);
	result += TestInt("PopBack" , 0 , DVectorPopBack(vector_double));
	RUNTEST(result);
	result += TestDouble("GetElement", 4 , *(double *)DVectorGetElement(vector_double , 4));
	RUNTEST(result);
	result += TestInt("PopBack" , 0 , DVectorPopBack(vector_double));
	RUNTEST(result);
	result += TestInt("PopBack" , 0 , DVectorPopBack(vector_double));
	RUNTEST(result);
	result += TestInt("PopBack" , 0 , DVectorPopBack(vector_double));
	RUNTEST(result);
	result += TestSize_t("size", 1 , DVectorSize(vector_double));
	RUNTEST(result);
	result += TestInt("IsEmpty", 0 , DVectorIsEmpty(vector_double));
	RUNTEST(result);
	result += TestSize_t("capacity" , 3 , DVectorCapacity(vector_double));
	RUNTEST(result);
	DVectorDestroy(vector_double);
	return result;
}

int TestVector_tFloat()
{
	float num = 4.0;
	float num2 = 6.0;
	size_t capacity = 2;
	d_vector_t *vector_float  = DVectorCreate(sizeof(float) , capacity);
	float result = 0;
	 
	result += TestSize_t("size", 0 , DVectorSize(vector_float));
	result += TestSize_t("capacity" , capacity , DVectorCapacity(vector_float));
	result += TestInt("IsEmpty", 1 , DVectorIsEmpty(vector_float));
	result += TestInt("PushBack", 0 , DVectorPushBack(vector_float , &num));
	result += TestDouble("GetElement", 4.0 , *(float *)DVectorGetElement(vector_float , 0));
	result += TestInt("PushBack", 0 , DVectorPushBack(vector_float , &num2));
	result += TestDouble("GetElement", 6.0 , *(float *)DVectorGetElement(vector_float , 1));
	result += TestInt("PushBack", 0 , DVectorPushBack(vector_float , &num));
	result += TestDouble("GetElement", 6.0 , *(float *)DVectorGetElement(vector_float , 1));
	result += TestSize_t("size", 3 , DVectorSize(vector_float));		
	result += TestSize_t("capacity" , capacity*2 , DVectorCapacity(vector_float));
	result += TestInt("PushBack", 0 , DVectorPushBack(vector_float , &num2));
	result += TestInt("PushBack", 0 , DVectorPushBack(vector_float , &num));
	result += TestSize_t("capacity" , capacity*4 , DVectorCapacity(vector_float));
	result += TestSize_t("Reserve" , 0, DVectorReserve(vector_float , 4));
	result += TestSize_t("capacity" , 6.0 , DVectorCapacity(vector_float));
	result += TestInt("PopBack" , 0 , DVectorPopBack(vector_float));
	result += TestDouble("GetElement", 4 , *(float *)DVectorGetElement(vector_float , 4));
	result += TestInt("PopBack" , 0 , DVectorPopBack(vector_float));
	result += TestInt("PopBack" , 0 , DVectorPopBack(vector_float));
	result += TestInt("PopBack" , 0 , DVectorPopBack(vector_float));
	result += TestSize_t("size", 1 , DVectorSize(vector_float));
	result += TestInt("IsEmpty", 0 , DVectorIsEmpty(vector_float));
	result += TestSize_t("capacity" , 3 , DVectorCapacity(vector_float));
	DVectorDestroy(vector_float);
	return result;
}

int TestVector_tChar()
{
	char ch = 'a';
	char ch2 = 'b';
	size_t capacity = 2;
	d_vector_t *vector_char  = DVectorCreate(sizeof(char) , capacity);
	char result = 0;
	 
	result += TestSize_t("size", 0 , DVectorSize(vector_char));
	result += TestSize_t("capacity" , capacity , DVectorCapacity(vector_char));
	result += TestInt("IsEmpty", 1 , DVectorIsEmpty(vector_char));
	result += TestInt("PushBack", 0 , DVectorPushBack(vector_char , &ch));
	result += TestChar("GetElement", 'a' , *(char *)DVectorGetElement(vector_char , 0));
	result += TestInt("PushBack", 0 , DVectorPushBack(vector_char , &ch2));
	result += TestChar("GetElement", 'b' , *(char *)DVectorGetElement(vector_char , 1));
	result += TestInt("PushBack", 0 , DVectorPushBack(vector_char , &ch));
	result += TestChar("GetElement", 'b' , *(char *)DVectorGetElement(vector_char , 1));
	result += TestSize_t("size", 3 , DVectorSize(vector_char));		
	result += TestSize_t("capacity" , capacity*2 , DVectorCapacity(vector_char));
	result += TestInt("PushBack", 0 , DVectorPushBack(vector_char , &ch2));
	result += TestInt("PushBack", 0 , DVectorPushBack(vector_char , &ch));
	result += TestSize_t("capacity" , capacity*4 , DVectorCapacity(vector_char));
	result += TestSize_t("Reserve" , 0, DVectorReserve(vector_char , 4));
	result += TestSize_t("capacity" , 6 , DVectorCapacity(vector_char));
	result += TestInt("PopBack" , 0 , DVectorPopBack(vector_char));
	result += TestChar("GetElement", 'a' , *(char *)DVectorGetElement(vector_char , 4));
	result += TestInt("PopBack" , 0 , DVectorPopBack(vector_char));
	result += TestInt("PopBack" , 0 , DVectorPopBack(vector_char));
	result += TestInt("PopBack" , 0 , DVectorPopBack(vector_char));
	result += TestSize_t("size", 1 , DVectorSize(vector_char));
	result += TestInt("IsEmpty", 0 , DVectorIsEmpty(vector_char));
	result += TestSize_t("capacity" , 3 , DVectorCapacity(vector_char));
	DVectorDestroy(vector_char);
	return result;
}

int TestVector_tString()
{
	char str1[] = "find May a shidoh";
	char str22[] = "find Ran a shidoh";
	char *str = str1;
	char *str2 = str22;
	size_t capacity = 2;
	d_vector_t *vector_string  = DVectorCreate(sizeof(char) , capacity);
	char result = 0;
	 
	result += TestSize_t("size", 0 , DVectorSize(vector_string));
	result += TestSize_t("capacity" , capacity , DVectorCapacity(vector_string));
	result += TestInt("IsEmpty", 1 , DVectorIsEmpty(vector_string));
	result += TestInt("PushBack", 0 , DVectorPushBack(vector_string , &str));
	result += TestString("GetElement", "find May a shidoh" , (char *)DVectorGetElement(vector_string , 0));
	result += TestInt("PushBack", 0 , DVectorPushBack(vector_string , &str2));
	result += TestString("GetElement", "find Ran a shidoh" , (char *)DVectorGetElement(vector_string , 1));
	result += TestInt("PushBack", 0 , DVectorPushBack(vector_string , &str));
	result += TestString("GetElement", "find Ran a shidoh" , (char *)DVectorGetElement(vector_string , 1));
	result += TestSize_t("size", 3 , DVectorSize(vector_string));		
	result += TestSize_t("capacity" , capacity*2 , DVectorCapacity(vector_string));
	result += TestInt("PushBack", 0 , DVectorPushBack(vector_string , &str2));
	result += TestInt("PushBack", 0 , DVectorPushBack(vector_string , &str));
	result += TestSize_t("capacity" , capacity*4 , DVectorCapacity(vector_string));
	result += TestSize_t("Reserve" , 0, DVectorReserve(vector_string , 4));
	result += TestSize_t("capacity" , 6 , DVectorCapacity(vector_string));
	result += TestInt("PopBack" , 0 , DVectorPopBack(vector_string));
	result += TestString("GetElement", "find May a shidoh" , (char *)DVectorGetElement(vector_string , 4));
	result += TestInt("PopBack" , 0 , DVectorPopBack(vector_string));
	result += TestInt("PopBack" , 0 , DVectorPopBack(vector_string));
	result += TestInt("PopBack" , 0 , DVectorPopBack(vector_string));
	result += TestSize_t("size", 1 , DVectorSize(vector_string));
	result += TestInt("IsEmpty", 0 , DVectorIsEmpty(vector_string));
	result += TestSize_t("capacity" , 3 , DVectorCapacity(vector_string));
	DVectorDestroy(vector_string);
	return result;
}


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
