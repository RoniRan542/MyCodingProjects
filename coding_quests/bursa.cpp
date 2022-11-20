/************************************************************
 *Name : Ran Aharon Cohen	 	    			            *
 *Date: 14.07.22		            		                *
 *Description : find the maximum profit to get from an array*
 *of stock values that fluctuate during the day.            *
 ************************************************************/

#include <iostream>
#include <vector>

int BursaFindMaxProfit(std::vector<int> stock_prices)
{
    int profit = 0;
    size_t idx_buy = 0;
    size_t idx_sell = 0;
    size_t idx_canid_buy = 0;
    size_t idx_canid_sell = 0;

    for (size_t i = 0; i < stock_prices.size(); ++i)
    {
        if (stock_prices[idx_canid_sell] - stock_prices[idx_canid_buy] > profit)
        {
            profit = stock_prices[idx_canid_sell] - stock_prices[idx_canid_buy];
            idx_buy = idx_canid_buy;
            idx_sell = idx_canid_sell;
        }

        if (stock_prices[idx_canid_buy] > stock_prices[i])
        {
            idx_canid_buy = i;
            idx_canid_sell = i;
        }
        else if (stock_prices[idx_canid_sell] < stock_prices[i])
        {
            idx_canid_sell = i;
        }
    }

    std::cout << "indexes[buy, sell] = [" << idx_buy << ", " << idx_sell << "] \n";

    return profit;
}

int main()
{
    std::vector<int> stock_prices = {6, 12, 3, 5, 1, 4, 9, 2};
    std::cout << "max profit = " << BursaFindMaxProfit(stock_prices) << std::endl;
    return 0;
}