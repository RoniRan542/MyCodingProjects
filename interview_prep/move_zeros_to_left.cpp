/*
Given an integer array, move all elements that are 0 to the left
while maintaining the order of other elements
in the array. The array must be modified in-place.
 */
#include <iostream>
#include <vector>

using namespace std;
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void move_zeros_left(vector<int> &vec)
{

    for (size_t i = 1; i < vec.size(); ++i)
    {
        if (0 == vec[i])
        {
            for (size_t j = i; j > 0 && vec[j - 1] != 0; --j)
            {
                swap(&vec[j], &vec[j - 1]);
            }
        }
    }
}

int main()
{
    vector<int> vec = {0, 7, 0, 2, 3, 0, 4, 0, 0, 5, 17, 0, 0, 0};

    move_zeros_left(vec);
    for (size_t i = 0; i < vec.size(); i++)
    {
        cout << vec[i] << " ";
    }

    cout << "\n";

    return 0;
}
