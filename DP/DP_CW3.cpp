#include <iostream>
#include <vector>
using namespace std;

// Q1. Paint Fence - GFG
    
long long solveUsingRec(int n, int k){ // TC: O(2^n), SC: O(n)
    // Base Case 
    if(n==1) return k;
    if(n==2){
        return (k + k*(k-1));
    }
        
    long long N1 = countWays(n-1,k);
    long long N2 = countWays(n-2,k);
    
    return (k-1)*(N1+N2);
}

long long solveUsingMem(int n,int k,vector<long long>& dp){ // TC: O(n), SC: O(n)
    // Base Case 
    long long mod=1000000007;
    if(n==1) return k;
    if(n==2){
        return (k + k*(k-1));
    }
    
    if(dp[n]!=-1){
        return dp[n];
    }
        
    // Recursive Call
    long long N1 = (solveUsingMem(n-1,k,dp)*(k-1))%mod;
    long long N2 = (solveUsingMem(n-2,k,dp)*(k-1))%mod;
    
    dp[n] = (N1+N2)%mod;
    
    return dp[n];
}

long long solveUsingTab(int n,int k){ // TC: O(n), SC: O(n)
    vector<long long> dp(n+1,-1);
    long long mod=1000000007;
    dp[1] = k;
    dp[2] = (k + k*(k-1));

    for(int i=3;i<=n;i++){
        dp[i] = ((k-1)*(dp[i-1] + dp[i-2]))%mod;
    }
    
    return dp[n];
}

long long solveUsingPat(int n,int k){ // TC: O(n), SC: O(1)
    long long mod=1000000007;
    long long prev1 = k;
    long long prev2 = (k + k*(k-1));
    long long curr = 0;

    if(n<2){
      return prev1;
    }

    for(int i=3;i<=n;i++){
        curr = ((k-1)*(prev1 + prev2))%mod;
        prev1 = prev2;
        prev2 = curr;
    }
    
    return prev2; // This covers both normal case and n==2 case
}

long long countWays(int n, int k){
    vector<long long> dp(n+1,-1);
    // return solveUsingMem(n,k,dp);
    //return solveUsingTab(n,k);
    return solveUsingPat(n,k);
    
}

// Q2. 0/1 Knapsack - GFG - V.V.V.V.V.V.V.V.V.IMP {Prime Concept of 2D-Dynamic Programming}
// TC: O(2^n), SC: O(n)
int solveUsingRec(int W, int wt[], int val[], int n,int index){
    // Base Case
    if(index>=n){ // If index is bahar than range, means no possible solution
        return 0;
    }
    
    // Processing + Recursive Call
    
    int include = 0;
    if(wt[index]<=W){ // Include only if weight is allowed
        int currWeight = wt[index];
        include = val[index] + solveUsingRec(W-currWeight,wt,val,n,index+1);
    }
    
    int exclude = 0 + solveUsingRec(W,wt,val,n,index+1);
    
    return max(include,exclude);
}

// TC: O(n*W), SC: O(n*W)
int solveUsingMem(int W, int wt[], int val[], int n,int index,vector<vector<int>> &dp){
    // Base Case
    if(index>=n){ // If index is bahar than range, means no possible solution
        return 0;
    }
    
    // Check if already exists in dp, so return
    if(dp[W][index]!=-1){
        return dp[W][index];
    }
    
    // Processing + Recursive Call
    
    int include = 0;
    if(wt[index]<=W){ // Include only if weight is allowed
        int currWeight = wt[index];
        include = val[index] + solveUsingMem(W-currWeight,wt,val,n,index+1,dp);
    }
    
    int exclude = 0 + solveUsingMem(W,wt,val,n,index+1,dp);
    
    dp[W][index] = max(include,exclude); // Store answer for that particular weight at that given index i.e. kisi given capacity pe agar yeh index ho, toh max value kya hogi
    
    return dp[W][index];
}

// TC: O(n*W), SC: O(n*W)
int solveUsingTab(int W, int wt[], int val[], int n){ 
    vector<vector<int>> dp(W+1,vector<int>(n+1,-1)); // This means 2D vector with capacity rows and (n+1) columns, initialised with -1
    int index = 0;
    
    for(int row=0;row<dp.size();row++){ // Handle the base case that all weights at nth index will be 0, as no operation is possible on index>=n
        dp[row][n] = 0; 
    }
    
    // Jis bhi direction mein variable move kar raha hai, uski opposite direction mein loop move karega to fill 2D Array. Also since return is fixed as per rules, modify the loops
    for(int i=0;i<=W;i++){ // First loop for weight moving 0->capacity, hence loop will move ulta i.e. from 0 to capacity
        for(int j=n-1;j>=0;j--){ // Second loop for index moving (total number of elements - 1)->0, hence loop will move ulta i.e. from total elements to 0
            int include = 0;
            if(wt[j]<=i){ // Include only if weight is allowed
                int currWeight = wt[j];
                include = val[j] + dp[i-currWeight][j+1];
            }
            
            int exclude = 0 + dp[i][j+1];
            
            dp[i][j] = max(include,exclude); // Store answer for that particular weight at that given index i.e. kisi given capacity pe agar yeh index ho, toh max value kya hogi
        }
    }

    return dp[W][0]; // Always return jo recursion mein bheja hota hai. yeh fixed rule hai do not change this
}

