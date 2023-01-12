#include <iostream>
#include <vector>
#include <chrono>

using namespace std;

bool IsValid(vector<vector<int>> &flags, int row, int col, int &n)
{
    for (int i = 0; i < row; ++i)
    {
        if (flags[i][col])
        {
            return false;
        }
    }

    for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; --i, --j)
    {
        if (flags[i][j])
        {
            return false;
        }
    }

    for (int i = row - 1, j = col + 1; i >= 0 && j < n; --i, ++j)
    {
        if (flags[i][j])
        {
            return false;
        }
    }

    return true;
}

void solveNQueens2(vector<vector<string>> &res, vector<string> &nQueens, vector<vector<int>> &flags, int row, int &n)
{
    if (row == n)
    {
        res.push_back(nQueens); // if a solution was found, insert to the res
        return;
    }

    for (int col = 0; col < n; ++col)
    {
        if (IsValid(flags, row, col, n))
        {
            flags[row][col] = 1;
            nQueens[row][col] = 'Q';
            solveNQueens2(res, nQueens, flags, row + 1, n);
            flags[row][col] = 0;
            nQueens[row][col] = '.';
        }
    }
}

vector<vector<string>> solveNQueens(int n)
{
    vector<vector<string>> res;
    vector<string> nQueens(n, string(n, '.'));
    vector<vector<int>> flags_matrix(n, vector<int>(n, 0));

    solveNQueens2(res, nQueens, flags_matrix, 0, n);
    return res;
}

int main()
{
    // Start the timer
    auto start = std::chrono::high_resolution_clock::now();
    vector<vector<string>> solutions = solveNQueens(5);
    // Stop the timer
    auto stop = std::chrono::high_resolution_clock::now();
    // Calculate the elapsed time
    auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    std::cout << "Elapsed time: " << elapsed.count() << " microseconds" << std::endl;
    for (size_t i = 0; i < solutions.size(); ++i)
    {
        for (size_t j = 0; j < solutions[i].size(); ++j)
        {
            cout << solutions[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
