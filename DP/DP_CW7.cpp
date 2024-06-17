#include <iostream>
#include <vector>
#include <map>
using namespace std;

// Subset Sum Pattern
// Q1. Partition Equal Subset Sum - (LC-416) - V.V.V.V.V IMP
bool solveUsingRecursion(vector<int>& nums,int index,int currSum, int target){
    // Base Case
    if(index>=nums.size()){
        return false;
    }
    if(currSum>target){
        return false;
    }
    if(currSum==target){
        return true;
    }

    // Recursive Call
    bool include = solveUsingRecursion(nums,index+1,currSum+nums[index],target);
    bool exclude = solveUsingRecursion(nums,index+1,currSum,target);

    return include || exclude;
}

bool solveUsingMem(vector<int>& nums,int index,int currSum, int target,vector<vector<int>> &dp){
    // Base Case
    if(index>=nums.size()){
        return false;
    }
    if(currSum>target){
        return false;
    }
    if(currSum==target){
        return true;
    }

    // Check for answer in vector
    if(dp[index][currSum]!=-1){
        return dp[index][currSum];
    }

    // Recursive Call
    bool include = solveUsingMem(nums,index+1,currSum+nums[index],target,dp);
    bool exclude = solveUsingMem(nums,index+1,currSum,target,dp);

    dp[index][currSum] = (include || exclude);

    return dp[index][currSum];
}

bool solveUsingTab(vector<int>& nums, int target){
    int n = nums.size();
    vector<vector<int>> dp(n+2,vector<int>(target+1,0)); // Rows represent index moving 0->n, cols represent currSum moving 0->target
    // Mark vector with 0's to handle first two condtions. Now third base condition says ki haar row jaha target hai, waha true hona chahiye, so mark it as 1

    for(int row=0;row<=n;row++){
        dp[row][target] = 1;
    }

    // Iterative Call
    for(int index_looper = n-1;index_looper>=0;index_looper--){
        for(int currSum_index = target;currSum_index>=0;currSum_index--){
            bool include = false;
            if(currSum_index+nums[index_looper] <= target){ // Basically to ensure ki hum out of index nahi jaa rahe, Jaha tak target meet hota hai wahi tak include karo, else pattern will break. Make sure when converting to dp to cover all indexes being accessed
                include = dp[index_looper+1][currSum_index+nums[index_looper]];
            }
            bool exclude = dp[index_looper+1][currSum_index];

            dp[index_looper][currSum_index] = (include || exclude);
        }
    }

    return dp[0][0];
}

bool solveUsingSO1(vector<int>& nums, int target){
    int n = nums.size();
    vector<int> currRow(target+1,0); // Represents current row initialised with 0 to handle base cases
    vector<int> nextRow(target+1,0); // Represents next row initialised with 0 to handle base cases
    // Now third base condition says ki haar row jaha target hai, waha true hona chahiye, so mark it as 1 in both arrays

    currRow[target] = 1;
    nextRow[target] = 1;
    

    // Iterative Call
    for(int index_looper = n-1;index_looper>=0;index_looper--){
        for(int currSum_index = target;currSum_index>=0;currSum_index--){
            bool include = false;
            if(currSum_index+nums[index_looper] <= target){ // Basically to ensure ki hum out of index nahi jaa rahe, Jaha tak target meet hota hai wahi tak include karo, else pattern will break. Make sure when converting to dp to cover all indexes being accessed
                include = nextRow[currSum_index+nums[index_looper]];
            }
            bool exclude = nextRow[currSum_index];

            currRow[currSum_index] = (include || exclude);
        }
        // IMP step - Updation
        nextRow = currRow;
    }

    return nextRow[0];
}  

bool canPartition(vector<int>& nums) {
    int totalSum = 0;
    for(int i=0;i<nums.size();i++){
        totalSum+= nums[i];
    }

    if(totalSum&1){// if total sum is odd, cannot divide in two equal parts
        return false; 
    }

    int index = 0;
    int currSum = 0;
    int target = totalSum/2;
    int n = nums.size();
    // vector<vector<int>> dp(n+1,vector<int>(target+1,-1)); // Rows reprenet index moving 0->n, cols represent currSum moving 0->target
    // // return solveUsingRecursion(nums,index,currSum,target);
    // return solveUsingMem(nums,index,currSum,target,dp);
    // return solveUsingTab(nums,target);
    return solveUsingSO1(nums,target);
}

