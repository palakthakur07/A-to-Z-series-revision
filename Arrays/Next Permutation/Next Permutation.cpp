/*
------------------------------------------------------------
Problem : Next Permutation

Approaches
1. Brute Force
2. Better (STL)
3. Optimal

Time Complexity
Brute   : O(N! × N)
Better  : O(N)
Optimal : O(3N)

Space Complexity
Brute   : O(N! × N)
Better  : O(1)
Optimal : O(1)
------------------------------------------------------------
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// ======================================================
// Better Approach (Using STL)
// ======================================================

void nextPermutationSTL(vector<int>& nums)
{
    next_permutation(nums.begin(), nums.end());
}

// ======================================================
// Optimal Approach
// ======================================================

void nextPermutationOptimal(vector<int>& nums)
{
    int n = nums.size();
    int index = -1;

    // Step 1: Find the break point
    for(int i = n - 2; i >= 0; i--)
    {
        if(nums[i] < nums[i + 1])
        {
            index = i;
            break;
        }
    }

    // Step 2: If no break point exists
    if(index == -1)
    {
        reverse(nums.begin(), nums.end());
        return;
    }

    // Step 3: Find the next greater element
    for(int i = n - 1; i > index; i--)
    {
        if(nums[i] > nums[index])
        {
            swap(nums[i], nums[index]);
            break;
        }
    }

    // Step 4: Reverse the suffix
    reverse(nums.begin() + index + 1, nums.end());
}

// ======================================================
// Print Function
// ======================================================

void print(vector<int>& nums)
{
    for(int num : nums)
        cout << num << " ";

    cout << endl;
}

// ======================================================
// Driver Code
// ======================================================

int main()
{
    vector<int> nums1 = {1,2,3};
    vector<int> nums2 = nums1;

    nextPermutationSTL(nums1);
    nextPermutationOptimal(nums2);

    cout << "Using STL : ";
    print(nums1);

    cout << "Optimal   : ";
    print(nums2);

    return 0;
}