/*************************************************
 *Name : Ran Aharon Cohen	 	    			 *
 *Date: 	22.11.22		            		 *
 *Description :	 convert from roman numbers to   *
 *decimal                                        *
 *************************************************/

#include <iostream>
#include <unordered_map>

size_t ConvertRomanToDecimal(const std::string &roman)
{
    std::unordered_map<char, size_t> lut = {{'I', 1}, {'V', 5}, {'X', 10}, {'L', 50}, {'C', 100}, {'D', 500}, {'M', 1000}};
    size_t res = 0;
    size_t temp = 0;

    for (int i = roman.length() - 1; i >= 0; --i)
    {
        size_t curr_num = lut[roman[i]];
        if (curr_num < temp)
        {
            res -= curr_num;
        }
        else
        {
            res += curr_num;
            temp = curr_num;
        }
    }

    return res;
}

int main()
{
    std::string roman = "MCDXLI";
    std::cout << ConvertRomanToDecimal(roman) << std::endl;

    return 0;
}
