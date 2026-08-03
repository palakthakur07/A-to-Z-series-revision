#include <bits/stdc++.h>
using namespace std;

/*
-----------------------------------------
Variant 1 : Find Element at (R,C)
TC : O(r)
SC : O(1)
-----------------------------------------
*/

int nCr(int n, int r)
{
    long long res = 1;

    for (int i = 0; i < r; i++)
    {
        res = res * (n - i);
        res = res / (i + 1);
    }

    return res;
}

/*
-----------------------------------------
Variant 2 : Print Nth Row
TC : O(N)
SC : O(1) (excluding answer vector)
-----------------------------------------
*/

vector<int> generateRow(int row)
{
    long long ans = 1;

    vector<int> ansRow;

    ansRow.push_back(1);

    for (int col = 1; col < row; col++)
    {
        ans = ans * (row - col);
        ans = ans / col;

        ansRow.push_back(ans);
    }

    return ansRow;
}

/*
-----------------------------------------
Variant 3 : Pascal Triangle
LeetCode 118
TC : O(N²)
SC : O(N²)
-----------------------------------------
*/

class Solution
{
public:
    vector<vector<int>> generate(int numRows)
    {
        vector<vector<int>> ans;

        for (int row = 1; row <= numRows; row++)
        {
            ans.push_back(generateRow(row));
        }

        return ans;
    }
};