#include <iostream>
#include <limits.h>
#include <vector>
#include <limits.h>
#include <queue>
#include <set>
#include <unordered_set>
#include <stack>

using namespace std;

// Q1. Reverse an Array - All Approaches (GFG)
void solveusingRecursion(vector<int> &arr,int start,int end){
    if(start>=end){
        return;
    }

    arr[start] = arr[start] ^ arr[end];
    arr[end] = arr[end] ^ arr[start];
    arr[start] = arr[start] ^ arr[end];

    solveusingRecursion(arr,start+1,end-1);
}

void reverseArray(vector<int> &arr) {
    // Method 1 : New Array and store elements in reverse
    vector<int> nums(arr.size());
    for(int i=0;i<arr.size();i++){
        nums[i] = arr[(arr.size()-i)-1];
    }

    arr = nums;

    // Method 2: Two Pointer
    int start = 0;
    int end = arr.size() - 1;

    while(start<end){
        swap(arr[start],arr[end]);
        start++;
        end--;
    }

   // Method 3 : Using Recursion
    int start = 0;
    int end = arr.size() - 1;
    solveusingRecursion(arr,start,end);

    // Method 4: Using Stack
    stack<int> st;
    for(int i=0;i<arr.size();i++){
        st.push(arr[i]);
    }

    int i = 0;
    while(!st.empty()){
        arr[i] = st.top();
        st.pop();
        i++;
    }
}

// Q2. Find the "Kth" smallest element of an Array (GFG)
int kthSmallest(int arr[], int l, int r, int k) {
        // Method 1 : Sorting in place and giving kth Index : Brute Force
        sort(arr,arr+(r+1));
        return arr[k-1];;
        
        // // Method 2: Min Heap : Better
        // priority_queue<int,vector<int>,greater<int>> minHeap;
        // for(int i=l;i<r+1;i++){
        //     minHeap.push(arr[i]);
        // }
        
        // while(k-1){
        //     minHeap.pop();
        //     k--;
        // }
        
        // // Method 3: Max Heap : Best
        // priority_queue<int> maxHeap;
        // for(int i=l;i<k;i++){
        //     maxHeap.push(arr[i]);
        // }
        
        // for(int i=k;i<r+1;i++){
        //     if(arr[i]<maxHeap.top()){
        //         maxHeap.pop();
        //         maxHeap.push(arr[i]);
        //     }
        // }
    
        
        // return maxHeap.top();
        
    }

// Q3. Find the "Kth" largest element of an Array (LC-215)
int findKthLargest(vector<int>& nums, int k) {
    // Method 1: Sort in place and ans at n-k index : Brute Force
    if(nums.size()==0) return 0;
    sort(nums.begin(),nums.end()); 
    return nums[nums.size()-k];

    // Method 2: Max Heap : Better
    // priority_queue<int> maxHeap;
    // for(int i=0;i<nums.size();i++){
    //     maxHeap.push(nums[i]);
    // }

    // while(k-1){
    //     maxHeap.pop();
    //     k--;
    // }

    // Method 3: Min Heap :Best Method
    // priority_queue<int,vector<int>,greater<int>> minHeap;
    // for(int i=0;i<k;i++){
    //     minHeap.push(nums[i]);
    // }

    // for(int i=k;i<nums.size();i++){
    //     if(nums[i]>minHeap.top()){
    //         minHeap.pop();
    //         minHeap.push(nums[i]);
    //     } 
    // }


    // return minHeap.top();

}

// Q4. Intersection of Two Arrays (LC-349)
vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
    if(nums1.size()==0 || nums2.size()==0){
        return {};
    }

    set<int> st;
    vector<int> ans;

    sort(nums1.begin(),nums1.end());
    sort(nums2.begin(),nums2.end());

    int i = 0;
    int j = 0;

    while(i<nums1.size() && j < nums2.size()){
        if(nums1[i] == nums2[j]){
            st.insert(nums1[i]);
            i++;
            j++;
        }
        else if(nums1[i]<nums2[j]){
            i++;
        }
        else{
            j++;
        }
    }

    for(auto element:st){
        ans.push_back(element);
    }

    return ans;
}

