#include <iostream>
#include <vector>
#include <map>
using namespace std;



struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};


// Q1. Longest Palindromic SubString - (LC-5) - V.V.V.V.V IMP
int maxLen = 1; // kisi palindrome ki min length ek toh hogi hai
int palindrome_start_index = 0; // to get the position jaha se max palindrome shuru hota hai
bool solveUsingRecursion(string s,int start,int end){
    if(start>=end){ // Matlab sabh kuch check kar liya hai ya single element pe ho, both true palindromes
        return true;
    }

    // Recursive Call
    bool flag = false;
    if(s[start]==s[end]){
        flag = solveUsingRecursion(s,start+1,end-1);
    }

    if(flag){ // agar toh string palindrome hai, toh uski length store karke max se compare karo
        int currLen = end - start + 1;
        if(currLen>maxLen){
            maxLen = currLen; // this will store the length of max Palindrome
            palindrome_start_index = start; // this will tell string kaha se shuru ho rahi thi
        }
    }

    return flag; 
}

bool solveUsingMem(string s,int start,int end,vector<vector<int>> &dp){
    if(start>=end){ // Matlab sabh kuch check kar liya hai ya single element pe ho, both true palindromes
        return true;
    }

    // Check if it is already in the array
    if(dp[start][end]!=-1){
        return dp[start][end];
    }

    // Recursive Call
    bool flag = false;
    if(s[start]==s[end]){
        flag = solveUsingMem(s,start+1,end-1,dp);
    }

    if(flag){ // agar toh string palindrome hai, toh uski length store karke max se compare karo
        int currLen = end - start + 1;
        if(currLen>maxLen){
            maxLen = currLen; // this will store the length of max Palindrome
            palindrome_start_index = start; // this will tell string kaha se shuru ho rahi thi
        }
    }

    return dp[start][end]=flag; 
}

// TAB SOLUTION - PUT IT HERE


string longestPalindrome(string s) { // MLE - Memory Limit Exceeded de raha hai
    int n = s.size();

    vector<vector<int>> dp(n+1,vector<int>(n+1,-1));
    for(int i=0;i<n;i++){
        for(int j=i;j<n;j++){
            // bool isPalindrome = solveUsingRecursion(s,i,j);
            bool isPalindrome = solveUsingMem(s,i,j,dp);
        }
    }

    return s.substr(palindrome_start_index,maxLen);
}

// Q2. Word Break - (LC-139) - V.V.V.V.V IMP
bool checkValid(vector<string>& wordDict, string &word){
    for(auto i:wordDict){
        if(word==i){
            return true;
        }
    }
    return false;
}

bool solveUsingRecursion(string s, vector<string>& wordDict, int start){
    // Base Case
    if(start==s.size()){ // Matlab saari string traverse ho gayi hai, so true
        return true;
    }

    string word = "";
    bool flag = false;
    for(int i=start;i<s.size();++i){
        word += s[i];
        if(checkValid(wordDict,word)){ // If created word is in dictionary, then check if agge ka is a valid ans
            flag = flag || solveUsingRecursion(s,wordDict,i+1); // || lagane se word banke loop chalta rehta hai, jisse saare combinations test ho jate hai, aur kisi ek ka bhi true hai toh total ans is true
        }
    }
    return flag;
}

bool solveUsingMem(string s, vector<string>& wordDict, int start,vector<int> &dp){
    // Base Case
    if(start==s.size()){ // Matlab saari string traverse ho gayi hai, so true
        return true;
    }

    if(dp[start]!=-1){
        return dp[start];
    }

    string word = "";
    bool flag = false;
    for(int i=start;i<s.size();++i){
        word += s[i];
        if(checkValid(wordDict,word)){ // If created word is in dictionary, then check if agge ka is a valid ans
            flag = flag || solveUsingMem(s,wordDict,i+1,dp); // || lagane se word banke loop chalta rehta hai, jisse saare combinations test ho jate hai, aur kisi ek ka bhi true hai toh total ans is true
        }
    }

    return dp[start] = flag;
}

bool solveUsingTab(string s, vector<string>& wordDict){
    int n = s.size();
    vector<int> dp(n+1,1);

    for(int start_index = n-1;start_index>=0;start_index--){
        string word = "";
        bool flag = false;
        for(int i=start_index;i<s.size();++i){
            word += s[i];
            if(checkValid(wordDict,word)){ // If created word is in dictionary, then check if agge ka is a valid ans
                flag = flag || dp[i+1]; // || lagane se word banke loop chalta rehta hai, jisse saare combinations test ho jate hai, aur kisi ek ka bhi true hai toh total ans is true
            }
        }
        dp[start_index] = flag;
    }

    

    return dp[0];
}



bool wordBreak(string s, vector<string>& wordDict) {
    // vector<int> dp(s.size(),-1);
    // return solveUsingRecursion(s,wordDict,0);
    // return solveUsingMem(s,wordDict,0,dp);
    return solveUsingTab(s,wordDict);
}

// Q3. Word Break II - (LC-140) - V.V.V.V.V IMP
vector<string> solveUsingRecursion(string &s,unordered_map<string,bool> &dict,int start){
    // Base Case
    if(start>=s.size()){
        return {""}; // If looper agge badh gaya, so empty string
    }

    vector<string> ans;
    string word;

    // Recursive Call
    for(int i = start;i<s.size();i++){
        word.push_back(s[i]);
        if(dict.find(word)==dict.end()){ // Jab tak valid word nahi hai, agge badhte raho
            continue;
        }

        // If here, matlab mil gaya hai valid word, so right ki call laga do
        auto right = solveUsingRecursion(s,dict,i+1); // This will give all possible sentences  at the right of curr word
        for(auto eachRightSentence:right){
            string eachRightPart;
            if(eachRightSentence.size()>0){ // Jab tak sentences hai, space + sentence ko daalte raho. In this case, format ka pattern maintain rahega
                eachRightPart = " " + eachRightSentence;
            }
            ans.push_back(word + eachRightPart);
        }
    }
    return ans;
}

vector<string> solveUsingMem(string &s,unordered_map<string,bool> &dict,int start,unordered_map<int,vector<string>> &dp){
    // Base Case
    if(start>=s.size()){
        return {""}; // If looper agge badh gaya, so empty string
    }

    vector<string> ans;
    string word;

    if(dp.find(start)!=dp.end()){
        return dp[start];
    }

    // Recursive Call
    for(int i = start;i<s.size();i++){
        word.push_back(s[i]);
        if(dict.find(word)==dict.end()){ // Jab tak valid word nahi hai, agge badhte raho
            continue;
        }

        // If here, matlab mil gaya hai valid word, so right ki call laga do
        auto right = solveUsingMem(s,dict,i+1,dp); // This will give all possible sentences  at the right of curr word
        for(auto eachRightSentence:right){
            string eachRightPart;
            if(eachRightSentence.size()>0){ // Jab tak sentences hai, space + sentence ko daalte raho. In this case, format ka pattern maintain rahega
                eachRightPart = " " + eachRightSentence;
            }
            ans.push_back(word + eachRightPart);
        }
    }

    return dp[start]=ans; // Store the possible sentences at any given index
}

vector<string> wordBreak2(string s, vector<string>& wordDict) {
    unordered_map<string,bool> dict;
    for(auto word:wordDict){ // Push all words in map for easy comparision
        dict[word] = 1;
    }

    unordered_map<int,vector<string>> dp;

    // return solveUsingRecursion(s,dict,0);
    return solveUsingMem(s,dict,0,dp);
}

// Q3. Unique BST II - (LC-95) - V.V.V.V.V IMP
vector<TreeNode*> solveUsingRecursion(int start,int end){
    // Base Case
    if(start>end){
        return {0}; // Basically NULL pointer
    }
    if(start==end){
        return {new TreeNode(start)};
    }


    vector<TreeNode*> ans;

    for(int i=start;i<=end;i++){
        // Post Order Traversal (LRN)
        vector<TreeNode*> left = solveUsingRecursion(start,i-1); // all treenodes possible in left of start
        vector<TreeNode*> right = solveUsingRecursion(i+1,end); // all treenodes possible in right of start

        
        for(int j=0;j<left.size();j++){ // Left ke sarre BST ko ek ek karke curr se laga do
            for(int k=0;k<right.size();k++){ // Right ke sarre BST ko ek ek karke curr se laga do
                TreeNode* currNode = new TreeNode(i); // Different cause we will get 4(multiple of 4 basically) unique combinations
                currNode->left = left[j];
                currNode->right = right[k];

                ans.push_back(currNode); 
            }
        }
    }

    return ans;
}

vector<TreeNode*> solveUsingMem(int start,int end,map<pair<int,int>,vector<TreeNode*>> &dp){
    // Base Case
    if(start>end){
        return {0}; // Basically NULL pointer
    }
    if(start==end){
        return {new TreeNode(start)};
    }

    if(dp.find({start,end})!=dp.end()){
        return dp[{start,end}];
    }


    vector<TreeNode*> ans;

    for(int i=start;i<=end;i++){
        // Post Order Traversal (LRN)
        vector<TreeNode*> left = solveUsingMem(start,i-1,dp); // all treenodes possible in left of start
        vector<TreeNode*> right = solveUsingMem(i+1,end,dp); // all treenodes possible in right of start

        
        for(int j=0;j<left.size();j++){ // Left ke sarre BST ko ek ek karke curr se laga do
            for(int k=0;k<right.size();k++){ // Right ke sarre BST ko ek ek karke curr se laga do
                TreeNode* currNode = new TreeNode(i); // Different cause we will get 4(multiple of 4 basically) unique combinations
                currNode->left = left[j];
                currNode->right = right[k];

                ans.push_back(currNode); 
            }
        }
    }

    return dp[{start,end}]=ans;
}


vector<TreeNode*> generateTrees(int n) {
    // return solveUsingRecursion(1,n);
    // vector<vector<vector<TreeNode*>>> dp(n+1,vector<vector<TreeNode*>>(n+1,vector<TreeNode*>(n+1,0)));  // 3D DP
    map<pair<int,int>,vector<TreeNode*>> dp; // {start,end} -> vector<TreeNode*>
    return solveUsingMem(1,n,dp);
}

// Q4. House Robber III - (LC-337) - V.V.V.V.V IMP
int solveUsingRecursion(TreeNode* root){
    // Base Case
    if(!root){
        return 0;
    }

    int RobThisHouse = 0;
    int doNotRobThisHouse = 0;

    // Recursive Call

    // Case A - Include current house
    RobThisHouse += root->val;
    if(root->left){
        // Since we cannot rob directly attached houses, we make left ke {left,right} ke combinations ke call
        RobThisHouse += solveUsingRecursion(root->left->left);
        RobThisHouse += solveUsingRecursion(root->left->right);
    }
    if(root->right){ 
        // Since we cannot rob directly attached houses, we make right ke {left,right} combinations ke call
        RobThisHouse += solveUsingRecursion(root->right->left);
        RobThisHouse += solveUsingRecursion(root->right->right);
    }

    // Case B - Do Not Include Current House
    if(root->left){
        doNotRobThisHouse += solveUsingRecursion(root->left);
    }
    if(root->right){
        doNotRobThisHouse += solveUsingRecursion(root->right);
    }

    return max(RobThisHouse,doNotRobThisHouse);
}

int solveUsingMem(TreeNode* root,unordered_map<TreeNode*,int> &dp){
    // Base Case
    if(!root){
        return 0;
    }

    int RobThisHouse = 0;
    int doNotRobThisHouse = 0;

    // Check
    if(dp.find(root)!=dp.end()){
        return dp[root];
    }

    // Recursive Call

    // Case A - Include current house
    RobThisHouse += root->val;
    if(root->left){
        // Since we cannot rob directly attached houses, we make left ke {left,right} ke combinations ke call
        RobThisHouse += solveUsingMem(root->left->left,dp);
        RobThisHouse += solveUsingMem(root->left->right,dp);
    }
    if(root->right){ 
        // Since we cannot rob directly attached houses, we make right ke {left,right} combinations ke call
        RobThisHouse += solveUsingMem(root->right->left,dp);
        RobThisHouse += solveUsingMem(root->right->right,dp);
    }

    // Case B - Do Not Include Current House
    if(root->left){
        doNotRobThisHouse += solveUsingMem(root->left,dp);
    }
    if(root->right){
        doNotRobThisHouse += solveUsingMem(root->right,dp);
    }

    return dp[root]=max(RobThisHouse,doNotRobThisHouse);
}

