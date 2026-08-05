#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    //================ BRUTE FORCE ================//
    // Sort the intervals. For each interval not already covered by the last
    // merged interval in the answer, expand forward through subsequent
    // intervals as long as they overlap, then push the merged result.
    // Time: O(N log N + N)  |  Space: O(N)
    vector<vector<int>> mergeBrute(vector<vector<int>>& array) {
        int n = array.size();
        sort(array.begin(), array.end());
        vector<vector<int>> answer;

        for (int i = 0; i < n; i++) {
            // Already covered by the last merged interval — skip
            if (!answer.empty() && array[i][1] <= answer.back()[1]) {
                continue;
            }

            int start = array[i][0];
            int end = array[i][1];

            for (int j = i + 1; j < n; j++) {
                if (array[j][0] <= end) {
                    end = max(end, array[j][1]);
                } else {
                    break; // sorted array, nothing further can overlap
                }
            }

            answer.push_back({start, end});
        }

        return answer;
    }

    //================ OPTIMAL ================//
    // Sort the intervals. In a single pass, compare each interval only with
    // the last interval placed in the answer — merge if it overlaps,
    // otherwise start a new interval.
    // Time: O(N log N)  |  Space: O(N)
    vector<vector<int>> merge(vector<vector<int>>& array) {
        int n = array.size();
        sort(array.begin(), array.end());
        vector<vector<int>> answer;

        for (int i = 0; i < n; i++) {
            // No overlap with the last merged interval — start a new one
            if (answer.empty() || array[i][0] > answer.back()[1]) {
                answer.push_back(array[i]);
            } else {
                // Overlaps — extend the end of the last merged interval
                answer.back()[1] = max(answer.back()[1], array[i][1]);
            }
        }

        return answer;
    }
};