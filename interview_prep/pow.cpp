#include <iostream>
#include <climits>
#include <cfloat>

using namespace std;

double myPow(double x, int n)
{
    double new_x = 1;
    double ans = 1;

    if (x == 1)
    {
        return 1;
    }

    if (n < 0)
    {
        for (; n < 0; ++n)
        {
            new_x *= x;
        }

        return 1 / new_x;
    }

    for (int i = 0; i < n; i++)
    {
        ans *= x;
    }

    return ans;
}

double myPow2(double x, int n)
{
    double ans = 1;
    long abs_n = n * (long)-1;
    while (abs_n > 0)
    {
        if ((abs_n & 1) == 1)
        {
            ans *= x;
        }

        abs_n >>= 1;
        x *= x;
    }

    return n < 0 ? 1 / ans : ans;
}

int main()
{
    /* cout << myPow(2.1, 3) << endl;
    cout << myPow(2, 10) << endl;
    cout << ((myPow(2, -10)) * 1024) << endl;
 */
    cout << myPow(2, -2147483648) << endl;
    cout << myPow2(2, -2147483648) << endl;
    return 0;
}
