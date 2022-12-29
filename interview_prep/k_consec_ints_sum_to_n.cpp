// Given two integers N and K, the task is to find K consecutive integers such that their sum is N.

#include <iostream>
#include <vector>

using namespace std;

// complexity is O(n^2)
int KConsecIntsSumToN(const vector<int> &array, vector<int> &result, size_t K, int N)
{
    int temp_sum = 0;
    size_t curr_kth = 0;

    for (size_t i = 0; i < array.size(); ++i)
    {
        temp_sum += array[i];
        if ((curr_kth == (K - 1)) && temp_sum == N)
        {
            for (size_t j = i; j > (i - K); --j)
            {
                result[curr_kth] = array[j];
                --curr_kth;
            }

            return 1;
        }
        else if (temp_sum > N || (curr_kth + 1) == K)
        {
            i -= curr_kth;
            curr_kth = 0;
            temp_sum = 0;
        }
        else
        {
            ++curr_kth;
        }
    }

    result.resize(0);

    return -1;
}

// complexity is O(n)

int BetterKConsecIntsSumToN(const vector<int> &array, vector<int> &result, size_t K, int N)
{
    int temp_sum = 0;
    size_t curr_kth = 0;
    size_t start_k = 0;
    for (size_t i = 0; i < array.size(); ++i)
    {
        temp_sum += array[i];
        if ((curr_kth == (K - 1)) && temp_sum == N)
        {
            for (size_t j = i; j > (i - K); --j)
            {
                result[curr_kth] = array[j];
                --curr_kth;
            }

            return 1;
        }
        else if (temp_sum > N || (curr_kth + 1) == K)
        {
            temp_sum -= array[start_k];
            start_k += 1;
        }
        else
        {
            ++curr_kth;
        }
    }

    result.resize(0);

    return -1;
}

int main()
{
    vector<int> array = {1, 2, 3, 4, 5, 6, 7};
    vector<int> result(3);

    // cout << KConsecIntsSumToN(array, result, 3, 18) << endl;
    cout << BetterKConsecIntsSumToN(array, result, 3, 18) << endl;

    for (size_t i = 0; i < result.size(); i++)
    {
        cout << result[i] << " ";
    }
    cout << "\n";

    return 0;
}
