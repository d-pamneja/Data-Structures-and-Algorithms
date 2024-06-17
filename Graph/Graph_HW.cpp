#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <list>
#include <queue>
#include <stack>
#include <set>
using namespace std;

// Q1. Eventual Safe States - (LC-802)
// Here, if the current node leads to a cycle, then it is not a safe state.
// Thus, every node which is entering a cycle can never be safe.
// So here, we will try to find the nodes that are part of a cycle, and then mark them as unsafe.

bool solveDFS(int srcNode,unordered_map<int,bool> &vis, unordered_map<int,bool>&dfsTrack,vector<int> adj[],vector<int> &safeNodes){
    vis[srcNode]=true;
    dfsTrack[srcNode]=true;
    
    for(auto neighbour:adj[srcNode]){
        if(!vis[neighbour]){
            bool DFSkaAns = solveDFS(neighbour,vis,dfsTrack,adj,safeNodes);
            if(DFSkaAns==true){
                return true;
            }
        }
        else if(vis[neighbour]==1 && dfsTrack[neighbour]==1){ // Matlab yaha, agar neighbour already visited hai, aur DFS bhi usse phir se vsist kar raha hai, matlab cycle
            return true;
        }
    }

    
    // Backtrack - V.V.V.V.V.V.V.V.V.V - IMP
    dfsTrack[srcNode]=false;
    safeNodes[srcNode]=1; // Matlab agar yaha tak aa gayi, so safe node hai, so uske index ko true mark kar do

    return false;
}

vector<int> eventualSafeNodes(int V, vector<int> adj[]) {
    int srcNode = 0;
    unordered_map<int,bool> vis;
    unordered_map<int,bool> dfsTrack;
    
    vector<int> ans;
    vector<int> safeNodes;
    
    for(int i=0;i<V;i++){
        if(!vis[i]){
            solveDFS(i,vis,dfsTrack,adj,safeNodes);
        }
    }
    
    for(int i=0;i<V;i++){
        if(safeNodes[i]){
            ans.push_back(i);
        }
    }
    
    return ans;
}

// Q2. Minimum Multiplication to reach End - (GFG)
const int mod = 100000;
int minimumMultiplications(vector<int>& arr, int start, int end) {
    queue<int> qu;
    vector<int> ans(100000,-1); // Will also work as visisted array, as well as storing number of steps to reach current end
    
    ans[start] = 0;
    qu.push(start);
    
    while(!qu.empty()){
        int front = qu.front();
        qu.pop();
        
        if(front==end){
            return ans[end];
        }
        
        for(auto num:arr){
            int newNode = (front*num)%mod;
            if(ans[newNode]==-1){ // Matlab not visited hai 
                ans[newNode] = ans[front] + 1;
                qu.push(newNode); 
            }
        }
    }
    
    return -1;
}

// Q3. Find the City With the Smallest Number of Neighbors at a Threshold Distance - (LC 1334)
int dijkstra(int n,int srcNode, unordered_map<int,list<pair<int,int>>> &adjList, int &disanceThreshold){
    vector<int> distance(n+1,INT_MAX);
    set<pair<int,int>> st; // {distance,node}

    // Initial State
    // Yaha, source node ka distance and source node ko push karo
    st.insert({0,srcNode});
    distance[srcNode] = 0;
    int reachableCities = 0;

    while(!st.empty()){
        auto topEleIndex = st.begin(); // Will give reference of element
        pair<int,int> topPair = *topEleIndex; // Dereference index to give the element

        int topDist = topPair.first;
        int topNode = topPair.second;

        st.erase(st.begin());

        if(topNode != srcNode && topDist <= disanceThreshold){
            reachableCities++;
        }

        // Update distance of neighbours
        for(auto neighbourPair:adjList[topNode]){
            int neighbourNode = neighbourPair.first;
            int neighbourDist = neighbourPair.second;
            int currDist = topDist + neighbourDist;

            if(currDist < distance[neighbourNode]){
                // Matlab agar phele ka distance + curr distance < existing, toh update in the set as we have a new entry. Phele set ki entry nikalo, phir distance array update karo aur phir daal do set mein. Make sure this order is maintained
                auto prevEntry = st.find({distance[neighbourNode],neighbourNode});
                if(prevEntry!=st.end()){
                    st.erase(prevEntry);
                }

                // Now, also update in the distane array
                distance[neighbourNode] = currDist;

                // Finally, insert the new entry in the stack
                st.insert({distance[neighbourNode],neighbourNode});
                
            }
        }
    }

    return reachableCities;
}

