/***************************************************************
*Name : Ran Aharon Cohen		 									 *
*Reviewar:  														 *
*Date:  10/3/22													 *												 
*Description : 														 *
**********************************************************************/
#include <stdio.h> /*printf*/

#include "slinked.h"


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
int TestCreate();     
int TestIsEmpty();
int TestInsertCount();
int TestSetGetData();
int TestIsIterEqual();
int TestEndBegin();
int TestFind();
int IsMatch(const void *data, void *parameter);
int TestForEach();
int AddNum( void *data, void *parameter);
int TestSize_t(const char *str, size_t expected, size_t result);
int TestInt(const char *str, int expected, int result);
int TestPointers(const char *str, void *expected, void *result);

int main()
{
    
	printf("----------------Test for create----------------\n");
    RUNTEST(TestCreate());
    printf("\n----------------Test for is empty----------------\n");
	RUNTEST(TestIsEmpty());
	printf("\n----------------Test for  begin end----------------\n");
	RUNTEST(TestEndBegin());
	printf("\n----------------Test for Insert and Count----------------\n");
	RUNTEST(TestInsertCount());
	printf("\n----------------Test for Set Get Data----------------\n");
	RUNTEST(TestSetGetData());
	printf("\n----------------Test for Is Iter Equal----------------\n");
	RUNTEST(TestIsIterEqual());
	printf("\n----------------Test for Find----------------\n");
	RUNTEST(TestFind());
	printf("\n----------------Test for For Each----------------\n");
	RUNTEST(TestForEach());
    return 0;
}

int TestCreate()
{
	int result = 0 ;
	s_linked_list_t *list1 = SLinkedListCreate();
	
	result += TestInt("IsEmpty", 1 , SLinkedListIsEmpty(list1));
	RUNTEST(result);
	result += TestSize_t("ListCount" , 0 , SLinkedListCount(list1));
	RUNTEST(result);
	SLinkedListDestroy(list1);

	return result;
}

int TestIsEmpty()
{
	int result = 0 ;
	s_linked_list_t *list1 = SLinkedListCreate();
	s_list_iter_t iter = SLinkedListBegin(list1);
	
	result += TestInt("IsEmpty", 1 , SLinkedListIsEmpty(list1));
	RUNTEST(result);
	result += TestInt("Insert" , 4 , *(int *)SLinkedListInsertBefore(iter , (void *)4));
	RUNTEST(result);
	result += TestInt("IsEmpty", 0 , SLinkedListIsEmpty(list1));
	RUNTEST(result);
	result += TestInt("Insert" , 4 , *(int *)SLinkedListInsertBefore(iter , (void *)4));
	RUNTEST(result);
	result += TestInt("Insert" , 4 , *(int *)SLinkedListInsertBefore(iter , (void *)4));
	RUNTEST(result);
	result += TestInt("IsEmpty", 0 , SLinkedListIsEmpty(list1));
	RUNTEST(result);
	SLinkedListRemove(iter);
	result += TestInt("IsEmpty", 0 , SLinkedListIsEmpty(list1));
	RUNTEST(result);
	SLinkedListRemove(iter);
	result += TestInt("IsEmpty", 0 , SLinkedListIsEmpty(list1));
	RUNTEST(result);
	result += TestSize_t("ListCount" , 1 , SLinkedListCount(list1));
	RUNTEST(result);
	SLinkedListRemove(SLinkedListBegin(list1));
	result += TestSize_t("ListCount" , 0 , SLinkedListCount(list1));
	RUNTEST(result);
	result += TestInt("IsEmpty", 1 , SLinkedListIsEmpty(list1));
	RUNTEST(result);
	SLinkedListDestroy(list1);
	

	return result;
}


