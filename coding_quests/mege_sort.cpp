/************************************************************
 *Name : Ran Aharon Cohen	 	    			            *
 *Date: 14.07.22		            		                *
 *Description : implement merge sort                        *
 ************************************************************/
#include <iostream>
#include <cstring>
#include <stdlib.h>

using namespace std;

static const size_t g_sizeof_int = sizeof(int);

void MergeSort(int *arr, size_t size)
{
    size_t left_size = size / 2;
    size_t right_size = size - left_size;

    if (1 >= size)
    {
        return;
    }

    MergeSort(arr, left_size);
    MergeSort(arr + left_size, right_size);

    int *left = new int[left_size];
    int *right = new int[right_size];

    memcpy(left, arr, g_sizeof_int * left_size);
    memcpy(right, arr + left_size, g_sizeof_int * right_size);

    int *mid = left + left_size;
    int *end = right + right_size;
    while (left < mid && right < end)
    {
        if (*left < *right)
        {
            *arr = *left;
            ++arr;
            ++left;
        }
        else
        {
            *arr = *right;
            ++arr;
            ++right;
        }
    }

    while (left < mid)
    {
        *arr = *left;
        ++arr;
        ++left;
    }

    while (right < end)
    {
        *arr = *right;
        ++arr;
        ++right;
    }

    delete[](left - left_size);
    delete[](right - right_size);
}

int main()
{
    int arr[10] = {7, 2, 5, 4, 9, 1, 10, 6, 3, 8};
    MergeSort(arr, 10);

    for (size_t i = 0; i < 10; i++)
    {
        cout << arr[i];
    }
    cout << endl;

    return 0;
}