// Q5. Union of Two Arrays (GFG)
int doUnion(int a[], int n, int b[], int m)  {
    // // Two Pointer Apporach
    // sort(a,a+n);
    // sort(b,b+m);
    
    // if(n==0 || m==0) return 0;
    
    // int i=0;
    // int j=0;
    
    // vector<int> ans;
    
    // while(i<n && j<m){
    //     if(a[i]==b[j]){
    //         ans.push_back(a[i++]);
    //         j++;
    //     }
    //     else if(a[i]<b[j]){
    //         ans.push_back(a[i++]);
    //     }
    //     else{
    //         ans.push_back(b[j++]);
    //     }
    // }
    
    // while(i<n){
    //     ans.push_back(a[i++]);
    // }
    
    // while(j<m){
    //     ans.push_back(b[j++]);
    // }
    
    // return ans.size();
    
    
    // Set Approach
    if(n==0 || m==0) return 0;
    
    set<int> st;
    int count = 0;
    
    for(int i=0;i<n;i++){
        st.insert(a[i]);
    }
    
    for(int j=0;j<m;j++){
        st.insert(b[j]);
    }
    
    for(auto element:st){
        count++;
    }
    
    return count;

}

// Q6. Minimum Jump to Reach End (GFG)
int minJumps(int arr[], int n){
    if(n==1){ // IMP Condition, yaha mein galti karta hoon
        return 0;
    }
    
    if(arr[0]==0){ // IMP Condition, yaha mein galti karta hoon
        return -1;
    }
    
    int count = 0;
    int farthest = 0;
    int current = 0;
    
    
    for(int i=0;i<n-1;i++){
        farthest = max(farthest,i+arr[i]);
        if(i==current){ // Agge future point pe current ko rakh do and wait karo
            count++;
            current = farthest;
        }
        
        if(current==n-1){ // Imp Condition for further optmisisation
            break;
        }
    }
    
    if(current<n-1){ // Agar akhri step tak bhi nahi reach kiye, toh nahi kar paaogay
        return -1;
    }
    
    return count;
}

// Q7. Find Duplicate in an Array (LC-287)
int findDuplicate(vector<int>& nums) {
    // // Brute Force - Sort and then check for repetition - TC : O(nLogn) SC(1)
    // sort(nums.begin(),nums.end());
    // int ans;
    // for(int i=0;i<nums.size()-1;i++){
    //     if(nums[i]==nums[i+1]){
    //         ans = nums[i];
    //         break;
    //     }
    // }
    // return ans;

    // //Negative Index Marking -> O(n) SC-> O(1)
    // int ans = -1;
    // for(int i = 0; i<nums.size();i++){
    //     int index = abs(nums[i]);

    //     // Check if already visited, then return
    //     if(nums[index]<0){
    //         ans = index;
    //         break;
    //     }
    //     nums[index] *= -1;
    // }
    // return ans;

    // // Optimised Approach - TC - O(N) SC-O(1)
    while(nums[0]!=nums[nums[0]]){
        swap(nums[0],nums[nums[0]]);    
    }

    return nums[0];
}

vector<vector<int>> merge(vector<vector<int>>& intervals) {
    // Array Apporach
    if(intervals.size()==0){
        return {{}};
    }
    if(intervals.size()==1){
        return intervals;
    }

    sort(intervals.begin(),intervals.end());

    vector<vector<int>> mergedIntervals;
    mergedIntervals.push_back(intervals[0]);

    for(int i=1;i<intervals.size();i++){
        vector<int> curr = intervals[i];
        vector<int> &prev = mergedIntervals.back(); // Remember to tak eby reference for updation

        if(curr[0]<=prev[1]){
            prev[1] = max(prev[1],curr[1]);
        }
        else{
            mergedIntervals.push_back(curr);
        }
    }

    return mergedIntervals;

    // Stack Approach
    // if(intervals.size()==0){
    //     return {{}};
    // }
    // if(intervals.size()==1){
    //     return intervals;
    // }

    // sort(intervals.begin(),intervals.end(),myComp);

    // stack<vector<int>> st;
    // st.push(intervals[0]);

    // for(int i=1;i<intervals.size();i++){
    //     vector<int> curr = intervals[i];
    //     vector<int> &prev = st.top(); // By reference to change value if interval merges

    //     if(curr[0]<=prev[1]){
    //         prev[1] = max(prev[1],curr[1]);
    //     }
    //     else{
    //         st.push(curr);
    //     }
    // }

    // vector<vector<int>> mergedIntervals;
    // while(!st.empty()){
    //     mergedIntervals.insert(mergedIntervals.begin(),st.top());
    //     st.pop();
    // }

    // return mergedIntervals;
}

