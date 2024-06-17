#include <iostream>
#include <queue>
using namespace std;

class ListNode{ // Singly Linked List
    public:
    
    int val; // Block which will store the data
    ListNode * next; // Block which will store the address of next pointer 

    ListNode(){ // Default Ctor
        this->next = NULL; // Point this Node towards NULL (Good industry practice)
    }

    ListNode(int data){ // Parameterized Ctor
        this->val = data; // set the current data to the given parameter 
        this->next = NULL; // Point this Node towards NULL (Good industry practice)
    }

};

// Q1. Remove Stones to Minimize the Total - LeetCode(1962)
int minStoneSum(vector<int>& piles, int k) {
    priority_queue<int> pq;

    for(int i=0;i<piles.size();i++){ // Push all elements into max heap
        int element = piles[i];
        pq.push(element);
    }

    while(k--){ // Perform the operation k times and update the heap
        int topElement = pq.top();
        pq.pop();

        pq.push(topElement - floor(topElement/2));
    }

    int ans = 0;

    while(!pq.empty()){ // Store the sum of all elements of heap
        ans += pq.top();
        pq.pop();
    }

    return ans;
}

// Q2. Reorganize String - LeetCode(767) - V.V.VIMP
class stringCount{
    public:
        char ch;
        int count;

        stringCount(char c,int value){
            this->ch = c;
            this->count = value;
        }
};

class myComp{
    public:
        bool operator()(stringCount a,stringCount b){
            return a.count < b.count;
        }
};

string reorganizeString(string s) {
    string ans = "";

    // 1. Count Frequency
    int freq[26] = {0}; // Here, we will map A-Z to 0-25 index
    for(int i=0;i<s.length();i++){
        char ch = s[i];
        freq[ch-'a']++; // ch - 'a' gets the alphabetical index of ch
    }

    // 2. Create MaxHeap to store string and it's freq;
    priority_queue<stringCount,vector<stringCount>,myComp> pq;

    for(int i=0;i<26;i++){
        if(freq[i]>0){
            stringCount temp(i+'a',freq[i]); 
            pq.push(temp);
        }
    }

    // 3. Now, we take out two top chars from max-Heap and keep on inserting them in ans
    while(pq.size()>1){
        stringCount top1 = pq.top();
        pq.pop();

        stringCount top2 = pq.top();
        pq.pop();

        ans.push_back(top1.ch);
        top1.count--;

        ans.push_back(top2.ch);
        top2.count--;

        if(top1.count>0){
            pq.push(top1);
        }

        if(top2.count>0){
            pq.push(top2);
        }
    }

    // 4. There might be a case where a single element is left, so we place a check on that before entering

    if(pq.size()==1){
        stringCount top1 = pq.top();
        pq.pop();

        ans.push_back(top1.ch);
        top1.count--;

        if(top1.count!=0){ // Means answer NOT POSSIBLE
            return "";
        }

    }

    return ans;
}

// Q3. Longest Happy String - LeetCode(1405) - V.V.V.VIMP
class happyString{
    public:
        char ch;
        int count;

        happyString(char c,int value){
            this->ch = c;
            this->count = value;
        }
};

class myComp2{
    public:
        bool operator()(happyString a,happyString b){
            return a.count < b.count;
        }
};

string longestDiverseString(int a, int b, int c) {
    // 1. Create a max heap based on custom comparator to store string and it's freq;
    priority_queue<happyString,vector<happyString>,myComp2> pq;

    // 2. Push the chars and their at most equried count
    if(a>0){
        happyString temp('a',a);
        pq.push(temp);
    }
    if(b>0){
        happyString temp('b',b);
        pq.push(temp);
    }
    if(c>0){
        happyString temp('c',c);
        pq.push(temp);
    }

    // 3. Now, we will take at most 2 of the top 2 max chars and push it into the ans string
    string ans = "";
    while(pq.size()>1){
        happyString top1 = pq.top();
        pq.pop();

        happyString top2 = pq.top();
        pq.pop();

        if(top1.count >=2){ // If has more than 2 count, add it two times and reduce the frequency count
            ans.push_back(top1.ch);
            ans.push_back(top1.ch);
            top1.count-=2;
        }
        else{ // Else, only push it once
            ans.push_back(top1.ch);
            top1.count--;
        }

        if(top2.count >=2 && top2.count >= top1.count){ // If has more than 2 count, add it two times and reduce the frequency count. Also, we make sure that 2nd has more count than first only then we push it two times (Greedy Apporach) so that we get the longest string.
            ans.push_back(top2.ch);
            ans.push_back(top2.ch);
            top2.count-=2;
        }
        else{ // Else, only push it once
            ans.push_back(top2.ch);
            top2.count--;
        }

        // Now, push the updated values back into the Heap
        if(top1.count>0){
            pq.push(top1);
        }

        if(top2.count>0){
            pq.push(top2);
        }
    }

    // 4. Now, there could be that one value is still left, so we handle that serperately
    if(pq.size()==1){
        happyString final = pq.top();
        pq.pop();

        if(final.count >=2){ // If has more than 2 count, add it two times and reduce the frequency count
            ans.push_back(final.ch);
            ans.push_back(final.ch);
            final.count-=2;
        }
        else{ // Else, only push it once
            ans.push_back(final.ch);
            final.count--;
        }
    }

    return ans;

}

// Q4. Median of a Stream - LeetCode(295) - V.V.V.V.VIMP
class MedianFinder {
public:
    double median;
    priority_queue<int> maxHeap;
    priority_queue<int,vector<int>,greater<int>> minHeap;

    MedianFinder() {
        median = 0.0;
    }
    
    void addNum(int num) {
        // CASES

        // 1. MaxHeap.size() is equal to MinHeap.size()
        if(maxHeap.size()==minHeap.size()){
            // 1. If num > median, then we push it in minimum
            if(num>median){
                minHeap.push(num);
                median = minHeap.top();
            }
            // 2. If num > median, then we push it in minimum
            else{
                maxHeap.push(num);
                median = maxHeap.top();
            }

        }
        // 2. MaxHeap.size() is '1' greator than MinHeap.size()
        else if(maxHeap.size()==minHeap.size()+1){
            // 1. If num > median, then we push it in minimum
            if(num>median){
                minHeap.push(num);
                median = minHeap.top();
            }
            // 2. If num > median, then we remove the top of MaxHeap and push it into minHeap, and then push new element into maxHeap
            else{
                int maxTop = maxHeap.top();
                maxHeap.pop();

                minHeap.push(maxTop);
                maxHeap.push(num);
            }

            median = (minHeap.top() + maxHeap.top())/2.0;

        }
        // 3. MinHeap.size() is '1' greator than MaxHeap.size()
        else if(minHeap.size()==maxHeap.size()+1){
            // 1. If num > median, then we remove the top of MinHeap and push it into maxHeap, and then push new element into minHeap
            if(num>median){
                int minTop = minHeap.top();
                minHeap.pop();

                maxHeap.push(minTop);
                minHeap.push(num);
                
            }
            // 2. If num > median, then we push it in maximum
            else{
                maxHeap.push(num);
                median = maxHeap.top();
                
            }

            median = (minHeap.top() + maxHeap.top())/2.0;

        }
    }
    
    double findMedian() {
        return median;
        
    }
};