int rob(TreeNode* root) {
    unordered_map<TreeNode*,int> dp; // Ek given tree ke liye max possible amount kitna hai i.e. {tree}->amount
    // return solveUsingRecursion(root);
    // TREE MEIN BOTTOM UP KA SENSE NAHI BANTA, CAUSE VOH KHUD EK TOP DOWN STRUCTURE HAI
    return solveUsingMem(root,dp);
}

// Q5. Stone Game - (LC-877) - V.V.V.V.V IMP
bool stoneGame(vector<int>& piles) {
    // If one person plays optimally to maximise her wins, and other plays optimally to minimise his
    // The person who picks the first will always win
    // Hence, as allice picks first, there always exists at least one possibility that she wins
    // The problem asks to return if there exists such a way
    return true;
}

// Q6. Stone Game II - (LC-1140) - V.V.V.V.V IMP
int solveUsingRecursion(vector<int>& piles,int looper,int M,bool isAliceTurn){
    if(looper==piles.size()){
        return 0;
    }

    int ans = isAliceTurn ? INT_MIN : INT_MAX;
    int totalStones = 0;

    for(int X=1;X<=2*M;X++){
        if(looper + X - 1 >= piles.size()){
            break; // Matlab out of bound, so end loop
        }
        totalStones += piles[looper + X - 1]; // jaha par khade ho, waha se M stones utha lo and total mein add kar do
        if(isAliceTurn){
            ans = max(ans,totalStones + solveUsingRecursion(piles,looper + X, max(X,M),!isAliceTurn) ); // Ans of alice so maximise and now, start from current position plus previous start. allice ne X plies uthaye so new pos = start + X se and also set M as max(X,M)
        }
        else{
            ans = min(ans,solveUsingRecursion(piles,looper + X, max(X,M),!isAliceTurn)); // This is the answer of Bob, so we write min in it as question say both will work optimally to maximise allice ke stones, toh kar toh bob bhi max raha hoga, par humme allice ka ans chahiye toh isliye min karegangay
        }

    }

    return ans;
}

int solveUsingMem(vector<int>& piles,int looper,int M,bool isAliceTurn,vector<vector<vector<int>>> &dp){
    if(looper==piles.size()){
        return 0;
    }

    if(dp[looper][M][isAliceTurn]!=-1){
        return dp[looper][M][isAliceTurn];
    }

    int ans = isAliceTurn ? INT_MIN : INT_MAX;
    int totalStones = 0;

    for(int X=1;X<=2*M;X++){
        if(looper + X - 1 >= piles.size()){
            break; // Matlab out of bound, so end loop
        }
        totalStones += piles[looper + X - 1]; // jaha par khade ho, waha se M stones utha lo and total mein add kar do
        if(isAliceTurn){
            ans = max(ans,totalStones + solveUsingMem(piles,looper + X, max(X,M),!isAliceTurn,dp) ); // Ans of alice so maximise and now, start from current position plus previous start. allice ne X plies uthaye so new pos = start + X se and also set M as max(X,M)
        }
        else{
            ans = min(ans,solveUsingMem(piles,looper + X, max(X,M),!isAliceTurn,dp)); // This is the answer of Bob, so we write min in it as question say both will work optimally to maximise allice ke stones, toh kar toh bob bhi max raha hoga, par humme allice ka ans chahiye toh isliye min karegangay
        }

    }

    return dp[looper][M][isAliceTurn]=ans;
}

int solveUsingTab(vector<int>& piles){
    int n = piles.size();
    vector<vector<vector<int>>> dp(n+1,vector<vector<int>>(n+1,vector<int>(2,0)));


    for(int looper = n-1;looper>=0;looper--){
        for(int M = n;M>=1;M--){
            for(int isAliceTurn=0;isAliceTurn<=1;isAliceTurn++){
                int ans = isAliceTurn ? INT_MIN : INT_MAX;
                int totalStones = 0;
                for(int X=1;X<=2*M;X++){
                    if(looper + X - 1 >= piles.size()){
                        break; // Matlab out of bound, so end loop
                    }
                    totalStones += piles[looper + X - 1]; // jaha par khade ho, waha se M stones utha lo and total mein add kar do
                    if(isAliceTurn){
                        ans = max(ans,totalStones + dp[looper + X][max(X,M)][!isAliceTurn] ); // Ans of alice so maximise and now, start from current position plus previous start. allice ne X plies uthaye so new pos = start + X se and also set M as max(X,M)
                    }
                    else{
                        ans = min(ans,dp[looper + X][max(X,M)][!isAliceTurn]); // This is the answer of Bob, so we write min in it as question say both will work optimally to maximise allice ke stones, toh kar toh bob bhi max raha hoga, par humme allice ka ans chahiye toh isliye min karegangay
                    }
                }
                dp[looper][M][isAliceTurn] = ans;
            }
        }
    }

    return dp[0][1][1];
}

int stoneGameII(vector<int>& piles) {
    // int looper = 0;
    // int M = 1;
    // bool isAliceTurn = true;
    // int n = piles.size();
    // vector<vector<vector<int>>> dp(n+1,vector<vector<int>>(n+1,vector<int>(n+1,-1)));
    // return solveUsingRecursion(piles,looper,M,isAliceTurn);
    // return solveUsingMem(piles,looper,M,isAliceTurn,dp);
    return solveUsingTab(piles);
}

// Q7. Stone Game III - (LC-1406) - V.V.V.V.V IMP
int solveUsingRecursion(vector<int>& sv,int start){
    if(start==sv.size()){ // Matlab out of bound ho gaye ho, so no valid ans
        return 0;
    }

    int ans = INT_MIN; // Alice ka ans maximise karna hai
    int total = 0;

    for(int X=1;X<=3;X++){ // Choice can be either 1,2 or 3
        if((start+X - 1)>=sv.size()){
            break;
        }
        total += sv[start + X - 1]; // add current selection to total stones
        ans = max(ans,total -  solveUsingRecursion(sv,start+X)); // Here, logic is {alice ka final ans} =  {Alice ke total till now} - {Recursion ka ans}
    }
    
    return ans;
}

int solveUsingMem(vector<int>& sv,int start,vector<int> &dp){
    if(start==sv.size()){ // Matlab out of bound ho gaye ho, so no valid ans
        return 0;
    }

    if(dp[start]!=-1){
        return dp[start];
    }

    int ans = INT_MIN; // Alice ka ans maximise karna hai
    int total = 0;

    for(int X=1;X<=3;X++){ // Choice can be either 1,2 or 3
        if((start+X - 1)>=sv.size()){
            break;
        }
        total += sv[start + X - 1]; // add current selection to total stones
        ans = max(ans,total -  solveUsingMem(sv,start+X,dp)); // Here, logic is {alice ka final ans} =  {Alice ke total till now} - {Recursion ka ans}
    }
    
    return dp[start]=ans;
}

int solveUsingTab(vector<int>& sv){
    int n = sv.size();
    vector<int> dp(n+1,0);

    for(int start=n-1;start>=0;start--){
        int ans = INT_MIN; // Alice ka ans maximise karna hai
        int total = 0;

        for(int X=1;X<=3;X++){ // Choice can be either 1,2 or 3
            if((start+X - 1)>=sv.size()){
                break;
            }
            total += sv[start + X - 1]; // add current selection to total stones
            ans = max(ans,total -  dp[start+X]); // Here, logic is {alice ka final ans} =  {Alice ke total till now} - {Recursion ka ans}
        } 
        dp[start]=ans;
    }

    return dp[0];
}

int solveUsingSO1(vector<int>& sv){
    int n = sv.size();
    int curr = 0; // Current start ka sum depends on uske next ke 3 cells
    int next1 = 0;
    int next2 = 0;
    int next3 = 0;

    for(int start=n-1;start>=0;start--){
        int ans = INT_MIN; // Alice ka ans maximise karna hai
        int total = 0;

        if(start < sv.size()){ // matlab there is room for start+1, so arr[start+1] valid operation as we can move one step ahead
            total += sv[start]; // add current selection to total stones
            ans = max(ans,total -  next1); // Here, logic is {alice ka final ans} =  {Alice ke total till now} - {Recursion ka ans}
        }
        if(start+1 < sv.size()){ // matlab there is room for start+1, so arr[start+1] valid operation as we can move two steps ahead
            total += sv[start + 1]; // add current selection to total stones
            ans = max(ans,total -  next2); // Here, logic is {alice ka final ans} =  {Alice ke total till now} - {Recursion ka ans}
        }
        if(start+2 < sv.size()){ // matlab there is room for start+2, so arr[start+2] valid operation as we can move three step ahead
            total += sv[start + 2]; // add current selection to total stones
            ans = max(ans,total -  next3); // Here, logic is {alice ka final ans} =  {Alice ke total till now} - {Recursion ka ans}
        } 
        curr=ans;

        // Updation - V.V.V.V.V IMP
        next3 = next2;
        next2 = next1;
        next1 = curr;
    }

    return next1;
}

string stoneGameIII(vector<int>& stoneValue) {
    int n = stoneValue.size();
    vector<int> dp(n+1,-1);
    // int ans = solveUsingRecursion(stoneValue,0); // Will give the answer Alice - Bob
    // int ans = solveUsingMem(stoneValue,0,dp); // Will give the answer Alice - Bob
    // int ans = solveUsingTab(stoneValue); // Will give the answer Alice - Bob
    int ans = solveUsingSO1(stoneValue); // Will give the answer Alice - Bob

    if(ans>0){
        return "Alice";
    }
    else if(ans<0){
        return "Bob";
    }
    else{
        return "Tie";
    }
}

