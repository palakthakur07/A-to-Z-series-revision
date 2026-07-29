/*
    Problem: Majority Element

    Approaches:
    1. Brute Force
    2. Better (Hash Map)
    3. Optimal (Moore's Voting Algorithm)
*/

#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

// ==================== BRUTE FORCE ====================

int majorityElementBrute(vector<int>& nums)
{
    int n = nums.size();

    for(int i = 0; i < n; i++)
    {
        int count = 0;

        for(int j = 0; j < n; j++)
        {
            if(nums[i] == nums[j])
                count++;
        }

        if(count > n / 2)
            return nums[i];
    }

    return -1;
}

// Time Complexity : O(N²)
// Space Complexity: O(1)


// ==================== BETTER (HASH MAP) ====================

int majorityElementBetter(vector<int>& nums)
{
    unordered_map<int, int> freq;
    int n = nums.size();

    for(int num : nums)
        freq[num]++;

    for(auto it : freq)
    {
        if(it.second > n / 2)
            return it.first;
    }

    return -1;
}

// Time Complexity : O(N)
// Space Complexity: O(N)


// ==================== OPTIMAL (MOORE'S VOTING) ====================

int majorityElementOptimal(vector<int>& nums)
{
    int count = 0;
    int candidate = -1;

    for(int num : nums)
    {
        if(count == 0)
            candidate = num;

        if(num == candidate)
            count++;
        else
            count--;
    }

    count = 0;

    for(int num : nums)
    {
        if(num == candidate)
            count++;
    }

    if(count > nums.size() / 2)
        return candidate;

    return -1;
}

// Time Complexity : O(N)
// Space Complexity: O(1)


// ==================== DRIVER CODE ====================

int main()
{
    vector<int> nums = {2, 2, 1, 1, 1, 2, 2};

    cout << "Brute Force : "
         << majorityElementBrute(nums) << endl;

    cout << "Better      : "
         << majorityElementBetter(nums) << endl;

    cout << "Optimal     : "
         << majorityElementOptimal(nums) << endl;

    return 0;
}