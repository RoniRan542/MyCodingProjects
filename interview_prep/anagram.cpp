
#include <iostream>

using namespace std;
bool isAnagram(string s, string t)
{

    int lut[256] = {0};

    if (s.length() != t.length())
    {
        return false;
    }

    for (size_t i = 0; i < s.length(); ++i)
    {
        lut[(size_t)s[i]] += 1;
        lut[(size_t)t[i]] -= 1;
    }

    for (size_t i = 0; i < s.length(); ++i)
    {
        if (lut[(size_t)s[i]] != 0)
        {
            return false;
        }
    }

    return true;
}

int main()
{
    string s = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaab";
    string t = "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbba";

    cout << isAnagram(s, t) << endl;

    return 0;
}