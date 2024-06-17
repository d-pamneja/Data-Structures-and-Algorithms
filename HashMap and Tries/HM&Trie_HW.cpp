#include <iostream>
#include <string.h>
#include <queue>
#include <unordered_map>
#include <map>
using namespace std;

class TrieNode{
  public:
    char value;
    TrieNode* children[26];
    bool isTerminal;

    TrieNode(char val) {
      this->value = val;
      for(int i=0; i<26; i++) {
        children[i] = NULL;
      }
      this->isTerminal = false;
    }
};

struct Node
{
	int data;
	struct Node* next;
	
	Node(int x){
	    data = x;
	    next = NULL;
	}
	
};

// Q1. Array Subset of another array - GFG
string isSubset(int a1[], int a2[], int n, int m) { // TC :O(m+n), SC: O(n)
    unordered_map<int,int> map;
    string ans = "Yes";
    
    for(int i=0;i<n;i++){ // Store elements in A1
        map[a1[i]]++;
    }
    
    // Check all elements of A2 in A1 in exact same quantity
    for(int i=0;i<m;i++){ 
        if(map.find(a2[i])==map.end()){ // Means not present, so exit
            ans = "No";
            break;
        }
        else{ // Present
            if(map[a2[i]]>0){
                map[a2[i]]--;
            }
            else{
                ans = "No";
                break;
            }
        }
    }
    
    return ans;
}

// Q2. Union of two Linked Lists - GFG
struct Node* makeUnion(struct Node* head1, struct Node* head2){ // TC: O(n+m), SC: O(n+m)
    map<int,Node*> map;
    
    Node* curr = head1;
    while(curr){ // Enter first LL in map
        map[curr->data] = curr;
        curr = curr->next;
    }
    
    curr = head2;
    while(curr){ // Enter second LL in map
        map[curr->data] = curr;
        curr = curr->next;
    }
    
    curr = 0;
    Node* UL = NULL;
    for(auto it = map.begin();it!=map.end();it++){ // Iterate the map and add to new UL
        if(curr==0){ // No list, so create first node and place head
            UL = it->second;
            curr = UL;
        }
        else{ // Add to the end of the list
            curr->next = it->second; 
            curr = curr->next;
        }
    }
    curr->next = NULL; // Set the last node as tail node
    
    return UL;
}

// Q3. Intersection of two Linked Lists - GFG
Node* findIntersection(Node* head1, Node* head2){ // TC: O(n+m), SC: O(n)
    unordered_map<int,int> map; //{element, number of occurence}, use onordered as it does most in O(1)

    Node* curr = head2;
    while(curr){ // Hash elements of list 2, as we need the ordering later by list 1
        map[curr->data]++;
        curr = curr->next;
    }
    
    Node* IL = NULL; // Head of IL
    Node* looper = 0; // Use to iterate IL
    curr = head1; // Use to iterate list 1
    
    while(curr){
        if(map.find(curr->data) != map.end()){
            if(!IL){ // First element of IL, so set head and looper
                IL = curr;
                looper = IL;
            }
            else{
                if(map[curr->data] > 0){ // Means same occurence exists. With this, we only map elements with same value and same occurence
                    looper->next = curr;
                    looper = looper->next;
                    map[curr->data]--;
                }
            }
        }
        curr = curr->next;
    }
    
    if(looper){
        looper->next = NULL;
    }
    
    return IL;
}

// Q4. Sum Equals Sum - GFG
int findPairs(long long a[], long long n){ // TC: O(n^2), SC: O(n)
    unordered_map<long long,bool> map;
    
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            int sum = a[i] + a[j]; // Make pairs of sum 
            if(map.find(sum)!=map.end()){ // Means same pair exist, so return true
                return 1;
            }
            else{ // Store sum
                map[sum] = true;
            }
        }
    }
    
    return 0;
}

// Q5.Largest subarray with 0 sum - GFG
int maxLen(vector<int>&A, int n){  // TC: O(n), SC: O(n)
    unordered_map<int,int> map;
    
    int csum = 0; 
    int maxi = 0; // Will store length of subarray with MaxSum
    
    for (int i = 0; i < A.size(); i++) {
        csum += A[i];
    
        if (csum == 0) {/// Agar current sum khud hi 0 aa gaya, means yaha se lekar peeche tak sabh sum hokar 0 ho raha hai, so add that subarray.
            maxi = max(maxi, i + 1);
        } 
        else if (map.find(csum) == map.end()) { // Means nahi mila, so add it
            map[csum] = i;
        } 
        else { // Same mil gaya, matlab beech mein 0 bana hai
            maxi = max(maxi, i - map[csum]);
        }
    }
    
    return maxi; 
}

