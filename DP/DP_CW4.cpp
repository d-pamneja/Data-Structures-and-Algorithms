#include <iostream>
#include <vector>
using namespace std;

// Longest common subsequence pattern

// Q1. Longest common subsequence - (LC-1143)
int solveUsingRecursion(string a, string b, int i, int j){ // TC: O(2^n), SC: O(n)
    // Base Case
    if(i>=a.length()){
        return 0;
    }
    if(j>=b.length()){
        return 0;
    }

    // Recursive Call
    int ans = 0;
    if(a[i]==b[j]){
        ans = 1 + solveUsingRecursion(a,b,i+1,j+1); // Answer match kar gaye hai, toh dono ek ek index agge badh jao
    }
    else{
        int caseA = solveUsingRecursion(a,b,i+1,j); // Pheli string mein aage badh ke check kar lo
        int caseB = solveUsingRecursion(a,b,i,j+1); // Doosri string mein aage badh ke check kar lo

        ans = 0 + max(caseA,caseB); // Take max of both
    }

    return ans;
}

// Pass both strings by reference to avoid TLE and use 2D vector to store the answer
int solveUsingMem(string &a, string &b, int i, int j,vector<vector<int>> &dp){ // TC: O(n^2), SC: O(n^2)
    // Base Case
    if(i>=a.length()){
        return 0;
    }
    if(j>=b.length()){
        return 0;
    }

    // Check if answer existing
    if(dp[i][j]!=-1){
        return dp[i][j];
    }

    // Recursive Call
    int ans = 0;
    if(a[i]==b[j]){
        ans = 1 + solveUsingMem(a,b,i+1,j+1,dp); // Answer match kar gaye hai, toh dono ek ek index agge badh jao
    }
    else{
        int caseA = solveUsingMem(a,b,i+1,j,dp); // Pheli string mein aage badh ke check kar lo
        int caseB = solveUsingMem(a,b,i,j+1,dp); // Doosri string mein aage badh ke check kar lo

        ans = 0 + max(caseA,caseB); // Take max of both
    }

    dp[i][j] = ans; // Store in 2D array
    return dp[i][j];
}

// Pass both strings by reference to avoid TLE. Tabulation using 2D Vector
int solveUsingTab1(string &a, string &b){  // TC: O(n^2), SC: O(n^2)
    vector<vector<int>> dp(a.length()+1,vector<int>(b.length()+1,0));

    // Iterative Call
    for(int i=a.length()-1;i>=0;i--){
        for(int j=b.length()-1;j>=0;j--){
            int ans = 0;
            if(a[i]==b[j]){
                ans = 1 + dp[i+1][j+1]; // Answer match kar gaye hai, toh dono ek ek index agge badh jao yaani move to both next row and next col
            }
            else{
                int caseA = dp[i+1][j]; // Pheli string mein aage badh ke check kar lo yaani move to next row
                int caseB = dp[i][j+1]; // Doosri string mein aage badh ke check kar lo yaani move to next col

                ans = 0 + max(caseA,caseB); // Take max of both
            }
            dp[i][j] = ans; // Store in 2D array
        }
    }
    
    return dp[0][0];
}

// Pass both strings by reference to avoid TLE. Tabulation using two 1D Vector
int solveUsingTab2LoopChange(string &a, string &b){  // TC: O(n^2), SC: O(n)
    // here, the current cell's answer is dependent on it's current column and next column. Hence, create vectors of a length as we will go colummn wise i.e. column wise move karne ki liye rows ka patta hona zaroori hai, and earlier we made rows via a.length()
    vector<int> curr(a.length()+1,0); // To track current column
    vector<int> next(a.length()+1,0); // To track next column

    // Iterative Call for two vectors. yaha, switch the loops as earlier we ere going row wise but now we are going col wise
    for(int j=b.length()-1;j>=0;j--){
        for(int i=a.length()-1;i>=0;i--){
            int ans = 0;
            if(a[i]==b[j]){
                ans = 1 + next[i+1]; // (j+1) matlab next walla column, so move to it
            }
            else{
                int caseA = curr[i+1]; // (i+1) matlab next col, so move to it
                int caseB = next[i]; // (j+1) matlab next col, so move to it

                ans = 0 + max(caseA,caseB); // Take max of both
            }
            curr[i] = ans; // Store in current column
        }
        // Update steps - V.V.V. IMP. Always update after first loop is run successfully
        next = curr;
    }
    
    return next[0];
}

