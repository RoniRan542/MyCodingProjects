/**************************************************
 *Name : Ran Aharon Cohen	 	    			  *
 *Date: 	19.07.22		            		  *
 *Description : Given an integer k and a string s,*
 *find the length of the longest substring that   *
 *contains at most k distinct characters.         *
 **************************************************/
#include <iostream>
#include <string.h>

using namespace std;

string LongestKcharsSubstring(const string &str, size_t k)
{
    string res;
    string temp;
    size_t count = 0;
    char lut[256] = {0};
    size_t ret_index = 0;

    for (size_t i = 0; i < str.length(); i++)
    {

        if (lut[str[i]] == 0)
        {

            if (count == k)
            {
                if (temp.length() > res.length())
                {
                    res = temp;
                }
                i = ret_index - 1;
                count = 0;
                memset(lut, 0, 256);
                temp.clear();
            }
            else
            {
                if (count == 1)
                {
                    ret_index = i;
                }
                ++count;
                temp += str[i];
                lut[str[i]] = 1;
            }
        }
        else
        {
            temp += str[i];
        }
    }

    if (temp.length() > res.length())
    {
        res = temp;
    }

    return res;
}

int main()
{
    string s1 = "abcba";

    cout << s1 << " : " << LongestKcharsSubstring(s1, 2) << endl;
    return 0;
}