// Q6. Largest subarray of 0's and 1's - GFG
int maxLen(int arr[], int N){ // TC: O(n), SC: O(n) 
    unordered_map<int,int> map;
    
    int csum = 0; 
    int maxi = 0; // Will store length of subarray with MaxSum
    
    for (int i = 0; i < N; i++) { 
        int val = arr[i] == 0? -1:1; // Set all 0s to -1, and then the logic for largest subarray with sum 0 will work
        csum += val;
    
        if (csum == 0) {// Agar current sum khud hi 0 aa gaya, means yaha se lekar peeche tak sabh sum hokar 0 ho raha hai, so add that subarray. 
            maxi = max(maxi, i + 1);
        } 
        else if (map.find(csum) == map.end()) { // Means nahi mila, so add it
            map[csum] = i;
        } 
        else { // Same mil gaya, matlab beech mein 0 bana hai
            maxi = max(maxi, i - map[csum]);
        }
    }
    
    return maxi; 
}


// Q7. Replace words - LeetCode(648) - V.IMP
class Trie {
    TrieNode* root;

    void INSERT(TrieNode* root, string &word, int i) {
        if (i >= word.size()) {
            root->isTerminal = true;
            return;
        }

        int index = word[i] - 'a';

        if (!root->children[index]) {
            root->children[index] = new TrieNode(word[i]);
        }

        // Recursion
        INSERT(root->children[index], word, i + 1);
    }

    bool SEARCH(TrieNode* root, string &word, int &i) {
        if (root->isTerminal) {
            return true;
        }

        if (i >= word.size()) {
            return root->isTerminal;
        }

        int index = word[i++] - 'a';

        // Check if child node exists before accessing members
        if (root->children[index]) {
            // Recursion
            return SEARCH(root->children[index], word, i);
        }

        return false;
    }

    bool STARTSWITH(TrieNode* root, string &word, int i) {
        if (i >= word.size()) {
            return true;
        }

        int index = word[i] - 'a';

        // Check if child node exists before accessing members
        if (root->children[index]) {
            // Recursion
            return STARTSWITH(root->children[index], word, i + 1);
        }

        return false;
    }
public:
    Trie(){
        root = new TrieNode('\0');
    }
    
    void insert(string word) {
        INSERT(root,word,0);
    }
    
    int search(string word) {
        int i = 0;
        bool gotIt = SEARCH(root,word,i);;
        return gotIt ? i : -1;
    }
    
    bool startsWith(string prefix) {
        return STARTSWITH(root,prefix,0);
    }
};


class Solution {
public:
string replaceWords(vector<string>& dictionary, string sentence) { // TC: O(n), SC: O(m)
    string ans = "";
    Trie trie;

    // Insert dictionary into trie
    for(auto el:dictionary){
        trie.insert(el);
    }

    // Pick each word and find if it is in trie
    int start = 0;
    int end = 0;
    while(end<sentence.size()){
        if(sentence[end]==' ' || end==sentence.size()-1){ // Means new or final word of the sentence pe end khada hai
            int len = end == sentence.size() - 1 ? sentence.size():end - start;
            string word = sentence.substr(start,len); // Will give each word one by one

            int trieMatchIndex = trie.search(word); // Will tell ki trie mein kitne char match hue hai current word ke, index of that
            ans += trieMatchIndex!= -1 ? word.substr(0,trieMatchIndex):word;

            if(sentence[end]==' '){
                ans+= ' ';
            }
                        start = end + 1;
        }
        ++end;
    }

    return ans;

}
};

// Q8. Top K Frequent Words - LeetCode(692) - V.V.V.IMP
class TrieNode{
  public:
    char value;
    TrieNode* children[26];
    bool isTerminal;
    int frequency;

    TrieNode(char val) {
      this->value = val;
      for(int i=0; i<26; i++) {
        children[i] = NULL;
      }
      this->isTerminal = false;
      this->frequency = 0;
    }
};