// Q9. Concatenation of Array (LC-1929)
vector<int> getConcatenation(vector<int>& nums) {
    if(nums.size()==0) return {};

    vector<int> ans(2*nums.size());

    for(int i=0;i<nums.size();i++){
        ans[i] = nums[i];
    }

    int j = 0;
    for(int i=nums.size();i<2*nums.size();i++){
        ans[i] = nums[j++];
    }

    return ans;
}

// Q10. Next Permutation (LC-31)
void nextPermutation(vector<int>& nums) {
    // Brute Force - Using Queue and Map to generate all permutations, and giving (array's index + 1)th as answer. This will take TC -> O(n! * n), that is why it is a useless approach

    // Better Approach - Using STL Function next_permutation. This will also take TC -> O(n! * n)
    // next_permutation(nums.begin(),nums.end());
    
    // Optimal Approach - TC -> O(n), SC -> O(1)
    // 1. Find the first index where nums[index] < nums[index + 1]. That will be the pivot index
    // 2. Find the element just bigger than the pivot index, and swap the element with the element at pivot index
    // 3. Sort the array from (index + 1)th index till the end

    int n = nums.size();
    if(n<=1) return;
    int pivotIndex = -1; // Initialsie with -1, as the array could be the largest as well, which means it is the greatest permutation, so return sorted array

    for(int i=n-2;i>=0;i--){
        if(nums[i]<nums[i+1]){
            pivotIndex = i;
            break;
        }
    }

    if(pivotIndex == -1){
        sort(nums.begin(),nums.end());
        return;
    }

    for(int i=n-1;i>pivotIndex;i--){
        if(nums[i]>nums[pivotIndex]){
            swap(nums[pivotIndex],nums[i]);
            break;
        }
    }

    reverse(nums.begin()+pivotIndex+1,nums.end());
}

// Q11. Count Inversions in an Array (GFG)


// Q12. Best Time to Buy and Sell Stock (LC-121)
int maxProfit(vector<int>& prices) {
    // Optimal
    int n = prices.size();
    if(n<2) return 0;

    int maxProfit = 0; // Lowest profit will always be 0
    int minPrice = prices[0]; // Assuming that first day has the lowest price, IMP Condtion

    for(int i=1;i<n;i++){
        if(prices[i] > prices[i-1]){ // Matlab on ith day, we can see a stock with some profit, so we add it to maxProfit and maximise it
            maxProfit = max(maxProfit,prices[i] - minPrice);
        }
        else{ // Means we cannot sell today, so we can check if this is the lowest price day and store it to minPrice and minimise it
            minPrice = min(minPrice,prices[i]);
        }
    }

    return maxProfit; 
}

// Q13. Common in Three Sorted Arrays (GFG)
int remove_duplicate(int a[],int n){ // IMP Condition, yaha mein galti karta hoon iss fucntion mein
    if (n==0 || n==1)
        return n;
    
    int j = 0; // To store index of next unique element
    
    for (int i=0; i < n-1; i++)
        if (a[i] != a[i+1])
            a[j++] = a[i]; //Update the first occurence of an element at it's righful place, and skip others
    
    a[j++] = a[n-1]; // Store the last element
        
    return j;// Return the new size of the array
}

vector <int> commonElements (int A[], int B[], int C[], int n1, int n2, int n3){
    if(n1==0 || n2==0 || n3==0) return {};
    vector<int> ans;
    
    n1 = remove_duplicate(A,n1);
    n2 = remove_duplicate(B,n2);
    n3 = remove_duplicate(C,n3);
    
    int i = 0;
    int j = 0;
    int k = 0;
    
    while(i<n1 && j<n2 && k<n3){
        if(A[i]==B[j] && B[j]==C[k]){
            ans.push_back(A[i++]);
            j++;
            k++;
        }
        
        else if(A[i]<B[j]){
            i++;
        }
        
        else if(B[j]<C[k]){
            j++;
        }
        
        else{
            k++;
        }
    }
    
    
    return ans;
}

