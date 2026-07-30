#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> transpose(vector<vector<int>>& mat)
{
    int rows = mat.size();
    int cols = mat[0].size();

    vector<vector<int>> tMat(cols, vector<int>(rows));

    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            tMat[j][i] = mat[i][j];
        }
    }

    return tMat;
}

int main()
{
    vector<vector<int>> mat =
    {
        {1,2,3},
        {4,5,6}
    };

    vector<vector<int>> ans = transpose(mat);

    for(auto row : ans)
    {
        for(int x : row)
            cout << x << " ";

        cout << endl;
    }

    return 0;
}