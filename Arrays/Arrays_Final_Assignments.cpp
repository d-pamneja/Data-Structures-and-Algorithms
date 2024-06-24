#include <iostream>
#include <limits.h>
#include <vector>
#include <limits.h>
#include <queue>
#include <set>
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