class myComp{
    public:
        bool operator()(const pair<int,string> &a,const pair<int,string> &b){
            return a.first==b.first ? a < b : a.first > b.first; // If same freq, return lexo smaller word, else the word with larger frew
        }
};

class Trie2 {
    TrieNode* root;

    void INSERT(TrieNode* root, string &word, int i) {
        if (i >= word.size()) {
            root->isTerminal = true;
            ++root->frequency;
            return;
        }

        int index = word[i] - 'a';

        if (!root->children[index]) {
            root->children[index] = new TrieNode(word[i]);
        }

        // Recursion
        INSERT(root->children[index], word, i + 1);
    }

    void TRAVERSE(TrieNode* root,string &s,priority_queue<pair<int,string>,vector<pair<int,string>>,myComp> &pq,int k){
        if(!root){
            return;
        }
        if(root->isTerminal){
            if(pq.size()<k){
                pq.push({root->frequency,s});
            }
            else if(pq.size()==k && root->frequency > pq.top().first){  // IMPORTANT
                //Storing the top k frequent word 
                pq.pop();
                pq.push({root->frequency,s});
            }
        }
        for(int i=0;i<26;i++){
            if(root->children[i]){
                s.push_back(i+'a');
                TRAVERSE(root->children[i],s,pq,k);
                s.pop_back(); // Backtracking
            }
        }
    }
public:
    Trie2(){
        root = new TrieNode('\0');
    }
    
    void insert(string word) {
        INSERT(root,word,0);
    }

    void traverse(priority_queue<pair<int,string>,vector<pair<int,string>>,myComp> &pq,int k){
        string s;
        TRAVERSE(root,s,pq,k);
    }
};




class Solution {
public:

    vector<string> topKFrequent(vector<string>& words, int k) { // TC: O(n*log(k)), SC: O(n)
        Trie2 trie;
        vector<string> ans;

        for(auto word:words){ // Using trie as a hash map
            trie.insert(word);
        }

        priority_queue<pair<int,string>,vector<pair<int,string>>,myComp> pq;
        trie.traverse(pq,k);

        while(!pq.empty()){
            auto top = pq.top();
            pq.pop();

            ans.push_back(top.second);
        }

        reverse(ans.begin(),ans.end()); // Since pq (min heap) is sorted by word order and not count order, we reverse it

        return ans;

    }
};

// Q9. Camelcase Matching - LeetCode(1023) - V.V.V.IMP
class TrieNode2{
  public:
    char value;
    TrieNode2* children[58]; // Since we have to store both lower and upper case 
    bool isTerminal;

    TrieNode2(char val) {
      this->value = val;
      for(int i=0; i<58; i++) {
        children[i] = NULL;
      }
      this->isTerminal = false;
    }
};

class Trie {
    TrieNode2* root;

    void INSERT(TrieNode2* root, string &word, int i) {
        if (i >= word.size()) {
            root->isTerminal = true;
            return;
        }

        int index = word[i] - 'A';

        if (!root->children[index]) {
            root->children[index] = new TrieNode2(word[i]);
        }

        // Recursion
        INSERT(root->children[index], word, i + 1);
    }

    bool SEARCHSPL(TrieNode2* root, string &word, int i) {
        if (i >= word.size()) {
            return root->isTerminal;
        }

        int index = word[i] - 'A';

        // Check if child node exists before accessing members
        if (root->children[index]) {
            // Recursion
            return SEARCHSPL(root->children[index], word, i+1);
        }
        else if(islower(word[i])){
            return SEARCHSPL(root,word,i+1); // Matlab agar lower case mila hai, toh consume kar do i.e. do not move from the position on the tree
        }

        return false;
    }

public:
    Trie(){
        root = new TrieNode2('\0');
    }
    
    void insert(string &word) {
        INSERT(root,word,0);
    }
    
    int search(string &word) {
        return SEARCHSPL(root,word,0);
    }

};

vector<bool> camelMatch(vector<string>& queries, string pattern) { // TC: O(Pattern Length) + O(n*m), SC: O(Pattern Length)
    vector<bool> ans;
    Trie trie;
    trie.insert(pattern);

    for(auto qr:queries){
        ans.push_back(trie.search(qr));
    }

    return ans;
}


