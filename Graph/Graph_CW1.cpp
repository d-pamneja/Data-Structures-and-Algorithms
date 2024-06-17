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
};

template <typename T> // To make the graph generic for all data types
class WeightedGraph{
  public:
    unordered_map<T,list<pair<T,int>>> adjList;

    void addEdge(T u,T v,int weight,bool isDirected){
      if(isDirected){
        // Means sirf u se v ka edge hai i.e. u->v
        adjList[u].push_back({v,weight});
      }
      else{
        // Means dono u se v AND v se u edge hai i.e. u->v & v->u
        adjList[u].push_back({v,weight});
        adjList[v].push_back({u,weight});
      }
    }

    void PrintAdjList(){
      for(auto i:adjList){
        T node = i.first;
        auto arr = i.second;
        cout<<node<<"-> {";

        for(auto WeightedNeighbour:arr){
          cout<<" { ";
          cout<<WeightedNeighbour.first<<",";
          cout<<WeightedNeighbour.second;
          cout<<" } ,";
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
          T neighbourData = neighbour.first; // The data of the node
          if(!vis[neighbourData]){
            qu.push(neighbourData);
            vis[neighbourData]=true;
          }
        }
        cout<<endl;
      }
    }

    void DFSTraversal(T srcNode,unordered_map<T,bool> &vis){
      vis[srcNode] = true;
      cout<<srcNode<<endl;

      for(auto neighbour:adjList[srcNode]){
        if(!vis[neighbour.first]){
          DFSTraversal(neighbour.first,vis);
          // here, base case is automatically handled as if it is false marked, we do not do anything
        }
      }
    }
};

int main() {
  WeightedGraph<int> g;
  g.addEdge(0, 1,5,1);
  g.addEdge(1, 2,12, 0);
  // g.addEdge(1, 3, 30,1);
  g.addEdge(3, 17, 19,0);
  g.addEdge(2, 4, 21,0);
  g.addEdge(2, 19,11, 1);
  g.addEdge(4, 5, 19,1);
  g.addEdge(5, 7, 19,0);


  // g.PrintAdjList();
  unordered_map<int,bool> vis;
  // g.DFSTraversal(0,vis);

  // In case the components are disconnected, we use a for loop to tackle this, as shown below
  int graphNodes = 6;
  for(int i=0;i<graphNodes;i++){
    if(!vis[i]){
      g.DFSTraversal(i,vis);
    }
  }

}