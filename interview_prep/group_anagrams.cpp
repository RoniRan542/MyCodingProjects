#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<string>> groupAnagrams(const vector<string> &strs)
{
    size_t size = strs.size();

    if (size == 0)
    {
        vector<vector<string>> res(size);
        return res;
    }
    else if (size == 1)
    {
        vector<vector<string>> res(1);
        res[0][0] = strs.front();

        return res;
    }

    vector<string> temp(strs[0].length());
    for (const auto &str : strs)
    {
        vector<string> temp(str.length());
        for (const auto &str : strs)
        {
        }
    }
}