/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
- Author:Ran
- Date: 05/31/22
- Reviewed By: Karen
*ktour_test.c
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#include <stdio.h> /* for printf */
#include <time.h>  /*time*/

#include "../include/ktour.h"

#define RUNTEST(test)                     \
	{                                     \
		if (!(test))                      \
		{                                 \
			printf("\x1b[0;34m");         \
			printf("OK!\n");              \
			printf("\x1b[0m");            \
		}                                 \
		else                              \
		{                                 \
			printf("\x1b[1;31m");         \
			printf("\nTest Failed!\n\n"); \
			printf("\x1b[0m");            \
		}                                 \
	}

static int CompereInt(int expected_val, int recieved_val, int line);
static int CheckBuffer(int *buffer);
static void Print(int *buffer);

void LUTest();
int TourTest();

int main()
{
	/* LUTest();*/

	RUNTEST(TourTest());
	return 0;
}

int TourTest()
{
	int result = 0;
	int start = 0;
	int buffer[64] = {0};
	int i = 0;
	clock_t before = 0;
	clock_t after = 0;
	clock_t min = 1000;
	clock_t diff = 0;
	int best = 0;
	clock_t max = 0;
	clock_t sum = 0;
	int worst = 0;

	printf("Testing KnightTour: \n");

	for (; i < 64; ++i)
	{
		before = clock();
		result += (0 != KnightTour(i, buffer));
		Print(buffer);
		result += (0 != CheckBuffer(buffer));
		after = clock();
		diff = (after - before);
		printf("start in square number %d is: %ld\n", i, diff);
		if (min > diff)
		{
			min = diff;
			best = i;
		}

		if (max < diff)
		{
			max = diff;
			worst = i;
		}
		sum += diff;
	}

	printf("best square number is: %d time: %ld\n", best, min);
	printf("worst square number is: %d time: %ld\n", worst, max);
	printf("avg time: %ld\n", (sum / 64));

	return result;
}

/*************************************************************************/
static int CheckBuffer(int *buffer)
{
	int i = 0;
	int j = 0;

	for (; i < 63; ++i)
	{
		for (j = i + 1; j < 64; ++j)
		{
			if (buffer[i] == buffer[j])
			{
				printf("failed: %d\n", buffer[i]);
				return 1;
			}
		}
	}

	return 0;
}

static void Print(int *buffer)
{
	int i = 0;

	for (; i < 64; ++i)
	{
		printf("%d ", buffer[i]);
	}
	puts("");
}

static int CompereInt(int expected_val, int recieved_val, int line)
{
	if (recieved_val != expected_val)
	{
		printf("\x1b[1;33m");
		printf("----------------FAIL line %d----------------\n", line);
		printf("expected %d, recieved %d\n", expected_val, recieved_val);
		printf("\x1b[0m");
		return 1;
	}

	return 0;
}
