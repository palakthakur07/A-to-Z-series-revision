/*
------------------------------------------------------------
Problem : Leaders in an Array

Approaches
1. Brute Force
2. Optimal

Time Complexity
Brute   : O(N²)
Optimal : O(N)

Space Complexity
Brute   : O(N)
Optimal : O(N)
------------------------------------------------------------
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// ======================================================
// Brute Force Approach
// ======================================================

vector<int> leadersBrute(vector<int>& nums)
{
    vector<int> ans;
    int n = nums.size();

    for(int i = 0; i < n; i++)
    {
        bool leader = true;

        for(int j = i + 1; j < n; j++)
        {
            if(nums[j] > nums[i])
            {
                leader = false;
                break;
            }
        }

        if(leader)
            ans.push_back(nums[i]);
    }

    return ans;
}

// ======================================================
// Optimal Approach
// ======================================================

vector<int> leadersOptimal(vector<int>& nums)
{
    vector<int> ans;

    int n = nums.size();
    int maxElement = nums[n - 1];

    ans.push_back(maxElement);

    for(int i = n - 2; i >= 0; i--)
    {
        if(nums[i] > maxElement)
        {
            ans.push_back(nums[i]);
            maxElement = nums[i];
        }
    }

    reverse(ans.begin(), ans.end());

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
    vector<int> nums = {10, 22, 12, 3, 0, 6};

    vector<int> brute = leadersBrute(nums);
    vector<int> optimal = leadersOptimal(nums);

    cout << "Brute Force : ";
    print(brute);

    cout << "Optimal     : ";
    print(optimal);

    return 0;
}