/*
given a matrix of numbers N/N. Find the maximum size of Identity
matrix (Identity Matrix is a square matrix in which all the elements
of the main diagonal are 1’s and all other elements are zeros) in
the lower right corner.
 */

#include <iostream>
#include <vector>

using namespace std;

int MatrixIdentity(std::vector<std::vector<int>> matrix, int dimentions)
{
    int n = matrix.size();

    if (dimentions > n)
    {
        return 0;
    }
    else
    {
        for (int i = n - dimentions; i < n; i++)
        {
            if (i == n - dimentions && matrix[i][i] != 1)
            {
                return 0;
            }
            else if (i == n - dimentions && matrix[i][i] == 1)
            {
                continue;
            }
            if (matrix[i][n - dimentions] != 0)
            {
                return 0;
            }
            if (matrix[n - dimentions][i] != 0)
            {
                return 0;
            }
        }
    }

    int ret = MatrixIdentity(matrix, dimentions + 1);
    dimentions = ((ret > 0) ? ret : dimentions);
    return dimentions;
}

int main()
{
    std::vector<std::vector<int>> matrix = {{2, 3, 4, 5, 3},
                                            {2, 1, 0, 0, 0},
                                            {3, 0, 1, 0, 0},
                                            {6, 0, 0, 1, 0},
                                            {2, 0, 0, 0, 2}};
    std::cout << MatrixIdentity(matrix, 1) << std::endl;

    return 0;
}