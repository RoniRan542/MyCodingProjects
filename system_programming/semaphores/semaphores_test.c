/************************************************
*Name: Ran Aharon Cohen                            *
*Reviewer: Osher                                *
*Date: 16.06.22                                 *
*File: semaphore_test.c                              *
************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "semaphores.h"

enum status
{
	SUCCESS = 0,
	FAILURE
};

static int ExtractArgBySpace(char *input, int *num, int *undo);

int main(int argc, char *argv[])
{
	int status = SUCCESS;
	int id = SemCreate(argv[1], 1, 5);
	char input[30] = {0};
	int num = 0;
	int undo = 0;
	
	while('x' != input[0] && 0 <= status)
	{
		scanf("%[^\n]%*c",input);
		num = 0;
		undo = 0;
		switch(input[0])
		{
			case 'v':
				   	 printf("semaphore value: %d\n", SemGetVal(id));
				   	 break;
			case 'd':
					 ExtractArgBySpace(input, &num, &undo);
					 status = SemDecrement(id, num, undo);
					 break;
			case 'i':
					 ExtractArgBySpace(input, &num, &undo);
					 SemIncrement(id,  num, undo);
					 break;
		   case 'x':
		   			break;
		   default:
					continue;
					 
		}
		
	}
	
	
	SemDestroy(id);
	
    return 0;
}

static int ExtractArgBySpace(char *input, int *num, int *undo)
{
	int i = 0;
	char arg[25] = "";
	char *runner = arg;
	input = input + 2;
	
	
	while('\0' != *input && ' ' != *input)
	{
		*runner = *input; 
		++input;
		++runner;
	}
	*runner = '\0';
	*num = atoi(arg);
	printf("num: %d\n", *num);
	if(' ' == *input)
	{
		++input;
		*undo = atoi(input);
	}
	printf("undo: %d\n", *undo);
	
	return 0;
}
