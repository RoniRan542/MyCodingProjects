/*************************************************
 *Name : Ran Aharon Cohen	 	 *			 *
 *Date: 	19.03.22		 *   		 	 *
 *Description :quiz 9 - MaxSubArray		 	 *
 **************************************************/
#include <stdio.h>/* printf */
#include <limits.h>
#include <math.h>

#define max(x, y) (x > y ? x : y)

int MaxSubArray(int num[], int size);
int MinusesMaxSubArray(int num[], int size);

int main()
{
    int MyArray[] = {-3, 1, -8, 12, 0, -3, 5, -9, 4};
    int MyArray2[] = {-2, 5, -3, 4, -1, 2, 3, -5, 4};
    int MyArray3[] = {-2, -5, -3, -2, -1, -2, -3, -5, -4};

    int result_max = MinusesMaxSubArray(MyArray3, 9);
    printf("Maximum SubArray 3 is: %i \n", result_max);

    result_max = MinusesMaxSubArray(MyArray, 9);
    printf("Maximum SubArray is: %i\n", result_max);

    result_max = MaxSubArray(MyArray2, 9);
    printf("Maximum SubArray is: %i\n", result_max);

    return 0;
}

int MaxSubArray(int num[], int size)
{
    int max_sum = 0;
    int curr_sum = 0;
    int idx1 = 0;
    int idx2 = 0;
    int i = 0;
    int update_idx1 = 0;

    for (i = 0; i < size; ++i)
    {
        curr_sum += num[i];
        if (curr_sum < 0)
        {
            curr_sum = 0;
            update_idx1 = i + 1;
        }

        if (curr_sum > max_sum)
        {
            max_sum = curr_sum;
            idx2 = i;
            idx1 = update_idx1;
        }
    }

    printf("max_sum indexes: %d, %d\n", idx1, idx2);
    return max_sum;
}

int MinusesMaxSubArray(int num[], int size)
{
    int max_sum = INT_MIN;
    int curr_sum = 0;
    int i = 0;

    for (i = 0; i < size; ++i)
    {
        curr_sum += num[i];
        if (curr_sum < num[i])
        {
            curr_sum = num[i];
        }

        if (curr_sum > max_sum)
        {
            max_sum = curr_sum;
        }
    }

    return max_sum;
}