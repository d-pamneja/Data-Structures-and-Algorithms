# include <iostream>
# include <vector>
# include <string.h>

using namespace std;

// Q1. Reverse String - (LC-344)
void reverseString(vector<char>& s) {
    int n = s.size();
    if(n<=1) return;
    // // Brute Force - Reverse using STL - TC : O(N), SC : O(1)
    // reverse(s.begin(),s.end());

    // Better - Swap from start and finish - TC : O(N), SC : O(1)
    int i = 0;
    int j = n-1;

    while(i<j){
        swap(s[i++],s[j--]);
    }
    
    return;
}

// Q2. Palindrome String - (GFG)
int isPalindrome(string S){
    int n = S.length();
    if(n<=1) return 1;
    
    // // Brute Force - Using Map - TC : O(N), SC : O(N)
    // unordered_map<int,int> mp; // element, freq of element
    // for(int i=0;i<n;i++){
    //     mp[S[i]]++;
    // }
    
    // bool foundOdd = false;
    // for(auto el:mp){
    //     if(el.second&1){
    //         if(foundOdd){
    //             return 0;
    //         }
    //         else{
    //             foundOdd = true;
    //         }
    //     }
    // }
    
    // return 1;
    
    // Optimal - Two Pointer Approach - TC : O(N), SC : O(1)
    int i = 0;
    int j = n - 1;
    
    while(i<j){
        if(S[i]!=S[j]){
            return 0;
        }
        i++;
        j--;
    }
    
    return 1;
}

// Q3. Valid Palindrome - (LC-125)
bool isValidPalindrome(string s) {
    int n = s.size();
    int start = 0;
    int end = n - 1;

    while(start<=end){
        if(!isalnum(s[start])){
            start++; 
            continue;
        }
        if(!isalnum(s[end])){
            end--;
            continue;
        }
        if(tolower(s[start])!=tolower(s[end])){
            return false;
        }
        else{
            start++;
            end--;
        }
    }

    return true;
}

// Q4. Duplicate Characters (CodeNinjas)
vector<pair<char,int>> duplicate_char(string s, int n){
    if(n<=1) return {};

    // // Better Approach - TC : O(N), SC : O(N)
    // map<char,int> mp; // element, freq of element
    // vector<pair<char,int>> ans;

    // for(int i=0;i<n;i++){
    //     mp[s[i]]++;
    // }

    // for(auto el:mp){
    //     if(el.second>1){
    //         ans.push_back(make_pair(el.first,el.second));
    //     }
    // }

    // return ans;

    // Optimal Approach - TC - O(N), SC : O(1)
    vector<int> alphaBig(26,0);
    vector<int> alphaSmall(26,0);
    vector<pair<char,int>> ans;
    for(int i=0;i<n;i++){
        if(s[i]>='A' && s[i]<='Z')
            alphaBig[s[i]-'A']++;
        else
            alphaSmall[s[i]-'a']++;
    }

    for(int i=0;i<alphaBig.size();i++){
        if(alphaBig[i]>1){
            ans.push_back(make_pair(i+'A',alphaBig[i]));
        }
    }

    for(int i=0;i<alphaSmall.size();i++){
        if(alphaSmall[i]>1){
            ans.push_back(make_pair(i+'a',alphaSmall[i]));
        }
    }

    return ans;
}

// Q5. String Shuflle (LC-1528)
 string restoreString(string s, vector<int>& indices) {
    int n = indices.size();
    if(n<=1) return s;

    // // Brute Force - Empty string and then placing - TC - O(N), SC - O(N)
    // string result(n, ' ');
    // for (int i = 0; i < n; i++) {
    //     result[indices[i]] = s[i];
    // }

    // return result;

    // Optimal Approach - TC - O(N), SC - O(1)
    for(int i=0;i<n;i++){
        while(indices[i] != i) {
            swap(s[i], s[indices[i]]); // Swap the current element with the element at its correct position
            swap(indices[i], indices[indices[i]]); // Also swap the indices
        }

    }

    return s;
}