// Q14. Count Pairs with Given Sum (GFG)
int getPairsCount(int arr[], int n, int k) {
    // Brute Force -TC : O(N^2) - TLE
    // if(n<1) return n==k;
    // int count = 0;
    
    // for(int i=0;i<n-1;i++){
    //     int target = k - arr[i];
    //     if(target>0){
    //         for(int j = i+1;j<n;j++){
    //             if(arr[j]==target){
    //                 count++;
    //             }
    //         }
    //     }
    // }
    // return count;
    
    // // Better Approach : Sorting and Two Pointer : TC : O(NLogN)
    // sort(arr,arr+n);
    // int left = 0;
    // int right = n - 1;
    // int count = 0;
    
    // while(left<right){
    //     if(arr[left]+arr[right]==k){
    //         count++;
    //         int m = left + 1; // To handle duplicates
    //         while(m<right && arr[m]+arr[right]==k){
    //             m++;
    //             count++;
    //         }
    //         right--; // Finally when out of the above loop, means arr[m] + arr[right] > k, so move right backwards
    //     }
    //     else if(arr[left]+arr[right]<k){
    //         left++;
    //     }
    //     else{
    //         right--;
    //     }
    // }
    
    // return count;
    
    // Best Approach - Unordered Map - TC : O(N), SC:O(N)
    int count = 0;
    unordered_map<int,int> mp; // {element, frequency of element}
    
    for(int i=0;i<n;i++){
        int target = k - arr[i];
        
        if(target <0){
            continue;
        }
        
        if(mp[target]){
            count += mp[target];
        }
        
        mp[arr[i]]++;
    }
    
    return count;
}

// Q15. Subarray with 0 Sum (GFG)
bool subArrayExists(int arr[], int n){
    // // Brute Force Approach - TC: O(N^2), SC: O(1) - TLE
    // if(n<1) return false;
    // int sum=0;
    // for(int i=0;i<n-1;i++){
    //     sum=arr[i];
    //     if(sum==0) return true;
        
    //     for(int j=i+1;j<n;j++){
    //         sum+=arr[j];
    //         if(sum==0){
    //             return true;
    //         }
    //     }
    // }
    // return false;
    
    // Optimal Approach - Unordered Map - TC: O(N), SC: O(N)
    if(n<1) return false;
    
    unordered_map<int,bool> mp;
    int sum = 0;
    
    for(int i=0;i<n;i++){
        sum += arr[i];
        
        if(mp[sum] || sum==0){
            return true;
        }
        
        mp[sum] = true;
        
    }
    
    return false;
}

// Q16. Count Occurences More than n/k (GFG)
int countOccurence(int arr[], int n, int k) {
    // // Brute Force - Sorting - TC: O(NLogN), SC: O(N)
    // if(n<1) return 0;
    // sort(arr,arr+n);
    // int ans = 0;
    // int limit = n/k;

    // int count = 1; // count for current element, as voh minimum ek baar toh ayega hi
    // for(int i=1;i<n;i++){
    //     if(arr[i]==arr[i-1]){ // Means same element hai, so count++
    //         count++;
    //     }
    //     else{
    //         if(count > limit){ // Means unique element, so check limit for previous element
    //             ans++;
    //         }
    //         count = 1; // Reset count for next element, IMP CONDITION, yaha mein glati karta hoon
    //     }
    // }
    
    // // Perform the iteration for the last element
    // if(count > limit){
    //     ans++;
    // }
    
    // return ans;
    
    // Optimal Approach - Unordered Map - TC : O(N), SC: O(N)
    if(n<1) return 0;
    int count = 0;
    int limit = n/k;
    
    unordered_map<int,int> mp; // {element,frequency of that element}
    for(int i=0;i<n;i++){
        mp[arr[i]]++;
    }
    
    for(auto element:mp){
        if(element.second > limit){
            count++;
        }
    }
    
    return count;
}

// Q17. Triplet Sum in Array (GFG)
 bool find3Numbers(int A[], int n, int X){
    // // Brute Force - TC : O(N^3), SC : O(1)
    // if(n<3) return false;
    
    // for(int i=0;i<n-2;i++){
    //     for(int j=i+1;j<n-1;j++){
    //         int target = X - (A[i] + A[j]);
    //         for(int k = j+1;k<n;k++){
    //             if(A[k]==target){
    //                 return true;
    //             }
    //         }
    //     }
    // }
    
    // return false;
    
    // Best Approach - Unordered Map, find pairs of two (K-curr element) makes a number which can be made via pairs
    // TC - O(N^2), SC : O(N)
    if(n<3) return false;
    unordered_map<int,int> mp; // {element, frequency of element}
    
    for(int i=0;i<n-2;i++){
        int target = X - A[i];
        for(int j=i+1;j<n;j++){
            int currTarget = target - A[j];
            
            if(currTarget <0){
                continue;
            }
            
            if(mp[currTarget]){
                return true;
            }
            
            mp[A[j]]++;
        }
        mp.clear();
    }
    
    return false;
}

