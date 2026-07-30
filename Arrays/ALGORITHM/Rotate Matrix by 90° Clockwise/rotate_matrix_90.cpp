#include <iostream>
#include <vector>
using namespace std;

void rotateMatrix(vector<vector<int>>& mat)
{
    int n = mat.size();

    for(int i = 0; i < n / 2; i++)
    {
        for(int j = i; j < n - i - 1; j++)
        {
            int temp = mat[i][j];

            mat[i][j] = mat[n - 1 - j][i];

            mat[n - 1 - j][i] = mat[n - 1 - i][n - 1 - j];

            mat[n - 1 - i][n - 1 - j] = mat[j][n - 1 - i];

            mat[j][n - 1 - i] = temp;
        }
    }
}

int main()
{
    vector<vector<int>> mat =
    {
        {1,2,3},
        {4,5,6},
        {7,8,9}
    };

    rotateMatrix(mat);

    for(auto row : mat)
    {
        for(int x : row)
            cout << x << " ";

        cout << endl;
    }

    return 0;
}