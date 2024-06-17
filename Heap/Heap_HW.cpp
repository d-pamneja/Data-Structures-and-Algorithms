#include <iostream>
#include <queue>
#include <limits.h>
using namespace std;

class Node {
public:
  int key;
  Node *left;
  Node *right;

  Node(int val) {
    this->key = val;
    this->left = NULL;
    this->right = NULL;
  }
};

// Q1. Check if a Binary Tree is a Heap - GFG
int totalCount(struct Node* root){
    if(root==NULL){
        return 0;
    }

    // NLR
    int l = totalCount(root->left);
    int r =  totalCount(root->right);
    return  1 + l + r;
}

bool isCBT(struct Node* root, int index, int totalNodes){
    if(root==NULL){
        return true;
    }
    
    if(index>totalNodes){
        return false;
    }
    
    // Simple check if there exists an index greater than total nodes, means not a CBT
    bool leftSubTree = isCBT(root->left,2*index,totalNodes);
    bool rightSubTree = isCBT(root->right,2*index + 1,totalNodes);
    
    return (leftSubTree && rightSubTree);

}

bool isMaxOrder(struct Node* root){
    if(root==NULL){ // If NULL nodes, means nothing to compare, hence assume true
        return true;
    }
    
    bool left = isMaxOrder(root->left);
    bool right = isMaxOrder(root->right);
    int ans = false; // Starting flag to store the final answer in based on conditions
    
    // Here, the case of only right child will not come, as that already will be rejected in the CBT function 
    
    
    // Processing
    if(!root->left && !root->right){ // Case 1. If leaf node, means in max order
        ans =  true;
    }
    
    else if(root->left && !root->right){ // Case2. If only left child
        ans =  root->key > root->left->key;
    }
    
    else{ // Case 3. If both left and  right child
        ans = (root->key > root->left->key) && (root->key > root->right->key);
    }
    
    return ans && left && right;
}

bool isHeap(struct Node* root) { // TC:O(n) SC:O(n)
    int totalNodes = totalCount(root);
    int index = 1; // A heap is suppose to start from '1' in 1-based indexing, hence we assume this
    
    return isCBT(root,index,totalNodes) && isMaxOrder(root);
}

// Q2.  Merge two Binary Heaps - GFG - V.V.V.V.IMP

void heapify(vector<int> &ans,int index,int size){ // TC:O(logn) SC:O(1)
    while(true){
        // 0 based indexing
        int leftIndex = 2 * index + 1;
        int rightIndex = 2 * index + 2;
        
        int maxIndex = index;
        
        if(leftIndex<size && ans[leftIndex] > ans[maxIndex]){
            maxIndex = leftIndex;
        }
        if(rightIndex<size && ans[rightIndex] > ans[maxIndex]){
            maxIndex = rightIndex;
        }
        
        if(maxIndex==index){
            break;
        }
        
        swap(ans[maxIndex],ans[index]);
        index = maxIndex;
    }
}


vector<int> mergeHeaps(vector<int> &a, vector<int> &b, int n, int m) { // TC:O(nlogn) SC:O(n+m)
    vector<int> ans(a.begin(),a.end());
    ans.insert(ans.end(),b.begin(),b.end());
    
    for(int i=(ans.size()/2)-1;i>=0;i--){ // Since we will heapify all EXCEPT leaf nodes
        heapify(ans,i,ans.size());
    }

    // // Direct Approach
    // // 1. Push all elements of both arrays in MaxHeap
    // priority_queue<int> pq;
    
    // for(int i=0;i<n;i++){
    //     pq.push(a[i]);
    // }
    
    // for(int i=0;i<m;i++){
    //     pq.push(b[i]);
    // }
    
    // // 2. Create final answer from MaxHeap
    
    // vector<int> ans;
    
    // while(!pq.empty()){
    //     int top = pq.top();
    //     pq.pop();
        
    //     ans.push_back(top);
    // }
    
    return ans;
    
}

// Q3. K Closest Points to Origin - LeetCode(973) - V.V.VIMP
class kClose{
    public:
        vector<int> arr;
        double distance;

        kClose(vector<int> point,double value){
            this->arr = point;
            this->distance = value;
        }
};

class myComp{
    public:
        bool operator()(kClose* a,kClose* b){
            return a->distance > b->distance;
        }
};


