/****************************************************************
 *Name : Ran Aharon Cohen	 	    			                *
 *Date: 14.07.22		            		                    *
 *Description : Compute the fewest amount of coins that you need*
 in order to make up the sum                                    *
 ****************************************************************/
#include <iostream>
#include <assert.h>

using namespace std;

int MinCoinsToSum(int *coins, size_t size, int sum, size_t count)
{
    int result = 0;

    assert(coins);

    if (0 > sum)
    {
        return -1;
    }
    else if (sum == 0)
    {
        return count;
    }

    for (size_t i = 0; i < size; ++i)
    {
        size_t temp_sum = sum;
        temp_sum -= coins[i];
        ++count;
        result = MinCoinsToSum(coins + i, size - i, temp_sum, count);
        if (result > 0)
        {
            return result;
        }
        else
        {
            --count;
        }
    }

    return result;
}

int main()
{
    int coins[3] = {4, 2, 1}; // array should be ordered from biggest coin to smallest
    cout << MinCoinsToSum(coins, 3, 23, 0) << "\n";

    return 0;
}