// Q18. Find Maximum Product Subarray (LC-152)
int maxProduct(vector<int>& nums) {
    // // Brute Force Approach - TC : O(N^2), SC: O(1)
    // int n = nums.size();
    // if(n<1) return 0;
    // if(n==1) return nums[0];
    // double maxi = INT_MIN;

    // for (int i = 0; i < n; i++) {
    //     double currProd = 1;
    //     for (int j = i; j < n; j++) {
    //         // Calculate product of current subarray
    //         currProd *= nums[j];

    //         // Update max_product if necessary
    //         maxi = max(maxi, currProd);
    //     }
    // }

    // return (int)maxi;

    // Optimal Approach - Modified Kadane's / Doge's/Chem's Algorithm - TC : O(N), SC : O(1)
    int n = nums.size();
    if(n<1) return 0;
    if(n==1) return nums[0];
    
    double maxi = INT_MIN;
    double currProd = 1;
    for(int i=0;i<n;i++){ // Left to Right, finding prefix multiplication
        currProd *= nums[i];
        maxi = max(maxi,currProd);
        
        if(currProd==0){
            currProd = 1;
        }
    }
    
    currProd = 1;
    
    for(int i=n-1;i>0;i--){ // Right to Left, finding sufix multiplication
        currProd *= nums[i];
        maxi = max(maxi,currProd);
        
        if(currProd==0){
            currProd = 1;
        }
    }
    
    return (int)maxi;
}

// Q19. Longest Consecutive Subsequence (LC-128)
bool linearSearchInArray(vector<int> &nums, int x){
    int N = nums.size();
    for(int i=0;i<N;i++){
        if(nums[i]==x){
            return true;
        }
    }
    
    return false;
}

int longestConsecutive(vector<int>& nums) {
        // // Brute Force - TC : O(N^2), SC : O(1)
    // if(N<1) return 0;
    // if(N==1) return 1;
    
    // int maxLen = 1;
    // for(int i=0;i<N;i++){
    //     int x = arr[i];
    //     int count = 1;
    //     while(linearSearchInArray(arr,x+1)){
    //         count++;
    //         x++;
    //     }
        
    //     maxLen = max(maxLen,count);
    // }
    
    // return maxLen;
    // Better Approach - Sorting and Updating - TC : O(NlogN), SC: O(1)
//   sort(nums.begin(),nums.end());
//   int N = nums.size();
//   if(N<1) return 0;
//   if(N==1) return 1;
    
//   int maxi = 1;
//   int currLen = 1;
    
//   for(int i=1;i<N;i++){
//       if(nums[i] - nums[i-1]==1){
//           currLen++;
//           maxi = max(maxi,currLen);
//       }
//       else{
//           if(nums[i]==nums[i-1]){
//               continue;
//           }
//           else{
//              currLen = 1;
//           }
//       }
//   }
    
//   return maxi;

    // Optimal Approach - Using Set and Checking for previous element - TC : O(N), SC : O(N)
    int N = nums.size();
    if(N<1) return 0;
    if(N==1) return 1;

    // Step 1. Push all elements into the set
    unordered_set<int> st;
    for(int i=0;i<N;i++){
    st.insert(nums[i]);
    }

    // Step 2. For each element, check if it's previous exists in set.
    // When we reach an element which does not have it's previous, means we have reached the starting point of the consecutive subsequence
    int maxi = 1;

    for(auto it:st){
    if(st.find(it-1)==st.end()){ // Matlab iske peeche ka element nahi hai, means this is the start of the subsequence
        int count = 1;
        int x = it;
        while(st.find(x + 1) != st.end()){
            count++;
            x++;
        }
        maxi = max(maxi,count);
    }
    }

    return maxi;
}

// Q20. Smallest Subarray with Sum Greater than x (GFG)
int smallestSubWithSum(int arr[], int n, int x){
    // // Brute Force Approach - TC : O(NlogN), SC : O(1)
    // if(n==0) return 0;
    // if(n==1) return arr[0]>x;
    
    // int mini = INT_MAX;
    // int left = 0;
    // int right = 0;
    // int currSum = 0;
    
    // while(right<n){
    //     currSum += arr[right++];
    //     while(currSum>x){
    //         mini = min(mini,right - left);
    //         currSum -= arr[left++];
    //     }
    // }
    
    // return mini == INT_MAX ? 0 : mini;
    
    // Optimal Approach - Sliding Windown - TC : O(N), SC : O(1)
    if(n==0) return 0;
    if(n==1) return arr[0]>x;
    
    int mini = INT_MAX;
    int left = 0;
    int currSum = 0;
    
    for(int right = 0;right<n;right++){
        currSum += arr[right];
        while(currSum>x){
            mini = min(mini,right - left + 1);
            currSum -= arr[left++];
        }
    }
    
    return mini == INT_MAX ? 0 : mini;
}

