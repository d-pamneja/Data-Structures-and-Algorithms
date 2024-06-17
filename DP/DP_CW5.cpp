#include <iostream>
#include <vector>
using namespace std;

// Longest Increasing Subsequence Pattern

// Q1. Longest Increasing Subsequence - (LC-300) - V.V.V.V.V.V.V.V.V.V IMP
// Jab bhi insertion,replacement and deletion ki baat ho based on some condition, yeh wala pattern use karo lagega most of the times
// yaha index shifting ka concept bhi use hua hai, so keep that in mind

int solveUsingRecursion(vector<int>& nums,int curr, int prev){ // TC: O(2^n), SC: O(n)
    // Base Case
    if(curr>=nums.size()){
        return 0;
    }

    // Recursive Call
    int include = 0;
    if(prev == -1 || nums[curr]>nums[prev]){ // Means agar prev starting pe hi hai, so naturally we will have to include curr element
        include = 1 + solveUsingRecursion(nums,curr+1,curr); // Include current element and then increase both curr and prev i.e. prev ko agge badhana matlab curr pe lana (prev+1 maat kariyo, it breaks pattern as prev is an imaginary variable)
    }
    int exclude = 0 + solveUsingRecursion(nums,curr+1,prev); // Exclude current element and then increase curr and prev stays the same i.e. jab include hi nahi kiya so no need to move prev

    return max(include,exclude);
}

int solveUsingMem(vector<int>& nums,int curr, int prev, vector<vector<int>> &dp){ // TC: O(n^2), SC: O(n^2)
    // Base Case
    if(curr>=nums.size()){
        return 0;
    }

    // Since prev starts from -1, we will do index shifting to make it valid
    if(dp[curr][prev+1]!=-1){
        return dp[curr][prev+1];
    }

    // Recursive Call
    int include = 0;
    if(prev == -1 || nums[curr]>nums[prev]){ // Means agar prev starting pe hi hai, so naturally we will have to include curr element
        include = 1 + solveUsingMem(nums,curr+1,curr,dp); // Include current element and then increase both curr and prev i.e. prev ko agge badhana matlab curr pe lana (prev+1 maat kariyo, it breaks pattern as prev is an imaginary variable)
    }
    int exclude = 0 + solveUsingMem(nums,curr+1,prev,dp); // Exclude current element and then increase curr and prev stays the same i.e. jab include hi nahi kiya so no need to move prev

    dp[curr][prev+1] = max(include,exclude); // since prev will get -1, hence add +1 to it to make all cases valid
    return dp[curr][prev+1]; //  since prev will get -1, hence add +1 to it to make all cases valid
}

int solveUsingTab(vector<int>& nums){ // TC: O(n^2), SC: O(n^2)
    vector<vector<int>> dp(nums.size()+1,vector<int>(nums.size()+1,0)); // Note here, prev column is imaginary col hence we will operate on prev + 1


    // Iterative Call
    for(int i=nums.size()-1;i>=0;i--){ // Curr went from 0->n, so uska ulta hoga. Plus yaha if we start from n-1, we have already handled curr=n walla case
        for(int j=i-1;j>=-1;j--){ // Prec went from -1->n-1, so uska ulta hoga i.e. curr ke ek peeche se shuru hoga
            int include = 0;
            if(j == -1 || nums[i]>nums[j]){ // Means agar prev starting pe hi hai, so naturally we will have to include curr element
                include = 1 + dp[i+1][i+1]; // Include current element and then increase both curr and prev i.e. prev ko agge badhana matlab curr pe lana (prev+1 maat kariyo, it breaks pattern as prev is an imaginary variable). In tabulation, make both of them i+1 as i==current index
            }
            int exclude = 0 + dp[i+1][j+1]; // Exclude current and then increase curr and prev stays the same i.e. jab include hi nahi kiya so no need to move prev, but since prev will get -1, hence add +1 to it to make all cases valid

            dp[i][j+1] = max(include,exclude);
        }
    }
    
    return dp[0][0];
}

int solveUsingSO1(vector<int>& nums){ // TC: O(n^2), SC: O(n)
    // Here, current row is dependent on curr+1 row, so we use two arrays
    vector<int> curr(nums.size()+1,0);
    vector<int> next(nums.size()+1,0);

    // Iterative Call - Since yaha hum row wise hi traverse kar rahe hai, no need to switch loops
    for(int i=nums.size()-1;i>=0;i--){ // Curr went from 0->n, so uska ulta hoga. Plus yaha if we start from n-1, we have already handled curr=n walla case
        for(int j=i-1;j>=-1;j--){ // Prec went from -1->n-1, so uska ulta hoga i.e. curr ke ek peeche se shuru hoga
            int include = 0;
            if(j == -1 || nums[i]>nums[j]){ // Means agar prev starting pe hi hai, so naturally we will have to include curr element
                include = 1 + next[i+1]; // Include current element and then increase both curr and prev i.e. prev ko agge badhana matlab curr pe lana (prev+1 maat kariyo, it breaks pattern as prev is an imaginary variable). In tabulation, make both of them i+1 as i==current index
            }
            int exclude = 0 + next[j+1]; // Exclude current and then increase curr and prev stays the same i.e. jab include hi nahi kiya so no need to move prev, but since prev will get -1, hence add +1 to it to make all cases valid

            curr[j+1] = max(include,exclude);
        }
        // Update Step
        next = curr;
    }
    
    return next[0];
}