int findTheCity(int n, vector<vector<int>>& edges, int distanceThreshold) {
    unordered_map<int,list<pair<int,int>>> adjList;

    for(auto edge:edges){
        int &u = edge[0];
        int &v = edge[1];
        int &weight = edge[2];

        // Since undirected, put u->v and v->u
        adjList[u].push_back({v,weight});
        adjList[v].push_back({u,weight});
    }

    int city = 0;
    int minReachableCities = INT_MAX;

    for(int i = 0; i<n;i++){
        int reachableCityCount = dijkstra(n,i,adjList,distanceThreshold);
        if(reachableCityCount <= minReachableCities){
            minReachableCities = reachableCityCount;
            city = i;
        }
    }

    return city; 
}

// Q4. Prim's Algorithm - (GFG)
// Spanning Tree is a tree that connects all the vertices in a graph without any cycles and with minimum possible total edge weight.
// Basically, it has 3 properties:
// a. We convert a tree to a graph by adding edges
// b. It has V-1 edges and V nodes
// c. Every node is reachable from every other node

// Prim's Algorithm is used to find the minimum spanning tree in a graph
// Basically, each edge would be having a weight, and we need to find the minimum weight edge that connects the tree
// Matlab ek aisa spanning tree banana hai jo purre tree ka cummulative weight ko minimum karre aur saath mein saare nodes ko connect kare
int getMinValueNodeIndex(vector<int> &key,vector<int> &MST){ // Here, the answer will give the index, which will represent the actual node
    int nodeValue = INT_MAX;
    int index = -1;
    for(int i=0;i<key.size();i++){
        if(key[i]<nodeValue && MST[i]==0){ // Matlab node with min weight jo abh tak mst mein nahi hai
            nodeValue = key[i];
            index = i;
        }
    }
    
    return index;
}


int spanningTree(int V, vector<vector<int>> adj[]){
    // Prim's Algo
    
    vector<int> key(V,INT_MAX); // Stores min spanning tree ke edge ka min weight
    vector<int> MST(V,0); // to keep track of which nodes are added to the MST
    vector<int> parent(V,-1); // stores final MST ka parent relation
    
    // Initiliasiation
    key[0] = 0;
    
    
    while(true){
        int u = getMinValueNodeIndex(key,MST); 
        // break condition check, matlab jaha koi min node which is not visited milli hi nahi
        if(u==-1){
            break;
        }
        
        MST[u] = 1;
        
        // Now, we process all adjacent nodes to u
        for(auto edge: adj[u]){
            int v = edge[0];
            int weight = edge[1];
            
            if(MST[v]==0 && weight<key[v]){
                key[v] = weight;
                parent[v] = u;
            }
        }
    }
    
    int sum = 0;
    for(int i=0;i<key.size();i++){
        sum += key[i];
    }
    
    return sum;
}

// Q5. Kruskal's Algorithm - (GFG)
// Kruskal's Algorithm is used to find the minimum spanning tree in a graph
// Here, the concept of union set and path compression is used, revise that from video
// It asks for a linear data structure to store the edges, so we will use a vector of pairs to store the edges and their weights, and we keep it sorted by weights
// We keep it sorted as we have to start processing with the minimum weight edge first
// We keep a parent array to keep track of the parent of each node, and we keep updating it as we keep adding edges. We update based on rank, and we keep the parent of the node with higher rank as the parent of the node with lower rank

static bool myComp(vector<int> &a,vector<int> &b){
    return a[2]<b[2]; // Sort it via weights
}

int findParent(vector<int> &parent,int node){
    if(parent[node]==node){ // matlab khud ka hi parent hai, so return itself
        return node;
    }
    
    return parent[node] = findParent(parent,parent[node]); // find the parent recursively and store it for current node i.e. path compression
}

void unionSet(int u,int v,vector<int> &parent,vector<int> &rank){ 
        if(rank[u]<rank[v]){ // Yani v ki rank badi, make it parent of u and update rank
            parent[u] = v;
            rank[v]++;
        }
        else{ // matlab u ki rank badi, so make u parent of v and update rank
            parent[v] = u;
            u++;
        }
}


