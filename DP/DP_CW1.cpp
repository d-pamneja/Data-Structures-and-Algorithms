#include <iostream>
#include <vector>
using namespace std;

// Q1. Fibonacci Number - Leetcode(509)
int solveUsingMemoisation(int n,vector<int> &sols){ // Takes more space as compared to Tabulation, as it sends function call for each n
    // Top Down Approach {Recursion + Memoisation}

    // Base Case
    if(n==0 || n==1){
        return n;
    }
    // If answer already exists, do not calculate
    if(sols[n]!= -1){
        return sols[n];
    }

    // Store ans in DP Array
    sols[n] = solveUsingMemoisation(n-1,sols) + solveUsingMemoisation(n-2,sols);

    // Recursive Call
    return sols[n];
}

int solveUsingTabulation(int n, vector<int> &sols2){ // Takes less space as compared to Memoisation, as it fills the entire DP array iteratively
    // Bottom Up Approach {Iteration + Tabulation}

    for(int i=2;i<(n+1);i++){ // Here, fill the entire solution array till n iteratively
        sols2[i] = sols2[i-1] + sols2[i-2];
    }

    // Recursive Call
    return sols2[n];
}

int solveUsingPattern(int n){
    // Pattern Apporach {Iteration + Space Optimisation}
    if(n==0) return 0;
    if(n==1) return 1;
    int prev = 0;
    int curr = 1;
    int ans;

    for(int i=2;i<(n+1);i++){ // Here, fill keep on 
        ans = curr + prev;
        prev = curr;
        curr = ans;
    }
    return ans;
}

int fib(int n) { // TC: O(n), SC: O(n)
    // 1. Create a DP array to store solutions
    // vector<int> sols(n+1,-1); // Will have max n+1 answers

    vector<int> sols2(n+1,-1); // Will have max n+1 answers
    // Now for bottom up, fill the base cases manually
    // Base Case
    if(n==0 || n==1){
        return n;
    }
    sols2[0] = 0;
    sols2[1] = 1;

    //return solveUsingMemoisation(n,sols); // Top Down
    // return solveUsingTabulation(n,sols2); // Bottom Up
    return solveUsingPattern(n);
}

// Q2. Maximise the Cut Segments - GFG
int solver(int n, int x, int y, int z,vector<int> &dp){ // Using Recursion + Memoisation
    if(n==0) return 0;
    if(n<0) return INT_MIN; // IMP Condition, Mein yeh bhul jata hoon
    
    if(dp[n]!=INT_MIN){
        return dp[n];
    }
    
    int opt1 = 1+ solver(n-x,x,y,z,dp);
    int opt2 = 1+ solver(n-y,x,y,z,dp);
    int opt3 = 1+ solver(n-z,x,y,z,dp);
    
    dp[n] = max(opt1,max(opt2,opt3));
    return dp[n];
}

int maximizeTheCuts(int n, int x, int y, int z){
    vector<int> dp(n+1,INT_MIN);
    int ans = solver(n,x,y,z,dp);
    if(ans<0) return 0; // IMP Condition, Mein yeh bhul jata hoon
    return ans;
}