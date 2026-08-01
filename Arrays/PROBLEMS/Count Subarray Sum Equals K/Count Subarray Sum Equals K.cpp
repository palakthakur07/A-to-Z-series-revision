#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    //================ BRUTE FORCE ================//

    int subarraySumBrute(vector<int>& nums, int k) {

        int n = nums.size();
        int cnt = 0;

        for (int i = 0; i < n; i++) {

            for (int j = i; j < n; j++) {

                int sum = 0;

                for (int l = i; l <= j; l++) {
                    sum += nums[l];
                }

                if (sum == k)
                    cnt++;
            }
        }

        return cnt;
    }

    //================ BETTER ================//

    int subarraySumBetter(vector<int>& nums, int k) {

        int n = nums.size();
        int cnt = 0;

        for (int i = 0; i < n; i++) {

            int sum = 0;

            for (int j = i; j < n; j++) {

                sum += nums[j];

                if (sum == k)
                    cnt++;
            }
        }

        return cnt;
    }

    //================ OPTIMAL ================//

    int subarraySum(vector<int>& nums, int k) {

        int n = nums.size();

        map<int, int> mpp;

        mpp[0] = 1;

        int preSum = 0;
        int cnt = 0;

        for (int i = 0; i < n; i++) {

            preSum += nums[i];

            int remove = preSum - k;

            cnt += mpp[remove];

            mpp[preSum]++;
        }

        return cnt;
    }
};