#include <iostream>
#include <unordered_map>
#include <list>
#include <queue>
using namespace std;

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

    void topoOrderDFS(T srcNode,stack<T> &topoOrder,unordered_map<T,bool> &vis){
      vis[srcNode] = true;

      for(auto neighbourPair:adjList[srcNode]){
        T neighbourNode = neighbourPair.first;
        // int neighbourDist = neighbourPair.second;

        if(!vis[neighbourNode]){
          topoOrderDFS(neighbourNode,topoOrder,vis);
        }        
      }

      topoOrder.push(srcNode);
    }

    void shortestPathDFS(stack<T> &topoOrder,int n){
      vector<int> distance(n,INT_MAX);

      // Here, hum stack ke sabse top ko hi source manengay, as it is the most independent of them all
      auto srcNode = topoOrder.top();
      topoOrder.pop();
      distance[srcNode] = 0; // source ka khud se toh distance 0 hi hoga

      // Now, we will update the distance of the neighbours of the source node
      for(auto neighbourPair:adjList[srcNode]){
        T neighbourNode = neighbourPair.first;
        int neighbourDist = neighbourPair.second;

        // modify the distance to reach till neighbour node from source node
        if(distance[srcNode]+neighbourDist < distance[neighbourNode]){
          distance[neighbourNode] = distance[srcNode]+neighbourDist;
        }
      }
      

     // Now, we apply the same logic for all nodes in stack
      while(!topoOrder.empty()){
        auto front = topoOrder.top();
        topoOrder.pop();

        // Now, we will update the distance of the neighbours of the source node
        for(auto neighbourPair:adjList[front]){
          T neighbourNode = neighbourPair.first;
          int neighbourDist = neighbourPair.second;

          // modify the distance to reach till neighbour node from source node
          if(distance[front]+neighbourDist < distance[neighbourNode]){
            distance[neighbourNode] = distance[front]+neighbourDist;
          }
        }  
      }

      for(auto i:distance){
        cout<<i<<",";
      }
      cout<<endl;
    }
};

// Q1. Dijkstra's Algorithm - V.V.V.V.V.V.V.V.V.V.Imp
// Dijkstra's Algorithm is a Greedy Algorithm, which is used to find the shortest path from a source node to all other nodes in the given graph.
// It is used for both directed and undirected graphs, but it does not work for graphs with negative weight edges.
template <typename T>
void dijkstraShortest(int n,T srcNode, T destNode,int &ans){
  vector<int> distance(n+1,INT_MAX);
  set<pair<int,T>> st; // {distance,node}

  // Initial State
  // Yaha, source node ka distance and source node ko push karo
  st.insert({0,srcNode});
  distance[srcNode] = 0;

  while(!st.empty()){
    auto topEleIndex = st.begin(); // Will give reference of element
    pair<int,T> topPair = *topEleIndex; // Dereference index to give the element

    int topDist = topPair.first;
    T topNode = topPair.second;

    st.erase(st.begin());

    // Update distance of neighbours
    for(auto neighbourPair:adjList[topNode]){
      int neighbourNode = neighbourPair.first;
      T neighbourDist = neighbourPair.second;

      if(topDist + neighbourDist < distance[neighbourNode]){
        // Matlab agar phele ka distance + curr distance < existing, toh update in the set as we have a new entry. Phele set ki entry nikalo, phir distance array update karo aur phir daal do set mein. Make sure this order is maintained
        auto prevEntry = st.find({distance[neighbourNode],neighbourNode});
        if(prevEntry!=st.end()){
          st.erase(prevEntry);
        }

        // Now, also update in the distane array
        distance[neighbourNode] = topDist + neighbourDist;

        // Finally, insert the new entry in the stack
        st.insert({distance[neighbourNode],neighbourNode});
        
      }
      
    }
  }

  ans = distance[destNode];
  
}