int solveUsingBinarySearch(vector<int> &nums){ // TC: O(nlogn), SC: O(n)
    if(nums.size()==0){
        return 0;
    }

    vector<int> ans;
    // Now, phele element toh store karna hi padgea 
    ans.push_back(nums[0]);

    for(int i=1;i<nums.size();i++){
        // Logic here is, agar curr num jo hai, voh ans ke last se bada hai, toh usse daal do ans mein
        // Agar nahi hai, matlab usse just bada number exist karta hai
        // toh, uss just bade ka index find out kar ke de do aur uss element ko nums[i] se replace kar do
        // In this way, ek sorted array banti rahegi which will be of the size of longest increasing subsequence
        if(ans.back()<nums[i]){
            ans.push_back(nums[i]);
        }
        else{
            int index = lower_bound(ans.begin(),ans.end(),nums[i]) - ans.begin();// Yeh nums[i] se just bada number de dega. Yeh ideally humme nums[i] ke first occurence dene ki koshish karega, jab nahi milega toh usse just bade number ki first occurence de dega apne aap 
            ans[index] = nums[i];
        }
    }

    return ans.size();
}

int lengthOfLIS(vector<int>& nums) {
    int curr = 0;
    int prev = -1; // Here, prev is an imaginary number to start the series. -1 means no number isse phele
    vector<vector<int>> dp(nums.size()+1,vector<int>(nums.size()+1,-1)); // Note here, prev column is imaginary col hence we will operate on prev + 1
    // return solveUsingRecursion(nums,curr,prev);
    // return solveUsingMem(nums,curr,prev,dp);
    // return solveUsingTab(nums);
    // return solveUsingSO1(nums);
    return solveUsingBinarySearch(nums);
}

// Q2. Maximum heights by stacking cuboids - (LC-1691)
bool check(vector<int> &curr,vector<int> &prev){ // Will give if current cuboid can be kept on next cuboid
    // Yaha, as per the loops in SO1, curr means bada walla dabba
    // Prev means chota walla dabba
    // So, boolean comparision will be chota < bada. V.V.V.V IMP STEP
    if(prev[0]<=curr[0] && prev[1]<=curr[1] && prev[2]<=curr[2]){
        return true;
    }
    else{
        return false;
    }

}

int solveUsingSO1(vector<vector<int>>& cuboids){
    // Here, current row is dependent on curr+1 row, so we use two arrays
    vector<int> curr(cuboids.size()+1,0);
    vector<int> next(cuboids.size()+1,0);

    // Iterative Call - Since yaha hum row wise hi traverse kar rahe hai, no need to switch loops
    for(int i=cuboids.size()-1;i>=0;i--){ // Curr went from 0->n, so uska ulta hoga. Plus yaha if we start from n-1, we have already handled curr=n walla case
        for(int j=i-1;j>=-1;j--){ // Prec went from -1->n-1, so uska ulta hoga i.e. curr ke ek peeche se shuru hoga
            int include = 0;
            if(j == -1 || check(cuboids[i],cuboids[j])){ // Means agar prev starting pe hi hai, so naturally we will have to include curr element
                int height = cuboids[i][2]; // Current cuboid (cuboids[i]) ki height
                include = height + next[i+1]; // Include current element and then increase both curr and prev i.e. prev ko agge badhana matlab curr pe lana (prev+1 maat kariyo, it breaks pattern as prev is an imaginary variable). In tabulation, make both of them i+1 as i==current index
            }
            int exclude = 0 + next[j+1]; // Exclude current and then increase curr and prev stays the same i.e. jab include hi nahi kiya so no need to move prev, but since prev will get -1, hence add +1 to it to make all cases valid

            curr[j+1] = max(include,exclude);
        }
        // Update Step
        next = curr;
    }
    
    return next[0];
}

int maxHeight(vector<vector<int>>& cuboids) {
    // Step1.1 -  Phele toh saare cuboids ko by ref sort kar do, we will assume the last of each as it's height
    for(auto &cuboid:cuboids){
        sort(cuboid.begin(),cuboid.end());
    }
    // Step1.2 - Phir purre structure ko hi sort kar do
    sort(cuboids.begin(),cuboids.end());
    int ans = solveUsingSO1(cuboids);

    return ans;
    
}