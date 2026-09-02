#include <vector>
#include <limits.h>

using namespace std;

// Ques. Find Maximum and Minium - All Approaches (GFG : https://www.geeksforgeeks.org/problems/find-minimum-and-maximum-element-in-an-array4428/1)
// Ans.
vector<int> getMinMax(vector<int> &arr) {
    // Brute Force - Inbuilt Sort - TC : O(N*logN), SC : O(N)
    vector<int> sortedArr = arr;
    sort(sortedArr.begin(),sortedArr.end());
    return {sortedArr[0],sortedArr[sortedArr.size()-1]};
    
    // Better Approach - Iterate the Array with updates to min and max (INT_MIN and INT_MAX) - TC : O(N), SC : O(1)
    int minimum = INT_MAX;
    int maximum = INT_MIN;
    
    for(int i = 0; i < arr.size(); i ++){
        const int val = arr[i];
        if(val < minimum){
            minimum = val;
        }
        if(val > maximum){
            maximum = val;
        }
    }
    
    return {minimum, maximum};
    
    // Optimal Approach - Comparison in Pairs - TC : O(N), SC : O(1)
    int n = arr.size();
    int mini, maxi, i;

    if (n % 2 == 1) { // Initialize min and max
        mini = maxi = arr[0];
        i = 1;
    } else {
        if (arr[0] < arr[1]) {
            mini = arr[0];
            maxi = arr[1];
        } else {
            mini = arr[1];
            maxi = arr[0];
        }
        i = 2;
    }

    while (i < n - 1) {         // Process elements in pairs (so increment of i by 2)
        if (arr[i] < arr[i + 1]) {
            mini = min(mini, arr[i]);
            maxi = max(maxi, arr[i + 1]);
        } else {
            mini = min(mini, arr[i + 1]);
            maxi = max(maxi, arr[i]);
        }
        i += 2;
    }

    return {mini, maxi};
}