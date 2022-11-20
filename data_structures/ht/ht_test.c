/***************************************************************
*Name : Ran Aharon Cohen	 									 *
*Reviewar:  														 *
*Date:  03/20/22													 *												 
*Description : 														 *
**********************************************************************/
#include <stdio.h> /* for printf */
#include <assert.h>/*asssert */
#include <stdlib.h>

#include "dll.h"
#include "ht.h"
#define Max_len (256)
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

int CreateDestroyTest(void);
int InsertTest(void);
int TestDict(void);
int ForEachFind(void);
int TestInt(const char *str, int expected, int result);
int IsMatch(const void *data, void *parameter);
int Cmp(const void *data, const void * old_data, void *parameter);
int ActionAdd(void *data, void *parameter);
int Print(void *data, void *param);
static void PrintList(dll_list_t *list);
size_t HashIntFunc(const void *data, void *param);
size_t HashStrFunc(const void *data, void *param);
static int SpellChecker(ht_t *ht, char *input);
static void RunSpellCheck(ht_t *ht);	

int main()
{
   	
   	
   	
	printf("\n----------------Test for Create Destroy ----------------\n");
    RUNTEST(CreateDestroyTest());
   	printf("\n----------------Test for InsertTest ----------------\n");
    RUNTEST(InsertTest());
  
     printf("\n----------------Test for ForEachFind ----------------\n");
    RUNTEST(ForEachFind());
   /* printf("\n----------------Test for TestDict ----------------\n");
    RUNTEST(TestDict());*/
    
    return 0;
}

int CreateDestroyTest(void)
{
	int result = 0;
	int param = 0;
	
	ht_t *ht = NULL;
	ht = HTCreate(&HashIntFunc, &param, &Cmp, &param, 5);
	result += TestInt("is not NULL? ",0, NULL == ht);
	result += TestInt("HTIsEmpty? ",1, HTIsEmpty(ht));
	result += TestInt("HTSize? ",0, HTSize(ht));
	
	HTDestroy(ht);
	return result;
}

int InsertTest()
{
    int result = 0;
   	ht_t *ht = NULL;
   	int param = 0;
    int arr[70] = {0};
    int i = 0;
    ht = HTCreate(&HashIntFunc, &param, &Cmp, &param, 5);
    if (NULL == ht)
    {
        return 1;
    }
    
    result += !(HTIsEmpty(ht));
    for (i = 0; i < 70; ++i)
    {
        arr[i] = i;
        result += HTInsert(ht, &arr[i]);
        result += ((size_t)i + 1 != HTSize(ht));
        result += HTIsEmpty(ht);
    }
    
    for (i = 69; 0 <= i; --i)
    {
        HTRemove(ht, &arr[i]);
        printf("%ld\n",HTSize(ht));
        result += ((size_t)i  != HTSize(ht));
        RUNTEST(result);
    }
	

    HTDestroy(ht);

    return result;
}

int ForEachFind()
{
    int result = 0;
   	ht_t *ht = NULL;
   	int param = 0;
   	int arr[70] = {0};
    int i = 0;
    int stam = 180;
    
    ht = HTCreate(&HashIntFunc, &param, &Cmp, &param, 20);
    if (NULL == ht)
    {
        return 1;
    }
    

    if (NULL == ht)
    {
        return 1;
    }

    for (i = 0; i < 70; ++i)
    {
        arr[i] = i;
        result += HTInsert(ht, &arr[i]);
        result += (&arr[i] != HTFind(ht, &arr[i]));
    }
	RUNTEST(result);
	result += (NULL == HTFind(ht, &param));
	result += (NULL != HTFind(ht, &stam));
	RUNTEST(result);
	/*printf("stam (180) = %d", HTFind(ht, &stam));*/
    
	RUNTEST(result);
   /* result += (0 != HTForEach(ht, &Print, &stam));	*/
    
    HTDestroy(ht);

    return result;
}

int TestDict(void)
{
	int result = 0;
	int param = 0;
	FILE *infile;
	char *buffer;
	long numbytes;
   	char *word;
   	char *runner = NULL; 
	ht_t *ht = NULL;
	
	ht = HTCreate(&HashStrFunc, &param, &Cmp, &param, 5);
	
	infile = fopen("/usr/share/dict/words", "r");
	if(infile == NULL)
    {
  		printf(" open failed");
  		return 1;
    }
    
    fseek(infile, 0L, SEEK_END);
	numbytes = ftell(infile);	
	fseek(infile, 0L, SEEK_SET);	
	
	buffer = (char*)calloc(numbytes, sizeof(char));	
	if(buffer == NULL)
    {
    	printf(" malloc failed");
  		return 1;
    }
    
    fread(buffer, sizeof(char), numbytes, infile);
    fclose(infile);
    runner = buffer;
    word = buffer;
    
    while('\0' != *runner)
    {
    	
    	if('\n' == *runner)
    	{	
    		*runner = '\0';
    		HTInsert(ht, word);
    		word = runner + 1;
    	}
    	++runner;
    }
    
    HTInsert(ht, word);
    
    RunSpellCheck(ht);
   	free(buffer);
   
	HTDestroy(ht);
	
	return result;
}
static void RunSpellCheck(ht_t *ht)
{
	char input[30] = "";
	printf("\n\n Fun started :-)\n ");
	scanf("%s",input);
	
	while(strcmp(input,"quit"))
	{
		SpellChecker(ht, input);
		scanf("%s",input);
	}
	
	printf("Fun saddenlly ended :-( ");
}

int TestInt(const char *str, int expected, int result)
{
    printf("%s\n" , str);
    (void)str;
    return !(expected == result);
}
 

int Cmp(const void *data, const void * old_data, void *parameter)
{
	(void)parameter;
	return (*(int *)data - *(int *)old_data); 
}


int ActionAdd(void *data, void *parameter)
{
	*(int *)data += *(int *)parameter;
	
	return 0;
}

int Print(void *data, void *param)
{
	(void)param;
	printf("%s ~|\n", (char *)data);
	
	return 0;
}

int IsMatch(const void *data, void *parameter)
{
	return (*(int*)data == *(int*)parameter);
}

size_t HashStrFunc(const void *data, void *param)
{
	char *key = (char *)data;
	
	size_t len = strnlen(key, Max_len);
	size_t hash_code = 0;
	size_t i = 0;
	
	for(i = 0; len > i; ++i)
	{
		hash_code += key[i];
		hash_code *= key[i];	
	}
	
	(void)param;
	return hash_code;
}

size_t HashIntFunc(const void *data, void *param)
{
	int key = *(int *)data;
	
	
	size_t hash_code = 0;
	size_t i = 0;
	
	hash_code = key * 12345;
	
	(void)param;
	return hash_code;
}

static int SpellChecker(ht_t *ht, char *input)
{
	if(NULL == HTFind(ht,input))
	{
		printf("couldn't find %s you'r looking for in the dictionary\n", input);
	}
	else
	{
		printf("%s was found in the dictionary! Trilili Tralala \n", input);
	}
	
	return 0;
}
