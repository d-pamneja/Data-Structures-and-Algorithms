#include <iostream>
#include <queue>
using namespace std;


class Node {
public:
  int data;
  Node *left;
  Node *right;

  Node(int val) {
    this->data = val;
    this->left = NULL;
    this->right = NULL;
  }
};

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Info{
  public:
    int maxVal;
    bool isHeap;

  Info(int value,bool isHeap){
    this->maxVal = value;
    this->isHeap = isHeap;
  }
    
};

// Q1. Kth Largest Element in an Array - LeetCode(215)
int findKthLargest(vector<int>& nums, int k) {

    // // Unoptimised (Using Max-Heap) TC:O(n) SC:O(n)
    //priority_queue<int> pq;
    // for(int i=0;i<nums.size();i++){ // Push all elements into the queue
    //     pq.push(nums[i]);
    // }

    // for(int i=0;i<k-1;i++){ // Pop first (k-1) elements
    //     pq.pop();
    // }

    // Optimised (Using Min-Heap) TC:O(n) SC:O(k)
    priority_queue<int,vector<int>,greater<int> > pq; // Min Heap


    for(int i=0;i<k;i++){ // Push the first k elements into the queue
        pq.push(nums[i]);
    }

    for(int i=k;i<nums.size();i++){ // Next, we push elements smaller than the top into the queue
        if(nums[i]>pq.top()){
            pq.pop();
            pq.push(nums[i]);
        }
    }


    return pq.top(); // Kth Largest will be on top
}

// Q2. Find Kth Smallest Element in an Array
int getKthSmallest(int nums[], int size, int k){ // (Using Max-Heap) TC:O(n) SC:O(k)
  priority_queue<int> pq;
  for(int i=0;i<k;i++){ // Push the first k elements into the queue
      pq.push(nums[i]);
  }

  for(int i=k;i<size;i++){ // Next, we push elements smaller than the top into the queue
      if(nums[i]<pq.top()){
          pq.pop();
          pq.push(nums[i]);
      }
  }

  return pq.top();
}

// Q3. Check if a Binary Tree is a Heap - GFG
bool isHeap(struct Node* root) { // TC:O(N) SC:O(N)
    if(root==NULL ){
        return true;
    }
    
    if((root->left==NULL) && (root->right==NULL)){
        return true;
    }
    
      // LRN
      bool leftAns = isHeap(root->left);
      bool rightAns = isHeap(root->right);
    
      // Processing
      if(leftAns && rightAns){
          if((root->left->data < root->data) && (root->right->data < root->data)){
              return true;
          }
          else{
              return false;
          }
      }  
      else{
        return false;
      }
}

// Q4. Check if a Binary Tree is a Heap - LeetCode(958)
bool isCompleteTree(TreeNode* root) {    // TC:O(N) SC:O(N)
    // Using variant of Level Order Traversal   
    queue<TreeNode*> q;
    q.push(root);
    bool nullFound = false;

    while(!q.empty()){
        TreeNode* front = q.front();
        q.pop();

        if(front==NULL){
            nullFound = true;
        }
        else{
            if(nullFound){ // Means if ever we found a Null Node before and now a non-Null Node appears, means there is a missing CBT Node, hence we return false
                return false;
            }
            q.push(front->left);
            q.push(front->right);
        }
    }
    return true;
}

// Q5. Convert a Binary Tree to a Max Heap - GFG
void CreateInorder(Node* root, vector<int> &inorder){
    if(root==NULL){
        return;
    }
    
    // LNR
    CreateInorder(root->left,inorder);
    
    inorder.push_back(root->data);
    
    CreateInorder(root->right,inorder);
}
  
void replaceUsingPostOrder(Node* &root, vector<int> &inorder, int &index){
    if(root==NULL){
        return;
    }
    
    // LRN
    
    replaceUsingPostOrder(root->left,inorder,index);
    replaceUsingPostOrder(root->right,inorder,index);
    
    root->data = inorder[index]; // Replace the value of current node with it's supposed inorder value
    index++;
      
}
  
void convertToMaxHeapUtil(Node* root){ // TC:O(N) SC:O(N)
    // Store Inorder of the Tree
    vector<int> inorder;
    
    CreateInorder(root,inorder);
    
    // Replace Node Values with Inorder Traversal
    int index = 0;
    replaceUsingPostOrder(root,inorder,index);
    
}





int main(){
    return 0;
}