// Pass both strings by reference to avoid TLE. Tabulation using two 1D Vector
int solveUsingTab2NoLoopChange(string &a, string &b){ 
    // here, the current cell's answer is dependent on it's current row and next row. Hence, create vectors of a length as we will go row wise i.e. row wise move karne ki liye cols ka patta hona zaroori hai, and earlier we made cols via b.length()
    vector<int> curr(b.length()+1,0); // To track current column
    vector<int> next(b.length()+1,0); // To track next column

    // Iterative Call for two vectors. yaha, DO NOT switch the loops as earlier we are going row wise only
    for(int i=a.length()-1;i>=0;i--){
        for(int j=b.length()-1;j>=0;j--){
            int ans = 0;
            if(a[i]==b[j]){
                ans = 1 + next[j+1]; // (j+1) matlab next walla column, so move to it. Modify via jth index as loop not switched
            }
            else{
                int caseA = curr[j+1]; // (i+1) matlab next col, so move to it Modify via jth index as loop not switched
                int caseB = next[j]; // (j+1) matlab next col, so move to it Modify via jth index as loop not switched

                ans = 0 + max(caseA,caseB); // Take max of both
            }
            curr[j] = ans; // Store in current column Modify via jth index as loop not switched
        }
        // Update steps - V.V.V. IMP. Always update after first loop is run successfully
        next = curr;
    }
    
    return next[0];
}



int longestCommonSubsequence(string text1, string text2) {
    // int i = 0;
    // int j = 0;
    // vector<vector<int>> dp(text1.length()+1,vector<int>(text2.length()+1,-1));
    // return solveUsingMem(text1,text2,i,j,dp);
    // return solveUsingTab1(text1,text2);
    return solveUsingTab2LoopChange(text1,text2);

}

// Q2. Longest Palindromic Subsequence - (LC-516)
// based on LC-1143 i.e. Longest Common Subsequence
int longestPalindromeSubseq(string s) {
    string s1 = s;
    reverse(s1.begin(),s1.end());

    return longestCommonSubsequence(s,s1);
}

// Q3. Edit Distance - (LC-72) V.V.V.V.V.V.V.V IMP
int solveUsingRecursionED(string &a,string &b,int i,int j){
    // Base Case
    // Agar koi bhi moving index apni range se bahar chala gaya, total more operation needed are doosri string ke remaining
    if(i>=a.length()){
        return b.length() - j;
    }
    if(j>=b.length()){
        return a.length() - i;
    }

    // Recursive Call
    int ans = 0;
    if(a[i]==b[j]){ // Agar match kar jaye, dono agge badh lo
        ans = 0 + solveUsingRecursionED(a,b,i+1,j+1);
    }
    else{
        int caseInsert = 1 + solveUsingRecursionED(a,b,i,j+1);
        int caseReplace = 1 + solveUsingRecursionED(a,b,i+1,j+1);
        int caseDelete = 1 + solveUsingRecursionED(a,b,i+1,j);

        ans = min(caseInsert,min(caseReplace,caseDelete));
    }
    return ans;
}