// Q21. Array Subset of another array (GFG)
string isSubset(int a1[], int a2[], int n, int m) {
    // // Better Approach - TC : O(NlogN + MlogM), SC : O(1)
    // if(n < 1 || m < 1) return "No";
    // sort(a1,a1+n);
    // sort(a2,a2+m);

    // int i = 0;
    // int j = 0;

    // while(i<n && j<m){
    //     if(a1[i]==a2[j]){
    //         j++;
    //     }
    //     i++;
    // }

    // if(j==m){ // Means reached end of sub array, matlab all elements present
    //     return "Yes";
    // }
    // else{
    //     return "No";
    // }

    // Optimal Approach - TC : O(max(N,M)), SC : O(N)
    if(n < 1 || m < 1) return "No";
    unordered_map<int,int> mp; // {element, frequency of element}

    for(int i=0;i<n;i++){
        mp[a1[i]]++;
    }

    for(int i=0;i<m;i++){
        if(mp.find(a2[i])!=mp.end()){
            if(mp[a2[i]]>0){
                mp[a2[i]]--;
            }
            else{
                return "No";
            }
        }
        else{
            return "No";
        }
    }

    return "Yes";
}

// Q22. Factorial of Large Numbers (GFG)
vector<int> factorial(int N){
    // Optimal Approach - TC : O(N^2), SC: O(N)
    if(N<1) return {0};
    if(N==1) return {1};
    
    vector<int> ans;
    ans.push_back(1); // Initilaise answer with N=1, and build the factorial from 2->n
    int carry = 0;
    
    for(int i = 2;i<=N;i++){
        for(int j = 0;j<ans.size();j++){
            int x = (ans[j]*i) + carry;
            ans[j] = x%10;
            carry = x/10;
        }
        
        while(carry){ // IMP CONDITION, yaha mein galti karta hoon
            ans.push_back(carry%10);
            carry /= 10;
        }
    }
    
    reverse(ans.begin(),ans.end());
    return ans;
}

// Q23. Palindrome Array (GFG)
bool isPalindrome(int x){
    string str = to_string(x);
    
    int i = 0;
    int j = str.size() - 1;
    
    while(i<j){
        if(str[i]!=str[j]){
            return false;
        }
        i++;
        j--;
    }
    
    return true;
}

int PalinArray(int a[], int n){
    if(n<1) return 0;
    
    for(int i=0;i<n;i++){
        if(!isPalindrome(a[i])){
            return 0;
        }
    }
    
    return 1;
}

// Q24. Three way partitioning (GFG)
void threeWayPartition(vector<int>& array,int a, int b){
    // // Brute Force - TC : O(N), SC: O(N)
    // if(array.size()<1) return;
    
    // vector<int> arr1;
    // vector<int> arr2;
    // vector<int> arr3;
    
    // for(int i=0;i<array.size();i++){
    //     if(array[i]<a){
    //         arr1.push_back(array[i]);
    //     }
    //     else if(array[i]>=a && array[i]<=b){
    //         arr2.push_back(array[i]);
    //     }
    //     else if(array[i]>b){
    //         arr3.push_back(array[i]);
    //     }
    // }
    
    // vector<int> ans;
    
    // for(int i=0;i<arr1.size();i++){
    //     ans.push_back(arr1[i]);
    // }
    
    // for(int i=0;i<arr2.size();i++){
    //     ans.push_back(arr2[i]);
    // }
    
    // for(int i=0;i<arr3.size();i++){
    //     ans.push_back(arr3[i]);
    // }
    
    // array = ans;

    // Optimal Approach - Swapping - TC: O(N), SC: O(1)
    if(array.size()<1) return;
    int last = 0;
    
    for(int i=0;i<array.size();i++){
        if(array[i]<a){
            swap(array[i],array[last]);
            last++;
        }
    }
    
    for(int i=0;i<array.size();i++){
        if(array[i]>=a && array[i]<=b){
            swap(array[i],array[last]);
            last++;
        }
    }
    
    return;
}

