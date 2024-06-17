#include <iostream>
#include <unordered_map>
#include <map>
#include <list>
#include <queue>
#include <stack>
using namespace std;

template<typename T>
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

// Q1. Bellman Ford Algorithm
// Can tell the shortest path and can also tell if there is a negative cycle. Although we cannot get the answer in case a negative cycle is present, but if it isn't and we have positive and neagtive weights, then we can get the shortest path.
// It will run for n-1 times and perform relaxation, where n is the number of vertices. After n-1 times, we will have the shortest path.
// In case there is still an update in the n-th iteration, then there is a negative cycle.
template<typename T>
void BellManFord(int n,T srcNode){ // Single source shortest path
    bool negativeCycle = false;
    vector<int> dist(n,INT_MAX);
    dist[srcNode - 'A'] = 0; // for char based

    // Now, we will perform relaxation for (n-1) times
    for(int i=1;i<n;i++){
        // Traverse on entire edge list
        for(auto neighbours:adjList){
            for(auto neighbour:neighbours.second){
                char u = neighbours.first; // Current node
                char v = neighbour.first;  // Outing edge
                int weight = neighbour.second; // Outgoing edge ka weight

                if(dist[u-'A']!= INT_MAX && (dist[u-'A'] + weight < dist[v-'A'])){ // prevent integer overflow
                    dist[v-'A'] = dist[u-'A'] + weight;
                }
            }
        }       
    }

    // Yaha tak shortest distance ready hai. Now run relaxation one more time, if it tries to again update dist array, means negative cycle
    for(auto neighbours:adjList){
        for(auto neighbour:neighbours.second){
            char u = neighbours.first; // Current node
            char v = neighbour.first;  // Outing edge
            int weight = neighbour.second; // Outgoing edge ka weight

            if(dist[u-'A']!= INT_MAX && (dist[u-'A'] + weight < dist[v-'A'])){ // prevent integer overflow
                negativeCycle = true;
                break;
            }
        }
    }

    if(negativeCycle){
        cout<<"Negative Cycle Present"<<endl;
        return;
    }
    else if(!negativeCycle){
        cout<<"No Negative Cycle Present"<<endl;
        for(int i=0;i<n;i++){
            cout<<dist[i]<<",";
        }
        cout<<endl;
    } 
}  

// Q2. Floyd Warshall Algorithm
// It is used to find the shortest path between all pairs of vertices in a graph. It is a dynamic programming algorithm.
// Basically, we find the shortest path for all vertices by considering each node as a source node and then updating the shortest path.
// It is used for both directed and undirected graphs, but it does not work for graphs with negative weight cycles.
// Basically, a 2D array is used to store the shortest distance between all pairs of vertices. Initially, this array is filled with the weight of the edges between the vertices. Then, we update the array by considering all nodes as an source node.
template<typename T>
void floydWarshall(int n){
    vector<vector<int>> dist(n,vector<int>(n,1e9)); // Find the reason that why 1e9 and not INT_MAX

    // Assuming int based indexing here i.e. int elements as nodes
    // As from a node, it's minimum distance with itself will be 0, create initial state
    for(int i=0;i<n;i++){
    dist[i][i]=0;
    }

    // Now, some weights will also be given in the graph, so update distance array accordingly
    for(auto neighbours:adjList){
        for(auto neighbour:neighbours.second){
            auto u = neighbours.first;
            auto v = neighbour.first;
            int weight = neighbour.second;

            dist[u][v] = weight; // Update the given weights as it is from edge u->v
        }
    }

    // Now, we use a helper logic
    // basically, node u se v janne tak ke saare path nikalo, and use the minimum one
    for(int helper=0;helper<n;helper++){
        for(int src=0;src<n;src++){
            for(int dest=0;dest<n;dest++){
                int helperDist = dist[src][helper] + dist[helper][dest]; // Matlab going from src to dest via helper node
                dist[src][dest] = min(dist[src][dest],helperDist);
            }
        }
    }


    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cout<<dist[i][j]<<",";
        }
        cout<<endl;
    }
}

// Q3. Kosaraju Algorithm
// In this algorithm, we find the strongly connected components in a graph. A strongly connected component is a set of vertices in a directed graph where there is a path between each pair of vertices.
// Matlab ek strongly connected component mein, har node se har node tak jaane ka raasta hota hai i.e. ek cycle hota hai.
// Now, yaha order of traversal is important, as we need to traverse in reverse order. Ordering ke hisab se hi answer aayega.
// Agar hum time based type ordering ko follow karte hai, toh yeh do kaam karayegi.
// Ya toh hum sirf current strongly connected component mein ghumte jayenge, ya fir hum saare strongly connected components ko traverse ho chukke ho usse lekar aage badh jaayenge.
// Humme sarre SCC jo traverse ho chuke hai waha firse jane mein koi problem nahi hai, as they are already traversed and we will use vissted array to keep track of them and avoid revisiting them.
// Asana bhasha mein bolle, agar hum ek SCC se doosre SCC mein ja rahe hai, toh humne pakka ek already traversed SCC mein ja rahe hai.
// Basically, we first do a DFS traversal and store the order of traversal in a stack. Then, we reverse the graph and do a DFS traversal again, but this time, we pop the elements from the stack and do a DFS traversal.
template<typename T>
void DFSofSCC(int node, stack<int> &ordering,unordered_map<int,bool> &vis){
  vis[node] = true;

  for(auto neighbour:adjList[node]){
    if(!vis[neighbour.first]){
      DFSofSCC(neighbour.first,ordering,vis);
    }
  }

  ordering.push(node);
}

