/*
    Problem: Sort an Array of 0s, 1s and 2s

    Approaches:
    1. Brute Force (Sorting)
    2. Better (Counting)
    3. Optimal (Dutch National Flag Algorithm)
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// ==================== BRUTE FORCE ====================

void sortBrute(vector<int>& arr)
{
    sort(arr.begin(), arr.end());
}

// Time Complexity : O(N log N)
// Space Complexity: O(1)


// ==================== BETTER (COUNTING) ====================

void sortBetter(vector<int>& arr)
{
    int count0 = 0;
    int count1 = 0;
    int count2 = 0;

    for(int num : arr)
    {
        if(num == 0)
            count0++;
        else if(num == 1)
            count1++;
        else
            count2++;
    }

    int index = 0;

    while(count0--)
        arr[index++] = 0;

    while(count1--)
        arr[index++] = 1;

    while(count2--)
        arr[index++] = 2;
}

// Time Complexity : O(N)
// Space Complexity: O(1)


// ==================== OPTIMAL (DUTCH NATIONAL FLAG) ====================

void sortOptimal(vector<int>& arr)
{
    int low = 0;
    int mid = 0;
    int high = arr.size() - 1;

    while(mid <= high)
    {
        if(arr[mid] == 0)
        {
            swap(arr[low], arr[mid]);
            low++;
            mid++;
        }
        else if(arr[mid] == 1)
        {
            mid++;
        }
        else
        {
            swap(arr[mid], arr[high]);
            high--;
        }
    }
}

// Time Complexity : O(N)
// Space Complexity: O(1)


// ==================== PRINT FUNCTION ====================

void printArray(vector<int>& arr)
{
    for(int num : arr)
        cout << num << " ";

    cout << endl;
}


// ==================== DRIVER CODE ====================

int main()
{
    vector<int> arr = {2, 0, 2, 1, 1, 0};

    vector<int> brute = arr;
    vector<int> better = arr;
    vector<int> optimal = arr;

    sortBrute(brute);
    sortBetter(better);
    sortOptimal(optimal);

    cout << "Brute Force : ";
    printArray(brute);

    cout << "Better      : ";
    printArray(better);

    cout << "Optimal     : ";
    printArray(optimal);

    return 0;
}