// Q25. Chocolate Distribution Problem (GFG)
long long findMinDiff(vector<long long> a, long long n, long long m){
    // Optimal Approach - Sliding Window - TC : O(NlogN), SC : O(1)
    if(n<1 || m<1 || n<m) return 0;

    sort(a.begin(),a.end());

    long long mini = a[0];
    long long maxi = a[m-1]; 
    long long diff = maxi - mini;
    
    int j = 0;
    for(long long i=m;i<n;i++){
        mini = a[++j];
        maxi = a[i];
        
        diff = min(diff,maxi-mini);
    }
    
    return diff;
} 

// Q26. Trap Rain Water (LC-42)
int trap(vector<int>& height) {
    // Optimal Approach - Preprocess Array - TC : O(N), SC: O(N)
    if(height.size()<1) return 0;
    int totalCapacity = 0;

    // Step 1. Preprocess max element till now from left
    vector<int> left(height.size());
    left[0] = height[0];
    for(int i=1;i<height.size();i++){
        left[i] = max(height[i],left[i-1]);
    }

    // Step 2. Preprocess max element till now from right
    vector<int> right(height.size());
    right[height.size()-1] = height[height.size()-1];
    for(int i=height.size()-2;i>=0;i--){
        right[i] = max(height[i],right[i+1]);
    }

    // Step 3. Add to total capacity based on formula
    for(int i=0;i<height.size()-1;i++){
        totalCapacity += min(left[i],right[i]) - height[i];
    }

    return totalCapacity;
}

// Q27 Median of Two Sorted Arrays (LC-4)
 double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
    if(nums1.size()<1 && nums2.size()<1){
        return (double)0;
    }

    // // Brute Force Approach - Merge Both Arrays into one sorted array - TC : O(N+M), SC : O(N+M)
    // vector<int> arr;
    // int i = 0;
    // int j = 0;

    // while(i<nums1.size() && j<nums2.size()){
    //     if(nums1[i]<=nums2[j]){
    //         arr.push_back(nums1[i++]);
    //     }
    //     else{
    //         arr.push_back(nums2[j++]);
    //     }
    // }

    // while(i<nums1.size()){
    //     arr.push_back(nums1[i++]);
    // }

    // while(j<nums2.size()){
    //     arr.push_back(nums2[j++]);
    // }

    // int size = arr.size();
    // if(size&1){
    //     double ans = arr[(size-1)/2];
    //     return ans;
    // }
    // else{
    //     int first = (size/2) - 1;
    //     double ans = (arr[first] + arr[first + 1])/(double)2;
    //     return ans;
    // }

    // Optimal Approach - Binary Search Method + Partition - TC : O(log(min(N,M))), SC : O(1)
    // IMP QUES, DRY RUN MULTIPLE TIMES
    int n1 = nums1.size();
    int n2 = nums2.size();

    int n = n1 + n2;

    if(n1 > n2){
        return findMedianSortedArrays(nums2,nums1);
    }

    // Step 1. Create a search space (this is for the number of elements we will take from the first array). Here, n1 < n2, so we take n1 as end point to reduce computation complexity.
    int low = 0;
    int high = n1;

    int left = (n1 + n2 + 1)/2; 

    while(low<=high){
        int mid1 = ((high - low)/2) + low;
        int mid2 = left - mid1;

        // Setting l1,l2,r1,r2

        int l1 = INT_MIN;
        int l2 = INT_MIN;

        int r1 = INT_MAX;
        int r2 = INT_MAX;

        if(mid1<n1){
            r1 = nums1[mid1];
        }

        if(mid2<n2){
            r2 = nums2[mid2];
        }

        if(mid1 - 1 >=0){
            l1 = nums1[mid1-1];
        }

        if(mid2 - 1 >=0){
            l2 = nums2[mid2-1];
        }

        // Comparision
        if(l1<=r2 && l2<=r1){
            if(n%2==1){ // Odd Case
                return max(l1,l2);
            }
            else{
                double ans = (double)(max(l1,l2) + min(r1,r2))/2.0;
                return ans;
            }
        }

        else if(l1 > r2){
            high = mid1 - 1;
        }
        else{
            low = mid1 + 1;
        }

    }

    return double(0);
}