template<typename T>
void DFSofRevSCC(int node, unordered_map<int,bool> &vis,unordered_map<T,list<pair<T,int>>> &RevAdjList){
  vis[node] = true;
  cout<<node<<",";

  for(auto neighbour:RevAdjList[node]){
    if(!vis[neighbour.first]){
      DFSofRevSCC(neighbour.first,vis,RevAdjList);
    }
  }
}

template<typename T>
int stronglyConnectedComponents(int n){
  // Step 1: Get the time based ordering
  stack<int> ordering;
  unordered_map<int,bool> vis;

  for(int i=0;i<n;i++){
    if(!vis[i]){
      DFSofSCC(i,ordering, vis);
    }
  }
  
  // Step 2: Reverse the edges
  // Now, since we do not know which edges connected SCCs, we reverse all edges
  unordered_map<T,list<pair<T,int>>> RevAdjList;
  for(auto a:adjList){
    auto list = a.second;
    for(auto b:list){
      int u = a.first;
      int v = b.first;

      RevAdjList[v].push_back({u,b.second}); // effectively reverses the list with maintaining the weights
    }
  }

  // Step 3: Traverse using ordering and count components
  int count = 0;
  unordered_map<int,bool> vis2;

  while(!ordering.empty()){
    int node = ordering.top();
    ordering.pop();

    if(!vis2[node]){
      cout<<"SCC Number "<<count+1<<" : ";
      DFSofRevSCC(node,vis2,RevAdjList);
      count++;
      cout<<endl;
    }
  }

  return count;
}

// Q4. Critical connections in a network - (LC 1192) - V.V.V.V.V.V.V.V. IMP
// Bridges in a graph are the edges that if removed, will increase the number of disconnected components in the graph. These are also called critical connections.
// In this problem, we are given a network of n nodes represented by an undirected graph. We need to find all the critical connections in the network.
// We can solve this problem using Tarjan's Algorithm. In this algorithm, we find the bridges in a graph. 
// We maintain a insert time (TIN) and a low time (LOW) for each node. The discovery time is the time at which the node is inserted, and the low time is the minimum of the insertion time of the current node.
// Asan bhasha mein, TIN matlab jab current node pe aye toh time kya tha, aur LOW matlab uss node ko insert karne ka minimum time.
// Agar kisi node ke LOW ke value se kam kisi neighbour ka TIN hai, toh woh edge critical hai. i.e. if LOW of current Node > TIN of neighbour Node, then the edge connecting neighbour and current node is critical.
void edgeTester(int src,int parent,unordered_map<int,list<int>> &adjList,int &timer,vector<vector<int>> &ans,vector<int> &tin,vector<int> &low,unordered_map<int,bool> &vis){
    vis[src] = true;
    tin[src] = timer;
    low[src] = timer;
    timer++;

    // Now, we handle the neighbours
    for(auto neighbour:adjList[src]){
        // Case 1: if neighbour is the parent only
        if(neighbour==parent){
            // We can ignore this case, else we get stuck in loop
            continue;
        }

        // Case 2: If not visited
        if(!vis[neighbour]){
            // abh, neighbour ki call laga do
            edgeTester(neighbour,src,adjList,timer,ans,tin,low,vis);
            // abh, jis bhi node pe ho, uske low ko update kar do
            low[src] = min(low[src],low[neighbour]);

            // Abh, bridge testing karo. Yaani agar neighbour ka low > current node ke TIN se, matlab bridge mill gaya
            if(low[neighbour] > tin[src]){
                vector<int> bridge;
                bridge.push_back(src);
                bridge.push_back(neighbour);
                ans.push_back(bridge);
            }   
        }
        // Case 3: If visited
        else{
            // Agar already visisted, matlab no need of bridge testing
            // Sirf low ko update kar do
            low[src] = min(low[src],low[neighbour]);
        }
    }
}

vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {
    // Create Adjacency List
    unordered_map<int,list<int>> adjList;
    for(auto vec:connections){
        int u = vec[0]; // Node 1
        int v = vec[1]; // Node 2
        // Since this is undirected, edge will go from both u -> v and v->u
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    // 
    int timer = 1;
    vector<vector<int>> ans;
    vector<int> low(n,0);
    vector<int> tin(n,0);
    unordered_map<int,bool> vis;

    int src = 0;
    int parent = -1;

    edgeTester(src,parent,adjList,timer,ans,tin,low,vis);

    return ans;
}