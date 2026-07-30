/*
------------------------------------------------------------
Problem : Maximum Subarray Sum

Approaches
1. Brute Force
2. Better
3. Optimal (Kadane's Algorithm)

Time Complexity
Brute  : O(N^3)
Better : O(N^2)
Optimal: O(N)

Space Complexity
Brute  : O(1)
Better : O(1)
Optimal: O(1)
------------------------------------------------------------
*/

#include <iostream>
#include <vector>
#include <climits>
using namespace std;

// ======================================================
// Brute Force Approach
// ======================================================

int maximumSubarrayBrute(vector<int>& nums)
{
    int n = nums.size();
    int maxi = INT_MIN;

    for(int i = 0; i < n; i++)
    {
        for(int j = i; j < n; j++)
        {
            int sum = 0;

            for(int k = i; k <= j; k++)
            {
                sum += nums[k];
            }

            maxi = max(maxi, sum);
        }
    }

    return maxi;
}

// ======================================================
// Better Approach
// ======================================================

int maximumSubarrayBetter(vector<int>& nums)
{
    int n = nums.size();
    int maxi = INT_MIN;

    for(int i = 0; i < n; i++)
    {
        int sum = 0;

        for(int j = i; j < n; j++)
        {
            sum += nums[j];
            maxi = max(maxi, sum);
        }
    }

    return maxi;
}

// ======================================================
// Optimal Approach (Kadane's Algorithm)
// ======================================================

int maximumSubarrayOptimal(vector<int>& nums)
{
    int sum = 0;
    int maxi = INT_MIN;

    for(int i = 0; i < nums.size(); i++)
    {
        sum += nums[i];

        maxi = max(maxi, sum);

        if(sum < 0)
        {
            sum = 0;
        }
    }

    return maxi;
}

// ======================================================
// Driver Code
// ======================================================

int main()
{
    vector<int> nums = {-2,1,-3,4,-1,2,1,-5,4};

    cout << "Brute Force : "
         << maximumSubarrayBrute(nums) << endl;

    cout << "Better      : "
         << maximumSubarrayBetter(nums) << endl;

    cout << "Optimal     : "
         << maximumSubarrayOptimal(nums) << endl;

    return 0;
}