// TC: O(n*W), SC: O(W)
int solveUsingPatSO1(int W, int wt[], int val[], int n){ // V.V.V.V. IMP Case, yaha 2D array ki jagah 1D array use hua hai aur loop ulta chala hai
    // In this pattern, we will build the ans from last col first row -> lat row first col
    vector<int> next(W+1,0); // Represent Weight vector
    vector<int> curr(W+1,-1); // Represent Index vector

    // Jis bhi direction mein variable move kar raha hai, uski opposite direction mein loop move karega to fill 2D Array. Also since return is fixed as per rules, modify the loops
    for(int j=n-1; j>=0; j--){ // First loop for index moving (total number of elements - 1)->0, hence loop will move ulta i.e. from total elements to 0
        for(int i=0; i<=W; i++){ // Second loop for weight moving 0->capacity, hence loop will move ulta i.e. from 0 to capacity
            int include = 0;
            if(wt[j]<=i){ // Include only if weight is allowed
                int currWeight = wt[j];
                include = val[j] + next[i-currWeight]; // this moves modified weight to next column i.e. yaha (j+1) ka matlab {next} array se tha
            }
            
            int exclude = 0 + next[i]; // this moves the weight to next column i.e. yaha (j+1) ka matlab {next} array se tha
            
            curr[i] = max(include,exclude); // Store answer for that particular weight at current index (represneted by current vector) i.e. kisi given capacity pe agar yeh index ho, toh max value kya hogi matlab yaha pehle (j) tha, which implied curr array 
            
            // Shift the arrays : V.V.IMP STEP
        }
        next = curr; // Matlab abh, current array ka answer build ho gaya hai, so shift next to current array which will then help to build ans for peeche ke array   
    }

    return curr[W]; // Always return jo recursion mein bheja hota hai. yeh fixed rule hai do not change this. Yaha curr will automatically be moved to the 0th column 
}

// TC: O(n*W), SC: O(W)
int solveUsingPatSO2(int W, int wt[], int val[], int n){ // V.V.V.V. IMP Case // Yaha 1D array use hua hai aur loop ulta chala hai, dhyana se dekho aur dry run karo
    // In this pattern, we will build the ans from last col last row -> first col last row i.e. answer next[W] pe banega
    vector<int> next(W+1,0); // Represent Single vector, with answer building from last row of each col to it's top

    // Yaha loops ulte hongay, dry run and see
    for(int j=n-1;j>=0;j--){ 
        for(int i=W; i>=0; i--){ 
            int include = 0;
            if(wt[j]<=i){ // Include only if weight is allowed
                int currWeight = wt[j];
                include = val[j] + next[i-currWeight]; // this moves modified weight to next column i.e. yaha (j+1) ka matlab {next} array se tha
            }
            
            int exclude = 0 + next[i]; // this moves the weight to next column i.e. yaha (j+1) ka matlab {next} array se tha
            
            next[i] = max(include,exclude); // Store answer for that particular weight at current index 
        }
    }

    return next[W]; // Always return jo recursion mein bheja hota hai. yeh fixed rule hai do not change this. Yaha curr will automatically be moved to the 0th column 
}

//Function to return max value that can be put in knapsack of capacity W.
int knapSack(int W, int wt[], int val[], int n) { 
    vector<vector<int>> dp(W+1,vector<int>(n+1,-1)); // This means 2D vector with capacity rows and (n+1) columns, initialised with -1
    int index = 0;
    
    // int ansRec = solveUsingRec(W,wt,val,n,index);
    // int ansMem = solveUsingMem(W,wt,val,n,index,dp);
    //int ansTab = solveUsingTab(W,wt,val,n);
    // int ansSO1 = solveUsingPatSO1(W,wt,val,n); // 2 points here : 1) Loop ki direction check karo, mistake yaha ho sakti hai 2) Shifting mein dhyaan rakho
    int ansSO2 = solveUsingPatSO2(W,wt,val,n); // Imp point here : 1) Loop ki direction check karo, mistake yaha ho sakti hai
    
    return ansSO2;
}