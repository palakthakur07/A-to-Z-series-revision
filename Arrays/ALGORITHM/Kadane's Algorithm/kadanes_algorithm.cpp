#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int maxSubArray(vector<int>& nums)
{
    int currSum = 0;
    int maxSum = INT_MIN;

    for(int i = 0; i < nums.size(); i++)
    {
        currSum += nums[i];

        maxSum = max(maxSum, currSum);

        if(currSum < 0)
            currSum = 0;
    }

    return maxSum;
}

int main()
{
    vector<int> nums = {-2,1,-3,4,-1,2,1,-5,4};

    cout << maxSubArray(nums);

    return 0;
}