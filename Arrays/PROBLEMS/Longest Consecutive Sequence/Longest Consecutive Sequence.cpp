#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    //================ BRUTE FORCE ================//

    bool ls(vector<int> &arr, int num) {
        for (int i = 0; i < arr.size(); i++) {
            if (arr[i] == num)
                return true;
        }
        return false;
    }

    int longestConsecutiveBrute(vector<int> &arr) {

        int n = arr.size();
        int longest = 1;

        for (int i = 0; i < n; i++) {

            int x = arr[i];
            int cnt = 1;

            while (ls(arr, x + 1)) {
                x = x + 1;
                cnt++;
            }

            longest = max(longest, cnt);
        }

        return longest;
    }

    //================ BETTER ================//

    int longestConsecutiveBetter(vector<int> &arr) {

        int n = arr.size();

        if (n == 0)
            return 0;

        sort(arr.begin(), arr.end());

        int longest = 1;
        int cnt = 0;
        int lastSmaller = INT_MIN;

        for (int i = 0; i < n; i++) {

            if (arr[i] - 1 == lastSmaller) {

                cnt++;
                lastSmaller = arr[i];
            }

            else if (lastSmaller != arr[i]) {

                cnt = 1;
                lastSmaller = arr[i];
            }

            longest = max(longest, cnt);
        }

        return longest;
    }

    //================ OPTIMAL ================//

    int longestConsecutive(vector<int> &arr) {

        int n = arr.size();

        if (n == 0)
            return 0;

        int longest = 1;

        unordered_set<int> st;

        for (int i = 0; i < n; i++) {
            st.insert(arr[i]);
        }

        for (auto it : st) {

            if (st.find(it - 1) == st.end()) {

                int cnt = 1;
                int x = it;

                while (st.find(x + 1) != st.end()) {
                    x = x + 1;
                    cnt++;
                }

                longest = max(longest, cnt);
            }
        }

        return longest;
    }
};