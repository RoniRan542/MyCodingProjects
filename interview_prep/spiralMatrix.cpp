#include <iostream>
#include <vector>

using namespace std;

vector<int> recurseSpiralOrder(vector<vector<int>> &matrix, vector<int> &result, int x, int y)
{
    if (y - x == 0)
    {
        return result;
    }
    if (y - x == 1)
    {
        cout << matrix[x][y - 1] << endl;
        result.push_back(matrix[x][y]);
    }

    int left = matrix[0].size() - y;

    for (int i = left; i < y; ++i)
    {
        cout << matrix[x][i] << endl;
        result.push_back(matrix[x][i]);
    }

    int down = matrix.size() - x;
    int up = matrix.size() - down;

    for (int i = up; i < down; ++i)
    {
        cout << matrix[i][y] << endl;
        result.push_back(matrix[i][y]);
    }

    for (int i = y; i > left; --i)
    {
        cout << matrix[down - 1][i] << endl;
        result.push_back(matrix[down - 1][i]);
    }

    for (int i = down - 1; i > up; --i)
    {
        cout << matrix[i][left] << endl;
        result.push_back(matrix[i][left]);
    }

    return recurseSpiralOrder(matrix, result, x + 1, y - 1);
}

vector<int> spiralOrder(vector<vector<int>> &matrix)
{
    int counter = 0;
    int start_x = 0;
    int end_x = matrix.size();
    int start_y = 0;
    int end_y = matrix[0].size();
    int walk_x = 0;
    int walk_y = 0;
    int res_size = end_x * end_y;
    vector<int> result;

    while (1)
    {
        if (counter >= res_size)
        {
            break;
        }
        while (walk_y < end_y) // go right
        {
            result.push_back(matrix[walk_x][walk_y]);
            ++counter;
            ++walk_y;
        }
        ++start_x;
        --walk_y;
        ++walk_x;
        if (counter >= res_size)
        {
            break;
        }

        while (walk_x < end_x) // go down
        {
            result.push_back(matrix[walk_x][walk_y]);
            ++counter;
            ++walk_x;
        }
        --end_y;
        --walk_x;
        --walk_y;
        if (counter >= res_size)
        {
            break;
        }
        // go left
        while (walk_y >= start_y)
        {
            result.push_back(matrix[walk_x][walk_y]);
            ++counter;
            --walk_y;
        }
        ++walk_y;
        --end_x;
        --walk_x;
        if (counter >= res_size)
        {
            break;
        }
        // go up
        while (walk_x >= start_x)
        {
            result.push_back(matrix[walk_x][walk_y]);
            ++counter;
            --walk_x;
        }
        ++walk_x;
        ++start_y;
        ++walk_y;
    }

    return result;
}

int main()
{
    vector<vector<int>> matrix = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}};

    vector<int> results = spiralOrder(matrix);

    for (size_t i = 0; i < results.size(); ++i)
    {
        cout << results[i] << " ";
    }
    cout << "\n";

    return 0;
}