int spanningTree(int V, vector<vector<int>> adj[]){
    // Kruskal's Algo
    vector<int> parent(V);
    vector<int> rank(V,0);
    
    for(int u=0;u<V;u++){ // Make all nodes as individual components, yaani khud ke hi parent
        parent[u]=u;
    }
    
    // Make edges Linear DS
    vector<vector<int>> edges; // { u,v,wt } -> u se v tak ka edge with "wt" jitna weight
    for(int u=0;u<V;u++){
        for(auto edge:adj[u]){
            int v = edge[0];
            int weight = edge[1];
            edges.push_back({u,v,weight});
        }
    }
    
    // Now, sort the edges Linear DS
    sort(edges.begin(),edges.end(),myComp);
    
    int ans = 0;
    
    for(auto edge:edges){
        int u = edge[0];
        int v = edge[1];
        int weight = edge[2];
        
        u = findParent(parent,u);
        v = findParent(parent,v);
        
        if(u==v){ // Matlab if they both have same parents, ignore
            continue;
        }
        else if(u!=v){
            // Matlab we will include the initial edge, and use it's weight in final ans
            unionSet(u,v,parent,rank);
            ans += weight;
        }
    }
    
    return ans;
}

// Q6. Account Merge - (LC 721) - V.V.V.V.V IMP
int findParent(vector<int> &parent,int node){
    if(parent[node]==node){ // matlab khud ka hi parent hai, so return itself
        return node;
    }
    
    return parent[node] = findParent(parent,parent[node]); // find the parent recursively and store it for current node i.e. path compression
}

void unionSet(int u,int v,vector<int> &parent,vector<int> &rank){ 
    u = findParent(parent,u);
    v = findParent(parent,v);
    if(rank[u]<rank[v]){ // Yani v ki rank badi, make it parent of u and update rank
            parent[u] = v;
            rank[v]++;
    }
    else{ // matlab u ki rank badi, so make u parent of v and update rank
            parent[v] = u;
            u++;
    }
}

vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
    int n = accounts.size();

    vector<int> parent(n);
    vector<int> rank(n,0);

    for(int u=0;u<n;u++){
        parent[u] = u;
    }

    unordered_map<string,int> mp; // to store mail ID and it's original owner

    for(int i=0;i<n;i++){
        auto account = accounts[i];
        for(int j = 1;j<account.size();j++){
            string&mail = account[j]; // address of mail
            auto it = mp.find(mail);
            if(it==mp.end()){
                // matlab mail exist nahi karti hai already map mein
                mp[mail] = i;
            }
            else{
                // matlab already exist karta hai, toh current user ka and iska union kar do
                unionSet(i,it->second,parent,rank);
            }
        }
    }

    unordered_map<int,set<string>> preAns; // to store owner ID and it's respective emails in sorted order
    for(auto it:mp){
        int accountNo = it.second;
        auto mail = it.first;

        accountNo = findParent(parent,accountNo); // Will store current owner ka parent, effectively merging the owners
        preAns[accountNo].insert(mail);
    }

    vector<vector<string>> ans;
    for(auto it:preAns){
        int ownerID = it.first;
        auto ownerName = accounts[ownerID][0];
        auto ownerEmails = it.second;

        vector<string> temp;
        temp.push_back(ownerName);
        for(auto mail:ownerEmails){
            temp.push_back(mail);
        }
        ans.push_back(temp);
    }

    return ans;

}

// Q7. Number of operations to make network connected - (LC 1319)
// Here, we need (n-1) edges to connect n components, so if we have less than n-1 edges, we can't connect all components
// Also, for each component, we need to find the number of extra edges. Basically, a component with n nodes needs n-1 edges to connect all nodes, so we need to find if that component has any extra edges.
// If total number of extra edges >= number of components - 1, then we can connect all components, else we return -1
int findParent(vector<int> &parent,int node){
    if(parent[node]==node){ // matlab khud ka hi parent hai, so return itself
        return node;
    }
    
    return parent[node] = findParent(parent,parent[node]); // find the parent recursively and store it for current node i.e. path compression
}

void unionSet(int u,int v,vector<int> &parent,vector<int> &rank){ 
    if(rank[u]<rank[v]){ // Yani v ki rank badi, make it parent of u and update rank
            parent[u] = v;
            rank[v]++;
    }
    else{ // matlab u ki rank badi, so make u parent of v and update rank
            parent[v] = u;
            u++;
    }
}

