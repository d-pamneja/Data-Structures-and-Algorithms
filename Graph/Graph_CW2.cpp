#include <iostream>
#include <unordered_map>
#include <list>
#include <queue>
using namespace std;

// Q1. Detect Cycle in an Undirected Graph using BFS- GFG
bool solveBFS(int srcNode,vector<int> adj[],unordered_map<int,bool> &vis){
    queue<int> qu;
    unordered_map<int,int> parent;

    qu.push(srcNode);
    parent[srcNode] = -1;
    vis[srcNode] = true;

    while(!qu.empty()){
        int front = qu.front();
        qu.pop();

        for(auto neighbour:adj[front]){
            if(neighbour==parent[front]){ // agar parent ko hi visit karna hai, toh skip that case from check
                continue;
            }
            if(!vis[neighbour]){
                qu.push(neighbour);
                parent[neighbour] = front;
                vis[neighbour] = true;
            }
            else if(vis[neighbour]==true){ // Imp Condition, yaani agar humara current child is trying to visit a node jo uska parent nahi hai, that means cycle. 
                // This virtually means ki hum ek visited node ko phir se check kar rahe hai jiska parent same nahi hai, hota toh upar se continue ho jata
                return true;
            }
        }
    }

    return false;
}


bool isCycle(int V, vector<int> adj[]) {
    unordered_map<int,bool> vis;
    for(int i=0;i<V;i++){
        if(!vis[i]){
            bool ans = solveBFS(i,adj,vis);
            if(ans==true){
                return true;
            }
        }
    }
    return false;
}

// Q2. Detect Cycle in a Undirected Graph using DFS - GFG
bool solveDFS(int srcNode,vector<int> adj[],unordered_map<int,bool> &vis,int parent){
    vis[srcNode] = true;
    
    for(auto neighbour:adj[srcNode]){
        if(neighbour==parent){ // agar parent ko hi visit karna hai, toh skip that case from check
            continue;
        }
        if(!vis[neighbour]){
            bool ans =  solveDFS(neighbour,adj,vis,srcNode);
            if(ans==true) return true;
        }
        else if(vis[neighbour]==true){ // yaha, agar koi kisi aise node ko vapis visit kar raha hai, it means it is trying to visit someone who is not their parent. Agar parent hota, apne aap upar se continue ho jata i.e. CYCLE HAI
            return true;
        }
    }
    
    return false;
}


bool isCycle(int V, vector<int> adj[]) {
    unordered_map<int,bool> vis;
    for(int i=0;i<V;i++){
        if(!vis[i]){
        //   bool ans = solveBFS(i,adj,vis);
            int parent = -1;
            bool ans = solveDFS(i,adj,vis,parent);
            if(ans==true){
                return true;
            }
        }
    }
    return false;
}

// Q3. Detect Cycle in a Directed Graph using DFS - GFG
bool solveDFS(int srcNode,unordered_map<int,bool> &vis,
    unordered_map<int,bool>&dfsTrack,vector<int> adj[]){
        
    vis[srcNode]=true;
    dfsTrack[srcNode]=true;
    
    for(auto neighbour:adj[srcNode]){
        if(!vis[neighbour]){
            bool ans = solveDFS(neighbour,vis,dfsTrack,adj);
            if(ans==true){
                return true;
            }
        }
        else if(vis[neighbour]==1 && dfsTrack[neighbour]==1){ // Matlab yaha, agar neighbour already visited hai, aur DFS bhi usse phir se vsist kar raha hai, matlab cycle
            return true;
        }
    }

    
    // Backtrack - V.V.V.V.V.V.V.V.V.V - IMP
    dfsTrack[srcNode]=false;
    
    
    return false;
}

bool isCyclic(int V, vector<int> adj[]) {
    unordered_map<int,bool> vis;
    unordered_map<int,bool> dfsTrack;
    
    for(int node=0;node<V;node++){
        if(!vis[node]){
            bool ans = solveDFS(node,vis,dfsTrack,adj);
            if(ans==true){
                return true;
            }
        }
    }
    
    return false;
}

// Q4. Detect Cycle in a Directed Graph using BFS - GFG


