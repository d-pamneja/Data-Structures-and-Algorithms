#include <iostream>
#include <unordered_map>
#include <list>
#include <queue>
using namespace std;

// Q1. Course Schedule II - (LC-210)
void topoSortBFS(int numCourses,vector<int> &ans,unordered_map<int,list<int>> &adjList){
    queue<int> q;
    unordered_map<int,int> indegree;

    //initialise kardi indegree 
    for(auto i : adjList) {
        for(auto nbr: i.second){
            indegree[nbr]++;
        }
    }

    //push all zero indegree wali node into queue
    for(int node=0; node<numCourses; node++) {
        if(indegree[node] == 0) {
            q.push(node);
        }
    }

    //BFS chalate hai
    while(!q.empty()) {
        int frontNode = q.front();
        q.pop();
        ans.push_back(frontNode);

        for(auto nbr: adjList[frontNode]) {
            indegree[nbr]--;

            //check for zero
            if(indegree[nbr] == 0) {
                q.push(nbr);
            }
        }
    }
}

vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
    vector<int> ans;
    unordered_map<int,list<int>> adjList;

    //initialise kardi adjList 
    for(auto i : prerequisites) {
        adjList[i[1]].push_back(i[0]);
    }

    topoSortBFS(numCourses,ans,adjList);
    
    if(ans.size()==numCourses)  return ans;
    else return {};
}

// Q2. Path with Maximum Effort - (LC-1631) V.V.V.V.V.V.V.V. IMP
bool isSafe(int newNodeRow,int newNodeCol,int currNodeRow,int currNodeCol, int row,int col,vector<vector<int>> &effort){
    if(newNodeRow>=0 && newNodeCol>=0 && newNodeRow<row && newNodeCol<col && effort[currNodeRow][currNodeCol]<effort[newNodeRow][newNodeCol]){ // yaha, current effort ko compare karna padega new effort se, nahi toh TLE aayega
        return true;
    }
    else{
        return false;
    }
}

int minimumEffortPath(vector<vector<int>>& heights) {
    priority_queue<pair<int,pair<int,int>>,vector<pair<int,pair<int,int>>>, greater<pair<int,pair<int,int>>>> miniQu; // {effort, {row index of node,col index of node}} -> basically, this means absolute max effort to reach current node ki location i.e. row aur col
    int row = heights.size();
    int col = heights[0].size();

    int destNodeRow = row - 1;
    int destNodeCol = col - 1;

    vector<vector<int>> effort(row,vector<int>(col,INT_MAX));

    // Initialise effort matrix and min heap
    effort[0][0]=0; // starting node ki location ka effort khud se 0 hi hoga
    miniQu.push({effort[0][0],{0,0}}); 

    while(!miniQu.empty()){
        auto topPair = miniQu.top();
        miniQu.pop();

        int currEffort = topPair.first;
        pair<int,int> currNodeIndexPair = topPair.second;
        int currNodeRow = currNodeIndexPair.first;
        int currNodeCol = currNodeIndexPair.second;

        // Now, let us travel to all four neighbours i.e. up,right, down and left
        int dRow[] = {-1,0,1,0}; // Moving up, right, down and left ke row pe impact i.e. +1 matlab increment, -1 matlab decrement and 0 matlab as it is
        int dCol[] = {0,1,0,-1}; // Moving up, right, down and left ke col pe impact i.e. +1 matlab increment, -1 matlab decrement and 0 matlab as it is

        for(int i=0;i<4;i++){ // Loop to go for all directions
            int newNodeRow = currNodeRow + dRow[i];
            int newNodeCol = currNodeCol + dCol[i];

            if(isSafe(newNodeRow,newNodeCol,currNodeRow,currNodeCol,row,col,effort)){
                // Basically, phele max diff ko maximise karo, aur phir effort array mein minimum daalo.
                // Effort maximised nikalo aur phir minimum walle ko hi track karo
                int maxDiff = max(currEffort,abs(heights[currNodeRow][currNodeCol]-heights[newNodeRow][newNodeCol])); // V.V.V.IMP
                // Check if we need to update the effort array
                effort[newNodeRow][newNodeCol] = min(effort[newNodeRow][newNodeCol],maxDiff);

                // Finally, min-Heap mein entry daal do
                if(newNodeRow!=destNodeRow || newNodeCol!=destNodeCol){ // V.V.V.V.V. IMP
                    miniQu.push({effort[newNodeRow][newNodeCol],{newNodeRow,newNodeCol}}); 
                }       
            }
        }


    }

    return effort[destNodeRow][destNodeCol];

}

