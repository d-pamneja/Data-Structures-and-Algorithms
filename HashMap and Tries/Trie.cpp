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
//insertion
void insertWord(TrieNode* root, string word) {
  //cout << "recieved word: " << word << " for insertion " << endl;
  //base case
  if(word.length() == 0) {
    root->isTerminal = true;
    return;
  }

  char ch = word[0];
  int index = ch - 'a';
  TrieNode* child;
  if(root->children[index] != NULL) {
    //present
      child = root->children[index];
  }
  else {
    //absent
     child = new TrieNode(ch);
     root->children[index] = child;
  }

  //recursion
  insertWord(child, word.substr(1));

}

bool searchWord(TrieNode* root, string word) {
  //base case
  if(word.length() == 0) {
    return root->isTerminal;
  }

  char ch = word[0];
  int index = ch - 'a';
  TrieNode* child;

  if(root->children[index] != NULL) {
    //present or found
    child = root->children[index];
  }
  else {
    //not found
    return false;
  }

  ///baaaki recursion
  bool recursionKaAns = searchWord(child, word.substr(1));
  return recursionKaAns;

}

void deleteWord(TrieNode* root, string word ) {
  if(word.length() == 0) {
    root->isTerminal = false;
    return;
  }

  //1 case mera
  char ch = word[0];
  int index = ch - 'a';
  TrieNode* child;

  if(root->children[index] != NULL) {
    //present, so traverse there
    child = root->children[index];
  }
  else{
    //not present
    return;
  }
  //baaki recursion tera
  deleteWord(child, word.substr(1));
}

void storeString(TrieNode* root, vector<string>& ans, string &input, string& prefix) {
  //base case
  if(root->isTerminal == true) {
    //ans store
    ans.push_back(prefix + input);
    //return ?
  }

  for(char ch='a'; ch<='z'; ch++) {
    int index = ch - 'a';
    TrieNode* next = root->children[index];
    if(next != NULL) {
      //child exist
      input.push_back(ch);
      //baaaki recursion
      storeString(next, ans, input, prefix);
      //backtrack
      input.pop_back();
    }
  }
}

void findPrefixString(TrieNode* root, string input, vector<string>& ans, string &prefix) {
  //base case
  if(input.length() == 0) {
    TrieNode* lastchar = root;
    storeString(lastchar, ans, input, prefix);
    return;
  }
  char ch = input[0];
  int index = ch - 'a';
  TrieNode* child;
  if(root->children[index] != NULL) {
    //child present
    child = root->children[index];
  }
  else {
    return;
  }
  //recursive call
  findPrefixString(child, input.substr(1), ans, prefix);
}

vector<vector<string> > getSuggestions(TrieNode* root, string input) {

  vector<vector<string> > output;
  TrieNode* prev = root;
  string inputhelper = "";

  for(int i=0; i<input.length(); i++) {
    char lastchar = input[i];
    int index = lastchar - 'a';
    TrieNode* curr = prev->children[index];

    if(curr == NULL) {
      break;
    }
    else {
      vector<string> nicheKaAns;
      inputhelper.push_back(lastchar);
      string dummy = ""; // We pass dummy cause we do not want to add anything
      storeString(curr, nicheKaAns, inputhelper, dummy);
      output.push_back(nicheKaAns);
      //important, prev ko agge badha kar current pe kar do
      prev = curr;
    }

  }
  return output;
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


int main() {
  TrieNode* root = new TrieNode('-');

  insertWord(root, "cater");
  insertWord(root, "care");
  insertWord(root, "com");
  insertWord(root, "lover");
  insertWord(root, "loved");
  insertWord(root, "load");
  insertWord(root, "lov");
  insertWord(root, "bat");
  insertWord(root, "cat");
  insertWord(root, "car");

  vector<vector<string> > ans = getSuggestions(root, "loa");
  //printing ans
  for(int i=0; i<ans.size(); i++) {
    cout << i << " -> ";
    for(auto str: ans[i]) {
      cout << str <<", ";
    }cout << endl;
  }


  // string input = "car ";
  // string prefix = input;
  // vector<string> ans;

  // findPrefixString(root, input, ans, prefix);

  // for(auto i: ans) {
  //   cout << i << " ";
  // }
  // cout << endl;



  return 0;
}
