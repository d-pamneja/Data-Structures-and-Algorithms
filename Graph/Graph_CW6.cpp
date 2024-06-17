#include <iostream>
#include <unordered_map>
#include <map>
#include <list>
#include <queue>
using namespace std;


// Q1. Number of Provinces - LeetCode(547)
void DFS(int srcNode,int n,unordered_map<int,bool> &vis,vector<vector<int>>& isConnected){
    vis[srcNode] = true;

    // current node ke neighbour, uske har column mein milengay. Matlab row fixed and col rotate karte raho

    for(int neighbourIndex=0;neighbourIndex<n;neighbourIndex++){ // Since this is a adj matrix, we need to make for loop
        if(isConnected[srcNode][neighbourIndex]==1){ // Matlab city connected hai
            if(!vis[neighbourIndex]){ // Matlab connection not visited, so make DFS call. Also handles khud se khud ka comparision case, as we have already marked vis[srcNode] true so won't enter node in case neighbourNode==srcNode
                DFS(neighbourIndex,n,vis,isConnected);
            }
        }
    }

}

int findCircleNum(vector<vector<int>>& isConnected) {
    int n = isConnected.size();
    int provinces = 0;
    unordered_map<int,bool> vis;

    for(int i=0;i<n;i++){
        if(!vis[i]){
            DFS(i,n,vis,isConnected);
            provinces++;
        }
    }

    return provinces;
}

// Q2. Number of Islands - LeetCode(200)
bool isSafe(int newRow,int newCol,int row,int col,map<pair<int,int>,bool> &vis){
    if(newRow>=0 && newRow<row && newCol >=0 && newCol<col && vis[{newRow,newCol}]==false){
        return true;
    }
    else{
        return false;
    }
}

void BFS(int srcRow,int srcCol,vector<vector<char>>& grid,map<pair<int,int>,bool> &vis){
    queue<pair<int,int>> qu;
    int row = grid.size();
    int col = grid[0].size();

    // Initialise queue and map
    qu.push({srcRow,srcCol});
    vis[{srcRow,srcCol}] = true;

    while(!qu.empty()){
        auto front = qu.front();
        qu.pop();

        int currRow = front.first;
        int currCol = front.second;

        int dRow[] = {-1,0,1,0};
        int dCol[] = {0,1,0,-1};

        for(int i=0;i<4;i++){
            int newRow = currRow + dRow[i];
            int newCol = currCol + dCol[i];

            if(isSafe(newRow,newCol,row,col,vis)){
                if(grid[newRow][newCol]=='1'){
                    qu.push({newRow,newCol});
                    vis[{newRow,newCol}] = true;
                }
            }
        }
    }   
}


int numIslands(vector<vector<char>>& grid) {
    // In this question, ham index ko nahi, har cell ko ek node manengay. So total operations we will run is m*n
    int rows = grid.size();
    int cols = grid[0].size();
    int islands = 0;
    map<pair<int,int>,bool> vis;


    // Since we are taking by cell, we will go to each cell i.e. double loop

    for(int i=0;i<rows;i++){
        for(int j=0;j<cols;j++){
            if(!vis[{i,j}] && grid[i][j]=='1'){
                BFS(i,j,grid,vis);
                islands++;
            }
        }
    }

    return islands;
}

// Q3. Flood Fill - LeetCode(733)
bool isSafe(int newRow,int newCol,int rows,int cols){
    if(newRow>=0 && newCol>=0 && newRow < rows && newCol < cols){
        return true;
    }
    else{
        return false;
    }
}

