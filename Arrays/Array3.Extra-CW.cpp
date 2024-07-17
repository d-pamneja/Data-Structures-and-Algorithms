
// CLASS NOTES: 10
// 	1. Moving All Negative Number to the Left Side of an Array
// 	2. Sort Colors (Leetcode-75)
//  3. Rotate Array (Leetcode-189)
//  4. Missing Number (Leetcode-268)
//  5. Row with maximum ones (VVIimp Leetcode-2643)
//  6. Rotate Image by 90 degree (VVImp Leetcode-48)

// HW SOLVE THESE APPROACHES WITH DIFFERENT APPROACHES

// CLASS HOMEWORK: 10
// 	0. Re-arrange array elements (Leetcode-2149) - 3.extra

#include <iostream>
#include <limits.h>
#include <vector>
#include <limits.h>
using namespace std;



void printArray(int arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }
}

// Q1. Moving All Negative Number to the End of the Array (GFG)
// void MoveNegFirst(int arr[], int n) // Moving negative to left ka function
// {
//     int j = 0; // Here, j is going to track the first positive i.e. jaha par sabse phele +ve number hai for the trail
//     for (int i = 0; i < n; i++)
//     {
//         if (arr[i] < 0)
//         {
//             swap(arr[i], arr[j]);
//             j++;
//         }
//     }
// }

void segregateElements(int arr[],int n){
    vector<int> v;
    
    for(int i=0;i<n;i++){ // First we push all positive elements
        if(arr[i]>=0){
            v.push_back(arr[i]);
        }
    }
    
    for(int i=0;i<n;i++){ // First we push all negative elements
        if(arr[i]<0){
            v.push_back(arr[i]);
        }
    }
    
    for(int i=0;i<n;i++){ // Finally, we replace all elements back with original array
        arr[i] = v[i];
    }
}

// Q2. Sort Colors (Leetcode-75)  - Dutch National Flag Problem
void sortColors(vector<int> &nums){
    int i = 0;
    int left = 0; // Position of Last 0 track karne ke liye
    int right = (nums.size() - 1); // Position of last 2's track karne ke liye

    while (i <= right)
    {
        if (nums[i] == 2)
        {
            // Agar starting mein 2 mille, usse end mein bhej ke right minus kar do, par because swap hoke 0 ya 1 hai we do not know, leave the index and left there only
            swap(nums[i], nums[right]);
            right--;
        }

        else if (nums[i] == 0)
        {
            // Case jab starting mein 0 mille, khud se hi swap kar do aur phir index aur left dono ko hi agge kar do
            swap(nums[i], nums[left]);
            left++;
            i++;
        }

        else
        { // agar 1 hai, toh agge bagh jao
            i++;
        }
    }
}


// Q3. Rotate Array (Leetcode-189) //Inteview Question
void rotate(vector<int>& nums, int k) {
        //Modulus Method
        vector<int> ans(nums.size());
        for(int i=0; i<nums.size();i++){
            ans[(i+k)%nums.size()] = nums[i];
        }
        nums=ans;
}

void rotate(vector<int>& nums, int k) { // IMP approach for Interview
        // Reverse Method
        k = k %(nums.size()); // Taaki k ki value n se badi na ho
        reverse(nums.begin(),nums.end());
        reverse(nums.begin(),nums.begin()+k);
        reverse(nums.begin()+k,nums.end());

        // [1,2,3,4,5,6,7]; k = 3
        // Reverse (0,n-1) -> [7,6,5,4,3,2,1]
        // Reverse (0, k -1) -> [5,6,7,4,3,2,1]
        // Reverse (k,n-1) -> [5,6,7,1,2,3,4]
}

// Q4. Missing Number (Leetcode-268) //Interview
int missingNumber(vector<int>& nums) {
        // // Sum Method
        // int ans = 0;
        // for(int i=0;i<nums.size();i++){
        //     ans += nums[i];
        // }
        // int n = nums.size();
        
        // return ((n*(n+1))/2) - ans;

        // XOR Method
        int ans = 0;
        for(int i=0;i<nums.size();i++){
            ans = ans^ nums[i];
        }
        for(int i=0;i<nums.size();i++){
            ans = ans^ i;
        }
        return ans;
}


// Q5. Row with maximum ones (VVIimp Leetcode-2643)
vector<int> rowAndMaximumOnes(vector<vector<int > >& mat) {
    vector<int> ans;
    int max_sum = INT_MIN;
    int max_row = -1;
    for(int i = 0;i<mat.size();i++){
        int sum = 0;
        for(int j=0;j<mat[i].size();j++){
            if(mat[i][j]==1){
                sum++;
            }
        }
        if(sum>max_sum){
            max_sum = sum;
            max_row = i;
        }
    }

    ans.push_back(max_row);
    ans.push_back(max_sum);
    return ans;
}

