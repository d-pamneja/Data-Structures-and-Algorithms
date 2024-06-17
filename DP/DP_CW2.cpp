#include <iostream>
#include <vector>
using namespace std;

// Q1. House Robber - (Leetcode-198)
int solveUsingMemoisation(vector<int>& nums, int index,vector<int>& dp){
    // Base Case
    if(index>=nums.size()){
        return 0;
    }

    if(dp[index]!=-1){
        return dp[index];
    }

    int include = nums[index] + solveUsingMemoisation(nums,index+2,dp); // Include current house
    int exclude = 0 + solveUsingMemoisation(nums,index+1,dp); // Exclude current house

    dp[index] = max(include,exclude);

    return dp[index];
}

int solveUsingTabulisation(vector<int>& nums){
    int n = nums.size();
    vector<int> dp(nums.size()+1,0);

    // This case will have no invalid index
    // Now, let us manually get the answer for the last index 
    dp[n-1] = nums[n-1]; // IMP Condition. Yaha mein galti karta hoon ki last index ka answer nahi mil raha, so I need to manually get that

    for(int i=(n-2);i>=0;i--){ // Imp Condition, start from n - 2. Yaha mein galti karta hoon ki last index ka answer nahi mil raha, so I need to manually get that
        int include = nums[i] + dp[i+2]; // Include current house
        int exclude = 0 + dp[i+1]; // Exclude current house

        dp[i] = max(include,exclude);
    }

    return dp[0]; // Right to left move kar rahe hai, so answer will be built at 0th index
}

int solveUsingPattern(vector<int>& nums){
    int n = nums.size();

    int next = 0;
    int prev = nums[n-1];
    int ans;

    if(n<2){ // Imp Special Case Condition. Yaha mein galti karta hoon
        return prev;
    }

    for(int i=(n-2);i>=0;i--){ //Imp Condition, start from n - 2. Yaha mein galti karta hoon
        int include = nums[i] + next; // Include current house
        int exclude = 0 + prev; // Exclude current house

        ans = max(include,exclude);

        // Update points
        next = prev;
        prev = ans;

    }

    return ans;
}

int rob(vector<int>& nums) {
    // int index = 0;
    // int n = nums.size();
    // vector<int> dp(n+1,-1);
    // return solveUsingMemoisation(nums,index,dp);
    return solveUsingTabulisation(nums);
}

// Q2. Coin Change - (Leetcode-322) V.V.V.V.V.V.V.IMP
int solveUsingRecursion(vector<int>& coins, int amount){
    // Base Case
    if(amount<=0){
        return 0;
    }

    // Recursive Relation
    int mini = INT_MAX;
    for(int i=0;i<coins.size();i++){
        if(amount - coins[i]>=0){ // To handle the negative case i.e. when amount stays +ve only then proceed
            int recursionKaAns = solveUsingRecursion(coins,amount - coins[i]);
            if(recursionKaAns!=INT_MAX){ // In case it does'nt hit upper limmit to prevent overflow
                int ans = 1 + recursionKaAns; // Assuming we have used the current coin, so we add that to usage and get final ans
                mini = min(mini,ans);
            } 
        }
    }
    return mini;
}

int solveUsingMem(vector<int>& coins,int amount,vector<int>& dp){
    // Base Case
    if(amount<=0){
        return 0;
    }

    if(dp[amount]!=(-1)){
        return dp[amount];
    }

    // Recursive Relation
    int mini = INT_MAX;
    for(int i=0;i<coins.size();i++){
        if(amount - coins[i]>=0){ // To handle the negative case i.e. when amount stays +ve only then proceed
            int recursionKaAns = solveUsingMem(coins,amount - coins[i],dp);
            if(recursionKaAns!=INT_MAX){ // In case it does'nt hit upper limmit to prevent overflow
                int ans = 1 + recursionKaAns; // Assuming we have used the current coin, so we add that to usage and get final ans
                mini = min(mini,ans);
            } 
        }
    }

    dp[amount] = mini;
    return dp[amount];
}

int solveUsingTabular(vector<int>& coins,int amount){
    // 1. Create 1-D array
    int n = amount;
    vector<int> dp(n+1,INT_MAX); // Amount + 1 ke size ki vector bana le, cause at max amount jitne elements hongay vector mein

    // 2. Base Case 
    dp[0] = 0;

    for(int value=1;value<=amount;value++){
        int mini = INT_MAX;
        for(int i=0;i<coins.size();i++){
            if(value - coins[i]>=0){ // To handle the negative case i.e. when amount stays +ve only then proceed
                int TabKaAns = dp[value - coins[i]];
                if(TabKaAns!=INT_MAX){ // In case it does'nt hit upper limmit to prevent overflow
                    int ans = 1 + TabKaAns; // Assuming we have used the current coin, so we add that to usage and get final ans
                    mini = min(mini,ans);
                } 
            }
        }
        dp[value] = mini;
    }
    return dp[amount];
}

int coinChange(vector<int>& coins, int amount) {
    int n = amount;
    vector<int> dp(n+1,-1); // Amount + 1 ke size ki vector bana le, cause at max amount jitne elements hongay vector mein
    int ansMem = solveUsingMem(coins,amount,dp);
    if(ansMem!=INT_MAX) return ansMem;
    else return -1;
    // int ansRec = solveUsingRecursion(coins,amount);
    // if(ansRec!=INT_MAX) return ansRec;
    // else return -1;
    
}