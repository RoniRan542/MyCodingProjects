/************************************************
*Name: Ran Aharon Cohen                              *
*Reviewer:                                      *
*Date: 04.07.22                                 *
*File: mt_counting_sort_test.c                              *
************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "mt_counting_sort.h"

#define AMOUNT_OF_BUFFERS (500)
#define N_DICT (100)
#define MAX_THREADS_AMOUNT (9)


#define RUNTEST(test) {\
            if (!test)\
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

enum return_status
{
    ERROR = -1,
    SUCCESS = 0,
    FAILURE
};

/*static int TestDictionary(void);*/
static int SortLinuxDict(size_t num_of_threads);
int ValidateSort(unsigned char *arr, size_t len);

int main()
{
    
    return SortLinuxDict(8);
}

static int SortLinuxDict(size_t num_of_threads)
{
	size_t i = 0;
	int status = SUCCESS;
	FILE *infile = NULL;
	unsigned char *buffer;
	unsigned char *multi_buffer;
	long numbytes = 0;
	
	infile = fopen("/usr/share/dict/words", "r");
	if(infile == NULL)
    {
  		printf(" open failed");
  		return FAILURE;
    }
    
    fseek(infile, 0L, SEEK_END);
	numbytes = ftell(infile);	
	fseek(infile, 0L, SEEK_SET);	
	
	buffer = (unsigned char*)calloc(numbytes, sizeof(unsigned char));
	if(buffer == NULL)
    {
    	printf(" malloc failed");
  		return FAILURE;
    }
    
    fread(buffer, sizeof(unsigned char), numbytes, infile);
    fclose(infile);
    
	multi_buffer = (unsigned char*)calloc(numbytes * AMOUNT_OF_BUFFERS, sizeof(unsigned char));	
	if(multi_buffer == NULL)
    {
    	printf(" malloc failed");
  		return FAILURE;
    }
    	
    for(i = 0; i < AMOUNT_OF_BUFFERS; ++i)
    {
        strcat((char *)multi_buffer,(char *)buffer);
    }

    
    if(SUCCESS != MtCountingSort(multi_buffer, numbytes * AMOUNT_OF_BUFFERS, num_of_threads))
    {
    	return FAILURE;
    }
    
    status = ValidateSort(multi_buffer, numbytes * AMOUNT_OF_BUFFERS);
    RUNTEST(status);

    free(buffer);
    buffer = NULL;
    free(multi_buffer);
    multi_buffer = NULL;
    
    return SUCCESS;
}

int ValidateSort(unsigned char *arr, size_t len)
{
    size_t i = 0;

    --len;
    for (i = 0; i < len; ++i)
    {
        if (arr[i] > arr[i + 1])
        {
            return FAILURE;
        }
    }

    return SUCCESS;
}
/* Shreiber's test - not working 
static int TestDictionary(void)
{
	int result = 0;
	clock_t t = 0;
    size_t i = 0;
    size_t n_chars = 0;
    FILE *fp = NULL;
    unsigned char *buffer = NULL;
	size_t n_threads = 0;

    fp = fopen("/usr/share/dict/words", "r");
    if (NULL == fp)
    {
        puts("failed to open words.txt");
		return -1;
    }

	fseek(fp, 0, SEEK_END);
    n_chars = ftell(fp);
    fseek(fp, 0, SEEK_SET);

	printf("n_chars: %ld\n",n_chars);
    buffer = (unsigned char *)calloc(N_DICT * n_chars, sizeof(char));
	if(NULL == buffer)
    {
    	return -1;
    }

    for(n_threads = 1; n_threads < MAX_THREADS_AMOUNT; ++n_threads)
	{	
		fseek(fp, 0, SEEK_SET);

		for (i = 0; i < N_DICT; ++i)
		{
			fread(buffer + i * n_chars, sizeof(char), n_chars, fp);
		}
		
		t = time(NULL);
		MtCountingSort(buffer, N_DICT * n_chars, n_threads);
		t = time(NULL) - t;

		printf("threads amount: %ld, time - %ld\n", n_threads, t);	
	}

	fclose(fp);
	fp = NULL;

	printf("%s\n", buffer);
	PrintArr(buffer,n_chars);
	result = CheckSort(buffer, N_DICT * n_chars);

	free(buffer);
    buffer = NULL;
	
	return result;
}*/