// Q6. Rotate Image by 90 degree (VVImp Leetcode-48) // Interview Question
void rotate(vector<vector<int > >& matrix) {
        // Transpose karle phele
        int n = matrix.size();
        for(int i=0;i<n;i++){
            for(int j=i;j<matrix[i].size();j++){
                swap(matrix[i][j],matrix[j][i]);
            }
        }
        // Saari rows ki reverse kar de abh
        for(int i=0;i<n;i++){
            reverse(matrix[i].begin(),matrix[i].end());
        }
}

// Q7. Re-arrange array elements (Leetcode-2149)
vector<int> rearrangeArray(vector<int>& nums) {
        int pos = 0;
        int neg = 1;
        vector<int> ans(nums.size(),-1);

        for(int i=0;i<nums.size();i++){
            if(nums[i]<0){
                ans[neg] = nums[i];
                neg+=2;
            }
            else{
                ans[pos] = nums[i];
                pos+=2;
            }
        }
        nums=ans;
        return nums;
}

// Q8. Maximum Subarray Sum (Kadane's Algorithm) - V.V.V.V.VIMP (GFG)
long long maxSubarraySum(int arr[], int n){
    // // Brute Force - All subarrays and sum check - TC : O(N^2), SC : O(1)
    // long long ans = INT_MIN;
    
    // for(int i=0;i<n;i++){
    //     long long currSum = arr[i];
    //     ans = max(ans,currSum);
        
    //     for(int j=i+1;j<n;j++){
    //         currSum += arr[j];
    //         ans = max(ans,currSum);
    //     }
    // }
    
    // return ans;

    // Optimal Approach - Kadane's Algo - TC : O(N), SC : O(1)
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

// Q9. Minimise Height II - GFG - IMP
// Part I: Minimise Height I
int getMinDiff(int arr[], int n, int k) {
    // code here
    sort(arr,arr+n);
    
    int diff = arr[n-1] - arr[0];
    
    int newMin = INT_MAX;
    int newMax = INT_MIN;
    
    for(int i=1;i<n;i++){
        // IMP Conditions
        newMin = min(arr[0]+k,arr[i]-k); // The distance can be minimized by either from adding k from the smallest element or the reducing k from current index, whichever is minimum
        newMax = max(arr[i-1]+k,arr[n-1]-k); // The distance can be minimized by either from reducing k from the largest element or adding k to the previous towers index, whichever is maximum
            // In newMax we do arr[i-1] because we are comparing the previous tower with the current tower, and it handles the case where values are not unique. 
            // If values are unique, then we can do arr[i] instead of arr[i-1]
            // If values are not unique, then we have to do arr[i-1] because we are comparing the previous tower with the current tower, and if we do arr[i], 
            // then it will compare the current tower with the current tower itself, which is wrong and will give wrong answer.
       
        diff = min(diff,newMax-newMin);
        
    }
    
    return diff;
    
}

// Part II: Minimise Height II
int getMinDiff2(int arr[], int n, int k) {
    // code here
    sort(arr,arr+n);
    
    int diff = arr[n-1] - arr[0];
    
    int newMin = INT_MAX;
    int newMax = INT_MIN;
    
    for(int i=1;i<n;i++){
        // IMP Conditions
        newMin = min(arr[0]+k,arr[i]-k); // The distance can be minimized by either from adding k from the smallest element or the reducing k from current index, whichever is minimum
        newMax = max(arr[i-1]+k,arr[n-1]-k); // The distance can be minimized by either from reducing k from the largest element or adding k to the previous towers index, whichever is maximum
            // In newMax we do arr[i-1] because we are comparing the previous tower with the current tower, and it handles the case where values are not unique. 
            // If values are unique, then we can do arr[i] instead of arr[i-1]
            // If values are not unique, then we have to do arr[i-1] because we are comparing the previous tower with the current tower, and if we do arr[i], 
            // then it will compare the current tower with the current tower itself, which is wrong and will give wrong answer.
        if(newMin<0){ // Skip if minimum difference is greater than 0, since height of tower cannot be less than 0. If -ve allowed, remove this negation
            continue;
        }
        
        diff = min(diff,newMax-newMin);
        
    }
    
    return diff;
    
}



int main()
{
    int arr[] = {-1, 2, -3, -4, 5};
    // MoveNegFirst(arr, 5);
    printArray(arr, 5);
}
