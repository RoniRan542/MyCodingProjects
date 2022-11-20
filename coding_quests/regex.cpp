/**********************************************************
 *Name : Ran Aharon Cohen	 	    			          *
 *Date: 	14.07.22		            		          *
 *Description : Implement regular expression matching     *
 *with the following special characters:                  *
 * .(period) which matches any single character           *
 * *(asterisk) which matches zero or more of the preceding*
 *  element.                                              *
 **********************************************************/
#include <iostream>

using namespace std;

bool RegEx(const string &str, const string &regex)
{
    size_t j = 0;
    for (size_t i = 0; i < regex.length(); ++i)
    {
        ++j;
        if (regex[i] == '*')
        {
            size_t x = i + 1;
            char c = regex[x];
            while (c == '.' || c == '*')
            {
                c = regex[++x];
            }
            i = x;

            while (str[j] != c && j < str.length())
            {
                ++j;
            }
        }
        else if (regex[i] == '.')
        {
            if (i < str.length())
            {
                continue;
            }
            else
            {
                return false;
            }
        }
        else
        {
            if (regex[i] == str[j])
            {
                continue;
            }
            else
            {
                return false;
            }
        }
    }

    return true;
}

int main()
{
    /* string input = "aaaaaaaAcCaaaaaB";
    string regex = ".**..A.C..*B"; */
    string input = "ababababababababababababaccc";
    string regex = "****.*.*.*.*.*.cccd";
    cout << RegEx(input, regex) << endl;

    return 0;
}