// Q10. Palindrome Pairs - LeetCode(336) - V.V.V.V.V.IMP
class TrieNode3{
  public:
    char value;
    TrieNode3* children[26];
    int stringNum; // Stores the index at which the string is 

    TrieNode3(char val) {
      this->value = val;
      for(int i=0; i<26; i++) {
        children[i] = NULL;
      }
      this->stringNum = -1;
    }
};

class Trie3 {
    TrieNode3* root;

    void INSERT(TrieNode3* root, string &word, int i,int &stringNum) {
        if (i >= word.size()) {
            root->stringNum = stringNum ;
            return;
        }

        int index = word[i] - 'a';

        if (!root->children[index]) {
            root->children[index] = new TrieNode3(word[i]);
        }

        // Recursion
        INSERT(root->children[index], word, i + 1,stringNum);
    }

public:
    Trie3(){
        root = new TrieNode3('\0');
    }
    
    void insert(string &word, int &stringNum) {
        INSERT(root,word,0,stringNum);
    }

    bool isPalindrome(string &s,int low,int high){
        while(low<=high){
            if(s[low]!=s[high]){
                return false;
            }
            low++;
            high--;
        }
        return true;
    }

    void searchCase2(TrieNode3* root,vector<int> &myPalindrome,string s){
        // Base Case
        if(root->stringNum != -1){
            if(isPalindrome(s,0,s.size()-1)){
                myPalindrome.push_back(root->stringNum);
            }
        }

        for(int i=0;i<26;i++){
            if(root->children[i]!= 0){
                s.push_back(i+'a');
                searchCase2(root->children[i],myPalindrome,s);
                s.pop_back(); // Backtrack
            }
        }
    }
    
    void search(string word,vector<int> &myPalindrome) {
        TrieNode3* curr = root;

        // Case 1 : When prefix of the string word EXACTLY matches the with a word in the tire, searching word khatam ho gaya
        for(int i=0;i<word.size();i++){
            int index = word[i] - 'a';

            if(curr->stringNum!=-1){ // Matlab koi word pura match ho gaya hai
                // check is rest of the suffix string (rest of the search word) is a palindrome
                if(isPalindrome(word,i,word.size()-1)){
                    myPalindrome.push_back(curr->stringNum);
                }
            }

            if(curr->children[index]){ // Matlab curr ke children pe hai, toh agge badh jao
                curr = curr->children[index];
            }
            else{
                return;
            }
        }

        // Case 2 : search word is a prefix of a word in the trie, check the remaining subtrees in trie for the palindrome
        searchCase2(curr,myPalindrome,""); // Check if agge ki palinedrome hai khud ya nahi

    } 
};

vector<vector<int>> palindromePairs(vector<string>& words) { // TC : O(n*k^2) SC: O(n*k)
    vector<vector<int>> ans;
    Trie3 trie;
    // insert all the strings in reverse order and mark it's string number as index of that word
    for(int i=0;i<words.size();i++){
        auto word = words[i];
        reverse(word.begin(),word.end());
        trie.insert(word,i);
    }

    // finding all palindromic pairs of each word
    for(int i=0;i<words.size();i++){
        vector<int> myPalindrome; // Finds all palinedromic pairs of ith word

        trie.search(words[i],myPalindrome); 

        for(auto it:myPalindrome){
            if(it!=i){
                ans.push_back({i,it});
            }
        }
    }

    return ans;
}

// Q11. 
class Trie4{
    public:
        Trie4* children[2];
        int isLast = 0;
};

void solve(Trie4* root,int row,int col,int M[1000][1000],vector<vector<int>> &ans){
    vector<int> tempRow;
    
    for(int i=0;i<col;i++){
        int element = M[row][i];
        tempRow.push_back(element);
        
        if(!root->children[element]){ // Means child does not exist, so create it
            root->children[element] = new Trie4();
        }
        
        root = root->children[element]; // Child exists, so move to it now
    }
    
    root->isLast++; // Means one row is added and it's count is kept
    
    if(root->isLast == 1){ // Means row is truly unique so add it to final ans
        ans.push_back(tempRow);
    }
}
vector<vector<int>> uniqueRow(int M[1000][1000],int row,int col){
    vector<vector<int>> ans;
    Trie4* root = new Trie4();
    
    // Insert in trie
    for(int i=0;i<row;i++){
        solve(root,i,col,M,ans);
    }
    
    return ans;
}

 