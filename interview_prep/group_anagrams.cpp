#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

bool IsAnagram(string word1, string word2)
{
    char lut[256] = {0};

    if (word1.size() != word2.size())
    {
        return false;
    }

    for (size_t i = 0; i < word1.size(); ++i)
    {
        lut[(int)word1[i]] += 1;
        lut[(int)word2[i]] -= 1;
    }

    size_t counter = 0;
    for (size_t i = 0; i < word1.size(); ++i)
    {
        // counter += lut[(int)word1[i]];
        if (lut[(int)word1[i]] != 0)
        {
            return false;
        }
    }

    return counter == 0;
}

vector<vector<string>> groupAnagrams(const vector<string> &strs)
{
    size_t size = strs.size();
    vector<vector<string>> anagram_groups = {{strs[0]}};

    if (size == 0)
    {
        return anagram_groups;
    }
    else if (size == 1)
    {
        return anagram_groups;
    }

    bool is_found = false;
    for (size_t j = 1; j < size; ++j)
    {
        for (size_t i = 0; i < anagram_groups.size(); ++i)
        {
            if (IsAnagram(anagram_groups[i][0], strs[j]))
            {
                anagram_groups[i].push_back(strs[j]);
                is_found = true;
                break;
            }
        }

        if (!is_found)
        {
            anagram_groups.push_back({strs[j]});
        }
        is_found = false;
    }

    return anagram_groups;
}

vector<vector<string>> groupAnagrams2(vector<string> &strs)
{
    vector<vector<string>> ans;

    unordered_map<string, vector<string>> mp;
    for (int i = 0; i < strs.size(); i++)
    {
        string s = strs[i];
        sort(strs[i].begin(), strs[i].end());
        mp[strs[i]].push_back(s);
    }

    // now simply put the elements  of second column of map in ans

    for (auto i : mp)
    {
        ans.push_back(i.second);
    }

    return ans;
}
int main()
{
    vector<string> strs1 = {
        "understatements",
        "affabler",
        "ampuls",
        "malices",
        "extemporizing"};

    /*  vector<vector<string>>
         anagroups = groupAnagrams(strs1); */

    vector<vector<string>>
        anagroups = groupAnagrams2(strs1);

    for (size_t i = 0; i < anagroups.size(); i++)
    {
        for (size_t j = 0; j < anagroups[i].size(); ++j)
        {
            cout << anagroups[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