// Q2. Number of dice rolls with target sum - (LC-1155) - V.V.V.V.V IMP
// Jaha par bhi explore all possible ways atta hai, waha par recursion pe loop chalana hota hai
long long int mod = 1000000007;
int SolveUsingRecursion(int n, int k, int target){ 
    // Base Case 
    if(target==0 && n==0){ // Matlab target bhi meet ho gaya AND number of dices bhi khatam ho gaye, matlab reached ideal base case
        return 1;
    }
    if(target!=0 && n==0){ // Matlab target toh nahi mila par dice kahatm ho gaye, no possible solution
        return 0;
    }
    if(target==0 && n!=0){ // target toh mil gaya, par dice bache hai, no possible solution
        return 0 ;
    }

    // Recursive Call
    int ans = 0;
    for(int face=1;face<=k;face++){
        ans+=SolveUsingRecursion(n-1,k,target-face); // Ek dice use kar liya so (n-1), and target to find now mein se current face (i) subtract ho gaya
    }

    return ans%mod;
}

int SolveUsingMem(int n, int k, int target,vector<vector<int>> &dp){ 
    // Base Case 
    if(target==0 && n==0){ // Matlab target bhi meet ho gaya AND number of dices bhi khatam ho gaye, matlab reached ideal base case
        return 1;
    }
    if(target!=0 && n==0){ // Matlab target toh nahi mila par dice kahatm ho gaye, no possible solution
        return 0;
    }
    if(target==0 && n!=0){ // target toh mil gaya, par dice bache hai, no possible solution
        return 0 ;
    }

    if(dp[n][target]!=-1){
        return dp[n][target];
    }

    // Recursive Call
    int ans = 0;
    for(int face=1;face<=k;face++){
        int MemKaAns = 0;
        if(target-face>=0)
            MemKaAns =  (SolveUsingMem(n-1,k,target-face,dp) % mod);
        ans = ((ans%mod) + (MemKaAns%mod))%mod; // Ek dice use kar liya so (n-1), and target to find now mein se current face (i) subtract ho gaya
    }

    dp[n][target] = ans%mod;

    return dp[n][target];
}

int SolveUsingTab(int n, int k, int target){ 
    vector<vector<int>> dp(n+1,vector<int>(target+1,0));

    // Base Case 
    dp[0][0] = 1;

    // Recursive Call
    for(int n_index=1;n_index<=n;n_index++){
        for(int target_index=0;target_index<=target;target_index++){
            int ans = 0;
            for(int face=1;face<=k;face++){
                int TabKaAns = 0;
                if(target_index-face>=0)
                    TabKaAns =  (dp[n_index-1][target_index-face] % mod);
                ans = ((ans%mod) + (TabKaAns%mod))%mod; // Ek dice use kar liya so (n-1), and target to find now mein se current face (i) subtract ho gaya
            }
            dp[n_index][target_index] = ans%mod;
        }
    }
    

    return dp[n][target];
}

int SolveUsingSO1(int n, int k, int target){ 
    vector<int> prevRow(target+2,0);
    vector<int> currRow(target+2,0);

    // Base Case 
    prevRow[0] = 1;

    // Recursive Call
    for(int n_index=1;n_index<=n;n_index++){
        for(int target_index=0;target_index<=target;target_index++){
            int ans = 0;
            for(int face=1;face<=k;face++){
                int TabKaAns = 0;
                if(target_index-face>=0)
                    TabKaAns =  (prevRow[target_index-face] % mod);
                ans = ((ans%mod) + (TabKaAns%mod))%mod; // Ek dice use kar liya so (n-1), and target to find now mein se current face (i) subtract ho gaya
            }
            currRow[target_index] = ans%mod;
        }
        prevRow = currRow;
    }
    

    return prevRow[target];
}



int numRollsToTarget(int n, int k, int target) {
    // vector<vector<int>> dp(n+1,vector<int>(target+1,-1));
    // return SolveUsingMem(n,k,target,dp);
    // return SolveUsingTab(n,k,target);
    return SolveUsingSO1(n,k,target);
}