// Q28. Set Matrix Zeroes (LC-73)
void setZeroes(vector<vector<int>>& matrix) {
    if(matrix.size()<1) return;
    int m = matrix.size();
    int n = matrix[0].size();
    // // Brute Force - Using Another Matrix - TC : O((N+M)*(N*M)), SC : O(N*M)
    // vector<vector<int>> visited = matrix;

    // for(int i=0;i<m;i++){
    //     for(int j=0;j<n;j++){
    //         if(matrix[i][j]==0){

    //             for(int k =0;k<n;k++){
    //                 visited[i][k] = 0;
    //             }

    //             for(int k =0;k<m;k++){
    //                 visited[k][j] = 0;
    //             }
    //         }
    //     }
    // }

    // matrix = visited;
    // return;

    // Better Approach - Iterating using Two Nested Loops and Stack - TC : O(M*N), SC : O(min(M,N)) [As in worst case, stack will either have all rows or all cols]

    // // First, store all indices where there is a 0
    // stack<pair<int,int>> st;
    // for(int i=0;i<m;i++){
    //     bool flag = false;
    //     int row = -1;
    //     int col = -1;

    //     for(int j=0;j<n;j++){
    //         if(matrix[i][j]==0){
    //             flag = true;
    //             row = i;
    //             col = j;
    //             st.push({row,col});
    //         }
    //     }

    // }

    // while(!st.empty()){
    //     auto top = st.top();
    //     st.pop();

    //     int row = top.first;
    //     int col = top.second;

    //     for(int i=0;i<n;i++){
    //         matrix[row][i] = 0;
    //     }

    //     for(int j=0;j<m;j++){
    //         matrix[j][col] = 0;
    //     }
    // }

    // return;

    // Optimal Approach - Using two variables and updating in constant space - TC: O(M*N), SC: O(1)

    bool isRow0 = false;
    bool isCol0 = false;

    // Step 1. Agar 0th row and col mein koi bhi 0 hai, set variable as true
    for(int i=0;i<m;i++){
        if(matrix[i][0]==0){
            isCol0 = true;
        }
    }

    for(int j=0;j<n;j++){
        if(matrix[0][j]==0){
            isRow0 = true;
        }
    }

    // Step 2: If we now see any 0, we will make the corresponding row no. and column no. equal to 0 in the 0th column and 0th row respectively
    for(int i=1;i<m;i++){
        for(int j=1;j<n;j++){
            if(matrix[i][j]==0){
                matrix[i][0]=0;
                matrix[0][j]=0;
            }
        }
    }

    // Step 3: Now we will update the values of the matrix except first row and first column to 0 if matrix[i][0]=0 or matrix[0][j]=0 for any (i,j).
    for(int i=1;i<m;i++){
        for(int j=1;j<n;j++){
            if(matrix[0][j]==0 || matrix[i][0]==0)
                matrix[i][j]=0;
        }
    }
    
    // Step 4: finally we will traverse the 0th row and 0th column and if we find any 0, we will make the whole row and whole column equal to 0
    if(isRow0){
        for(int j=0;j<n;j++)
            matrix[0][j]=0;
    }
    
    if(isCol0){
        for(int i=0;i<m;i++)
            matrix[i][0]=0;
    }

    return;
}

// Q29. Subarray Sum Equals K (LC-560)
int subarraySum(vector<int>& nums, int k) {
    if(nums.size()<1) return 0;
    if(nums.size()==1) return nums[0]==k;
    int count = 0;

    // // Brute Force - Make all subarrays and if matches with target, store - TC : O(N^2), SC : O(1)
    // for(int i = 0; i < nums.size(); i++){
    //     int sum = nums[i];
        
    //     if(sum == k){
    //         count++;
    //     }
        
    //     for(int j = i + 1; j < nums.size(); j++){
    //         sum += nums[j]; 
            
    //         if(sum == k){
    //             count++;
    //         }
    //     }
    // }

    // return count;

    // Optimal Apporach - Using Map and Logic - TC : O(N), SC : O(N)
    // Here, we cannot use two pointers
    vector<int> prefix(nums.size());
    int sum = 0;

    // Step 1: Create prefix sum array
    for(int i=0;i<nums.size();i++){
        sum += nums[i];
        prefix[i] = sum;
    }

    // Step 2: In map, traverse and check if there exists prefix[i] - k, means count increases by the frequency with which (prefix[i] - k) exists
    unordered_map<int,int> mp; //{element,frequency}
    for(int i=0;i<nums.size();i++){

        if(prefix[i]==k){
            count++;
        }

        if(mp.find(prefix[i]-k)!=mp.end()){ // Matlab current index and starting ke beech mein sum k hua hai, so add kar do kinti baar sum k hua hai
            count += mp[prefix[i]-k];
        }

        mp[prefix[i]]++;
    }

    return count;
} 

// Q30. 