vector<vector<int>> kClosest(vector<vector<int>>& points, int k) { // TC:O(nlogn) SC:O(n)

    vector<vector<int>> ans;
    priority_queue<kClose*,vector<kClose*>,myComp> pq; // Create custom minHeap

    // 1. Find the distance and push the point along with it's distance to minHeap
    for(int i=0;i<points.size();i++){
        vector<int> point = points[i];
        double distance = sqrt(pow((point[0] - 0),2.0) + pow((point[1] - 0),2.0)); // IMP : Chance of mistake high
        kClose* temp = new kClose(point,distance);
        pq.push(temp);
    }

    while(k--){
        kClose* top = pq.top();
        pq.pop();

        ans.push_back(top->arr);
    }

    return ans;

}

// Q4. Sliding Window Maximum - LeetCode(239) - IMP
vector<int> maxSlidingWindow(vector<int>& nums, int k) { // TC:O(nlogn) SC:O(n)
    priority_queue<pair<int,int>> pq; // MaxHeap with Pair<value,index>
    vector<int> ans;

    for(int i=0;i<k;i++){ // Push elements of first window in MaxHeap
        pq.push({nums[i],i});
    }

    ans.push_back(pq.top().first);

    // Now, we keep on pushing new elements adding the top given that it is a part of our permissable window indexs
    for(int i=k;i<nums.size();i++){
        pq.push({nums[i],i});

        // Remove if the present max is from previous index
        while(pq.top().second <= i - k){
            pq.pop();
        }

        ans.push_back(pq.top().first);
    }

    return ans;
}

// Q5. Rhombus Sum - LeetCode(1878) - V.IMP
bool checkBounds(vector<vector<int>>& grid,vector<pair<int,int>> &v){ // Will tell if all points are within the range or not, if any one violates, returns false
    int m = grid.size();
    int n = grid[0].size();

    for(auto p:v){
        if(p.first < 0 || p.second >= n || p.first >= m || p.second < 0){
            return false;
        }
    }
        
    return true;
}


bool getAllVertices(vector<vector<int>>& grid,vector<pair<int,int>> &v,pair<int,int> p,int &delta){ // Will tell whether we can get the vertices or not from a given center

    // Visualise the rhombus as connected by points A,B,C,D 
    pair<int,int> A(p.first - delta,p.second); // To move up, we reduce from row and col stays the same
    pair<int,int> B(p.first ,p.second + delta); // To move right, we add to col and row stays the same
    pair<int,int> C(p.first + delta,p.second); // To move down, we add to row and col stays the same  
    pair<int,int> D(p.first,p.second - delta); // To move left, we reduce from col and row stays the same

    // Now, push the above points to vector
    v[0] = A;
    v[1] = B;
    v[2] = C;
    v[3] = D;

    if(checkBounds(grid, v)){
        return true;
    }

    return false;
}

// TC:O(m*n) SC:O(m*n)
void getAllSum(vector<vector<int>>& grid,int &cx,int &cy,priority_queue<int> &pq){ // Will give the sum of each rhombus originaring at the given {cx,cy} point and all possible rhombus from it
    // First, we push this point itself into the maxHeap, as it to can be a rhombus of area 0
    pq.push(grid[cx][cy]);
    // Now, we will consider this given cell and keep on creating rhombus around this cell using the marker 'delta'

    int delta = 1;

    vector<pair<int,int>> v(4); // since a rhombus can be only 4 points, we will store 4 points into this

    while(getAllVertices(grid,v,{cx,cy},delta)){
        pair<int,int> &A = v[0]; // Upper point
        pair<int,int> &B = v[1]; // Righter point
        pair<int,int> &C = v[2]; // Lower point
        pair<int,int> &D = v[3]; // Lefter point

        int currSum = grid[A.first][A.second] + grid[B.first][B.second] + grid[C.first][C.second] + grid[D.first][D.second]; // The current sum of all the points

        // Now, we need the sum of all cells between A and B and add it to currSum
        for(int i=1;i<B.first-A.first;i++){
            currSum += grid[A.first + i][A.second + i];
        }

        // Now, we need the sum of all cells between B and C and add it to currSum
        for(int i=1;i<C.first-B.first;i++){
            currSum += grid[B.first + i][B.second - i];
        }

        // Now, we need the sum of all cells between C and D and add it to currSum
        for(int i=1;i<C.first-D.first;i++){
            currSum += grid[C.first - i][C.second - i];
        }

        // Now, we need the sum of all cells between D and A and add it to currSum
        for(int i=1;i<D.first-A.first;i++){
            currSum += grid[D.first - i][D.second + i];
        }

        pq.push(currSum); // Push the final sum of Rhombus
        delta++; // Finally, we increase delta to get newer rhombus

    }
}

