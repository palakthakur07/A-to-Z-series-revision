/*
------------------------------------------------------------
Problem : Best Time to Buy and Sell Stock

Approach
1. Optimal (Greedy)

Time Complexity : O(N)
Space Complexity: O(1)
------------------------------------------------------------
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// ======================================================
// Optimal Approach (Greedy)
// ======================================================

int maxProfit(vector<int>& prices)
{
    int minPrice = prices[0];
    int maxProfit = 0;

    for(int i = 1; i < prices.size(); i++)
    {
        int profit = prices[i] - minPrice;

        maxProfit = max(maxProfit, profit);

        minPrice = min(minPrice, prices[i]);
    }

    return maxProfit;
}

// ======================================================
// Driver Code
// ======================================================

int main()
{
    vector<int> prices = {7,1,5,3,6,4};

    cout << "Maximum Profit : "
         << maxProfit(prices) << endl;

    return 0;
}