#include <iostream>
#include <vector>

using namespace std;

int search_pivot_index(vector<int> &nums, int min, int max)
{
    int mid = (max - min) / 2;
    int mid_index = min + mid;

    if (mid < 1)
    {
        if (nums[mid_index] > nums[mid_index + 1])
        {
            return mid_index + 1;
        }

        return -1;
    }

    if (nums[mid_index] > nums[mid_index + 1])
    {
        return mid_index + 1;
    }

    int left = search_pivot_index(nums, min, mid_index);
    if (left > -1)
    {
        return left;
    }

    return search_pivot_index(nums, mid_index + 1, max);
}

int binary_search(vector<int> &nums, int target, int min, int max)
{
    int size = max - min;
    int mid = size / 2;
    int left = 0;
    int right = 0;

    if (size == 0)
    {
        if (target == nums[min])
        {
            return min;
        }

        return -1;
    }

    left = binary_search(nums, target, min, min + mid);
    right = binary_search(nums, target, min + mid + 1, max);

    if (left != -1)
    {
        return left;
    }

    return right;
}

int search(vector<int> &nums, int target)
{
    int size = nums.size();
    int pivot = search_pivot_index(nums, 0, size - 1);
    int left = 0;
    int right = 0;

    if (pivot)
    {
        left = binary_search(nums, target, 0, pivot - 1);
        right = binary_search(nums, target, pivot, size);
    }
    else
    {
        return binary_search(nums, target, 0, size);
    }

    return left > -1 ? left : right;
}

int main()
{
    vector<int> nums = {4, 5, 6, 7, 0, 1, 2};
    cout << "index of target " << search(nums, 0) << endl;

    return 0;
}