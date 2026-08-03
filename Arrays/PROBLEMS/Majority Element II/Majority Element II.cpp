#include <bits/stdc++.h>
using namespace std;

/*
-----------------------------------------
Brute Force
TC : O(N²)
SC : O(1)
-----------------------------------------
*/

vector<int> majorityElementBrute(vector<int> &nums)
{
    vector<int> ans;
    int n = nums.size();

    for (int i = 0; i < n; i++)
    {
        if (!ans.empty() && ans[0] == nums[i])
            continue;

        int cnt = 0;

        for (int j = 0; j < n; j++)
        {
            if (nums[j] == nums[i])
                cnt++;
        }

        if (cnt > n / 3)
            ans.push_back(nums[i]);

        if (ans.size() == 2)
            break;
    }

    return ans;
}

/*
-----------------------------------------
Better (Map)
TC : O(N log N)
SC : O(N)
-----------------------------------------
*/

vector<int> majorityElementBetter(vector<int> &nums)
{
    map<int, int> mpp;
    vector<int> ans;

    int n = nums.size();
    int mini = n / 3 + 1;

    for (int i = 0; i < n; i++)
    {
        mpp[nums[i]]++;

        if (mpp[nums[i]] == mini)
            ans.push_back(nums[i]);

        if (ans.size() == 2)
            break;
    }

    return ans;
}

/*
-----------------------------------------
Optimal
Extended Moore Voting Algorithm
TC : O(2N)
SC : O(1)
-----------------------------------------
*/

class Solution
{
public:
    vector<int> majorityElement(vector<int> &nums)
    {
        int cnt1 = 0, cnt2 = 0;
        int el1 = INT_MIN, el2 = INT_MIN;

        for (int i = 0; i < nums.size(); i++)
        {
            if (cnt1 == 0 && nums[i] != el2)
            {
                cnt1 = 1;
                el1 = nums[i];
            }
            else if (cnt2 == 0 && nums[i] != el1)
            {
                cnt2 = 1;
                el2 = nums[i];
            }
            else if (nums[i] == el1)
            {
                cnt1++;
            }
            else if (nums[i] == el2)
            {
                cnt2++;
            }
            else
            {
                cnt1--;
                cnt2--;
            }
        }

        cnt1 = 0;
        cnt2 = 0;

        for (int x : nums)
        {
            if (x == el1)
                cnt1++;
            else if (x == el2)
                cnt2++;
        }

        vector<int> ans;
        int mini = nums.size() / 3;

        if (cnt1 > mini)
            ans.push_back(el1);

        if (cnt2 > mini)
            ans.push_back(el2);

        sort(ans.begin(), ans.end());

        return ans;
    }
};