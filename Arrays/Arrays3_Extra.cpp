# include <iostream>
# include <vector>

using namespace std;

// Q1. Kadane's Algorithm - GFG - V.V.V.V.VIMP
long long maxSubarraySum(int arr[], int n){
    long long maxi = LONG_MIN; // Stores the maximum sum overall
    long long curr_maxi = 0; // Stores the current maximum
    
    for(int i=0;i<n;i++){
        curr_maxi += arr[i];
        
        if(curr_maxi>maxi){
            maxi = curr_maxi;
        }
        
        if(curr_maxi<0){
            curr_maxi = 0;
        }
        
    }
    
    return maxi;
    
}

// Q2. Minimise Height II - GFG - IMP
int getMinDiff(int arr[], int n, int k) {
    // code here
    sort(arr,arr+n);
    
    int diff = arr[n-1] - arr[0];
    
    int newMin = INT_MAX;
    int newMax = INT_MIN;
    
    for(int i=1;i<n;i++){
        // IMP Conditions
        newMin = min(arr[0]+k,arr[i]-k); // The distance can be minimized by either from adding k from the smallest element or the reducing k from current index, whichever is minimum
        newMax = max(arr[i-1]+k,arr[n-1]-k); // The distance can be minimized by either from reducing k from the largest element or adding k to the current index, whichever is maximum

        if(newMin<0){ // Skip if minimum difference is greater than 0, since height of tower cannot be less than 0. If -ve allowed, remove this negation
            continue;
        }
        
        diff = min(diff,newMax-newMin);
        
    }
    
    return diff;
    
}