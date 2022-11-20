/************************************************************
 *Name : Ran Aharon Cohen	 	    			            *
 *Date: 14.07.22		            		                *
 *Description : You get an array of buildings.              *
 Sum up the fillers that can hold water between them.       *
 Example:                                                   *
                                                            *
 *     *                                                    *
 * 3 * *   * 1 *    Output: 6                               *
 * * * * 2 * * *                                            *
 * * * * * * * *                                            *
 ************************************************************/
#include <iostream>
#include <vector>
using namespace std;

size_t NumOfFillers(vector<size_t> heights)
{
    size_t sum_of_fillers = 0;
    size_t high = heights.at(0);
    size_t curr_low = high;
    size_t count_lows = 0;
    size_t steps = 0;

    for (size_t i = 0; i < heights.size(); ++i)
    {
        if (heights.at(i) < high)
        {
            if (curr_low < heights.at(i))
            {
                sum_of_fillers += (steps * heights.at(i) - count_lows);
                count_lows += (steps * heights.at(i) - count_lows);
            }
            count_lows += heights.at(i);
            ++steps;
            curr_low = heights.at(i);
        }
        else
        {
            if (0 < steps)
            {
                size_t min = high < heights.at(i) ? high : heights.at(i);
                sum_of_fillers += (steps * min - count_lows);
            }
            high = heights.at(i);
            curr_low = high;
            count_lows = 0;
            steps = 0;
        }
    }

    return sum_of_fillers;
}

int main()
{
    vector<size_t> heights5 = {4, 2, 2, 6};
    std::cout << "{4, 2, 2, 6}: " << NumOfFillers(heights5) << std::endl;
    std::cout << "\n\n";
    vector<size_t> heights6 = {4, 2, 2, 3, 6};
    std::cout << "{4, 2, 2, 3, 6}: " << NumOfFillers(heights6) << std::endl;
    std::cout << "\n\n";
    vector<size_t> heights7 = {4, 2, 2, 3, 6, 4, 3, 2, 5};
    std::cout << "{4, 2, 2, 3, 6, 4, 3, 2, 5}: " << NumOfFillers(heights7) << std::endl;
    std::cout << "\n\n";
    vector<size_t> heights8 = {4, 2, 2, 3, 6, 4, 3, 2, 5, 7};
    std::cout << "{4, 2, 2, 3, 6, 4, 3, 2, 5, 7}: " << NumOfFillers(heights8) << std::endl;
    return 0;
}