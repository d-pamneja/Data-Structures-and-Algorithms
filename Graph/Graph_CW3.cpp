#include <iostream>
#include <unordered_map>
#include <list>
#include <queue>
using namespace std;

template <typename T> // To make the graph generic for all data types
class Graph{
  public:
    unordered_map<T,list<T>> adjList;

    void addEdge(T u,T v,bool isDirected){
      if(isDirected){
        // Means sirf u se v ka edge hai i.e. u->v
        adjList[u].push_back(v);
      }
      else{
        // Means dono u se v AND v se u edge hai i.e. u->v & v->u
        adjList[u].push_back(v);
        adjList[v].push_back(u);
      }
    }

    void PrintAdjList(){
      for(auto i:adjList){
        T node = i.first;
        list<T> arr = i.second;
        cout<<node<<"-> {";

        for(auto neighbour:arr){
          cout << neighbour <<",";
        }
        cout<<"}";
        cout<<endl;
      }
    }

    void BFSTraversal(T srcNode){
      // Visited Map
      unordered_map<T,bool> vis;

      // Queue
      queue<T> qu;

      // First, we maintain an initial state with the root/source node, and mark it true
      qu.push(srcNode);
      vis[srcNode] = true;

      while(!qu.empty()){
        T front = qu.front();
        cout<<front<<",";
        qu.pop();

        // Check all the neighbours
        for(auto neighbour:adjList[front]){
          if(!vis[neighbour]){
            qu.push(neighbour);
            vis[neighbour]=true;
          }
        }
        cout<<endl;
      }
    }

    void DFSTraversal(T srcNode,unordered_map<T,bool> &vis){
      vis[srcNode] = true;
      cout<<srcNode<<endl;

      for(auto neighbour:adjList[srcNode]){
        if(!vis[neighbour]){
          DFSTraversal(neighbour,vis);
          // here, base case is automatically handled as if it is false marked, we do not do anything
        }
      }
    }

    bool checkCycleUndirectedBFS(T srcNode){
      queue<T> qu;
      unordered_map<T,T> parent;
      unordered_map<T,bool> vis;

      qu.push(srcNode);
      parent[srcNode] = -1;
      vis[srcNode] = true;

      while(!qu.empty()){
        T front = qu.front();
        qu.pop();

        for(auto neighbour:adjList[front]){
          if(!vis[neighbour]){
            qu.push(neighbour);
            parent[neighbour] = front;
            vis[neighbour] = true;
          }
          else if(vis[neighbour]==true && neighbour!=parent[front]){ // Imp Condition, yaani agar humara current child agar front ka parent nahi hai, that means cycle. This virtually means that the current child has another parent apart from front at this moment, matlab cycle hai
            return true;
          }
        }
      }

      return false;
    }
};

// Q1. Topological Sort using DFS - GFG
// Only to be used in DAG (Directed Acyclic Graph) and whenever we talk about DEPENDENCY, we talk about TOPOLOGICAL SORT
void topoSortDFS(int srcNode,unordered_map<int,bool> &vis,vector<int> &ans,vector<int> adj[]){
    vis[srcNode] = true;
    
    for(auto neighbour:adj[srcNode]){
    if(!vis[neighbour]) // Matlab agar nahi visit kiya neighbour, go till it. with this we reach last node which is not dependent on any one
        topoSortDFS(neighbour,vis,ans,adj);
    }

    ans.push_back(srcNode); // This we, we recursively push nodes from least to most dependent
    
}

vector<int> topoSort(int V, vector<int> adj[]) {
    unordered_map<int,bool> vis;
    vector<int> ans;

    for(int node=0;node<V;node++){ // To handle for disconnected components
    if(!vis[node])
        topoSortDFS(node,vis,ans,adj);
    }
    
    reverse(ans.begin(),ans.end());
    
    return ans;
}



// Q2. Topological Sort using BFS - GFG - Kahn's Algorithm
// Only to be used in DAG (Directed Acyclic Graph) and whenever we talk about DEPENDENCY, we talk about TOPOLOGICAL SORT
bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
  vector<int> ans;
  vector<int> adjList[numCourses];
  queue<int> q;
  unordered_map<int,int> indegree;

  //initialise kardi indegree 
  for(auto i : prerequisites) {
      adjList[i[0]].push_back(i[1]);
      indegree[i[1]]++;
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

  return ans.size()==numCourses; // Matlab agar topo sort is equal to numCourses, toh possible hai `numCourses` ko complete karna
}

// Q3. Shortest Path in a Graph - BFS Undirected Graph
// IMP Line : Jo node sabse phele visit ho gayi, wahi uska shortest path hoga. Agar aap same node ko baad mein bhi visit kar rahe ho, toh uska shortest path wahi hoga jo sabse phele visit hua tha
void shortestPathBFS(int srcNode,int destNode){
  unordered_map<int,list<int>> adjList;
  queue<int> q;
  unordered_map<int,bool> visited;
  unordered_map<int,int> parent;

  // Initial state
  q.push(srcNode);
  visited[srcNode]=true;
  parent[srcNode] = -1;

  // Parent Initialisation
  while(!q.empty()){
    int frontNode = q.front();
    q.pop();

    for(auto nbr:adjList[frontNode]){
      if(!visited[nbr]){
        q.push(nbr);
        visited[nbr]=true;
        parent[nbr] = frontNode;
      }
    }
  }

  // We keep on pushing the parent from destNode to rootNode
  vector<int>ans;
  while(destNode!=-1){
    ans.push_back(destNode);
    destNode = parent[destNode];
  }

  reverse(ans.begin(),ans.end());
  for(auto i:ans){
    cout<<i<<",";
  }
  cout<<endl;
}