int TestInsertCount()
{
	int result = 0 ;
	int a = 4;
	int b = 6;
	int c = 54;
	s_linked_list_t *list1 = SLinkedListCreate();
	s_list_iter_t iter = SLinkedListBegin(list1);
	s_list_iter_t iter2 = SLinkedListBegin(list1);
	
	result += TestInt("IsEmpty", 1 , SLinkedListIsEmpty(list1));
	RUNTEST(result);
	result += TestSize_t("ListCount" , 0 , SLinkedListCount(list1));
	RUNTEST(result);
	result += TestInt("Insert" , 4 , *(int *)SLinkedListGetData(SLinkedListInsertBefore(iter ,&a)));
	RUNTEST(result);
	result += TestInt("IsEmpty", 0 , SLinkedListIsEmpty(list1));
	RUNTEST(result);
	result += TestInt("ListBegin" , 4 , *(int *)SLinkedListGetData(SLinkedListBegin(list1)));
	RUNTEST(result);
	
	result += TestInt("Insert" , 6 , *(int *)SLinkedListGetData(SLinkedListInsertBefore(iter , &b)));
	RUNTEST(result);
	result += TestSize_t("ListCount" , 2 , SLinkedListCount(list1));
	RUNTEST(result);
	result += TestInt("ListBegin" , 6 , *(int *)SLinkedListGetData(SLinkedListBegin(list1)));
	RUNTEST(result);
	iter2 = SLinkedListNext(iter);
	result += TestInt("GetData" , 4 , *(int *)SLinkedListGetData(iter2));
	RUNTEST(result);
	result += TestInt("Insert" , 54 , *(int *)SLinkedListGetData(SLinkedListInsertBefore(iter , &c)));
	RUNTEST(result);
	result += TestSize_t("ListCount" , 3 , SLinkedListCount(list1));
	RUNTEST(result);
	
	SLinkedListDestroy(list1);
	
	return result;
}

int TestEndBegin()
{
	int result = 0 ;
	int ints[3] = {4,6,15};
	s_linked_list_t *list1 = SLinkedListCreate();
	s_list_iter_t iter = SLinkedListBegin(list1);
	s_list_iter_t iter2 = SLinkedListBegin(list1);
	
	
	result += TestInt("Insert" , 4 , *(int *)SLinkedListGetData(SLinkedListInsertBefore(iter ,&ints[0])));
	RUNTEST(result);
	result += TestInt("ListBegin" , 4 , *(int *)SLinkedListGetData(SLinkedListBegin(list1)));
	RUNTEST(result);
	result += TestInt("Insert" , 6 , *(int *)SLinkedListGetData(SLinkedListInsertBefore(iter, &ints[1])));
	RUNTEST(result);
	result += TestInt("ListBegin" , 6 , *(int *)SLinkedListGetData(SLinkedListBegin(list1)));
	RUNTEST(result);
	iter2 = SLinkedListEnd(list1);
	result += TestInt("Insert" , 15 , *(int *)SLinkedListGetData(SLinkedListInsertBefore(iter2, &ints[2])));
	RUNTEST(result);
	iter = SLinkedListNext(iter);
	result += TestInt("GetData" , 4 , *(int *)SLinkedListGetData(iter));
	RUNTEST(result);
	iter = SLinkedListNext(iter);
	result += TestInt("GetData" , 15 , *(int *)SLinkedListGetData(iter));
	RUNTEST(result);
	iter2 = SLinkedListEnd(list1);
	result += TestPointers("Test Next data dummy" , NULL ,SLinkedListNext((iter2)));
	RUNTEST(result);
	result += TestSize_t("ListCount" , 3 , SLinkedListCount(list1));
	RUNTEST(result);
	SLinkedListDestroy(list1);
	
	return result;
}

