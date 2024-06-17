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

// Q1. Merge k Sorted Arrays - GFG - V.IMP
class kArrSort{
    public:
        int data;
        int rowIndex;
        int colIndex;

        kArrSort(int value,int row,int col){
            this->data = value;
            this->rowIndex = row;
            this->colIndex = col ;
        }
};

class myComp{
  public:
    bool operator()(kArrSort* a,kArrSort* b){
      return a->data > b->data; // Will give minimum value first based on the value
    };
};


vector<int> mergeKArrays(vector<vector<int>> arr, int K){
    int n = arr.size();
    vector<int> ans;
    priority_queue<kArrSort*,vector<kArrSort*>,myComp> pq; 

    // 1. Process the 0th index of k arrays 
    for(int row = 0;row<K;row++){
        int element = arr[row][0];
        kArrSort* temp = new kArrSort(element,row,0);
        pq.push(temp);
    }

    // 2. Run a loop till the priority queue is not empty
    while(!pq.empty()){
        kArrSort* top = pq.top();
        pq.pop();

        int topData = top->data;
        int topRow = top->rowIndex;
        int topCol = top->colIndex;
        
        ans.push_back(topData);

        // Now, push the next element of the same row from which the popped value was from

        if(topCol + 1 < n){
            int element = arr[topRow][topCol+1];
            kArrSort* newTemp = new kArrSort(element,topRow,topCol+1);
            pq.push(newTemp);
            
        }
        
    } 
    
    return ans;
}


// Q2. Merge K sorted linked lists - LeetCode(23) - V.IMP
class myComp2 {
    public:
        bool operator()(ListNode* a,ListNode* b){
            return a->val > b->val;
        };

};


ListNode* mergeKLists(vector<ListNode*>& lists) { 
    ListNode* head = NULL;
    ListNode* tail = NULL;

    // Create custom Min Heap
    priority_queue<ListNode*,vector<ListNode*>,myComp2> pq;

    // 1. Process first element of each linked list
    for(int i=0;i<lists.size();i++){
        ListNode* listHead = lists[i];
        if(listHead) // IMP
            pq.push(listHead);
    }

    // 2. 
    while(!pq.empty()){
        ListNode* topNode = pq.top();
        pq.pop();

        if(head==NULL){ // Means topNode is the first element
            head = topNode;
            tail = topNode;

            if(tail->next){ // If next of tail is not null, push it
                pq.push(tail->next);
            }

        }
        else{
            tail->next = topNode;
            tail = topNode;

            if(tail->next){ // If next of tail is not null, push it
                pq.push(tail->next);
            }
        }
    }

    return head;
    
}

// Q4. Smallest Range in K Lists (Leetcode-632) - V.V.V.V.V.VIMP
class kListRange{
    public:
        int data;
        int rowIndex;
        int colIndex;

        kListRange(int value,int row,int col){
            this->data = value;
            this->rowIndex = row;
            this->colIndex = col ;
        }
};

class myComp3{
  public:
    bool operator()(kListRange* a,kListRange* b){
      return a->data > b->data; // Will give minimum value first based on the value
    };
};

vector<int> smallestRange(vector<vector<int>>& nums) {
    vector<int> ans;
    priority_queue<kListRange*,vector<kListRange*>,myComp3> pq; 

    int maxi = INT_MIN; 
    int mini = INT_MAX; 

    // 1. Process first k-elements of each list
    for(int i=0;i<nums.size();i++){
        int element = nums[i][0];
        int row = i;
        int col = 0;

        maxi = max(maxi,element); 
        mini = min(mini,element);

        kListRange* temp = new kListRange(element,row,col);
        pq.push(temp);
    }      

    // 2. Create first range
    int ansStart = mini;
    int ansEnd = maxi;

    // 3. Run Loop to compare all ranges possible
    while(!pq.empty()){
        kListRange* topNode = pq.top();

        int topData = topNode->data;
        int topRow = topNode->rowIndex;
        int topCol = topNode->colIndex;

        pq.pop();

        mini = topNode->data; // New minimum

        // Since we already have the maximum from before, we straight away compare  for smaller ranges

        if((maxi-mini)<(ansEnd-ansStart)){ // If current range is smaller than existing range, update. V.V.V IMP
            ansStart = mini;
            ansEnd = maxi;
        }

        // Now, we have to insert the next element of the list whose element has been popped i.e. move to the next column of the SAME row 

        if(topCol+1 < nums[topRow].size()){
            int newElement = nums[topRow][topCol+1];
            maxi = max(maxi,newElement); // V.V.IMP

            kListRange* temp = new kListRange(newElement,topRow,topCol+1); 
            pq.push(temp);
        }
        else{ // Means that any one of the lists is over, hence the cycle ends as we need minimum one element from EACH list, hence exit
            break; // IMP
        }
    }

    ans.push_back(ansStart);
    ans.push_back(ansEnd);

    return ans;
}
