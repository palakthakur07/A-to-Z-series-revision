#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> multiply(vector<vector<int>>& arr,
                             vector<vector<int>>& brr)
{
    int n = arr.size();

    vector<vector<int>> res(n, vector<int>(n, 0));

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            for(int k = 0; k < n; k++)
            {
                res[i][j] += arr[i][k] * brr[k][j];
            }
        }
    }

    return res;
}

int main()
{
    vector<vector<int>> arr =
    {
        {1,2},
        {3,4}
    };

    vector<vector<int>> brr =
    {
        {5,6},
        {7,8}
    };

    vector<vector<int>> ans = multiply(arr, brr);

    for(auto row : ans)
    {
        for(int x : row)
            cout << x << " ";
        cout << endl;
    }

    return 0;
}