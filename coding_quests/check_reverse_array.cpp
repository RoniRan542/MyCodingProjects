/************************************************************
 *Name : Ran Aharon Cohen	 	    			            *
 *Date: 14.07.22		            		                *
 *Description : find the maximum profit to get from an array*
 *of stock values that fluctuate during the day.            *
 ************************************************************/
#include <iostream>
#include <assert.h>

using namespace std;

size_t CheckReverseArray(int *arr, size_t size, size_t n_ones)
{
    size_t temp_sum = 0;
    size_t real_sum = temp_sum;
    size_t count = 0;
    int first_one = 1;

    for (int i = (size - 1); i >= 0; --i)
    {
        if (1 == arr[i] && 1 == first_one)
        {
            count = 0;
            temp_sum = 1;
            first_one = 0;
        }
        else if (1 == arr[i] && 0 == first_one)
        {
            ++temp_sum;
        }
        else
        {
            ++count;
            if (n_ones < count)
            {
                if (real_sum < temp_sum + n_ones)
                {
                    real_sum = temp_sum + n_ones;
                }
                first_one = 1;
                temp_sum = 0;
                count = 0;
            }
        }
    }
    return real_sum;
}

size_t MaxConsecutiveOnes(int *arr, size_t size, size_t n_ones)
{
    size_t temp_sum = 0;
    size_t real_sum = temp_sum;
    size_t count = 0;
    int first_one = 1;

    assert(arr);

    for (size_t i = 0; i < size; i++)
    {
        if (1 == arr[i] && 1 == first_one)
        {
            count = 0;
            temp_sum = 1;
            first_one = 0;
        }
        else if (1 == arr[i] && 0 == first_one)
        {
            ++temp_sum;
        }
        else
        {
            ++count;
            if (n_ones < count)
            {
                if (real_sum < temp_sum + n_ones)
                {
                    real_sum = temp_sum + n_ones;
                }
                first_one = 1;
                temp_sum = 0;
                count = 0;
            }
        }
    }

    if (real_sum < temp_sum + n_ones)
    {
        real_sum = temp_sum + n_ones;
    }

    size_t reverse_res = CheckReverseArray(arr, size, n_ones);
    if (real_sum < reverse_res)
    {
        return reverse_res;
    }

    return real_sum;
}

int main()
{
    int arr[12] = {1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1};
    cout << MaxConsecutiveOnes(arr, 12, 2) << "\n";

    return 0;
}