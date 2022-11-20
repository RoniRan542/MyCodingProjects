#include <iostream>/*for cout*/
#include <ctime>   /*for clock()*/
#include "complex.hpp"

using namespace std;
using namespace ilrd;

enum status
{
    SUCCESS,
    FAILURE
};

int BenchMark()
{
    Complex c1(1, 1);
    Complex c2(1, 1);
    clock_t now = clock();

    for (int i = 0; i < 100000; ++i)
    {
        c1 + c2;
    }

    cout << "duration time: " << clock() - now << endl;

    return 0;
}

int main()
{
    Complex c1;
    cout << c1;
    Complex c2(4, 7);
    cout << c2;
    Complex c3(6, 2);
    cout << c3;
    cout << "c2 == c3: " << (c2 == c3) << " \n";
    cout << "c2 != c3: " << (c2 != c3) << " \n";

    cout << "c2 + c3: " << (c2 + c3) << " \n";
    cout << "c2 - c3: " << (c2 - c3) << " \n";
    cout << "c2 * c3: " << (c2 * c3) << " \n";
    cout << "c2 / c3: " << (c2 / c3) << " \n";

    cout << "c2 += c3: " << (c2 += c3) << " \n";
    cout << "c2 -= c3: " << (c2 -= c3) << " \n";
    cout << "c2 *= c3: " << (c2 *= c3) << " \n";
    cout << "c2 /= c3: " << (c2 /= c3) << " \n";

    cin >> c1;
    cout << c1;

    BenchMark();

    return SUCCESS;
}
