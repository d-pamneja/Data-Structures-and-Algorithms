#include <iostream>
#include <string.h>
#include <queue>
#include <unordered_map>
#include <map>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class stringCount{
    public:
        char ch;
        int count;

        stringCount(char c,int value){
            this->ch = c;
            this->count = value;
        }
};

class myComp{
    public:
        bool operator()(stringCount a,stringCount b){
            return a.count < b.count;
        }
};

// Q1. Reorganize String - Leetcode(767) - Using Map and MinHeap
string reorganizeString(string s) {
    string ans = "";
    unordered_map<char,int> freq;

    // 1. Count Frequency
    // int freq[26] = {0}; // Here, we will map A-Z to 0-25 index
    for(int i=0;i<s.length();i++){
        char ch = s[i];
        // freq[ch-'a']++; // ch - 'a' gets the alphabetical index of ch
        freq[ch]++;
    }

    // 2. Create MinHeap to store string and it's freq;
    priority_queue<stringCount,vector<stringCount>,myComp> pq;

    for(char i='a';i<='z';i++){
        if(freq[i]>0){
            stringCount temp(i,freq[i]); 
            pq.push(temp);
        }
    }

    // 3. Now, we take out two top chars from min-Heap and keep on inserting them in ans
    while(pq.size()>1){
        stringCount top1 = pq.top();
        pq.pop();

        stringCount top2 = pq.top();
        pq.pop();

        ans.push_back(top1.ch);
        top1.count--;

        ans.push_back(top2.ch);
        top2.count--;

        if(top1.count>0){
            pq.push(top1);
        }

        if(top2.count>0){
            pq.push(top2);
        }
    }

    // 4. There might be a case where a single element is left, so we place a check on that before entering

    if(pq.size()==1){
        stringCount top1 = pq.top();
        pq.pop();

        ans.push_back(top1.ch);
        top1.count--;

        if(top1.count!=0){ // Means answer NOT POSSIBLE
            return "";
        }

    }

    return ans;
}

// Q2. Linked List Cycle - Leetcode(141) - Using Map
bool hasCycle(ListNode *head) {

    // Map Approach
    map<ListNode*,bool> table;
    ListNode* temp = head;

    while(temp!=NULL){
        if(table.find(temp)!=table.end()){ // Means aleady existing element found, cycle exists
            return true;
        }
        else{ // Means visiting first time, so mark true
            table[temp]=true;
        }
        temp = temp->next;
    }
    // means no cycle/loop present
    return false;
    
}


int main() {
  // Creating a Map
  unordered_map<string,int> map;

  // Insertion - We ONLY insert pairs in a MAP - O(1)
  pair<string,int> p = make_pair("dhruv",25);
  pair<string,int> q("vineet",20);
  pair<string,int> r;
  r.first = "pamneja";
  r.second = 11;

  map.insert(p);
  map.insert(q);
  map.insert(r);
  map.insert({"ranvijay",25});

  map["singh"] = 11;
  map["balbir"] = 2000;

  // Size of Map
  cout<<"Size of Map : "<<map.size()<<endl;

  // Searching a Value via Key - O(1) [We are able to search as it is being implemented using an array and HASH function, in a black box method ]
  cout<<"Value of Dhruv : "<<map["dhruv"]<<endl; // IMP: If we try to find which is not there by this method, it will then CREATE that key after this line, thereby increasing the size
  cout<<"Value of Pamneja : "<<map.at("pamneja")<<endl;

  // Searching (Boolean) - O(1) 
  cout<<"Is Dhruv Present? "<<map.count("dhruv")<<endl;
  cout<<"Is Dhruv Present? "<<map.count("dhruvi")<<endl;

  if(map.find("dhruv")!=map.end()){ // This find function will find the value at stand on it's position if found, else will stand at map.end()
    cout<<"Found"<<endl;
  }
  else{
    cout<<"Not Found"<<endl;
  }
  

}