int solveUsingMemED(string &a,string &b,int i,int j,vector<vector<int>> &dp){
    // Base Case
    // Agar koi bhi moving index apni range se bahar chala gaya, total more operation needed are doosri string ke remaining
    if(i>=a.length()){
        return b.length() - j;
    }
    if(j>=b.length()){
        return a.length() - i;
    }

    // Check if already exists
    if(dp[i][j]!=-1){
        return dp[i][j];
    }

    // Recursive Call
    int ans = 0;
    if(a[i]==b[j]){ // Agar match kar jaye, dono agge badh lo
        ans = 0 + solveUsingMemED(a,b,i+1,j+1,dp);
    }
    else{
        int caseInsert = 1 + solveUsingMemED(a,b,i,j+1,dp);
        int caseReplace = 1 + solveUsingMemED(a,b,i+1,j+1,dp);
        int caseDelete = 1 + solveUsingMemED(a,b,i+1,j,dp);

        ans = min(caseInsert,min(caseReplace,caseDelete));
    }
    dp[i][j] = ans;
    return dp[i][j];
}

int solveUsingTab1ED(string &a,string &b){
    vector<vector<int>> dp(a.length()+1,vector<int>(b.length()+1,0));

    for(int row = 0;row<=a.length();row++){ // Last column ki saari rows pe {a.length() - current row} bhar do
        dp[row][b.length()] = a.length() - row;
    }

    for(int col = 0;col<=b.length();col++){ // Last row ki saari cols pe {b.length() - current col} bhar do
        dp[a.length()][col] = b.length() - col;
    }

    for(int i=a.length()-1;i>=0;i--){
        for(int j=b.length()-1;j>=0;j--){
            int ans = 0;
            if(a[i]==b[j]){ // Agar match kar jaye, dono agge badh lo
                ans = 0 + dp[i+1][j+1]; // Move to next row next column
            }
            else{
                int caseInsert = 1 + dp[i][j+1]; // Move to next column same row
                int caseReplace = 1 + dp[i+1][j+1]; // Move to next row next column
                int caseDelete = 1 + dp[i+1][j]; // Move to next row same column

                ans = min(caseInsert,min(caseReplace,caseDelete));
            }
            dp[i][j] = ans;
        }
    }

    return dp[0][0];
}

int solveUsingTab2ED(string &a,string &b){
    vector<int> curr(a.length()+1,0); // To track current column
    vector<int> next(a.length()+1,0); // To track next

    for(int row = 0;row<=a.length();row++){ // Last column ki saari rows pe {a.length() - current row} bhar do
        next[row]  = a.length() - row;
    }

    // Handle the last row second last column case - V.IMP else pattern will break
    // Yaha par matlab current column ke last row ke cell pe {b.length() - current col} le aa kaam done

    for(int j=b.length()-1;j>=0;j--){
        // yaha se naya column shuru hota hai, jiske last mein mujhe {b.length() - current col} daalna hai
        curr[a.length()] = b.length() - j; // V.V.V.V.V.V.V.V IMP - Base Case Handling
        for(int i=a.length()-1;i>=0;i--){
            int ans = 0;
            if(a[i]==b[j]){ // Agar match kar jaye, dono agge badh lo
                ans = 0 + next[i+1]; // (i+1) and (j+1) matlab next column, so move next ka agge, cause col moving to next
            }
            else{
                int caseInsert = 1 + next[i]; // // (j+1) matlab next column, so move next ka agge, cause col moving to next
                int caseReplace = 1 + next[i+1]; // (i+1) and (j+1) matlab next column, so move next ka agge cause col moving to next
                int caseDelete = 1 + curr[i+1]; // // (j) matlab same column, so move curr ka agge, cause col staying at same

                ans = min(caseInsert,min(caseReplace,caseDelete));
            }
            curr[i] = ans; // Place answer in curr same row i.e. curr[i]
        }
        // UPDATE : V.V.V.IMP (after first loop ends)
        next = curr;
    }

    return next[0];
}

int minDistance(string word1, string word2) {
    // int i = 0;
    // int j = 0;
    // vector<vector<int>> dp(word1.length()+1,vector<int>(word2.length()+1,-1));
    // return solveUsingMemED(word1,word2,i,j,dp);
    // return solveUsingTab1ED(word1,word2);
    return solveUsingTab2ED(word1,word2);
}
