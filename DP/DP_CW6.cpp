#include <iostream>
#include <vector>
#include <map>
using namespace std;

// Merge Intervals Pattern

// Q1. Guess Number Higher or Lower II - (LC-375) - V.V.V.V.V IMP
int solveUsingRecursion(int start,int end){
    // Base Case
    if(start > end){ // Matlab range se bahar challe gaye, toh penalty nahi hogi kuch
        return 0;
    }
    if(start == end){ // Matlab answer pe hi ho, toh no penalty
        return 0;
    }

    // Recursive Call
    int ans = INT_MAX;
    for(int i=start;i<=end;i++){ // 1->n se haar element pe ans nikalo, aur usme se max choose karo and sabka min choose karo
        int curr = i; // Means penalty i khud hai
        int left = solveUsingRecursion(start,i-1); // Means answer ith term ke left mein hai
        int right = solveUsingRecursion(i+1,end); // Means answer ith term ke right mein hai

        ans = min(ans, curr + max(left,right)); // Basically, this chooses the min amount needed to win if you are currently standing on ith term (matlab i ki penalty toh bharogay + left aur right se kitni chahiye win secure karne ke liye). Hence yaha min(ans,max(strategies)) lag raha hai
    }

    return ans;
}

int solveUsingMem(int start,int end,vector<vector<int>> &dp){
    // Base Case
    if(start > end){ // Matlab range se bahar challe gaye, toh penalty nahi hogi kuch
        return 0;
    }
    if(start == end){ // Matlab answer pe hi ho, toh no penalty
        return 0;
    }

    if(dp[start][end]!=-1){
        return dp[start][end];
    }

    // Recursive Call
    int ans = INT_MAX;
    for(int i=start;i<=end;i++){ // 1->n se haar element pe ans nikalo, aur usme se max choose karo and sabka min choose karo. 
        int curr = i; // Means penalty i khud hai
        int left = solveUsingMem(start,i-1,dp); // Means answer ith term ke left mein hai
        int right = solveUsingMem(i+1,end,dp); // Means answer ith term ke right mein hai

        ans = min(ans, curr + max(left,right)); // Basically, this chooses the min amount needed to win if you are currently standing on ith term (matlab i ki penalty toh bharogay + left aur right se kitni chahiye win secure karne ke liye). Hence yaha min(ans,max(strategies)) lag raha hai
    }
    dp[start][end] = ans;
    return dp[start][end];
}

int solveUsingTab(int start,int end,int n){
    vector<vector<int>> dp(n+2,vector<int>(n+2,0)); 

    // Iterative Call
    for(int start_index=n-1;start_index>=1;start_index--){ // start goes from 1->n, so yaha ulta
        for(int end_index=1;end_index<=n;end_index++){ // start goes from n->1, so yaha ulta
            // Base Case Handling
            if(start_index>end_index){
                // Invalid range, so continue/skip
                continue;
            }
            if(start_index==end_index){ // Means 0 hai ans, jo already stored hai, so skip
                continue;
            }
            int ans = INT_MAX;
            for(int i=start_index;i<=end_index;i++){ // 1->n se haar element pe ans nikalo, aur usme se max choose karo and sabka min choose karo. 
                int curr = i; // Means penalty i khud hai
                int left = dp[start_index][i-1]; // Means answer ith term ke left mein hai
                int right = dp[i+1][end_index]; // Means answer ith term ke right mein hai

                ans = min(ans, curr + max(left,right)); // Basically, this chooses the min amount needed to win if you are currently standing on ith term (matlab i ki penalty toh bharogay + left aur right se kitni chahiye win secure karne ke liye). Hence yaha min(ans,max(strategies)) lag raha hai
            }
            dp[start_index][end_index] = ans;
        }
    }
    return dp[1][n];
}


int getMoneyAmount(int n) {
    int start = 1;
    int end = n;
    // vector<vector<int>> dp(n+1,vector<int>(n+1,-1));
    // return solveUsingRecursion(start,end);
    // return solveUsingMem(start,end,dp);
    return solveUsingTab(start,end,n);
}

