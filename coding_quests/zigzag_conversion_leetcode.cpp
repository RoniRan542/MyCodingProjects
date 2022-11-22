/********************************************************
 *Name : Ran Aharon Cohen	 	    			        *
 *Date: 	22.11.22		            		        *
 *Description :	Write the code that will take a         *
 *string and make this conversion given a number of rows*
 ********************************************************/

#include <iostream>
#include <vector>

using namespace std;

string convert(string s, int numRows)
{

    string out;
    vector<string> output_rows(numRows);
    size_t i = 0;
    size_t x = 0;

    if (numRows <= 1)
    {
        return s;
    }
    while (i < s.length())
    {
        while (x < numRows && i < s.length())
        {
            output_rows[x] += s[i];
            ++x;
            ++i;
        }
        x = numRows - 2;

        while (x > 0 && i < s.length())
        {
            output_rows[x] += s[i];
            --x;
            ++i;
        }
    }

    for (size_t i = 0; i < numRows; ++i)
    {
        out += output_rows[i];
    }

    return out;
}