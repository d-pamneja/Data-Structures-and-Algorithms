#include <vector>
#include <limits.h>
#include <stack>

using namespace std;

// Ques. Reverse an Array - All Approaches (GFG : https://www.geeksforgeeks.org/problems/reverse-an-array/1)
// Ans.

void reverseArray(vector<int> &arr) {
    // Brute Force - Temp Array and Reverse Traverse - TC : O(N), SC : O(N)
    vector<int> temp;
    for(int i = arr.size() - 1; i >= 0;i--){
        temp.push_back(arr[i]);
    }
    arr = temp;
    
    // Optimal Approach 1 - Two Pointer - TC : O(N), SC : O(1)
    int start = 0;
    int end = arr.size() - 1;
    
    while(start<end){
        swap(arr[start],arr[end]);
        start++;
        end--;
    }
    
    // Optimal Approach 2 - Single Pointer - TC : O(N), SC : O(1)
    int n = arr.size();
    
    for(int i = 0;i < n/2; i++){
        swap(arr[i],arr[n-i-1]);
    }

    // In case of not allowed to use for or while loops, use a stack to reverse the array. It would
    // have TC: O(N) and SC: O(N)
    stack<int> st;
    for(int i = 0;i < n; i++){
        st.push(arr[i]);
    }

    int i = 0;
    while(!st.empty()){
        arr[i] = st.top();
        st.pop();
        i++;
    }
}
