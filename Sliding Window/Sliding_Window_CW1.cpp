#include <iostream>
#include <vector>
#include <limits.h>
#include <algorithm>
#include <queue>
using namespace std;

// Sliding Window Technique
// basically, this has 3 types of problems:
// 1. Fixed Size Window
// 2. Variable Size Window
// 3. Two Pointer Approach

// Naturally, we can work to further optimize the above questions with advanced data structures like heap, map, set, etc.

// Q1. Sliding Window Maximum (Leetcode-239)
vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    deque<int> dq;
    vector<int> ans;

    // Process first k elements
    for(int i=0;i<k;i++){
        // current element se jo bhi chote hai, unhe hatta do. In this way, we get max of current window
        while(!dq.empty() && nums[dq.back()]<nums[i]){
            dq.pop_back();
        }
        dq.push_back(i); // Index ko hi insert karna hai cause 
    }
    
    ans.push_back(nums[dq.front()]); // Store ans for first window

    // Process next windows ka ans
    for(int i=k;i<nums.size();i++){
        // Removal
        if(!dq.empty() && i - dq.front() >= k){ // matlab agar current index is out of range, so we remove that from deque. We check it my the formula current - front >=k, means violation hence remove kar do
            dq.pop_front();
        }
        // Addition
        while(!dq.empty() &&  nums[dq.back()]<nums[i]){
            dq.pop_back();
        }
        dq.push_back(i); // Index ko hi insert karna hai cause 

        // Storage
        ans.push_back(nums[dq.front()]);
    }

    return ans;
}

// Q2. Max Sum Subarray of size K - (GFG)
long maximumSumSubarray(int K, vector<int> &Arr , int N){
    long maxi = INT_MIN;
    long subarraySum = 0;
    for(int i=0;i<K;i++){
        subarraySum+=Arr[i];
    }
    maxi = max(maxi,subarraySum);
    
    for(int i=K;i<N;i++){
        // Removal of previous element
        subarraySum -= Arr[i-K];
        
        // Addition of current element
        subarraySum += Arr[i];
        
        // Updation
        maxi = max(maxi,subarraySum);
    }
    
    return maxi;
}

// Q3. Minimum Size Subarray Sum - (LC-209)
int minSubArrayLen(int target, vector<int>& nums) {
    int start = 0;
    int end = 0;
    int sum = 0;

    int mini = INT_MAX;

    while(end < nums.size()){
        sum = sum + nums[end]; // add humesha end se karte hai
        
        // Case A : Answer not found, toh window shorten kar do i.e. start badha do. Abh, since yaha multiple start updation ho sakte hai, use while loop
        while(sum >= target){
            // minimise
            if(sum>=target){
                mini = min(mini,end-start+1);
            }
            // current element which is pointed by start, should be removed from overall sum
            sum = sum - nums[start];
            start++;
        }

        // Case B : Also, upar walle loop se exit ho gaye, matlab guarantee hai ki sum < target, toh matlab answer found, so store and expand windown i.e. end badha do
        end++; 
    }

    if(mini==INT_MAX) return 0;
    else return mini;

}

// Q4. Binary Subarrays With Sum (LC-930)
int numSubarraysWithSum(vector<int>& nums, int goal) {
    int start = 0;
    int end = 0;
    int sum = 0;
    int count = 0;

    int prefixZero = 0;

    while(end<nums.size()){
        sum = sum + nums[end]; // add humesha end se karte hai
        
        while(start<end && (sum>goal || nums[start]==0)){
            // Update prefixZero based on start position
            if(nums[start]==1){
                prefixZero = 0;
            }
            else{
                prefixZero += 1;
            }

            // Sum mein se start walle ko minus kar do
            sum = sum - nums[start];

            // Update start
            start++;
        }

        if(sum==goal){
            count += prefixZero + 1; // Means prefix zero ka answer jo pehele bana hogo, and current walle ka
        }

        // If we have reached here, means we are left with no choice but to expand the window
        end++;
    }

    return count;
}


// Q5. Two Sum (LC-1)
vector<int> twoSum(vector<int>& nums, int target) {
    vector<pair<int,int>> arr; // {value,index}
    for(int i=0;i<nums.size();i++){
        int value = nums[i];
        int index = i;

        arr.push_back({value,index});
    }
    // Now, we sort the above as it sorts on the basis of value
    sort(arr.begin(),arr.end());

    int start = 0;
    int end = nums.size() - 1;
    vector<int> ans;

    while(start<end){
        int sum = arr[start].first + arr[end].first;
        if(sum==target){
            ans.push_back(arr[start].second);
            ans.push_back(arr[end].second);
            return ans;
        }
        else if(sum>target){
            end--;
        }
        else{
            start++;
        }
    }

    return ans;
}