int makeConnected(int n, vector<vector<int>>& connections) {
    vector<int> parent(n);
    vector<int> rank(n,0);

    for(int u=0;u<n;u++){
        parent[u] = u;
    }

    int noOfExtraEdges = 0;
    for(auto connection:connections){
        int u = connection[0];
        int v = connection[1];

        u = findParent(parent,u);
        v = findParent(parent,v);

        if(u!=v){ // Matlab both nodes in different component, so dono ka union kar do
            unionSet(u,v,parent,rank);
        }
        else{
            // Matlab dono ka parent same hai, so matlab we are trying to connect two nodes again in the same component i.e. extra edge hai
            noOfExtraEdges++;
        }
    }

    int noOfConnectedComponents = 0;
    for(int u=0;u<n;u++){
        if(parent[u]==u){
            noOfConnectedComponents++;
        }
    }

    int edgesNeededtoConnectAllComponents = noOfConnectedComponents-1;
    if(noOfExtraEdges >= edgesNeededtoConnectAllComponents){
        return edgesNeededtoConnectAllComponents;
    }
    else{
        return -1;
    }
}

// Q8. Word Ladder - (LC 127)
int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
    unordered_set<string> st(wordList.begin(),wordList.end());

    queue<pair<string,int>> qu;
    int noOfOperations = 1; // As beginWord will never be equal to endWord
    qu.push({beginWord,noOfOperations});
    // Abh jo bhi word queue mein chala gaya, usse set se erase kar do - IMP CONDITION
    st.erase(beginWord);

    while(!qu.empty()){
        auto front = qu.front();
        qu.pop();

        string currString = front.first;
        int currCount = front.second;

        if(currString==endWord){
            return currCount;
        }

        for(int index = 0;index<currString.length();index++){
            // Har index pe jo value hai, usko a-z se replace karke check karo. However, track the original position of modifying character taaki alge loop ke liye we can correct it from it's original position
            char originalCharacter = currString[index];
            for(char ch='a';ch<='z';ch++){
                currString[index] = ch; // Creates a new Word
                // Check if the new string is present in set
                if(st.find(currString)!=st.end()){
                    // Matlab a valid word, so insert in queue and remove the word from set
                    qu.push({currString,currCount+1});
                    st.erase(currString);
                }
            }
            currString[index] = originalCharacter; // IMP - bringing back the currString to it's original state
        }
    }
    return 0;
}

// Q9. Word Ladder II - GFG
vector<vector<string>> findSequences(string beginWord, string endWord, vector<string>& wordList) {
    unordered_set<string> st(wordList.begin(),wordList.end());
    vector<vector<string>> ans;

    queue<pair<vector<string>,int>> qu; // {[sequence of strings],count}
    int noOfOperations = 1; // As beginWord will never be equal to endWord
    qu.push({{beginWord},noOfOperations});

    int prevLevel = -1;
    vector<string> stringsToBeRemoved;

    while(!qu.empty()){
        auto front = qu.front();
        qu.pop();

        vector<string> currSequence = front.first;
        auto currString = currSequence[currSequence.size()-1]; // Modifications will only happen to last string of the current sequence
        int currLevel = front.second;

        if(currLevel!=prevLevel){
            // Matlab iss level pe aake pichle saare level ke strings to be removed ko hatta do 
            for(auto str:stringsToBeRemoved){
                st.erase(str);
            }
            stringsToBeRemoved.clear();
            prevLevel = currLevel;
        }

        if(currString==endWord){
            ans.push_back(currSequence);
        }

        for(int index = 0;index<currString.length();index++){
            // Har index pe jo value hai, usko a-z se replace karke check karo. However, track the original position of modifying character taaki alge loop ke liye we can correct it from it's original position
            char originalCharacter = currString[index];
            for(char ch='a';ch<='z';ch++){
                currString[index] = ch; // Creates a new Word
                // Check if the new string is present in set
                if(st.find(currString)!=st.end()){
                    // Matlab a valid word, so insert in temp sequence to create a new sequence
                    auto temp = currSequence;
                    temp.push_back(currString);
                    qu.push({temp,currLevel+1});
                    // Also, add these strings which are to be removed from final wordList - V.V.V IMP CONDITION
                    stringsToBeRemoved.push_back(currString);
                }
            }
            currString[index] = originalCharacter; // IMP - bringing back the currString to it's original state
        }
    }

    return ans;
}

