#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    //================ BRUTE FORCE ================//
    // Try every triplet using three nested loops.
    // Sort each valid triplet and store it in a set to remove duplicates.
    // Time: O(N^3 log M) | Space: O(2 * X)
    vector<vector<int>> threeSumBrute(vector<int>& nums) {
        int n = nums.size();
        set<vector<int>> st;

        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                for (int k = j + 1; k < n; k++) {
                    if (nums[i] + nums[j] + nums[k] == 0) {
                        vector<int> temp = {nums[i], nums[j], nums[k]};
                        sort(temp.begin(), temp.end());
                        st.insert(temp);
                    }
                }
            }
        }

        vector<vector<int>> ans(st.begin(), st.end());
        return ans;
    }

    //================ BETTER ================//
    // Fix i and j, use hashing to find the required third element.
    // Reset the hash set every time i changes.
    // Time: O(N^2) | Space: O(N) + O(2 * X)
    vector<vector<int>> threeSumBetter(vector<int>& nums) {
        int n = nums.size();
        set<vector<int>> st;

        for (int i = 0; i < n; i++) {
            set<int> hashset;
            for (int j = i + 1; j < n; j++) {
                int third = -(nums[i] + nums[j]);

                if (hashset.find(third) != hashset.end()) {
                    vector<int> temp = {nums[i], nums[j], third};
                    sort(temp.begin(), temp.end());
                    st.insert(temp);
                }

                hashset.insert(nums[j]);
            }
        }

        vector<vector<int>> ans(st.begin(), st.end());
        return ans;
    }

    //================ OPTIMAL ================//
    // Sort the array, fix i, use two pointers (j, k) to find the pair
    // that sums to -nums[i]. Skip duplicates directly using sorted order.
    // Time: O(N log N + N^2) | Space: O(1) (excluding answer list)
    vector<vector<int>> threeSumOptimal(vector<int>& nums) {
        int n = nums.size();
        sort(nums.begin(), nums.end());
        vector<vector<int>> ans;

        for (int i = 0; i < n; i++) {
            // avoid duplicate first elements
            if (i != 0 && nums[i] == nums[i - 1]) continue;

            int j = i + 1;
            int k = n - 1;

            while (j < k) {
                int sum = nums[i] + nums[j] + nums[k];

                if (sum < 0) {
                    j++;
                } else if (sum > 0) {
                    k--;
                } else {
                    vector<int> temp = {nums[i], nums[j], nums[k]};
                    ans.push_back(temp);
                    j++;
                    k--;

                    // skip duplicates for j
                    while (j < k && nums[j] == nums[j - 1]) j++;
                    // skip duplicates for k
                    while (j < k && nums[k] == nums[k + 1]) k--;
                }
            }
        }

        return ans;
    }

};