bool canPushIt(vector<int> &ans, int &value){ 
    for(auto val:ans){
        if(val==value){
            return false;
        }
    }

    return true;
}

vector<int> getBiggestThree(vector<vector<int>>& grid) { // TC:O(m*n) SC:O(m*n)
    vector<int> ans;

    priority_queue<int> pq; // Set also can be used

    int m = grid.size();
    int n = grid[0].size();

    for(int i=0;i<m;++i){
        for(int j=0;j<n;++j){
            getAllSum(grid,i,j,pq);
        }
    }

    while(!pq.empty() && ans.size()<3){
        int top = pq.top();
        pq.pop();
        
        if(canPushIt(ans,top)){ // Since we need distinct values
            ans.push_back(top);
        } 
    }

    return ans;
}

// Q6. Minimum Refuel Stops - LeetCode(871) - V.V.IMP
int minRefuelStops(int target, int startFuel, vector<vector<int>>& stations) { // TC:O(nlogn) SC:O(n)
    int stops = 0;
    int dist = 0;
    int i = 0;
    int fuel = startFuel;

    priority_queue< pair<int,int> > pq; // MaxHeap with {petrol,position of gas sation}

    while(true){
        while(i<stations.size()){ // Store potential stops in Heap (GREEDY APPROACH)
            // Here, we want to push all stations into maxHeap which are within the reach with my fuel from my current position
            if(stations[i][0] <= dist + fuel){ // Matlab agar curr dist + fuel se phele station hai, toh usse maxHeap mein daal do
                // Since we have to sort maxHeap via fuel, we will put capacity first
                pq.push({stations[i][1],stations[i][0]});
            }
            else{ 
                break;
            }
            i++;
        }

        // Now, we travel with full fuel level
        dist += fuel;
        fuel = 0;

        if(dist >= target){ // Means reached or exceeded
            break;
        }

        // Now, if we did not encounter any fuel stations and did not even reach our target, means ans not possible
        if(pq.empty()){
            stops = -1;
            break;
        }
        

        // Here, we will readjust the dist and fuel based on the distance travelled and fuel used till that station. IMPORTANT POINT
        auto&top = pq.top();
        fuel = (dist - top.second) + top.first; // Jitna distance chala - previous station ki position + ussi previous station ka sarra fuel
        dist = top.second; // Abh, new position will be that station ki position
        pq.pop();
        stops++;
    }

    return stops;
}

// Q7. Minimum Difference in Sums after Removal of Elements - LeetCode(2163) - V.V.V.VIMP
# define ll long long
long long minimumDifference(vector<int>& nums) { // TC:O(nlogn) SC:O(n)
    int n = nums.size()/3;
    vector<ll>prefix(nums.size(),-1),sufix(nums.size(),-1);

    // Prefix will store MinPossible SUM and Sufix will store MaxPossible SUM. Basically, prefix is trying to minimise sum_first while sufix is trying to maximise sum_second

    // prefix[i] = sum of first n elements from the left side
    // sufix[i] = sum of first n elements from the right side

    ll minisum = 0;
    priority_queue<ll> pq1; // MaxHeap
    for(int i=0;i<nums.size();i++){
        minisum += nums[i];
        pq1.push(nums[i]);

        // Now, we pop out maximum element if we get more than n elements in pq1
        if(pq1.size()>n){
            minisum -= pq1.top();
            pq1.pop();
        }

        // Now, if the size of max heap is equal to n, means it has the n minimum elements requried to make for prefix
        if(pq1.size()==n){
            prefix[i] = minisum;
        }
    }

    ll maxisum = 0;
    priority_queue<ll,vector<ll>,greater<ll>> pq2; // MinHeap
    for(int i=nums.size()-1;i>=0;i--){
        maxisum += nums[i];
        pq2.push(nums[i]);

        // Now, we pop out minimum element if we get more than n elements in pq2
        if(pq2.size()>n){
            maxisum -= pq2.top();
            pq2.pop();
        }

        // Now, if the size of min heap is equal to n, means it has the n maximum elements requried to make for prefix
        if(pq2.size()==n){
            sufix[i] = maxisum;
        }
    }

    ll ans= ULONG_MAX;
    for(int i=n-1;i<2*n;i++){ // Since the remaining will have 2*n elements, and we will not consider the first and last of each, as they both will be -1
        ans = min(ans,prefix[i]-sufix[i+1]);
    }

    return ans;
}