int TestSetGetData()
{
	int result = 0 ;
	s_linked_list_t *list1 = SLinkedListCreate();
	s_list_iter_t iter = SLinkedListBegin(list1);
	s_list_iter_t iter2 = SLinkedListBegin(list1);
	
	result += TestInt("IsEmpty", 1 , SLinkedListIsEmpty(list1));
	RUNTEST(result);
	result += TestInt("IsEmpty", 1 , SLinkedListIsEmpty(list1));
	RUNTEST(result);
	result += TestSize_t("ListCount" , 0 , SLinkedListCount(list1));
	RUNTEST(result);
	result += TestInt("Insert" , 4 , *(int *)SLinkedListInsertBefore(iter ,(void *)4));
	RUNTEST(result);
	result += TestInt("GetData" , 4 , (int)SLinkedListGetData(iter));
	RUNTEST(result);
	result += TestInt("IsEmpty", 0 , SLinkedListIsEmpty(list1));
	RUNTEST(result);
	result += TestInt("ListBegin" , 4 , *(int *)SLinkedListBegin(list1));
	RUNTEST(result);
	SLinkedListSetData(iter , (void *) 6);
	result += TestInt("ListBegin" , 6 , *(int *)SLinkedListBegin(list1));
	RUNTEST(result);
	result += TestInt("GetData" , 6 , (int)SLinkedListGetData(iter2));
	RUNTEST(result);
	SLinkedListSetData(iter , (void *) 17);
	result += TestInt("ListBegin" , 17 , *(int *)SLinkedListBegin(list1));
	RUNTEST(result);
	result += TestInt("GetData" , 17 , (int)SLinkedListGetData(iter2));
	RUNTEST(result);
	
	
	SLinkedListDestroy(list1);
	
	return result;
}

	
int TestIsIterEqual()
{
	int result = 0 ;
	s_linked_list_t *list1 = SLinkedListCreate();
	s_list_iter_t iter = SLinkedListBegin(list1);
	s_list_iter_t iter2 = SLinkedListBegin(list1);
	
	result += TestInt("IsIterEqual", 1 , SLinkedListIsIterEqual(iter , iter2));
	RUNTEST(result);
	result += TestInt("Insert" , 4 , *(int *)SLinkedListInsertBefore(iter ,(void *)4));
	RUNTEST(result);
	iter2 = SLinkedListNext(iter);
	result += TestInt("IsIterEqual", 0 , SLinkedListIsIterEqual(iter , iter2));
	RUNTEST(result);
	iter = SLinkedListNext(iter);
	result += TestInt("IsIterEqual", 1 , SLinkedListIsIterEqual(iter , iter2));
	RUNTEST(result);
	result += TestInt("Insert" , 5 , *(int *)SLinkedListInsertBefore(iter ,(void *)5));
	RUNTEST(result);
	iter2 = SLinkedListNext(iter2);
	result += TestInt("IsIterEqual", 0 , SLinkedListIsIterEqual(iter , iter2));
	RUNTEST(result);
	SLinkedListDestroy(list1);
	
	return result;
}

int IsMatch(const void *data, void *parameter)
{
	return ((int)data == (int)parameter);
}


int TestFind()
{
	int result = 0 ;
	s_linked_list_t *list = SLinkedListCreate();
	s_list_iter_t iter_start = SLinkedListBegin(list);
	s_list_iter_t iter_end = SLinkedListEnd(list);
	match_func_t find_func = IsMatch;
	int num = 5; 
	
	result += TestInt("IsIterEqual", 1 , SLinkedListIsIterEqual(iter_start , iter_end));
	result += TestInt("Insert" , 1 , *(int *)SLinkedListInsertBefore(iter_start ,(void *)1));
	result += TestInt("Insert" , 2 , *(int *)SLinkedListInsertBefore(iter_start ,(void *)2));
	result += TestInt("Insert" , 3 , *(int *)SLinkedListInsertBefore(iter_start ,(void *)3));
	result += TestInt("Insert" , 4 , *(int *)SLinkedListInsertBefore(iter_start ,(void *)4));
	result += TestInt("Insert" , 5 , *(int *)SLinkedListInsertBefore(iter_start ,(void *)5));
	RUNTEST(result);
	result += TestInt("ListBegin" , 5 , *(int *)SLinkedListBegin(list));
	RUNTEST(result);
	iter_end = SLinkedListEnd(list);
	result += TestInt("find" , 3 , *(int *)SLinkedListFind(find_func, (void *)3, iter_start, iter_end));
	RUNTEST(result);
	/*result += TestInt("find" , 5 , *(int *)SLinkedListFind(find_func, (void *)5, iter_start, iter_end));
	RUNTEST(result);
	iter_start = SLinkedListNext(iter_start);
	result += TestInt("find" , 4 , *(int *)SLinkedListFind(find_func, (void *)4, iter_start, iter_end));
	RUNTEST(result);
	result += TestInt("find" , 1 , *(int *)SLinkedListFind(find_func, (void *)1, iter_start, iter_end));
	RUNTEST(result);
	result += TestInt("find" , 0 , *(int *)SLinkedListFind(find_func, (void *)5, iter_start, iter_end));
	RUNTEST(result);
	iter_end = SLinkedListNext(iter_start);
	RUNTEST(result);
	result += TestInt("find" , 0 , *(int *)SLinkedListFind(find_func, (void *)4, iter_end, iter_start));
	RUNTEST(result);*/
	SLinkedListDestroy(list);
	return result;	
}