void DFS(int sr,int sc,int oldColor,int newColor,map<pair<int,int>,bool> &vis,vector<vector<int>> &image,vector<vector<int>> &ans){
    // Current source node ko true mark karke modify kar do
    vis[{sr,sc}] = true;
    ans[sr][sc] = newColor;

    int rows = image.size();
    int cols = image[0].size();

    int dRow[] = {-1,0,1,0};
    int dCol[] = {0,1,0,-1};

    for(int i=0;i<4;i++){
        int newRow = sr + dRow[i];
        int newCol = sc + dCol[i];

        if(isSafe(newRow,newCol,rows,cols) && vis[{newRow,newCol}]==false){ // We will need to check visited, as this will go in an infinite loop if newColor = oldColor
            if(image[newRow][newCol]==oldColor){
                ans[newRow][newCol]=newColor;
                DFS(newRow,newCol,oldColor,newColor,vis,image,ans);
            }
        }
    }
}

vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int color) {
    vector<vector<int>> ans = image;
    int oldColor = image[sr][sc];
    int newColor = color;

    // Now, handle the case if newColor==oldColor, no changes are requried
    if(oldColor==newColor){ // Important case
        return ans;
    }

    map<pair<int,int>,bool> vis;

    // Since yaha par jo source row and col hai, uske hisab se hi move karna hai. Hence, we will not use any for loop to reach all possivle components
    DFS(sr,sc,oldColor,newColor,vis,image,ans);
    return ans;
}

// Q4. Rotting Oranges - LeetCode(994) - V.V.V.V.V.V.V.V IMP
bool isSafe(int newRow,int newCol,int rows,int cols){
    if(newRow>=0 && newCol >=0 && newRow<rows && newCol<cols){
        return true;
    }
    else{
        return false;
    }
}

int orangesRotting(vector<vector<int>>& grid) {
    queue<pair<pair<int,int>,int>> qu; // {{coordinates},time}
    vector<vector<int>> temp = grid;
    int minTime = INT_MAX;

    int rows = temp.size();
    int cols = temp[0].size();
    int rottenOrangeCount = 0;
    int freshOrangeCount = 0;

    // Find all rotten orangaes and put them in queue
    for(int i=0;i<rows;i++){
        for(int j=0;j<cols;j++){
            if(temp[i][j]==2){
                qu.push({{i,j},0}); // Source node ka time 0 set kar rahe hai
                minTime = 0;
                rottenOrangeCount++;
            }
            else if(temp[i][j]==1){
                freshOrangeCount++;
            }
        }
    }

    // Handle the case there there are no rotten oranges - V.V.V.V.V.V.V.V.V.V IMP Edge Cases
    if(rottenOrangeCount==0){
        if(freshOrangeCount==temp.size()){ // Matlab saare oranges fresh hai, so no possible solution
            return -1;
        }
        else if(freshOrangeCount==0){ // yaha fresh aur rotten orange dono hi nahi hai, matlab khali hai toh 0
            return 0;
        }
    }


    // BFS
    while(!qu.empty()){
        auto front = qu.front();
        qu.pop();

        auto oldCoordinates = front.first;
        int oldTime = front.second;

        int oldRow = oldCoordinates.first;
        int oldCol = oldCoordinates.second;

        int dRow[] = {-1,0,1,0};
        int dCol[] = {0,1,0,-1};

        for(int i=0;i<4;i++){
            int newRow = oldRow + dRow[i];
            int newCol = oldCol + dCol[i];

            if(isSafe(newRow,newCol,rows,cols)){
                if(temp[newRow][newCol]==1){ // matlab fresh orange pada hai, toh rot kar do
                    temp[newRow][newCol] = 2;
                    // Rotten orange ko queue mein push kar do
                    int newTime = oldTime + 1;
                    qu.push({{newRow,newCol},newTime});
                    minTime = newTime;
                }
            }
        }
    }

    // Now, all oranges that could be rotten are rotten. Now, we want to check ki agar saare oranges rotten hai ya nahi
    for(int i=0;i<rows;i++){
        for(int j=0;j<cols;j++){
            if(temp[i][j]==1){ // ek bhi fresh orange mila, toh ans not possible
                return -1;
            }
        }
    }

    return minTime;
}
