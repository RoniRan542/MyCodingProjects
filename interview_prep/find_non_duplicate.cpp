/* 
    array with duplicates values and only 1 value not duplicated (ex 1,1,2,2,3,3,4) - Find the not duplicated value - in place.

    pseudo:
        go over the array.
        with each index, check for its dup and if found move one and swap.   
 */
#include <limits.h>
#include <stdio.h>


void swap(int *p1, int *p2)
{
    int temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}

int findNonDuplicated(int *array, int size)
{
    int i = 0;
    int j = 0;
    int is_dup = 0;


    for(i = 0; i < size; ++i)
    { 
        is_dup = 0;
         for ( j = i + 1; j < size; ++j)
         {
            if(array[i] == array[j])
            {
                ++i;
                swap(&array[i],&array[j]);
                is_dup = 1;
                break; 
            }
         }

         if(!is_dup)
         {
            return array[i];
         }
         
    }

    return INT_MIN;
}


int main()
{
    int arr[11] = {1,1,2,3,2,4,3,5,6,6,2};

    printf("the non-dup number is %d \n", findNonDuplicated(arr, 11));

    return 0;
}
