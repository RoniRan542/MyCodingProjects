/* Given three integer arrays sorted in ascending order, return the smallest number that is common in all three arrays.
 Return -1 if there is no common number. */

#include <iostream>
#include <vector>

using namespace std;

bool BinarySearch(vector<int> vec, int target, size_t left, size_t right)
{
    size_t mid = (right - left) / 2;

    if (mid == 0)
    {
        if (vec[left] == target || vec[right] == target)
        {
            return true;
        }
        return false;
    }

    mid = left + mid;

    if (vec[mid] < target)
    {
        return BinarySearch(vec, target, mid + 1, right);
    }

    return BinarySearch(vec, target, left, mid);
}

int smallest_common_number(vector<int> arr1, vector<int> arr2, vector<int> arr3)
{
    int pivot = 0;
    int i = 0;

    for (i = 0; i < (int)arr1.size(); ++i)
    {
        pivot = arr1[i];

        if (true == BinarySearch(arr2, pivot, 0, arr2.size() - 1))
        {
            if (true == BinarySearch(arr3, pivot, 0, arr3.size() - 1))
            {
                return pivot;
            }
        }
    }

    return -1;
}

int main()
{
    vector<int> arr1 = {1, 5, 7, 17, 18, 19};
    vector<int> arr2 = {0, 1, 15, 16, 17};
    vector<int> arr3 = {-17, -10, -2, 0, 1};

    cout << smallest_common_number(arr1, arr2, arr3) << endl;
    return 0;
}