// Q2. Minimum Cost Tree From Leaf Values - (LC-1130) - V.V.V.V.V IMP
// Here, we will have to PRE COMPUTE all the maximum for all ranges from 1->n and then use that to calculate the answer
int solveUsingRecursion(vector<int>& arr,map<pair<int,int>,int> &maxi,int start,int end){
    // Base Case
    if(start>end){ // matlab out of range
        return 0; 
    }
    if(start==end){ // matlab khud leaf node hai, so do not add in sum of non lead nodes
        return 0;
    }

    // Recursive Call
    int ans = INT_MAX;
    for(int i=start;i<end;i++){ // i is used here for partitioning
        int left = solveUsingRecursion(arr,maxi,start,i); // (i-1) se isliye nahi kiya cause i (curr element) ko bhi tree mein dalne ka hai
        int right = solveUsingRecursion(arr,maxi,i+1,end);
        // current node pe partition kari, matlab baaki uske leaf nodes ke multiplication ko current answer mein add karne ka + left ke answers + right ke answers 
        int leafNodesKiMultiplication = maxi[{start,i}] * maxi[{i+1,end}];

        ans = min(ans,leafNodesKiMultiplication + left + right); 
    }

    return ans;
}

int solveUsingMem(vector<int>& arr,map<pair<int,int>,int> &maxi,int start,int end,vector<vector<int>> &dp){
    // Base Case
    if(start>end){ // matlab out of range
        return 0; 
    }
    if(start==end){ // matlab khud leaf node hai, so do not add in sum of non lead nodes
        return 0;
    }

    // Check in array
    if(dp[start][end]!=-1){
        return dp[start][end];
    }

    // Recursive Call
    int ans = INT_MAX;
    for(int i=start;i<end;i++){ // i is used here for partitioning
        int left = solveUsingMem(arr,maxi,start,i,dp); // (i-1) se isliye nahi kiya cause i (curr element) ko bhi tree mein dalne ka hai
        int right = solveUsingMem(arr,maxi,i+1,end,dp);
        // current node pe partition kari, matlab baaki uske leaf nodes ke multiplication ko current answer mein add karne ka + left ke answers + right ke answers 
        int leafNodesKiMultiplication = maxi[{start,i}] * maxi[{i+1,end}];

        ans = min(ans,leafNodesKiMultiplication + left + right); 
    }

    // Store in array
    dp[start][end] = ans;

    return dp[start][end];
}

int solveUsingTab(vector<int>& arr,map<pair<int,int>,int> &maxi,int start,int end,int n){
    vector<vector<int>> dp(n+2,vector<int>(n+2,0));

    // Iterative Call
    for(int start_index = n;start_index>=0;start_index--){
        for(int end_index=0;end_index<=n;end_index++){
            if(start_index>=end_index){ // Invalid or lead node case, so continue/skip
                continue;
            }
            int ans = INT_MAX;
            for(int i=start_index;i<end_index;i++){ // i is used here for partitioning
                int left = dp[start_index][i]; // (i-1) se isliye nahi kiya cause i (curr element) ko bhi tree mein dalne ka hai
                int right = dp[i+1][end_index];
                // current node pe partition kari, matlab baaki uske leaf nodes ke multiplication ko current answer mein add karne ka + left ke answers + right ke answers 
                int leafNodesKiMultiplication = maxi[{start_index,i}] * maxi[{i+1,end_index}];

                ans = min(ans,leafNodesKiMultiplication + left + right); 
            }
            // Store ans - V.V.V IMP
            dp[start_index][end_index] = ans;
        }
    }

    return dp[0][n-1];
}

int mctFromLeafValues(vector<int>& arr) {
    // PreComputation
    map<pair<int,int>,int> maxi; // for index {i,j} the maximum value
    for(int i=0;i<arr.size();i++){
        maxi[{i,i}] = arr[i]; // Khud se khud tak ka max curr element hi hoga
        for(int j=i+1;j<arr.size();j++){
            maxi[{i,j}] = max(arr[j],maxi[{i,j-1}]); // i se j ka max will be curr jth element and i se lekar (j-1) ke dono ka max
        }
    }

    int n = arr.size();
    int start = 0;
    int end = n-1;

    vector<vector<int>> dp(n+1,vector<int>(n+1,-1));

    // return solveUsingRecursion(arr,maxi,start,end);
    // return solveUsingMem(arr,maxi,start,end,dp);
    return solveUsingTab(arr,maxi,start,end,n);


}