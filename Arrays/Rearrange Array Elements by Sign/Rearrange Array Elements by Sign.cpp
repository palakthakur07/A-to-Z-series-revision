/*
------------------------------------------------------------
Problem : Rearrange Array Elements by Sign

Approaches
1. Brute Force
2. Optimal
3. Follow-Up (Unequal Positives & Negatives)

Time Complexity
Brute    : O(N)
Optimal  : O(N)
Follow-Up: O(N)

Space Complexity
Brute    : O(N)
Optimal  : O(N)
Follow-Up: O(N)
------------------------------------------------------------
*/

#include <iostream>
#include <vector>
using namespace std;

// ======================================================
// Brute Force Approach
// ======================================================

vector<int> rearrangeBrute(vector<int>& nums)
{
    vector<int> positive;
    vector<int> negative;

    for(int num : nums)
    {
        if(num > 0)
            positive.push_back(num);
        else
            negative.push_back(num);
    }

    vector<int> ans(nums.size());

    for(int i = 0; i < positive.size(); i++)
    {
        ans[2 * i] = positive[i];
        ans[2 * i + 1] = negative[i];
    }

    return ans;
}

// ======================================================
// Optimal Approach
// ======================================================

vector<int> rearrangeOptimal(vector<int>& nums)
{
    vector<int> ans(nums.size());

    int posIndex = 0;
    int negIndex = 1;

    for(int num : nums)
    {
        if(num > 0)
        {
            ans[posIndex] = num;
            posIndex += 2;
        }
        else
        {
            ans[negIndex] = num;
            negIndex += 2;
        }
    }

    return ans;
}

// ======================================================
// Follow-Up (Unequal Positives & Negatives)
// ======================================================

vector<int> rearrangeFollowUp(vector<int>& nums)
{
    vector<int> positive;
    vector<int> negative;

    for(int num : nums)
    {
        if(num > 0)
            positive.push_back(num);
        else
            negative.push_back(num);
    }

    vector<int> ans;
    int i = 0, j = 0;

    while(i < positive.size() && j < negative.size())
    {
        ans.push_back(positive[i++]);
        ans.push_back(negative[j++]);
    }

    while(i < positive.size())
        ans.push_back(positive[i++]);

    while(j < negative.size())
        ans.push_back(negative[j++]);

    return ans;
}

// ======================================================
// Print Function
// ======================================================

void print(vector<int>& arr)
{
    for(int num : arr)
        cout << num << " ";

    cout << endl;
}

// ======================================================
// Driver Code
// ======================================================

int main()
{
    vector<int> nums = {3,1,-2,-5,2,-4};

    vector<int> brute = rearrangeBrute(nums);
    vector<int> optimal = rearrangeOptimal(nums);

    cout << "Brute Force : ";
    print(brute);

    cout << "Optimal     : ";
    print(optimal);

    vector<int> nums2 = {1,2,3,-1,-2};

    vector<int> follow = rearrangeFollowUp(nums2);

    cout << "Follow-Up   : ";
    print(follow);

    return 0;
}