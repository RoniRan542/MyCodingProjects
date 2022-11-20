/*Author: Ran Aharon Cohen
 Date: 28.04.22
 Reviewed By: 
 */
#include <stdio.h> /* printf */ 

#include "simpleshell.h"

#define RUNTEST(test) {\
            if (0 == test)\
            {\
                printf("\x1b[0;32m\x1b[1m\x1b[7m\x1b[5m");\
                printf("OK!\n\n");\
                printf("\x1b[0m");\
            }\
            else\
            {\
                printf("\x1b[1;31m\x1b[1m\x1b[7m\x1b[5m");\
                printf("Test Failed!\n\n");\
                printf("\x1b[0m");\
            }\
        }

int total_fails = 0;

enum status
{
	SUCCESS = 0,
	BOOL_FALSE = 0,
	FAIL = 1,
	BOOL_TRUE = 1
} status_t;


int ValCheckInt(int recieved_val, int expected_val, int line);
int ValCheckSizeT(size_t recieved_val, size_t expected_val, int line_test);
int TestInt(int expected, int result);
int TestCreate(void);

int main()
{
    int result = 0;
    printf("\n\n***************************************************************\n");
    printf("*              Test For Create Function                       *\n");
    printf("***************************************************************\n\n");
    result = TestCreate();
   	printf("THE FINAL RESULT OF THE TEST: ");
   	RUNTEST(result);
  
   	RUNTEST(result);
   	
    return 0;
}

int TestCreate(void)
{
	int result = 0;
	int status = 0;
	const char *fork_or_system = "fork";
	
	result = ValCheckInt(SimpleShell(fork_or_system), 0, __LINE__);
	status += result;
	result = ValCheckInt(SimpleShell("system"), 0, __LINE__);
	status += result;
	
   	printf("THE FINAL RESULT OF THE TEST: ");
   	RUNTEST(status);
	
	return status;
}

int Cmp(const void *new_data, const void * old_data, void *parameter)
{
	(void)parameter;
	return (*(int *)new_data - *(int *)old_data); 
}

int TestInt(int expected, int result)
{
	return ((expected == result) ? 0 : 1);
}

int ValCheckInt(int recieved_val, int expected_val, int line_test)
{
	if (recieved_val != expected_val)
	{
		printf("-----------------------FAIL line ");
		printf("\x1b[7m\x1b[1m%d\x1b[0m", line_test);
		printf("--------------------------\n");
		
		printf("got \x1b[1m%d\x1b[0m", recieved_val);
		printf(", when wanted \x1b[1m%d\x1b[0m\n", expected_val);

		++total_fails;
		
		return FAIL;
	}
	
	return SUCCESS;
}

int ValCheckSizeT(size_t recieved_val, size_t expected_val, int line_test)
{
	if (recieved_val != expected_val)
	{
		printf("-----------------------FAIL line ");
		printf("\x1b[7m\x1b[1m%d\x1b[0m", line_test);
		printf("--------------------------\n");
		
		printf("got \x1b[1m%lu\x1b[0m", recieved_val);
		printf(", when wanted \x1b[1m%lu\x1b[0m\n", expected_val);

		++total_fails;
		
		return FAIL;
	}
	
	return SUCCESS;
}

void PrintTotalFailes(void)
{
	if (0 < total_fails)
	{
		printf("\x1b[5m\x1b[31m");
		printf("*********************** Total Fails = ");
		printf("\x1b[4m%d\x1b[0m", total_fails);
		printf("\x1b[5m\x1b[31m");
		printf("*********************");
		printf("\x1b[0m\n");
	}

	else
	{
		printf("\x1b[5m\x1b[32m");
		printf("*************** NO FAILESSS!! TRILILI TRALALA! **************");
		printf("\x1b[0m\n");
	}
}


