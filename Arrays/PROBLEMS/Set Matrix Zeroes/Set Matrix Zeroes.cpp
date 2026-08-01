#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    //================ BRUTE FORCE ================//

    void markRow(vector<vector<int>> &matrix, int i, int m) {
        for (int j = 0; j < m; j++) {
            if (matrix[i][j] != 0)
                matrix[i][j] = -1;
        }
    }

    void markCol(vector<vector<int>> &matrix, int j, int n) {
        for (int i = 0; i < n; i++) {
            if (matrix[i][j] != 0)
                matrix[i][j] = -1;
        }
    }

    void setZeroesBrute(vector<vector<int>> &matrix) {

        int n = matrix.size();
        int m = matrix[0].size();

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {

                if (matrix[i][j] == 0) {
                    markRow(matrix, i, m);
                    markCol(matrix, j, n);
                }
            }
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {

                if (matrix[i][j] == -1)
                    matrix[i][j] = 0;
            }
        }
    }

    //================ BETTER ================//

    void setZeroesBetter(vector<vector<int>> &matrix) {

        int n = matrix.size();
        int m = matrix[0].size();

        vector<int> row(n, 0);
        vector<int> col(m, 0);

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {

                if (matrix[i][j] == 0) {
                    row[i] = 1;
                    col[j] = 1;
                }
            }
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {

                if (row[i] || col[j])
                    matrix[i][j] = 0;
            }
        }
    }

    //================ OPTIMAL ================//

    void setZeroes(vector<vector<int>> &matrix) {

        int n = matrix.size();
        int m = matrix[0].size();

        int col0 = 1;

        for (int i = 0; i < n; i++) {

            if (matrix[i][0] == 0)
                col0 = 0;

            for (int j = 1; j < m; j++) {

                if (matrix[i][j] == 0) {

                    matrix[i][0] = 0;
                    matrix[0][j] = 0;
                }
            }
        }

        for (int i = n - 1; i >= 0; i--) {

            for (int j = m - 1; j >= 1; j--) {

                if (matrix[i][0] == 0 || matrix[0][j] == 0)
                    matrix[i][j] = 0;
            }

            if (col0 == 0)
                matrix[i][0] = 0;
        }
    }
};