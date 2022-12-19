/*
given a matrix of numbers N/N. Find the maximum size of Identity
matrix (Identity Matrix is a square matrix in which all the elements
of the main diagonal are 1’s and all other elements are zeros) in
the lower right corner.
 */

#include <iostream>
#include <vector>

using namespace std;

int CountDiagonal(const vector<vector<int>> &matrix, int *dimensions)
{
    int counter = 0;
    for (int i = dimensions[0], j = dimensions[1]; i >= 0, j >= 0; --j, --i)
    {
        if (matrix[i][j] == 1)
        {
            ++counter;
        }
    }

    return counter;
}
int CountIdentityMatRec(const vector<vector<int>> &matrix, int *dimensions, int times)
{
    int result = 0;
    if (times == 1)
    {
        return 1;
    }

    return result;
}

int FindMaxIdentityMatrix(const vector<vector<int>> &matrix, int *dimensions)
{
    if (matrix[dimensions[0] - 1][dimensions[1] - 1] != 1)
    {
        return 0;
    }

    int times = CountDiagonal(matrix, dimensions);
    int result = 0;
    return CountIdentityMatRec(matrix, dimensions, times);
}

int main()
{

    return 0;
}