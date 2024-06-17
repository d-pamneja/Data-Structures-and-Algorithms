#include <iostream>
#include <vector>
#include <limits.h>
#include <algorithm>
#include <queue>
using namespace std;

// Greedy Technique
// Here, many data structures we use follow the greedy technique, such as :
// 1. Priority Queue
// 2. Sorting
// 3. Min-Heap
// 4. Max-Heap
// 5. Set

// Q1. DEFKIN - Defense of a Kingdom - (SPOJ)
int defkin(int row,int col,vector<pair<int,int>> location){
  // Now, we initilaise vector for x dimension i.e. cols which are protected by towers
  vector<int> xDim; // this will store x-coordinates of a tower
  // Create dummy towers for accurate position calculation
  xDim.push_back(0);
  xDim.push_back(col+1);

  for(int i=0;i<location.size();i++){
    xDim.push_back(location[i].first);
  }

  sort(xDim.begin(),xDim.end());

  // Now, we initilaise vector for y dimension i.e. rows which are protected by tower
  vector<int> yDim; // this will store y-coordinates of a tower
  // Create dummy towers for accurate position calculation
  yDim.push_back(0);
  yDim.push_back(row+1);

  for(int i=0;i<location.size();i++){
    yDim.push_back(location[i].second);
  }

  sort(yDim.begin(),yDim.end());

  // Now, let us fetch the lengths of all unprotected regions which are on x-axis
  vector<int> xUnprotected; // this will store difference between two towers on the x-axis
  for(int i=0;i<xDim.size();i++){
    int diff = xDim[i] - xDim[i-1] - 1;
    xUnprotected.push_back(diff);
  }

  // Now, let us fetch the breadth of all unprotected regions which are on y-axis
  vector<int> yUnprotected; // this will store difference between two towers on the y-axis
  for(int i=0;i<yDim.size();i++){
    int diff = yDim[i] - yDim[i-1] - 1;
    yUnprotected.push_back(diff);
  }

  int maxi = INT_MIN;

  for(int i=0;i<xUnprotected.size();i++){
    for(int j=0;j<yUnprotected.size();j++){
      int prod = xUnprotected[i] * yUnprotected[j];
      maxi = max(maxi,prod);
    }
  }

  return maxi;
}

// Q2. Min Cost of Ropes - (GFG)
long long minCost(long long arr[], long long n) {
    priority_queue<long long,vector<long long>,greater<long long>> minHeap;
    
    for(long long i=0;i<n;i++){
        long long val = arr[i];
        minHeap.push(val);
    }
    
    long long cost = 0;
    long long sum = 0;
    while(minHeap.size()>1){
        long long top1 = minHeap.top();
        minHeap.pop();
        long long top2 = minHeap.top();
        minHeap.pop();
        
        sum = top1 + top2; // current addition of two min values
        cost += sum;
        
        minHeap.push(sum);
    }
    
    return cost;
}

// Q3. Huffman Coding | Greedy Algo-3
// Read the question from the link : https://www.geeksforgeeks.org/huffman-coding-greedy-algo-3/

// Q4. Fractional Knapsack Problem - (GFG)
struct Item{
    int value;
    int weight;
};

double fractionalKnapsack(int w, Item arr[], int n) {
    int capacity = w;
    
    // Find the ratio of value per kg of weight
    vector<double> valueWeightRatio;
    for(int i=0;i<n;i++){
        double ratio = (arr[i].value * 1.0)/(arr[i].weight);
        valueWeightRatio.push_back(ratio);
    }
    
    priority_queue<pair<double,pair<int,int>>> maxHeap; // Ratio,{value,weight}
    
    for(int i=0;i<valueWeightRatio.size();i++){
        maxHeap.push({valueWeightRatio[i],{arr[i].value,arr[i].weight}});
    }
    
    double ans = 0;
    while(capacity!=0 && !maxHeap.empty()){
        auto front = maxHeap.top();
        double frontRatio = front.first;
        int frontValue = front.second.first;
        int frontWeight = front.second.second;
        maxHeap.pop();
        
        // Case A : Full Insert
        if(capacity >= frontWeight){
            ans += frontValue;
            capacity = capacity - frontWeight;
        }
        // Case B : Fractional Insert
        else{
            double adjustedValue = (frontRatio*capacity);
            ans += adjustedValue;
            capacity = 0;
            break;
        }
    }

    return ans;
}

// Q4. Number of meetings in one room - (GFG)
static bool myComp(pair<int,int> &a,pair<int,int> &b){
    return a.second < b.second;
}

int maxMeetings(int start[], int end[], int n){
    vector<pair<int,int>> meetings; // {start,end}
    for(int i=0;i<n;i++){
        meetings.push_back({start[i],end[i]});
    }
    
    sort(meetings.begin(),meetings.end(),myComp);
    
    int count = 1; // We will always include the first meeting
    int prevStart = meetings[0].first;
    int prevEnd = meetings[0].second;
    
    for(int i=1;i<n;i++){
        int currStart = meetings[i].first;
        int currEnd = meetings[i].second;
        
        // Case A : Curr start is after last meeting ends
        if(currStart > prevEnd){
            count++;
            prevStart = currStart;
            prevEnd = currEnd;
        }
        // Case B : Matlab meeting ongoing right now, so ignore
        
    }
    
    return count;
}

// Q5. Minimum train platforms required for a railway station - (GFG)
int findPlatform(int arr[], int dep[], int n){
    sort(arr, arr + n);
    sort(dep, dep + n);
    
    int platform = 1; 
    int maxi = 1;
    int i = 1;
    int j = 0;
    
    while(i<n && j<n){
        int currArrival = arr[i];
        int prevDeparture = dep[j];
        
        // Case A : Next train timing clash, so new platform needed
        if(currArrival <= prevDeparture){
            platform++;
            i++;
        }
        // Case B : Means no clash, so we can reduce the platform
        else{
            platform--;
            j++;
        }
        
        maxi = max(maxi,platform);
    }
    
    return maxi;
}

// Q6. Chocolate Distribution Problem - (GFG) - IMP : This has 2-4 variations, try all of them ASAP


// Q7. Chocolate Distribution Problem Set 2 - (GFG)