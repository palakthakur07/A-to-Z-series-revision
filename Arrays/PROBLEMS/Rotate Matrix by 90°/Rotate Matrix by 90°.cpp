#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    //================ BRUTE FORCE ================//

    void rotateBrute(vector<vector<int>> &matrix) {

        int n = matrix.size();

        vector<vector<int>> ans(n, vector<int>(n));

        for (int i = 0; i < n; i++) {

            for (int j = 0; j < n; j++) {

                ans[j][n - 1 - i] = matrix[i][j];
            }
        }

        matrix = ans;
    }

    //================ OPTIMAL ================//

    void rotate(vector<vector<int>> &matrix) {

        int n = matrix.size();

        // Step 1 : Transpose

        for (int i = 0; i < n; i++) {

            for (int j = i + 1; j < n; j++) {

                swap(matrix[i][j], matrix[j][i]);
            }
        }

        // Step 2 : Reverse every row

        for (int i = 0; i < n; i++) {

            reverse(matrix[i].begin(), matrix[i].end());

            // Can also be done using Two Pointer Approach.
        }
    }
};