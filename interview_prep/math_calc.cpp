#include <iostream>
#include <bits/stdc++.h>

using namespace std;

float CalcGeometricProgression(size_t repete, float numerator, float denominator)
{
    float result = 0;

    for (size_t k = 0; k < repete; ++k)
    {
        result += numerator / pow(denominator, k);
        cout << result << endl;
    }

    return result;
}

int main()
{
    cout << "S = k:1000 1/1.2^k = " << CalcGeometricProgression(1000, 1, 1.2) << endl;
    return 0;
}