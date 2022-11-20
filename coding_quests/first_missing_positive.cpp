/*****************************************************************
 *Name : Ran Aharon Cohen	 	    			                 *
 *Date: 14.07.22		            		                     *
 *Description : find the first missing positive integer.         *
 *In other words,find the lowest positive integer that does not  *
 *exist in the vector.The vector can contain duplicates and      *
 *negative numbers as well.                                      *
 ****************************************************************/
#include <iostream>
#include <vector>
void Swap(int *p1, int *p2);

int FindFirstMissingPositive(std::vector<int> vec)
{
    for (size_t i = 0; i < vec.size(); ++i)
    {
        if (vec[i] > 0)
        {
            Swap(&vec[i], &vec[vec[i]]);
        }
    }

    for (size_t i = 1; i < vec.size(); i++)
    {
        if (vec[i] != (int)i)
        {
            return i;
        }
    }

    return -1;
}

void Swap(int *p1, int *p2)
{
    int temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}

int main()
{
    std::vector<int> vec(12);

    vec.push_back(1);
    vec.push_back(4);
    vec.push_back(3);
    vec.push_back(5);
    vec.push_back(6);
    vec.push_back(-1);
    vec.push_back(-3);
    vec.push_back(0);
    vec.push_back(2);
    vec.push_back(4);
    vec.push_back(4);
    vec.push_back(7);
    vec.push_back(8);

    std::cout << FindFirstMissingPositive(vec) << std::endl;

    return 0;
}