// Q6. Minimum Window Substring (LC-76)
// In case of TLE, use vector instead of map for faster access
string minWindow(string s, string t) {
    int len1 = s.length();
    int len2 = t.length();

    if(len1<len2){ // Invalid case
        return "";
    }

    int ansIndex = -1;
    int ansLen = INT_MAX;

    unordered_map<char,int> sMap;
    unordered_map<char,int> tMap;
    for(auto ch:t){ // Store exact frequency of each character in string 't'
        tMap[ch]++;
    }

    int start = 0;
    int end = 0;
    int count = 0; // Basically shows count of actual pattern walli string ke chars present in current window. Yaani saare count's of chars in current window which are the same in "t" string
    while(end < len1){
        char ch = s[end];
        sMap[ch]++; // Update frequency of current char in sMap

        if(sMap[ch] <= tMap[ch]){ // agar current count of this char <= required count, toh count badha do
            count++;
        }

        if(count==len2){
            // yaha aa gaye, matlab ek window mil gayi hai jismein poora pattern exist karta hai, toh minimise window by using start
            // here, we will only minimise till the char at start index is extra in current window from the required pattern
            while(sMap[s[start]] > tMap[s[start]]){
                sMap[s[start]]--;
                start++;
            }

            // abh, anwer nikal lo
            int windowLen = end - start + 1;
            if(windowLen<ansLen){
                ansLen = windowLen;
                ansIndex = start;
            }
        }
        end++;
    }

    if(ansIndex == -1) return "";
    else return s.substr(ansIndex,ansLen);
}

// General summary of what kind of problem can/ cannot solved by Two Pointers - [https://leetcode.com/problems/subarray-sum-equals-k/discuss/301242/General-summary-of-what-kind-of-problem-can-cannot-solved-by-Two-Pointers]
// You may come up with two pointers/ sliding window technique at the very begin thought, which is not right after you have tried. Here is the general summary to expalin why we can not apply two pointers to solve this problem.

// Let go through the process of explanation by introducing what kind of problem can be solved with two pointers, such that if this problem doesn't match the criteria, it cannot be solved with two pointers.

// A problem can be solved by two pointers when two pointers come into place to help us reduce the total cases we need to consider, such that the corresponding time complexity will reduce too.

// Let's trying to solve longest-substring-without-repeating-characters firstly, which is a problem that can be solved by two pointers. After that, I will generalize the characteristics of that problem, such that we can know what kind of problem can be solved by two pointers.

// Given a string, find the length of the longest substring without repeating characters.

// Example 1:

// Input: "abcabcbb"
// Output: 3 
// Explanation: The answer is "abc", with the length of 3. 
// The very begin thought to solve problem above will be applying a brute-force solution, in which we maintain two index, i and j, such that for every i we test whether any possible j that form a substring s.substring(i,j)(both inclusive) doesn't contains repeating characters. This cost O(n^3).

// Now we need to find a better solution to reduce time complexity. The brute-force solution is not efficient, because it tests some cases that doesn't need to consider.

// case that are never valid: e.g., for Input: "abcabcbb", and i == 0, j ==3 such that we are testing substringabca right now. we found a repeating character a when seeing s.charAt(j) =='a', so we know that for a certain i == 0, the rightmost j will be j == 2 , because when j == 3 it contains repeating characters(s.charAt(3) =='a'), and when j == 4 it contains repeating characters(s.charAt(3) =='a') and when j == 5 it contains repeating characters(s.charAt(3) =='a'), ... and when j == n - 1 it still contains repeating characters(s.charAt(3) =='a').
// After oberserving that, we no long need to test every j such that j >= 3 when i == 0, so we can increase i by 1 .

// case that are included in the result already:
// Wait, after i = i + 1, what about j? Should j move left or move right or not move? Let go back to brute-force solution to get some intuition. In brute-force solution, whenever i++, the j should be j = i + 1. However if we apply j = i + 1, we still test some cases that should not being tested because they must be valid and they are included in the result alreay. For isntance, in case i == 0 and j == 3, we do i = i + 1 such that i becomes 1 now. we do not need to test case where i == 1 and j == 2 becuase we have tested case where i == 0 and j == 2, and it have been included in the result already. i == 1 and j == 2 is a sub case of i == 0 and j == 2, since result of i == 0 and j == 2 have been put in result, we no longer need to test i == 1 and j == 2. Consider if I tell you that I have 3 cats, will you doubt that I have at least 2 cats?

// So the result is we will make i++ and j stay at the same index before next round. (though in next round j++)

// Above is the specific problem that can be solved by two pinters. Now let's generalize the characteristics of the problems that can be solved by two pinters. The summary is simple:

// If a wider scope of the sliding window is valid, the narrower scope of that wider scope is valid mush hold.
// If a narrower scope of the sliding window is invalid, the wider scope of that narrower scope is invalid mush hold.
// With 2 rules above hold, we are able to optimize the brute-force solution to two pointers solution.

// I just show you what kind of question can be solved by two pointers by using some very simple Induction Reasoning. Now let me show you why this problem cannot be solved by two pointers. Like I said, If this problem doesn't meet the creteria that two pointer technique, it cannot be solved with two pointers.

// In this specific problem, rule 1 doesn't hold, because I can find a specific case such that it doesn't hold, e.g., if K is 3, 1,1,1 sum is 3, so 1,1,1, is valid, but 1,1 sum is 2 which means 1,1 is invalid, so rule 1 breaks.

// Rule2 doesn't hold, either, because I can find a specific case such that it doesn't hold, e.g., if K is 2, 1,1,1 sum is 3, so 1,1,1, is invalid, but 1,1,1,-1 sum is 2 which means 1,1,1,-1 is valid, so rule 2 breaks.