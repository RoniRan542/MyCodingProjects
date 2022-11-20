/*****************************************************************
 *Name : Ran Aharon Cohen	 	    			                 *
 *Date: 14.07.22		            		                     *
 *Description : implement a class of the median of set of numbers*
 *****************************************************************/
#include <iostream>
#include <set>

class Median
{
public:
    explicit Median();
    void Add(int value);
    double GetMedian() const noexcept;

private:
    std::multiset<int> container;
};

Median::Median()
{
    // empty
}

void Median::Add(int value)
{
    container.insert(value);
}

double Median::GetMedian() const noexcept
{
    size_t size = container.size();
    size_t i = 1;
    if (size % 2 != 0)
    {
        for (auto it : container)
        {
            if (i == size / 2 + 1)
            {
                return it;
            }

            ++i;
        }
    }
    else
    {
        i = 1;
        double avg = 0;
        for (auto it : container)
        {
            if (i == size / 2)
            {
                avg += it;
            }
            if (i == size / 2 + 1)
            {
                avg += it;
                return avg / 2;
            }

            ++i;
        }
    }
}

int main()
{
    Median median;
    median.Add(1);
    median.Add(4);
    median.Add(5);
    median.Add(2);
    median.Add(3);

    std::cout << median.GetMedian() << std::endl;
    Median median2;
    median2.Add(1);
    median2.Add(4);
    median2.Add(3);
    median2.Add(2);
    std::cout << median2.GetMedian() << std::endl;

    return 0;
}
