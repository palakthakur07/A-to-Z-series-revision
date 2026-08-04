#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    //================ BRUTE FORCE ================//
    // Try every possible quadruplet using four nested loops.
    // Use a set<vector<int>> to automatically filter out duplicates.
    // Time: O(N^4)  |  Space: O(2 * X) (X = number of unique quadruplets)
    vector<vector<int>> fourSumBrute(vector<int>& nums, int target) {
        int n = nums.size();
        set<vector<int>> st;

        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                for (int k = j + 1; k < n; k++) {
                    for (int l = k + 1; l < n; l++) {
                        // Use long long to avoid integer overflow
                        long long sum = nums[i];
                        sum += nums[j];
                        sum += nums[k];
                        sum += nums[l];

                        if (sum == target) {
                            vector<int> temp = {nums[i], nums[j], nums[k], nums[l]};
                            sort(temp.begin(), temp.end());
                            st.insert(temp);
                        }
                    }
                }
            }
        }

        vector<vector<int>> ans(st.begin(), st.end());
        return ans;
    }

    //================ BETTER ================//
    // Fix i, j, k with three nested loops. For each triplet, look up the
    // required fourth value in a hash set built only from elements strictly
    // between j and k, so no index is reused.
    // Time: O(N^3 * log M)  |  Space: O(N) + O(2 * X)
    vector<vector<int>> fourSumBetter(vector<int>& nums, int target) {
        int n = nums.size();
        set<vector<int>> st;

        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                unordered_set<int> hashSet;
                for (int k = j + 1; k < n; k++) {
                    long long sum = nums[i];
                    sum += nums[j];
                    sum += nums[k];
                    long long fourth = (long long)target - sum;

                    if (hashSet.find((int)fourth) != hashSet.end()) {
                        vector<int> temp = {nums[i], nums[j], nums[k], (int)fourth};
                        sort(temp.begin(), temp.end());
                        st.insert(temp);
                    }

                    // Insert nums[k] so future k's can find it as a potential fourth element
                    hashSet.insert(nums[k]);
                }
            }
        }

        vector<vector<int>> ans(st.begin(), st.end());
        return ans;
    }

    //================ OPTIMAL ================//
    // Sort the array. Fix i and j with nested loops, then use two pointers
    // (k, l) for the remaining two positions. Skip duplicates at all four
    // levels directly using the sorted order — no hash set or extra set needed.
    // Time: O(N^3)  |  Space: O(1) extra (excluding the answer list)
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        int n = nums.size();
        sort(nums.begin(), nums.end());
        vector<vector<int>> ans;

        for (int i = 0; i < n; i++) {
            // Skip duplicate first elements
            if (i > 0 && nums[i] == nums[i - 1]) continue;

            for (int j = i + 1; j < n; j++) {
                // Skip duplicate second elements
                if (j > i + 1 && nums[j] == nums[j - 1]) continue;

                int k = j + 1;
                int l = n - 1;

                while (k < l) {
                    long long sum = nums[i];
                    sum += nums[j];
                    sum += nums[k];
                    sum += nums[l];

                    if (sum < target) {
                        k++;
                    } else if (sum > target) {
                        l--;
                    } else {
                        ans.push_back({nums[i], nums[j], nums[k], nums[l]});
                        k++;
                        l--;

                        // Skip duplicates for k and l
                        while (k < l && nums[k] == nums[k - 1]) k++;
                        while (k < l && nums[l] == nums[l + 1]) l--;
                    }
                }
            }
        }

        return ans;
    }
};