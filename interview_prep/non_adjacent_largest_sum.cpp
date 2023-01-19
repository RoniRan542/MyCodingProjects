#include <iostream>
#include <vector>

using namespace std;

int findNonAdjacentLargestSum(vector<int> vec)
{
    bool is_adjacent = false;
    int curr_sum = 0;

    for (size_t i = 0; i < vec.size(); ++i)
    {
        cout << curr_sum << endl;
        if (i + 1 < vec.size())
        {
            if (is_adjacent == false && vec[i] > vec[i + 1])
            {
                curr_sum += vec[i];
                is_adjacent = true;
            }
            else
            {
                is_adjacent = false;
            }
        }
        else if (is_adjacent == false)
        {
            curr_sum += vec[i];
        }
    }

    return curr_sum;
}
int main()
{

    vector<int> vec1 = {5, 1, 1, 5};
    vector<int> vec3 = {2, 3, 6, 2, 5};
    vector<int> vec2 = {9, 2, 3, 8, 2, 11, 2, 7, 5};
    int res = findNonAdjacentLargestSum(vec3);
    cout << "result: " << res << endl;
    return 0;
}