// Q8. Minimum Insertions Steps to Make a String Palindrome - (LC-1312) - V.V.V.V.V IMP
// Longest Common Subsequence walla approach use karenge
// Pass both strings by reference to avoid TLE. Tabulation using two 1D Vector
int solveUsingTab2(string &a, string &b){  // TC: O(n^2), SC: O(n)
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



int longestCommonSubsequence(string &text1, string &text2) {
    return solveUsingTab2(text1,text2);
}

int longestPalindromeSubseq(string &s) {
    string s1 = s;
    reverse(s1.begin(),s1.end());

    return longestCommonSubsequence(s,s1);
}

int minInsertions(string s) {
    int LPS = longestPalindromeSubseq(s);
    int insertionsToDo = s.size() - LPS; // Jitne bhi faulty chars hai jo palindrome banne se rok rahe hai, unko total mein se subtract kar do cause utne hi lagengay palindrome banane mein
    return s.size() - LPS;
}

// Q9. Russian Doll Envelopes - (LC-354) - V.V.V.V.V IMP
int solveUsingRecursion(vector<vector<int>>& env,int prev,int curr){
    if(curr==env.size()){
        return 0;
    }

    int include = INT_MIN;
    if(prev == -1 || (env[prev][0]<env[curr][0] && env[prev][1]<env[curr][1])){ // matlab prev ki width aur height dono curr se choti ho ya toh prev abhi kuch bhi na ho
        include = 1 + solveUsingRecursion(env,curr,curr+1);
    }
    int exclude = solveUsingRecursion(env,prev,curr+1); // Matlab current doll exclude kar di, toh agge badh jao

    return max(include,exclude);
}

int solveUsingMem(vector<vector<int>>& env,int prev,int curr,vector<vector<int>>& dp){
    if(curr==env.size()){
        return 0;
    }

    if(dp[prev+1][curr]!=-1){
        return dp[prev+1][curr];
    }

    int include = INT_MIN;
    if(prev == -1 || (env[prev][0]<env[curr][0] && env[prev][1]<env[curr][1])){ // matlab prev ki width aur height dono curr se choti ho ya toh prev abhi kuch bhi na ho
        include = 1 + solveUsingMem(env,curr,curr+1,dp);
    }
    int exclude = solveUsingMem(env,prev,curr+1,dp); // Matlab current doll exclude kar di, toh agge badh jao

    return dp[prev+1][curr] = max(include,exclude); // Since prev yaha -1 hai, we add one to make it a valid index
}   

static bool myComp(vector<int> &a,vector<int> &b){
    if(a[0]==b[0]){
        return a[1] > b[1]; // Matlab a[1] and b[1] mein se bada phele i.e. decreasing
    }
    return a[0] < b[0]; // Else, sort width increasingly
}

int solveUsingBinarySearch(vector<vector<int>> &nums){ // TC: O(nLogn), SC: O(n)
    sort(nums.begin(),nums.end(),myComp); // Here, we will sort increasingly accordingly to width. Aur jaha par bhi width same ho jaye, we will sort decreasingly according to height. Hum chahte hai ki agar width same ho, toh sabse badi height walla phele aa jaye taaki usme zyada se zyada dolls aa sake. This will maintain the pattern of LIS
    if(nums.size()==0){
        return 0;
    }

    vector<int> ans;
    // Now, phele element ki height ko toh store karna hi padgea 
    ans.push_back(nums[0][1]);  

    for(int i=1;i<nums.size();i++){
        // Logic here is, agar curr num jo hai, voh ans ke last se bada hai, toh usse daal do ans mein
        // Agar nahi hai, matlab usse just bada number exist karta hai
        // toh, uss just bade ka index find out kar ke de do aur uss element ko nums[i] se replace kar do
        // In this way, ek sorted array banti rahegi which will be of the size of longest increasing subsequence
        if(ans.back()<nums[i][1]){
            ans.push_back(nums[i][1]);
        }
        else{
            int index = lower_bound(ans.begin(),ans.end(),nums[i][1]) - ans.begin();// Yeh nums[i] se just bada number de dega. Yeh ideally humme nums[i] ke first occurence dene ki koshish karega, jab nahi milega toh usse just bade number ki first occurence de dega apne aap 
            ans[index] = nums[i][1];
        }
    }

    return ans.size();
}



int maxEnvelopes(vector<vector<int>>& envelopes) {
    // sort(envelopes.begin(),envelopes.end());
    // int n = envelopes.size();

    // vector<vector<int>> dp(n+1,vector<int>(n+1,-1));
    // int ans = solveUsingRecursion(envelopes,-1,0);
    // int ans = solveUsingMem(envelopes,-1,0,dp);
    int ans = solveUsingBinarySearch(envelopes);

    return ans;
}

// Q10. Reducing Dishes - (LC-1402) - V.V.V.V.V IMP
int solveUsingRecursion(vector<int>& sat,int curr, int time){
    if(curr>=sat.size()) return 0;

    int ans = INT_MIN;

    int include = (time*sat[curr]) + solveUsingRecursion(sat,curr+1,time+1);
    int exclude = 0 + solveUsingRecursion(sat,curr+1,time);

    return max(include,exclude);

}

int solveUsingMem(vector<int>& sat,int curr, int time,vector<vector<int>> &dp){
    if(curr>=sat.size()) return 0;

    if(dp[curr][time]!=-1){
        return dp[curr][time];
    }

    int ans = INT_MIN;

    int include = (time*sat[curr]) + solveUsingMem(sat,curr+1,time+1,dp);
    int exclude = 0 + solveUsingMem(sat,curr+1,time,dp);

    return dp[curr][time] = max(include,exclude);

}

int solveUsingTab(vector<int>& sat){
    int n = sat.size();
    vector<vector<int>> dp(n+1,vector<int>(n+2,0));

    for(int curr = n - 1;curr>=0;curr--){
        for(int time = n;time>=0;time--){
            int ans = INT_MIN;

            int include = (time*sat[curr]) + dp[curr+1][time+1];
            int exclude = 0 + dp[curr+1][time];

            dp[curr][time] = max(include,exclude);
        }
    }

    return dp[0][1];
}


int maxSatisfaction(vector<int>& satisfaction) {
    sort(satisfaction.begin(),satisfaction.end()); // Sort as once you sort it, zyada satisfication walli dish zyada time stamp se multiply hogi, jisse like time coeff zyada se zyada badhega. Similarly, kam satisfaction walli kam time stamp se multily hogi, jisse like time coeff kam se kam girega
    // int n = satisfaction.size();
    // vector<vector<int>> dp(n+1,vector<int>(n+1,-1));
    // return solveUsingRecursion(satisfaction,0,1);
    // return solveUsingMem(satisfaction,0,1,dp);
    return solveUsingTab(satisfaction);
}

// Q11. Perfect Squares - (LC-279) - V.V.V.V.V IMP
int solveUsingRecursion(int n){
    // Base Case
    if(n==0) return 1; // Matlab agar ban gaya 0, means ban gaya perfecr square, so return success
    if(n<0) return 0; // Agar value hi nahi hai, no way possible

    int i = 1;
    int end = sqrt(n); // Iske badde kisi se bhi karogay answer not possible
    int ans = INT_MAX; // Cause final answer minimise karna hai

    while(i<=end){
        int perfectSquare = i*i;

        int numberOfPerfectSquares = 1 + solveUsingRecursion(n-perfectSquare);
        ans = min(ans,numberOfPerfectSquares);
        i++;
    }

    return ans;
}

int solveUsingMem(int n,vector<int>&dp){
    // Base Case
    if(n==0) return 1; // Matlab agar ban gaya 0, means ban gaya perfecr square, so return success
    if(n<0) return 0; // Agar value hi nahi hai, no way possible

    if(dp[n]!=-1){
        return dp[n];
    }

    int i = 1;
    int end = sqrt(n); // Iske badde kisi se bhi karogay answer not possible
    int ans = INT_MAX; // Cause final answer minimise karna hai

    while(i<=end){
        int perfectSquare = i*i;

        int numberOfPerfectSquares = 1 + solveUsingMem(n-perfectSquare,dp);
        ans = min(ans,numberOfPerfectSquares);
        i++;
    }

    return dp[n]=ans;
}

int solveUsingTab(int n){
    vector<int> dp(n+2,0);
    dp[0] = 1; // handles base case of n==0

    for(int n_index = 1;n_index<=n;n_index++){ // n went from n->0, so yaha ulta. Also, we have already handled n==0 in base case, so start from 0+1 yaani 1 se start karo
        int i = 1;
        int end = sqrt(n_index); // Iske badde kisi se bhi karogay answer not possible
        int ans = INT_MAX; // Cause final answer minimise karna hai

        while(i<=end){
            int perfectSquare = i*i;

            if(n_index-perfectSquare>=0){ // IMP Check to make indexing valid. If index not valid, no changes
                int numberOfPerfectSquares = 1 + dp[n_index-perfectSquare];
                ans = min(ans,numberOfPerfectSquares);
            }
            i++;
        }

        dp[n_index]=ans;
    }

    return dp[n];  
}

int numSquares(int n) {
    // vector<int> dp(n+1,-1);
    // return solveUsingRecursion(n)-1; // Cause yeh final answer mein humesha +1 extra dega
    // return solveUsingMem(n,dp)-1; // Cause yeh final answer mein humesha +1 extra dega
    return solveUsingTab(n)-1;
}

// Q12. Distinct Subsequences - (LC-115) - V.V.V.V.V IMP
int solveUsingRecursion(string &s,string &t,int i,int j){
    // Base Case
    if(j==t.size()) return 1; // Matlab choti string ka looper khatam, so solution mil gaya successfully
    if(i==s.size()) return 0; // Matlab badi string ka looper khatam, so no possible solutions

    int ans = 0;
    if(s[i]==t[j]){
        ans += solveUsingRecursion(s,t,i+1,j+1); // Dono ko match kiya, so dono mein aage badh jao
    }
    ans += solveUsingRecursion(s,t,i+1,j); // (i+1) se string skip karni hai, so sirf pheli string mein aage badho


    return ans;
}

int solveUsingMem(string &s,string &t,int i,int j,vector<vector<int>> &dp){
    // Base Case
    if(j==t.size()) return 1; // Matlab choti string ka looper khatam, so solution mil gaya successfully
    if(i==s.size()) return 0; // Matlab badi string ka looper khatam, so no possible solutions

    if(dp[i][j]!=-1){
        return dp[i][j];
    }

    int ans = 0;
    if(s[i]==t[j]){
        ans += solveUsingMem(s,t,i+1,j+1,dp); // Dono ko match kiya, so dono mein aage badh jao
    }
    ans += solveUsingMem(s,t,i+1,j,dp); // (i+1) se string skip karni hai, so sirf pheli string mein aage badho


    return dp[i][j]=ans;
}

int solveUsingTab(string &s,string &t){
    vector<vector<int>> dp(s.size()+1,vector<int>(t.size()+1,0));

    // Base Case
    for(int looper = 0;looper<=s.size();looper++){ // Handling base case 1 i.e. choti string ka looper khatam, so solution mil gaya successfully
        dp[looper][t.size()] = 1;
    }

    for(int i=s.size()-1;i>=0;i--){
        for(int j=t.size()-1;j>=0;j--){
            long long ans = 0;
            if(s[i]==t[j]){
                ans += dp[i+1][j+1]; // Dono ko match kiya, so dono mein aage badh jao
            }
            ans += dp[i+1][j]; // (i+1) se string skip karni hai, so sirf pheli string mein aage badho


            dp[i][j]=ans;
        }
    }

    return dp[0][0]; 
}

int solveUsingSO1(string &s,string &t){
    vector<int> currRow(t.size()+1,0);
    vector<int> nextRow(t.size()+1,0);

    for(int i=s.size()-1;i>=0;i--){
        // we cant fill last col while considering rows so we will fill it while going row wise:
        nextRow[t.size()] = 1; // Har row ke t.size() col ka ans apne ko 1 se start karna hai to handle base case 2
        for(int j=t.size()-1;j>=0;j--){
            long long ans = 0;
            if(s[i]==t[j]){
                ans += nextRow[j+1]; // Dono ko match kiya, so dono mein aage badh jao
            }
            ans += nextRow[j]; // (i+1) se string skip karni hai, so sirf pheli string mein aage badho

            currRow[j]=ans;
        }
        // UPDATION - V.V.V. IMP
        nextRow = currRow;
    }

    return nextRow[0]; 
}




int numDistinct(string s, string t) {
    // Here, i is to strack for first string, while j is to track for second string
    // vector<vector<int>> dp(s.size()+1,vector<int>(t.size()+1,-1));
    // return solveUsingRecursion(s,t,0,0);
    // return solveUsingMem(s,t,0,0,dp);
    // return solveUsingTab(s,t);
    return solveUsingSO1(s,t);
}

// Q13. Minimum swaps to make sequences increasing - (LC-801) - V.V.V.V.V IMP - TYPICAL hai, toh dry run karke samajhna padega
int solveUsingRecursion(vector<int>& nums1, vector<int>& nums2,int curr,int prev1,int prev2){
    if(curr==nums1.size()) return 0;

    int swap = INT_MAX;
    int noSwap = INT_MAX;

    // Swap
    if(prev1<nums2[curr] && prev2 <nums1[curr]){ // Swap in a way jisse increasing array banne doosra walla
        swap = 1 + solveUsingRecursion(nums1,nums2,curr+1,nums1[curr],nums2[curr]); // agar swap kar diya, toh both the prev's will keep track from the current i of their respective array
    }

    // No Swap
    if(prev1<nums1[curr] && prev2 < nums2[curr]){
        noSwap = 0 + solveUsingRecursion(nums1,nums2,curr+1,nums1[curr],nums2[curr]);
    }

    return min(swap,noSwap);
}

int solveUsingMem(vector<int>& nums1, vector<int>& nums2,int curr,int prev1,int prev2,vector<vector<int>> &dp,int isSwap){
    if(curr==nums1.size()) return 0;

    if(dp[curr][isSwap]!=-1){
        return dp[curr][isSwap];
    }

    int swap = INT_MAX;
    int noSwap = INT_MAX;

    // Swap
    if(prev1<nums2[curr] && prev2 <nums1[curr]){ // Swap in a way jisse increasing array banne doosra walla
        swap = 1 + solveUsingMem(nums1,nums2,curr+1,nums1[curr],nums2[curr],dp,!isSwap); // agar swap kar diya, toh both the prev's will keep track from the current i of their respective array
    }

    // No Swap
    if(prev1<nums1[curr] && prev2 < nums2[curr]){
        noSwap = 0 + solveUsingMem(nums1,nums2,curr+1,nums1[curr],nums2[curr],dp,isSwap);
    }

    return dp[curr][isSwap] = min(swap,noSwap); // Basically, for current index, will tell jo bhi ans hai
}

int solveUsingTab(vector<int>& nums1, vector<int>& nums2){
    vector<vector<int>> dp(nums1.size()+1,vector<int>(2,0)); // Basically, for all indexes tracks only two things, swap ka ans and no swap ka ans

    for(int curr=nums1.size()-1;curr>=1;curr--){ // (n-1) se lekar 1 tak isliye cause we will be accessing curr-1, so to make sure indexing valid ho
        for(int isSwap=1;isSwap>=0;isSwap--){
            int prev1 = nums1[curr-1];
            int prev2 = nums2[curr-1];

            if(isSwap){ // V.V. IMP
                swap(prev1,prev2); // Agar isSwap true hai, matlab swap karna hai, toh prev1 and prev2 bhi interchange hongay, just like phele
            }

            int swap = INT_MAX;
            int noSwap = INT_MAX;

            // Swap
            if(prev1<nums2[curr] && prev2 <nums1[curr]){ // Swap in a way jisse increasing array banne doosra walla
                swap = 1 + dp[curr+1][1]; // agar swap kar diya, toh both the prev's will keep track from the current i of their respective array
            }

            // No Swap
            if(prev1<nums1[curr] && prev2 < nums2[curr]){
                noSwap = 0 + dp[curr+1][0];
            }

            dp[curr][isSwap] = min(swap,noSwap); // Basically, for current index, will tell jo bhi ans hai
        }
    }

    return dp[1][0]; // Cause ek index add kar diya hai, so final answer initial position + 1 pe hoga
}

int minSwap(vector<int>& nums1, vector<int>& nums2) {
    // vector<vector<int>> dp(nums1.size()+1,vector<int>(2,-1)); // Basically, for all indexes tracks only two things, swap ka ans and no swap ka ans
    // // return solveUsingRecursion(nums1,nums2,0,-1,-1); // Curr,Prev1,Prev2
    // int isSwap = 0; // Boolean to check whether case of swap or not, initialised with no
    // return solveUsingMem(nums1,nums2,0,-1,-1,dp,isSwap); // Curr,Prev1,Prev2


        // Now, to handle when curr=0, we will need a previous as -1 in both arrays, so we can compare. Insert -1 dono arrays mein begin() se
    nums1.insert(nums1.begin(),-1);
    nums2.insert(nums2.begin(),-1);
    // The above will handle the need for prev1 and prev2
    return solveUsingTab(nums1,nums2); // Curr,Prev1,Prev2
}

// Q14. Predict the Winner - (LC-486) - V.V.V.V.V IMP
int solveUsingRecursion(vector<int>& nums,int start,int end){
    // base case
    if(start==end){
        return nums[start]; // matlab index mein ek hi element hai, toh wohi utha lo
    }

    // Difference = Score_p1 - Score_p2
    // So that means, if player 1 scores X points, difference increases by X
    // Also, if player 2 scores Y points, difference increases by Y
    // Matlab apne ko sirf P1 ka score nikalna hai aur P2 ka score (via Recursion) minus karna hai, and max lena hai dono diff ki possibilities ka

    int diffStart = nums[start] - solveUsingRecursion(nums,start+1,end); // Difference if player 1 picks start position ka element
    int diffEnd = nums[end] - solveUsingRecursion(nums,start,end-1); // Difference if player 1 picks end position ka element

    return max(diffStart,diffEnd);
}

int solveUsingMem(vector<int>& nums,int start,int end,vector<vector<int>> &dp){
    // base case
    if(start==end){
        return nums[start]; // matlab index mein ek hi element hai, toh wohi utha lo
    }

    if(dp[start][end]!=-1){
        return dp[start][end];
    }

    // Difference = Score_p1 - Score_p2
    // So that means, if player 1 scores X points, difference increases by X
    // Also, if player 2 scores Y points, difference increases by Y
    // Matlab apne ko sirf P1 ka score nikalna hai aur P2 ka score (via Recursion) minus karna hai, and max lena hai dono diff ki possibilities ka

    int diffStart = nums[start] - solveUsingMem(nums,start+1,end,dp); // Difference if player 1 picks start position ka element
    int diffEnd = nums[end] - solveUsingMem(nums,start,end-1,dp); // Difference if player 1 picks end position ka element

    return dp[start][end] = max(diffStart,diffEnd);
}

int solveUsingTab(vector<int>& nums){
    vector<vector<int>> dp(nums.size()+1,vector<int>(nums.size()+1,-1));

    // yaha, end ka base case hai ki jab bhi voh start ke equal ho, it will stop. Yaani in the 2D matrix, end goes from (size-1)->(start). Now, loop will be ulta, and will go from the start to (size-1).
    
    for(int start=nums.size()-1;start>=0;start--){
        for(int end=start;end<nums.size();end++){
            if(start==end){ // V.V.V. IMP - Base Case handling - put the check of base case ki agar start==end ho, waha seedha nums[start] rakh dene ka, else normal process pe jao
                dp[start][end] = nums[start];
            }
            else{
                // Difference = Score_p1 - Score_p2
                // So that means, if player 1 scores X points, difference increases by X
                // Also, if player 2 scores Y points, difference increases by Y
                // Matlab apne ko sirf P1 ka score nikalna hai aur P2 ka score (via Recursion) minus karna hai, and max lena hai dono diff ki possibilities ka

                int diffStart = nums[start] - dp[start+1][end]; // Difference if player 1 picks start position ka element
                int diffEnd = nums[end] - dp[start][end-1]; // Difference if player 1 picks end position ka element

                dp[start][end] = max(diffStart,diffEnd);
            }   
        }
        // diagonalBase--; // TYPICAL - UNDERTSAND YAAD SE
    }

    return dp[0][nums.size()-1];
}

bool predictTheWinner(vector<int>& nums) {
    // Basically, we have to tell ki overall cases mein se, agar ek bhi base case aisa hai jiske through p1 jeet sakta hai, toh overall answer apne aap true de dega i.e. agar kahi bhi recursive tree mein score +ve hai, P1 can win the game
    // return solveUsingRecursion(nums,0,nums.size()-1)>=0;
    


    // vector<vector<int>> dp(nums.size()+1,vector<int>(nums.size()+1,-1));
    // return solveUsingMem(nums,0,nums.size()-1,dp)>=0;
    
    return solveUsingTab(nums)>=0;
}

// Q15. Interleaving String - (LC-97) - V.V.V.V.V IMP
bool solveUsingRecursion(string &s1, string &s2, string &s3,int i,int j,int k){
    if(i==s1.size() && j==s2.size() && k==s3.size()){
        return true; // Matlab sab kuch match hoke string khatam ho gayi teeni
    }

    bool flag = false;
    // Dono condition if mein likho, taaki jonsi string se matching shuru ho, waha se start kar de. In this way as given below, dono apne aap match karte rahengay, jaha break hua, doosri string se match kar dengay. DRY RUN karke dekho
    if(i<s1.size() && s1[i]==s3[k]){
        flag = flag || solveUsingRecursion(s1,s2,s3,i+1,j,k+1);
    }

    if(j<s2.size() && s2[j]==s3[k]){
        flag = flag || solveUsingRecursion(s1,s2,s3,i,j+1,k+1);
    }

    return flag;
}

bool solveUsingMem(string &s1, string &s2, string &s3,int i,int j,int k,vector<vector<vector<int>>> &dp){
    if(i==s1.size() && j==s2.size() && k==s3.size()){
        return true; // Matlab sab kuch match hoke string khatam ho gayi teeni
    }

    if(dp[i][j][k]){
        return dp[i][j][k];
    }

    bool flag = false;
    // Dono condition if mein likho, taaki jonsi string se matching shuru ho, waha se start kar de. In this way as given below, dono apne aap match karte rahengay, jaha break hua, doosri string se match kar dengay. DRY RUN karke dekho
    if(i<s1.size() && s1[i]==s3[k]){
        flag = flag || solveUsingMem(s1,s2,s3,i+1,j,k+1,dp);
    }

    if(j<s2.size() && s2[j]==s3[k]){
        flag = flag || solveUsingMem(s1,s2,s3,i,j+1,k+1,dp);
    }

    return dp[i][j][k]=flag;
}

bool solveUsingTab(string &s1, string &s2, string &s3){
    vector<vector<vector<int>>> dp(s1.size()+1,vector<vector<int>>(s2.size()+1,vector<int>(s3.size()+1,0)));

    dp[s1.size()][s2.size()][s3.size()]= 1;

    // Teeno loop used to go till 0->size tak hi. Here, they would also hit (n) and waha pe hi check that, isliye we can see it went from 0->n+1 tak. Jab loop adjust hoga ulta karke, it will start from (n+1-1) = n se lekar 0 tak

    for(int i=s1.size();i>=0;i--){
        for(int j=s2.size();j>=0;j--){
            for(int k=s3.size();k>=0;k--){
                if(i==s1.size() && j==s2.size() && k==s3.size()){ // Base Case Handling - upar already set kar di, toh skip this
                    continue;
                }
                bool flag = false;
                // Dono condition if mein likho, taaki jonsi string se matching shuru ho, waha se start kar de. In this way as given below, dono apne aap match karte rahengay, jaha break hua, doosri string se match kar dengay. DRY RUN karke dekho
                if(i<s1.size() && s1[i]==s3[k]){
                    flag = flag || dp[i+1][j][k+1];
                }

                if(j<s2.size() && s2[j]==s3[k]){
                    flag = flag || dp[i][j+1][k+1];
                }

                dp[i][j][k]=flag;
            }
        }
    }

    return dp[0][0][0];
}

bool isInterleave(string s1, string s2, string s3) {
    // vector<vector<vector<int>>> dp(s1.size()+1,vector<vector<int>>(s2.size()+1,vector<int>(s3.size()+1,0)));
    // return solveUsingRecursion(s1,s2,s3,0,0,0); // Tracks loopers for s1,s2,s3 respectively
    // return solveUsingMem(s1,s2,s3,0,0,0,dp); // Tracks loopers for s1,s2,s3 respectively
    return solveUsingTab(s1,s2,s3); // Tracks loopers for s1,s2,s3 respectively
}

// Q16. Minimum number of removals to make Mountain Array - (LC-1671) - V.V.V.V.V IMP
// This is based on the longest increasing subsequence pattern, and we can interpret this as the maximum number of elements which 
// are needed to make a mountain array. If we find that, we can easily find the minimum number of elements to remove to make a mountain array
// Now, for any given index, we can find out the size of mountain which can be made IF THAT INDEX is made the peak of the mountain, and with that we choose the maximum one
// To find the max size of moutain possible, we find the Longest Increasing Subsequence from the left to right (LIS) of the current index, 
// and then add them with the Longest Decreasing Subsequence from the right to left (LDS) of the current index. 
// Finally, we add them together and subtract 1 as the current index is counted twice.  (i.e. LIS[i] + LDS[nums.size()-i-1] -1) 
// We do this for all the indexes and choose the maximum one. The answer will be the total number of elements minus the maximum size of mountain possible
// Also, if the LIS[i] or LDS[i] is 1, then we can't make a mountain with that index as peak, so we can't consider that index as peak of mountain
void solveUsingBinarySearch(vector<int> &nums,vector<int> &lis){ // TC: O(nLogn), SC: O(n)
    if(nums.size()==0){
        return;
    }

    vector<int> ans;
    // Now, phele element toh store karna hi padgea 
    ans.push_back(nums[0]);
    lis.push_back(1); // Starting index ka LIS sirf khud se hi hoga hence default is one

    for(int i=1;i<nums.size();i++){
        // Logic here is, agar curr num jo hai, voh ans ke last se bada hai, toh usse daal do ans mein
        // Agar nahi hai, matlab usse just bada number exist karta hai
        // toh, uss just bade ka index find out kar ke de do aur uss element ko nums[i] se replace kar do
        // In this way, ek sorted array banti rahegi which will be of the size of longest increasing subsequence
        if(ans.back()<nums[i]){
            ans.push_back(nums[i]);
            lis.push_back(ans.size()); // Jitne answer mein hai utne hi element LIS mein track kar do
        }
        else{
            int index = lower_bound(ans.begin(),ans.end(),nums[i]) - ans.begin();// Yeh nums[i] se just bada number de dega. Yeh ideally humme nums[i] ke first occurence dene ki koshish karega, jab nahi milega toh usse just bade number ki first occurence de dega apne aap 
            ans[index] = nums[i];
            lis.push_back(index+1); // V.V.V IMP Step
        }
    }

    return;
}


int minimumMountainRemovals(vector<int>& nums) { // TC : O(nLogn), SC: O(n)
    vector<int> lis,lds;
    solveUsingBinarySearch(nums,lis);
    // Now, if we reverse the array and find LIS, that effectively means finding the LDS
    reverse(nums.begin(),nums.end());
    solveUsingBinarySearch(nums,lds);


    int largestMountain = INT_MIN;
    for(int i=0;i<nums.size();i++){
        // Here, it is important that we access LDS using {nums.size()-i-1} indexing, as we are moving in LDS right to left
        if(lis[i]==1 || lds[nums.size()-i-1]==1){
            continue;
        }
        else{
            int currMountain = lis[i] + lds[nums.size()-i-1] - 1; // V.V.V.V.V. IMP STEP (Formula based)
            largestMountain = max(largestMountain,currMountain);
        }
    }

    return nums.size() - largestMountain;  
}

// Q17. Make Array Strictly Increasing - (LC-1187) - V.V.V.V.V IMP
// here, we take prev as element ratehr than index, we cannot make a 2D array as range of prev is from 0->1e+9. Hence, bottom up approach is not possible
#define UL (1e+9 + 1)
int solveUsingRecursion(vector<int>& arr1, vector<int>& arr2,int prev,int i){
    // Base Case
    if(i>=arr1.size()){
        return 0; // Invalid index
    }

        // Case A : Do not do anything i.e. condition is satisfied
    int operation1 = UL; // Minimise this operation and choose upper limit as initial point (question constraint do not allow intMax)
    if(prev<arr1[i]){
        operation1 = 0 + solveUsingRecursion(arr1,arr2,arr1[i],i+1);
    }

    // Case B : Find just bada from previous index and place it there to see if condition is satisfied
    int operation2 = UL; // Minimise this operation and choose upper limit as initial point (question constraint do not allow intMax)
    auto iterator = upper_bound(arr2.begin(),arr2.end(),prev); // Will give address of just bada from prev
    if(iterator!=arr2.end()){ // Matlab prev se just bada koi element mil gaya hai
        int index = iterator - arr2.begin();
        // Do not actually swap as we do not want to mess with existing array
        operation2 = 1 + solveUsingRecursion(arr1,arr2,arr2[index],i+1); 
    }

    return min(operation1,operation2);
}

int solveUsingMem(vector<int>& arr1, vector<int>& arr2,int prev,int i,map<pair<int,int>,int> &dp){
    // Base Case
    if(i>=arr1.size()){
        return 0; // Invalid index
    }

    // Check answer
    if(dp.find({prev,i})!=dp.end()){
        return dp[{prev,i}];
    }

    // Case A : Do not do anything i.e. condition is satisfied
    int operation1 = UL; // Minimise this operation and choose upper limit as initial point (question constraint do not allow intMax)
    if(prev<arr1[i]){
        operation1 = 0 + solveUsingMem(arr1,arr2,arr1[i],i+1,dp);
    }

    // Case B : Find just bada from previous index and place it there to see if condition is satisfied
    int operation2 = UL; // Minimise this operation and choose upper limit as initial point (question constraint do not allow intMax)
    auto iterator = upper_bound(arr2.begin(),arr2.end(),prev); // Will give address of just bada from prev
    if(iterator!=arr2.end()){ // Matlab prev se just bada koi element mil gaya hai
        int index = iterator - arr2.begin();
        // Do not actually swap as we do not want to mess with existing array
        operation2 = 1 + solveUsingMem(arr1,arr2,arr2[index],i+1,dp); 
    }

    return dp[{prev,i}] = min(operation1,operation2);
}

int makeArrayIncreasing(vector<int>& arr1, vector<int>& arr2) {
    sort(arr2.begin(),arr2.end()); // We sort the second array, taaki usme binary search laga paye while comparing agge

    map<pair<int,int>,int> dp; // This is from {prev,i} -> value. Here, we cannot make array as range of prev is from 0->1e+9
    // int ans = solveUsingRecursion(arr1,arr2,-1,0);
    int ans = solveUsingMem(arr1,arr2,-1,0,dp);
    return ans == UL ? -1:ans;
}

// Q18. Target Sum - (LC-494) - V.V.V.V.V IMP
int solveUsingRecursion(vector<int>& nums, int target,int i){
    // Base Case
    if(i>=nums.size()){
        return target==0 ? 1:0; // Invalid index, so check if answer has become target. If yes, means solution exists else no answer
    }

    int plus = solveUsingRecursion(nums,target - (nums[i]),i+1);
    int minus = solveUsingRecursion(nums,target - (-nums[i]),i+1);

    return plus + minus; // Gives total ways in which we can make valid expression
    
}

int solveUsingMem(vector<int>& nums, int target,int i,map<pair<int,int>,int> &dp){
    // Base Case
    if(i>=nums.size()){
        return target==0 ? 1:0; // Invalid index, so check if answer has become target. If yes, means solution exists else no answer
    }

    if(dp.find({i,target})!=dp.end()){
        return dp[{i,target}];
    }

    int plus = solveUsingMem(nums,target - (nums[i]),i+1,dp);
    int minus = solveUsingMem(nums,target - (-nums[i]),i+1,dp);

    return dp[{i,target}] = plus + minus; // Gives total ways in which we can make valid expression 
}

int solveUsingTab(vector<int>& nums, int target){
    map<pair<int,int>,int> dp;

    dp[{nums.size(),0}] = 1; // Means jaha target 0 hai AND index array khatam ho gayi hai, set answer as 1 

    // Now, target can range from -(total of nums) -> +(total of nums). This will define the movement of target
    int total = 0;
    for(int i=0;i<nums.size();i++){
        total+= nums[i];
    }
    
    for(int i=nums.size()-1;i>=0;i--){
        for(int target = -total;target<=total;target++){ // IMP Case condition, yaad se 
            int plus = dp.find({i+1,target - nums[i]})!=dp.end() ? dp[{i+1,target - nums[i]}] : 0;
            int minus = dp.find({i+1,target - (-nums[i])})!=dp.end() ? dp[{i+1,target - (-nums[i])}] : 0;

            dp[{i,target}] = plus + minus; // Gives total ways in which we can make valid expression 
        } 
    } 

    return dp[{0,target}];
}


int findTargetSumWays(vector<int>& nums, int target) {
    // Total target mein se final expression ko minus karte raho

    // map<pair<int,int>,int> dp; // Since {i,target}->value, target can get -ve, which will create issues in array comparision. hence map
    // return solveUsingRecursion(nums,target,0);
    // return solveUsingMem(nums,target,0,dp);
    return solveUsingTab(nums,target);
}

// Q19. Buy and Sell Stocks II - (LC-122) - V.V.V.V.V IMP
int solveUsingRecursion(vector<int>& prices,int index,bool buy){
    // Base Case
    if(index>=prices.size()) return 0;

    int profit = 0;

    // Abh profit = {Sell - Buy} or {-Buy + Sell}. Matlab jab bhi buy karo, uss price ko proft mein se minus karne ka hai, hence we add it into profit with a -ve sign, which effectively subtracts it

    if(buy){ // If true matlab buy karna allowed hai abhi
        // Case A : Make the purchase on that day
        int buyIt = -prices[index] + solveUsingRecursion(prices,index+1,0);

        // Case B : Do not make the purchase i.e. ignore it
        int skipIt = 0 + solveUsingRecursion(prices,index+1,1);

        profit = max(buyIt,skipIt);
    }
    else{ // Maltab cannot buy, only sell or ignore
        // Case A : Make the sale on that day
        int sellIt = prices[index] + solveUsingRecursion(prices,index+1,1);

        // Case B : Do not make the sale i.e. ignore it
        int skipIt = 0 + solveUsingRecursion(prices,index+1,0);

        profit = max(sellIt,skipIt);
    }

    return profit;
}

int solveUsingMem(vector<int>& prices,int index,bool buy,vector<vector<int>> &dp){
    // Base Case
    if(index>=prices.size()) return 0;

    if(dp[index][buy]!=-1){
        return dp[index][buy];
    }

    int profit = 0;

    // Abh profit = {Sell - Buy} or {-Buy + Sell}. Matlab jab bhi buy karo, uss price ko proft mein se minus karne ka hai, hence we add it into profit with a -ve sign, which effectively subtracts it

    if(buy){ // If true matlab buy karna allowed hai abhi
        // Case A : Make the purchase on that day
        int buyIt = -prices[index] + solveUsingMem(prices,index+1,0,dp);

        // Case B : Do not make the purchase i.e. ignore it
        int skipIt = 0 + solveUsingMem(prices,index+1,1,dp);

        profit = max(buyIt,skipIt);
    }
    else{ // Maltab cannot buy, only sell or ignore
        // Case A : Make the sale on that day
        int sellIt = prices[index] + solveUsingMem(prices,index+1,1,dp);

        // Case B : Do not make the sale i.e. ignore it
        int skipIt = 0 + solveUsingMem(prices,index+1,0,dp);

        profit = max(sellIt,skipIt);
    }

    return dp[index][buy]=profit;
}

int solveUsingTab(vector<int>& prices){
    vector<vector<int>> dp(prices.size()+1,vector<int>(2,0)); // har index ke liye either true or false hi ho sakta hai

    for(int index = prices.size()-1;index>=0;index--){
        for(int buy=0;buy<=1;buy++){
            int profit = 0;

            // Abh profit = {Sell - Buy} or {-Buy + Sell}. Matlab jab bhi buy karo, uss price ko proft mein se minus karne ka hai, hence we add it into profit with a -ve sign, which effectively subtracts it

            if(buy){ // If true matlab buy karna allowed hai abhi
                // Case A : Make the purchase on that day
                int buyIt = -prices[index] + dp[index+1][!buy];

                // Case B : Do not make the purchase i.e. ignore it
                int skipIt = 0 + dp[index+1][buy];

                profit = max(buyIt,skipIt);
            }
            else{ // Maltab cannot buy, only sell or ignore
                // Case A : Make the sale on that day
                int sellIt = prices[index] + dp[index+1][!buy];

                // Case B : Do not make the sale i.e. ignore it
                int skipIt = 0 + dp[index+1][buy];

                profit = max(sellIt,skipIt);
            }

            dp[index][buy]=profit;
        }
    }

    return dp[0][1];
}

int solveUsingSO1(vector<int>& prices){ // TC: O(n), SC: O(1)
    vector<int> curr(2,0); // Current Row
    vector<int> next(2,0); // Next Row



    for(int index = prices.size()-1;index>=0;index--){
        for(int buy=0;buy<=1;buy++){
            int profit = 0;

            // Abh profit = {Sell - Buy} or {-Buy + Sell}. Matlab jab bhi buy karo, uss price ko proft mein se minus karne ka hai, hence we add it into profit with a -ve sign, which effectively subtracts it

            if(buy){ // If true matlab buy karna allowed hai abhi
                // Case A : Make the purchase on that day
                int buyIt = -prices[index] + next[!buy];

                // Case B : Do not make the purchase i.e. ignore it
                int skipIt = 0 + next[buy];

                profit = max(buyIt,skipIt);
            }
            else{ // Maltab cannot buy, only sell or ignore
                // Case A : Make the sale on that day
                int sellIt = prices[index] + next[!buy];

                // Case B : Do not make the sale i.e. ignore it
                int skipIt = 0 + next[buy];

                profit = max(sellIt,skipIt);
            }

            curr[buy]=profit;
        }
        next = curr;
    }

    return next[1];
}


int maxProfit(vector<int>& prices) {
    // vector<vector<int>> dp(prices.size()+1,vector<int>(2,-1)); // har index ke liye either true or false hi ho sakta hai
    // return solveUsingRecursion(prices,0,true);
    // return solveUsingMem(prices,0,true,dp);
    // return solveUsingTab(prices);
    return solveUsingSO1(prices);
}

// Q20.  Buy and Sell Stocks III - (LC-123) - V.V.V.V.V IMP
int solveUsingRecursion(vector<int>& prices,int index,bool buy,int limit){
    // Base Case
    if(index>=prices.size() || limit==0) return 0;

    int profit = 0;

    // Abh profit = {Sell - Buy} or {-Buy + Sell}. Matlab jab bhi buy karo, uss price ko proft mein se minus karne ka hai, hence we add it into profit with a -ve sign, which effectively subtracts it

    if(buy){ // If true matlab buy karna allowed hai abhi
        // Case A : Make the purchase on that day
        int buyIt = -prices[index] + solveUsingRecursion(prices,index+1,!buy,limit);

        // Case B : Do not make the purchase i.e. ignore it
        int skipIt = 0 + solveUsingRecursion(prices,index+1,buy,limit);

        profit = max(buyIt,skipIt);
    }
    else{ // Maltab cannot buy, only sell or ignore
        // Case A : Make the sale on that day 
        // Here, limit is only modified when a transaction is complete i.e. when a stock is sold
        int sellIt = prices[index] + solveUsingRecursion(prices,index+1,!buy,limit-1);

        // Case B : Do not make the sale i.e. ignore it
        int skipIt = 0 + solveUsingRecursion(prices,index+1,buy,limit);

        profit = max(sellIt,skipIt);
    }

    return profit;
}

int solveUsingMem(vector<int>& prices,int index,bool buy,int limit,vector<vector<vector<int>>> dp){
    // Base Case
    if(index>=prices.size() || limit==0) return 0;

    if(dp[index][buy][limit]!=-1){
        return dp[index][buy][limit];
    }

    int profit = 0;

    // Abh profit = {Sell - Buy} or {-Buy + Sell}. Matlab jab bhi buy karo, uss price ko proft mein se minus karne ka hai, hence we add it into profit with a -ve sign, which effectively subtracts it

    if(buy){ // If true matlab buy karna allowed hai abhi
        // Case A : Make the purchase on that day
        int buyIt = -prices[index] + solveUsingMem(prices,index+1,!buy,limit,dp);

        // Case B : Do not make the purchase i.e. ignore it
        int skipIt = 0 + solveUsingMem(prices,index+1,buy,limit,dp);

        profit = max(buyIt,skipIt);
    }
    else{ // Maltab cannot buy, only sell or ignore
        // Case A : Make the sale on that day 
        // Here, limit is only modified when a transaction is complete i.e. when a stock is sold
        int sellIt = prices[index] + solveUsingMem(prices,index+1,!buy,limit-1,dp);

        // Case B : Do not make the sale i.e. ignore it
        int skipIt = 0 + solveUsingMem(prices,index+1,buy,limit,dp);

        profit = max(sellIt,skipIt);
    }

    return dp[index][buy][limit]=profit;
}

int solveUsingTab(vector<int>& prices){
    vector<vector<vector<int>>> dp(prices.size()+1,vector<vector<int>>(2,vector<int>(3,0)));
    
    for(int index=prices.size()-1;index>=0;index--){
        for(int buy=0;buy<=1;buy++){
            for(int limit=1;limit<=2;limit++){ // IMP: To make indexing valid, we let limit go from 1 to 2. Logically idea is ki kam se kam ek transaction toh karni padegi, as jab limit 0 ho there is no possible answer which is already handled in base case handling upar
                int profit = 0;

                if(buy){ // If true matlab buy karna allowed hai abhi
                    // Case A : Make the purchase on that day
                    int buyIt = -prices[index] + dp[index+1][!buy][limit];

                    // Case B : Do not make the purchase i.e. ignore it
                    int skipIt = 0 + dp[index+1][buy][limit];

                    profit = max(buyIt,skipIt);
                }
                else{ // Maltab cannot buy, only sell or ignore
                    // Case A : Make the sale on that day 
                    // Here, limit is only modified when a transaction is complete i.e. when a stock is sold
                    int sellIt = prices[index] + dp[index+1][!buy][limit-1];

                    // Case B : Do not make the sale i.e. ignore it
                    int skipIt = 0 + dp[index+1][buy][limit];

                    profit = max(sellIt,skipIt);
                }

                dp[index][buy][limit]=profit;

            }
        }
    }

    return dp[0][1][2];
}

int solveUsingSO1(vector<int>& prices){
    vector<vector<int>> curr(2,vector<int>(3,0));
    vector<vector<int>> next(2,vector<int>(3,0));
    
    for(int index=prices.size()-1;index>=0;index--){
        for(int buy=0;buy<=1;buy++){
            for(int limit=1;limit<=2;limit++){ // IMP: To make indexing valid, we let limit go from 1 to 2. Logically idea is ki kam se kam ek transaction toh karni padegi, as jab limit 0 ho there is no possible answer which is already handled in base case handling upar
                int profit = 0;

                if(buy){ // If true matlab buy karna allowed hai abhi
                    // Case A : Make the purchase on that day
                    int buyIt = -prices[index] + next[!buy][limit];

                    // Case B : Do not make the purchase i.e. ignore it
                    int skipIt = 0 + next[buy][limit];

                    profit = max(buyIt,skipIt);
                }
                else{ // Maltab cannot buy, only sell or ignore
                    // Case A : Make the sale on that day 
                    // Here, limit is only modified when a transaction is complete i.e. when a stock is sold
                    int sellIt = prices[index] + next[!buy][limit-1];

                    // Case B : Do not make the sale i.e. ignore it
                    int skipIt = 0 + next[buy][limit];

                    profit = max(sellIt,skipIt);
                }

                curr[buy][limit]=profit;
            }
        }
        next = curr;
    }

    return next[1][2];
}

int maxProfit(vector<int>& prices) {
    // Index,Buy and Limit ka 3D Array. Index can be 0->size-1; buy can be 0 or 1; limit can be 0,1 or 2;
    // vector<vector<vector<int>>> dp(prices.size()+1,vector<vector<int>>(2,vector<int>(3,-1)));
    // return solveUsingRecursion(prices,0,1,2);
    // return solveUsingMem(prices,0,1,2,dp);
    // return solveUsingTab(prices);
    return solveUsingSO1(prices);
}

// Q21. Buy and Sell Stocks IV - (LC-188) - V.V.V.V.V IMP
int solveUsingRecursion(vector<int>& prices,int index,bool buy,int limit){
    // Base Case
    if(index>=prices.size() || limit==0) return 0;

    int profit = 0;

    // Abh profit = {Sell - Buy} or {-Buy + Sell}. Matlab jab bhi buy karo, uss price ko proft mein se minus karne ka hai, hence we add it into profit with a -ve sign, which effectively subtracts it

    if(buy){ // If true matlab buy karna allowed hai abhi
        // Case A : Make the purchase on that day
        int buyIt = -prices[index] + solveUsingRecursion(prices,index+1,!buy,limit);

        // Case B : Do not make the purchase i.e. ignore it
        int skipIt = 0 + solveUsingRecursion(prices,index+1,buy,limit);

        profit = max(buyIt,skipIt);
    }
    else{ // Maltab cannot buy, only sell or ignore
        // Case A : Make the sale on that day 
        // Here, limit is only modified when a transaction is complete i.e. when a stock is sold
        int sellIt = prices[index] + solveUsingRecursion(prices,index+1,!buy,limit-1);

        // Case B : Do not make the sale i.e. ignore it
        int skipIt = 0 + solveUsingRecursion(prices,index+1,buy,limit);

        profit = max(sellIt,skipIt);
    }

    return profit;
}

int solveUsingMem(vector<int>& prices,int index,bool buy,int limit,vector<vector<vector<int>>> dp){
    // Base Case
    if(index>=prices.size() || limit==0) return 0;

    if(dp[index][buy][limit]!=-1){
        return dp[index][buy][limit];
    }

    int profit = 0;

    // Abh profit = {Sell - Buy} or {-Buy + Sell}. Matlab jab bhi buy karo, uss price ko proft mein se minus karne ka hai, hence we add it into profit with a -ve sign, which effectively subtracts it

    if(buy){ // If true matlab buy karna allowed hai abhi
        // Case A : Make the purchase on that day
        int buyIt = -prices[index] + solveUsingMem(prices,index+1,!buy,limit,dp);

        // Case B : Do not make the purchase i.e. ignore it
        int skipIt = 0 + solveUsingMem(prices,index+1,buy,limit,dp);

        profit = max(buyIt,skipIt);
    }
    else{ // Maltab cannot buy, only sell or ignore
        // Case A : Make the sale on that day 
        // Here, limit is only modified when a transaction is complete i.e. when a stock is sold
        int sellIt = prices[index] + solveUsingMem(prices,index+1,!buy,limit-1,dp);

        // Case B : Do not make the sale i.e. ignore it
        int skipIt = 0 + solveUsingMem(prices,index+1,buy,limit,dp);

        profit = max(sellIt,skipIt);
    }

    return dp[index][buy][limit]=profit;
}

int solveUsingTab(vector<int>& prices,int k){
    vector<vector<vector<int>>> dp(prices.size()+1,vector<vector<int>>(2,vector<int>(k+1,0)));
    
    for(int index=prices.size()-1;index>=0;index--){
        for(int buy=0;buy<=1;buy++){
            for(int limit=1;limit<=k;limit++){ // IMP: To make indexing valid, we let limit go from 1 to 2. Logically idea is ki kam se kam ek transaction toh karni padegi, as jab limit 0 ho there is no possible answer which is already handled in base case handling upar
                int profit = 0;

                if(buy){ // If true matlab buy karna allowed hai abhi
                    // Case A : Make the purchase on that day
                    int buyIt = -prices[index] + dp[index+1][!buy][limit];

                    // Case B : Do not make the purchase i.e. ignore it
                    int skipIt = 0 + dp[index+1][buy][limit];

                    profit = max(buyIt,skipIt);
                }
                else{ // Maltab cannot buy, only sell or ignore
                    // Case A : Make the sale on that day 
                    // Here, limit is only modified when a transaction is complete i.e. when a stock is sold
                    int sellIt = prices[index] + dp[index+1][!buy][limit-1];

                    // Case B : Do not make the sale i.e. ignore it
                    int skipIt = 0 + dp[index+1][buy][limit];

                    profit = max(sellIt,skipIt);
                }

                dp[index][buy][limit]=profit;

            }
        }
    }

    return dp[0][1][k];
}

int solveUsingSO1(vector<int>& prices,int k){
    vector<vector<int>> curr(2,vector<int>(k+1,0));
    vector<vector<int>> next(2,vector<int>(k+1,0));
    
    for(int index=prices.size()-1;index>=0;index--){
        for(int buy=0;buy<=1;buy++){
            for(int limit=1;limit<=k;limit++){ // IMP: To make indexing valid, we let limit go from 1 to 2. Logically idea is ki kam se kam ek transaction toh karni padegi, as jab limit 0 ho there is no possible answer which is already handled in base case handling upar
                int profit = 0;

                if(buy){ // If true matlab buy karna allowed hai abhi
                    // Case A : Make the purchase on that day
                    int buyIt = -prices[index] + next[!buy][limit];

                    // Case B : Do not make the purchase i.e. ignore it
                    int skipIt = 0 + next[buy][limit];

                    profit = max(buyIt,skipIt);
                }
                else{ // Maltab cannot buy, only sell or ignore
                    // Case A : Make the sale on that day 
                    // Here, limit is only modified when a transaction is complete i.e. when a stock is sold
                    int sellIt = prices[index] + next[!buy][limit-1];

                    // Case B : Do not make the sale i.e. ignore it
                    int skipIt = 0 + next[buy][limit];

                    profit = max(sellIt,skipIt);
                }

                curr[buy][limit]=profit;
            }
        }
        next = curr;
    }

    return next[1][k];
}

int maxProfit(int k, vector<int>& prices) {
    // Index,Buy and Limit ka 3D Array. Index can be 0->size-1; buy can be 0 or 1; limit can be 0->k;
    // vector<vector<vector<int>>> dp(prices.size()+1,vector<vector<int>>(2,vector<int>(k+1,-1)));
    // return solveUsingRecursion(prices,0,1,k);
    // return solveUsingMem(prices,0,1,k,dp);
    // return solveUsingTab(prices,k);
        return solveUsingSO1(prices,k);
}

// Q22. Buy and Sell Stocks V - (LC-714) - V.V.V.V.V IMP
int solveUsingRecursionV(vector<int>& prices,int index,bool buy,int fee){
    // Base Case
    if(index>=prices.size()) return 0;

    int profit = 0;

    // Abh profit = {Sell - Buy} or {-Buy + Sell}. Matlab jab bhi buy karo, uss price ko proft mein se minus karne ka hai, hence we add it into profit with a -ve sign, which effectively subtracts it

    if(buy){ // If true matlab buy karna allowed hai abhi
        // Case A : Make the purchase on that day
        int buyIt = -prices[index] + solveUsingRecursionV(prices,index+1,0,fee);

        // Case B : Do not make the purchase i.e. ignore it
        int skipIt = 0 + solveUsingRecursionV(prices,index+1,1,fee);

        profit = max(buyIt,skipIt);
    }
    else{ // Maltab cannot buy, only sell or ignore
        // Case A : Make the sale on that day
        int sellIt = prices[index]  - fee + solveUsingRecursionV(prices,index+1,1,fee);

        // Case B : Do not make the sale i.e. ignore it
        int skipIt = 0 + solveUsingRecursionV(prices,index+1,0,fee);

        profit = max(sellIt,skipIt);
    }

    return profit;
}

int solveUsingMem(vector<int>& prices,int index,bool buy,int fee,vector<vector<int>> &dp){
    // Base Case
    if(index>=prices.size()) return 0;

    if(dp[index][buy]!=-1){
        return dp[index][buy];
    }

    int profit = 0;

    // Abh profit = {Sell - Buy} or {-Buy + Sell}. Matlab jab bhi buy karo, uss price ko proft mein se minus karne ka hai, hence we add it into profit with a -ve sign, which effectively subtracts it

    if(buy){ // If true matlab buy karna allowed hai abhi
        // Case A : Make the purchase on that day
        int buyIt = -prices[index] + solveUsingMem(prices,index+1,0,fee,dp);

        // Case B : Do not make the purchase i.e. ignore it
        int skipIt = 0 + solveUsingMem(prices,index+1,1,fee,dp);

        profit = max(buyIt,skipIt);
    }
    else{ // Maltab cannot buy, only sell or ignore
        // Case A : Make the sale on that day
        int sellIt = prices[index]  - fee + solveUsingMem(prices,index+1,1,fee,dp);

        // Case B : Do not make the sale i.e. ignore it
        int skipIt = 0 + solveUsingMem(prices,index+1,0,fee,dp);

        profit = max(sellIt,skipIt);
    }

    return dp[index][buy]=profit;
}

int solveUsingTab(vector<int>& prices,int fee){
    vector<vector<int>> dp(prices.size()+1,vector<int>(2,0)); // har index ke liye either true or false hi ho sakta hai

    for(int index = prices.size()-1;index>=0;index--){
        for(int buy=0;buy<=1;buy++){
            int profit = 0;

            // Abh profit = {Sell - Buy} or {-Buy + Sell}. Matlab jab bhi buy karo, uss price ko proft mein se minus karne ka hai, hence we add it into profit with a -ve sign, which effectively subtracts it

            if(buy){ // If true matlab buy karna allowed hai abhi
                // Case A : Make the purchase on that day
                int buyIt = -prices[index] + dp[index+1][!buy];

                // Case B : Do not make the purchase i.e. ignore it
                int skipIt = 0 + dp[index+1][buy];

                profit = max(buyIt,skipIt);
            }
            else{ // Maltab cannot buy, only sell or ignore
                // Case A : Make the sale on that day
                int sellIt = prices[index] - fee + dp[index+1][!buy];

                // Case B : Do not make the sale i.e. ignore it
                int skipIt = 0 + dp[index+1][buy];

                profit = max(sellIt,skipIt);
            }

            dp[index][buy]=profit;
        }
    }

    return dp[0][1];
}

int solveUsingSO1(vector<int>& prices,int fee){ // TC: O(n), SC: O(1)
    vector<int> curr(2,0); // Current Row
    vector<int> next(2,0); // Next Row



    for(int index = prices.size()-1;index>=0;index--){
        for(int buy=0;buy<=1;buy++){
            int profit = 0;

            // Abh profit = {Sell - Buy} or {-Buy + Sell}. Matlab jab bhi buy karo, uss price ko proft mein se minus karne ka hai, hence we add it into profit with a -ve sign, which effectively subtracts it

            if(buy){ // If true matlab buy karna allowed hai abhi
                // Case A : Make the purchase on that day
                int buyIt = -prices[index] + next[!buy];

                // Case B : Do not make the purchase i.e. ignore it
                int skipIt = 0 + next[buy];

                profit = max(buyIt,skipIt);
            }
            else{ // Maltab cannot buy, only sell or ignore
                // Case A : Make the sale on that day
                int sellIt = prices[index] - fee + next[!buy];

                // Case B : Do not make the sale i.e. ignore it
                int skipIt = 0 + next[buy];

                profit = max(sellIt,skipIt);
            }

            curr[buy]=profit;
        }
        next = curr;
    }

    return next[1];
}

int maxProfit(vector<int>& prices, int fee) {
    // vector<vector<int>> dp(prices.size()+1,vector<int>(2,-1)); // har index ke liye either true or false hi ho sakta hai
    // return solveUsingRecursionV(prices,0,1,fee);
    // return solveUsingMem(prices,0,true,fee,dp);
    // return solveUsingTab(prices,fee);
    return solveUsingSO1(prices,fee);
}

// Q23. Buy and Sell with Cooldown - (LC-309) - V.V.V.V.V IMP
int solveUsingRecursionCD(vector<int>& prices,int index,bool buy,bool coolDown){
    // Base Case
    if(index>=prices.size()) return 0;

    int profit = 0;

    // Abh profit = {Sell - Buy} or {-Buy + Sell}. Matlab jab bhi buy karo, uss price ko proft mein se minus karne ka hai, hence we add it into profit with a -ve sign, which effectively subtracts it

    if(buy){ // If true matlab buy karna allowed hai abhi
        // Case A : Make the purchase on that day
        int buyIt = 0;
        if(coolDown==0) buyIt = -prices[index] + solveUsingRecursionCD(prices,index+1,0,0);

        // Case B : Do not make the purchase i.e. ignore it
        int skipIt = 0 + solveUsingRecursionCD(prices,index+1,1,0);

        profit = max(buyIt,skipIt);
    }
    else{ // Maltab cannot buy, only sell or ignore
        // Case A : Make the sale on that day
        int sellIt = prices[index] + solveUsingRecursionCD(prices,index+1,1,1);

        // Case B : Do not make the sale i.e. ignore it
        int skipIt = 0 + solveUsingRecursionCD(prices,index+1,0,0);

        profit = max(sellIt,skipIt);
    }

    return profit;
} 

int solveUsingMemCD(vector<int>& prices,int index,bool buy,bool coolDown,vector<vector<vector<int>>> &dp){
    // Base Case
    if(index>=prices.size()) return 0;

    if(dp[index][buy][coolDown]!=-1) return dp[index][buy][coolDown];

    int profit = 0;

    // Abh profit = {Sell - Buy} or {-Buy + Sell}. Matlab jab bhi buy karo, uss price ko proft mein se minus karne ka hai, hence we add it into profit with a -ve sign, which effectively subtracts it

    if(buy){ // If true matlab buy karna allowed hai abhi
        // Case A : Make the purchase on that day
        int buyIt = 0;
        if(coolDown==0) buyIt = -prices[index] + solveUsingMemCD(prices,index+1,0,0,dp);

        // Case B : Do not make the purchase i.e. ignore it
        int skipIt = 0 + solveUsingMemCD(prices,index+1,1,0,dp);

        profit = max(buyIt,skipIt);
    }
    else{ // Maltab cannot buy, only sell or ignore
        // Case A : Make the sale on that day
        int sellIt = prices[index] + solveUsingMemCD(prices,index+1,1,1,dp);

        // Case B : Do not make the sale i.e. ignore it
        int skipIt = 0 + solveUsingMemCD(prices,index+1,0,0,dp);

        profit = max(sellIt,skipIt);
    }

    return dp[index][buy][coolDown]=profit;
}

int solveUsingTab(vector<int>& prices){
    vector<vector<vector<int>>> dp(prices.size()+1,vector<vector<int>>(2,vector<int>(2,0)));

    for(int index=prices.size()-1;index>=0;index--){
        for(int buy=0;buy<=1;buy++){
            for(int coolDown=1;coolDown>=0;coolDown--){
                int profit = 0;

                // Abh profit = {Sell - Buy} or {-Buy + Sell}. Matlab jab bhi buy karo, uss price ko proft mein se minus karne ka hai, hence we add it into profit with a -ve sign, which effectively subtracts it

                if(buy){ // If true matlab buy karna allowed hai abhi
                    // Case A : Make the purchase on that day
                    int buyIt = 0;
                    if(coolDown==0) buyIt = -prices[index] + dp[index+1][0][0];

                    // Case B : Do not make the purchase i.e. ignore it
                    int skipIt = 0 + dp[index+1][1][0];

                    profit = max(buyIt,skipIt);
                }
                else{ // Maltab cannot buy, only sell or ignore
                    // Case A : Make the sale on that day
                    int sellIt = prices[index] + dp[index+1][1][1];

                    // Case B : Do not make the sale i.e. ignore it
                    int skipIt = 0 + dp[index+1][0][0];

                    profit = max(sellIt,skipIt);
                }

                dp[index][buy][coolDown]=profit;
            }
        }
    }
    

    return dp[0][1][0];
}

int solveUsingSO1(vector<int>& prices){
    vector<vector<int>> curr(2,vector<int>(2,0));
    vector<vector<int>> next(2,vector<int>(2,0));

    for(int index=prices.size()-1;index>=0;index--){
        for(int buy=0;buy<=1;buy++){
            for(int coolDown=1;coolDown>=0;coolDown--){
                int profit = 0;

                // Abh profit = {Sell - Buy} or {-Buy + Sell}. Matlab jab bhi buy karo, uss price ko proft mein se minus karne ka hai, hence we add it into profit with a -ve sign, which effectively subtracts it

                if(buy){ // If true matlab buy karna allowed hai abhi
                    // Case A : Make the purchase on that day
                    int buyIt = 0;
                    if(coolDown==0) buyIt = -prices[index] + next[0][0];

                    // Case B : Do not make the purchase i.e. ignore it
                    int skipIt = 0 + next[1][0];

                    profit = max(buyIt,skipIt);
                }
                else{ // Maltab cannot buy, only sell or ignore
                    // Case A : Make the sale on that day
                    int sellIt = prices[index] + next[1][1];

                    // Case B : Do not make the sale i.e. ignore it
                    int skipIt = 0 + next[0][0];

                    profit = max(sellIt,skipIt);
                }

                curr[buy][coolDown]=profit;
            }
        }
        next = curr;
    }
    

    return next[1][0];
}

int maxProfit(vector<int>& prices) {
    // vector<vector<vector<int>>> dp(prices.size()+1,vector<vector<int>>(2,vector<int>(2,-1)));
    // return solveUsingRecursion(prices,0,1,0);
    // return solveUsingMem(prices,0,1,0,dp);
    // return solveUsingTab(prices);
    return solveUsingSO1(prices);
}

// Q24. Minimum Cost for Tickets - (LC-983) - V.V.V.V.V IMP
int solveUsingRecursion(vector<int>& days, vector<int>& costs,int index){
    // Base Case
    if(index>=days.size()) return 0;

    // Case 1 - 1 day pass
    int oneDayPass = costs[0] + solveUsingRecursion(days,costs,index+1);

    // Case 2 - 7 day pass
    int passEnd7Day = days[index] + 7 - 1;
    int j7 = index;
    while(j7<days.size() && days[j7]<=passEnd7Day){ // Calculate the index jaha tak apni range chalegi
        j7++;
    }
    int sevenDayPass = costs[1] + solveUsingRecursion(days,costs,j7);

    // Case 3 - 30 day pass
    int passEnd30Day = days[index] + 30 - 1;
    int j30 = index;
    while(j30<days.size() && days[j30]<=passEnd30Day){ // Calculate the index jaha tak apni range chalegi
        j30++;
    }
    int thirtyDayPass = costs[2] + solveUsingRecursion(days,costs,j30);

    return min(oneDayPass,min(sevenDayPass,thirtyDayPass));
}

int solveUsingMem(vector<int>& days, vector<int>& costs,int index,vector<int> &dp){
    // Base Case
    if(index>=days.size()) return 0;

    if(dp[index]!=-1) return dp[index];

    // Case 1 - 1 day pass
    int oneDayPass = costs[0] + solveUsingMem(days,costs,index+1,dp);

    // Case 2 - 7 day pass
    int passEnd7Day = days[index] + 7 - 1;
    int j7 = index;
    while(j7<days.size() && days[j7]<=passEnd7Day){ // Calculate the index jaha tak apni range chalegi
        j7++;
    }
    int sevenDayPass = costs[1] + solveUsingMem(days,costs,j7,dp);

    // Case 3 - 30 day pass
    int passEnd30Day = days[index] + 30 - 1;
    int j30 = index;
    while(j30<days.size() && days[j30]<=passEnd30Day){ // Calculate the index jaha tak apni range chalegi
        j30++;
    }
    int thirtyDayPass = costs[2] + solveUsingMem(days,costs,j30,dp);

    return dp[index] = min(oneDayPass,min(sevenDayPass,thirtyDayPass));
}

int solveUsingTab(vector<int>& days, vector<int>& costs){
    vector<int> dp(days.size()+1,0);

    for(int index=days.size()-1;index>=0;index--){
        // Case 1 - 1 day pass
        int oneDayPass = costs[0] + dp[index+1];

        // Case 2 - 7 day pass
        int passEnd7Day = days[index] + 7 - 1;
        int j7 = index;
        while(j7<days.size() && days[j7]<=passEnd7Day){ // Calculate the index jaha tak apni range chalegi
            j7++;
        }
        int sevenDayPass = costs[1] + dp[j7];

        // Case 3 - 30 day pass
        int passEnd30Day = days[index] + 30 - 1;
        int j30 = index;
        while(j30<days.size() && days[j30]<=passEnd30Day){ // Calculate the index jaha tak apni range chalegi
            j30++;
        }
        int thirtyDayPass = costs[2] + dp[j30];

        dp[index] = min(oneDayPass,min(sevenDayPass,thirtyDayPass));
    }

    return dp[0];
}

int mincostTickets(vector<int>& days, vector<int>& costs){
    // vector<int> dp(days.size()+1,-1);
    // return solveUsingRecursion(days,costs,0);
    // return solveUsingMem(days,costs,0,dp);
    return solveUsingTab(days,costs);
}

// Q25. Minimum ASCII Delete Sum for Two Strings - (LC-712) - V.V.V.V.V IMP
int solveUsingRecursion(string &s1, string &s2,int i,int j){
    // Base Case
    int cost = 0;
    if(i==s1.size()||j==s2.size()){
        // then, we give the sum of ASCII chars of the remaining string

        for(int x=i;x<=s1.size();x++){
            cost+= s1[x];
        }

        for(int x=j;x<=s2.size();x++){
            cost+= s2[x];
        }

        return cost;
    }

    if(s1[i]==s2[j]){
        return solveUsingRecursion(s1,s2,i+1,j+1);
    }
    else{
        int CaseA = s1[i] + solveUsingRecursion(s1,s2,i+1,j); // i ko delete karke cost add karo and agge badho
        int CaseB = s2[j] + solveUsingRecursion(s1,s2,i,j+1); // j ko delete karke cost add karo and agge badho

        return min(CaseA,CaseB);
    }
}

int solveUsingMem(string &s1, string &s2,int i,int j,vector<vector<int>> &dp){
    if(dp[i][j]!=-1) return dp[i][j];
    // Base Case
    int cost = 0;
    if(i==s1.size()||j==s2.size()){
        // then, we give the sum of ASCII chars of the remaining string

        for(int x=i;x<=s1.size();x++){
            cost+= s1[x];
        }

        for(int x=j;x<=s2.size();x++){
            cost+= s2[x];
        }

        return dp[i][j]=cost;
    }

    if(s1[i]==s2[j]){
        return dp[i][j]=solveUsingMem(s1,s2,i+1,j+1,dp);
    }
    else{
        int CaseA = s1[i] + solveUsingMem(s1,s2,i+1,j,dp); // i ko delete karke cost add karo and agge badho
        int CaseB = s2[j] + solveUsingMem(s1,s2,i,j+1,dp); // j ko delete karke cost add karo and agge badho

        return dp[i][j]=min(CaseA,CaseB);
    }
}

int solveUsingTab(string &s1, string &s2){
    vector<vector<int>> dp(s1.size()+1,vector<int>(s2.size()+1,0));

    // BASE CASE HANDLING - V.V.V. IMP
    for(int x=s1.size()-1;x>=0;x--){
        dp[x][s2.size()] = s1[x] + dp[x+1][s2.size()];
    }

    for(int x=s2.size()-1;x>=0;x--){
        dp[s1.size()][x] = s2[x] + dp[s1.size()][x+1];
    }

    for(int i=s1.size()-1;i>=0;i--){
        for(int j=s2.size()-1;j>=0;j--){
            int cost = 0;
            if(s1[i]==s2[j]){
                cost=dp[i+1][j+1];
            }
            else{
                int CaseA = s1[i] + dp[i+1][j]; // i ko delete karke cost add karo and agge badho
                int CaseB = s2[j] + dp[i][j+1]; // j ko delete karke cost add karo and agge badho

                cost = min(CaseA,CaseB);
            }
            dp[i][j]=cost;
        }
    }

    return dp[0][0];   
}

int minimumDeleteSum(string s1, string s2){
    // vector<vector<int>> dp(s1.size()+1,vector<int>(s2.size()+1,-1));
    // return solveUsingRecursion(s1,s2,0,0);
    // return solveUsingMem(s1,s2,0,0,dp);
    return solveUsingTab(s1,s2);
}

// Q26. Ones and Zeroes - (LC-474) - V.V.V.V.V IMP
void convertStrsToNums(vector<string>& strs,vector<pair<int,int>> &numStrs){
    for(auto str:strs){
        int zeros = 0;
        int ones = 0; // kam se kam ek one toh hoga hi
        for(auto ch:str){
            if(ch=='0') zeros++;
            else ones++;
        }
        numStrs.push_back({zeros,ones});
    }
}

int solveUsingRecursion(vector<pair<int,int>> &numStrs, int index, int m, int n){
    // Base Case
    if(index == numStrs.size()) return 0;

    int zeros = numStrs[index].first;
    int ones = numStrs[index].second;

    int include = 0;
    int exclude = 0;


    if((m-zeros>=0)&&(n-ones>=0)){ // Current ko Include tabhi karo jab m and n dono exist karte ho
        include = 1 + solveUsingRecursion(numStrs,index+1,m-zeros,n-ones);
    }
    exclude = 0 + solveUsingRecursion(numStrs,index+1,m,n);

    return max(include,exclude);
}

int solveUsingMem(vector<pair<int,int>> &numStrs, int index, int m, int n,vector<vector<vector<int>>> &dp){
    // Base Case
    if(index == numStrs.size()) return 0;

    if(dp[index][m][n]!=-1) return dp[index][m][n];

    int zeros = numStrs[index].first;
    int ones = numStrs[index].second;

    int include = 0;
    int exclude = 0;


    if((m-zeros>=0)&&(n-ones>=0)){ // Current ko Include tabhi karo jab m and n dono exist karte ho
        include = 1 + solveUsingMem(numStrs,index+1,m-zeros,n-ones,dp);
    }
    exclude = 0 + solveUsingMem(numStrs,index+1,m,n,dp);

    return dp[index][m][n]=max(include,exclude);
}

int solveUsingTab(vector<pair<int,int>> &numStrs,int m,int n){
    vector<vector<vector<int>>> dp(numStrs.size()+1,vector<vector<int>>(m+1,vector<int>(n+1,0)));
    
    for(int index=numStrs.size()-1;index>=0;index--){
        for(int m_index=0;m_index<=m;m_index++){
            for(int n_index=0;n_index<=n;n_index++){
                int zeros = numStrs[index].first;
                int ones = numStrs[index].second;

                int include = 0;
                int exclude = 0;


                if((m_index-zeros>=0)&&(n_index-ones>=0)){ // Current ko Include tabhi karo jab m and n dono exist karte ho
                    include = 1 + dp[index+1][m_index-zeros][n_index-ones];
                }
                exclude = 0 + dp[index+1][m_index][n_index];

                dp[index][m_index][n_index]=max(include,exclude);
            }
        }
    }

    return dp[0][m][n];

}

int findMaxForm(vector<string>& strs, int m, int n) {
    // Instead of the vector of strings, let us create a vector of pair<int,int> -> {num of 0s,num of 1s} for counting easily ahead
    vector<pair<int,int>> numStrs;
    convertStrsToNums(strs,numStrs);

    // vector<vector<vector<int>>> dp(strs.size()+1,vector<vector<int>>(m+1,vector<int>(n+1,-1)));

    // return solveUsingRecursion(numStrs,0,m,n);
    // return solveUsingMem(numStrs,0,m,n,dp);
    return solveUsingTab(numStrs,m,n);
}

// Q27. Burst Balloons - (LC-312) - V.V.V.V.V.V.V.V.V.V.V.V.V.V.V IMP
// Here, we are not able to go from top to bottom, as we need to calculate the answer for the entire array, so we need to go from bottom to top
int solveUsingRecursion(vector<int>& nums,int start,int end){
    // Base Case
    if(start>end) return 0;

    int coins = INT_MIN;
    for(int i=start;i<=end;i++){
        // Now, we start bottom up here i.e. last ballon se start karne ka. basically, current baloon ko last singular baloon maan kar burst kar do and then build from there
        coins = max(coins,
            nums[start-1]*nums[i]*nums[end+1]
            + solveUsingRecursion(nums,start,i-1)
            + solveUsingRecursion(nums,i+1,end)
        ); // Current baloon ko burst karo 
    }

    return coins;
}

int solveUsingMem(vector<int>& nums,int start,int end,vector<vector<int>> &dp){
    // Base Case
    if(start>end) return 0;

    if(dp[start][end]!=-1) return dp[start][end];

    int coins = INT_MIN;
    for(int i=start;i<=end;i++){
        // Now, we start bottom up here i.e. last ballon se start karne ka. basically, current baloon ko last singular baloon maan kar burst kar do and then build from there
        coins = max(coins,
            nums[start-1]*nums[i]*nums[end+1]
            + solveUsingMem(nums,start,i-1,dp)
            + solveUsingMem(nums,i+1,end,dp)
        ); // Current baloon ko burst karo 
    }

    return dp[start][end]=coins;
}

int solveUsingTab(vector<int>& nums){
    vector<vector<int>> dp(nums.size()+1,vector<int>(nums.size()+1,0));

    
    // V.V.V.V.V. IMP LOOPS
    for(int start_index=nums.size()-2;start_index>=1;start_index--){
        for(int end_index=start_index;end_index<=nums.size()-2;end_index++){ // start end from start_index t handle base case
            int coins = INT_MIN;
            for(int i=start_index;i<=end_index;i++){
                // Now, we start bottom up here i.e. last ballon se start karne ka. basically, current baloon ko last singular baloon maan kar burst kar do and then build from there
                coins = max(coins,
                    nums[start_index-1]*nums[i]*nums[end_index+1]
                    + dp[start_index][i-1]
                    + dp[i+1][end_index]
                ); // Current baloon ko burst karo 
            }

            dp[start_index][end_index]=coins;
        }
    }

    return dp[1][nums.size()-2];
}

int maxCoins(vector<int>& nums) {
    // Create the artificial padding yaad se
    nums.insert(nums.begin(),1);
    nums.insert(nums.end(),1);

    // vector<vector<int>> dp(nums.size()+1,vector<int>(nums.size()+1,-1));
    // return solveUsingRecursion(nums,1,nums.size()-2);
    // return solveUsingMem(nums,1,nums.size()-2,dp);
    return solveUsingTab(nums);
}