int TestForEach()
{
	int result = 0 ;
	s_linked_list_t *list = SLinkedListCreate();
	s_list_iter_t iter_start = SLinkedListBegin(list);
	s_list_iter_t iter_end = SLinkedListEnd(list);
	action_func_t  math_func = AddNum;
	int num = 5;
	int num2 = 2;
	void *param = &num;

	
	result += TestInt("Insert" , 1 , *(int *)SLinkedListInsertBefore(iter_start ,(void *)1));
	result += TestInt("Insert" , 2 , *(int *)SLinkedListInsertBefore(iter_start ,(void *)2));
	result += TestInt("Insert" , 3 , *(int *)SLinkedListInsertBefore(iter_start ,(void *)3));
	result += TestInt("Insert" , 4 , *(int *)SLinkedListInsertBefore(iter_start ,(void *)4));
	result += TestInt("Insert" , 5 , *(int *)SLinkedListInsertBefore(iter_start ,(void *)5));
	RUNTEST(result);
	iter_end = SLinkedListEnd(list);
	result += TestInt("forEach" , 0 , SLinkedListForEach(math_func, param, iter_start, iter_end));
	RUNTEST(result);
	result += TestInt("GetData" , 10 , (int)SLinkedListGetData(iter_start));
	RUNTEST(result);
	iter_start = SLinkedListNext(iter_start);
	result += TestInt("GetData" , 9 , (int)SLinkedListGetData(iter_start));
	RUNTEST(result);
	iter_start = SLinkedListNext(iter_start);
	result += TestInt("GetData" , 8 , (int)SLinkedListGetData(iter_start));
	RUNTEST(result);
	iter_start = SLinkedListNext(iter_start);
	result += TestInt("GetData" , 7 , (int)SLinkedListGetData(iter_start));
	RUNTEST(result);
	iter_start = SLinkedListNext(iter_start);
	result += TestInt("GetData" , 6 , (int)SLinkedListGetData(iter_start));
	RUNTEST(result);
	iter_start = SLinkedListBegin(list);
	
	param = &num2;
	iter_start = SLinkedListNext(iter_start);
	result += TestInt("forEach" , 0 , SLinkedListForEach(math_func, param, iter_start, iter_end));
	RUNTEST(result);
	iter_start = SLinkedListBegin(list);
	result += TestInt("GetData" , 10 , (int)SLinkedListGetData(iter_start));
	RUNTEST(result);
	iter_start = SLinkedListNext(iter_start);
	result += TestInt("GetData" , 11 , (int)SLinkedListGetData(iter_start));
	RUNTEST(result);
	iter_start = SLinkedListNext(iter_start);
	result += TestInt("GetData" , 10 , (int)SLinkedListGetData(iter_start));
	RUNTEST(result);
	iter_start = SLinkedListNext(iter_start);
	result += TestInt("GetData" , 9 , (int)SLinkedListGetData(iter_start));
	RUNTEST(result);
	iter_start = SLinkedListNext(iter_start);
	result += TestInt("GetData" , 8 , (int)SLinkedListGetData(iter_start));
	RUNTEST(result);
	
	
	return result;	
}

int AddNum(void *data, void *parameter)
{
	*(int *)data += *(int *)parameter;
	return 0;
}

int TestSize_t(const char *str, size_t expected, size_t result)
{
	printf("%s\n" , str);
	return !(expected == result);
}

int TestInt(const char *str, int expected, int result)
{
	printf("%s\n" , str);
	return !(expected == result);
}

int TestPointers(const char *str, void *expected, void *result)
{
	printf("%s\n" , str);
	return !( expected == result);
}

