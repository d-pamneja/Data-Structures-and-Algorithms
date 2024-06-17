#include <iostream>
#include <vector>
#include <limits.h>
#include <string.h>
#include <math.h>
using namespace std;



// Bitwise operators
// Some basic assumptions are that we should know the tabular representation of operations such as : 
// 1. AND
// 2. OR
// 3. XOR
// 4. NOT/NEGATION
// 5. LEFT SHIFT
// 6. RIGHT SHIFT

// Most significant bit is the leftmost bit and the least significant bit is the rightmost bit.

// Also, we should know the conversion of 
// 1. Decimal to Binary
// 2. Binary to Decimal

// We should also know the complement of :
// 1. 1's complement - In this, we just flip the bits
// 2. 2's complement - In this, we flip the bits and add 1 to the least significant bit

// We should also know the SIGN BIT and how it is used to represent the sign of the number
// If the sign bit is 0, then the number is positive
// If the sign bit is 1, then the number is negative

// In case of odd-even numbers :
// If the least significant bit (rightmost bit) is 0, then the number is even
// If the least significant bit (rightmost bit) is 1, then the number is odd

// If a number is operated with & 1, and the answer is 0, then the number is even
// If a number is operated with & 1, and the answer is 1, then the number is odd

// If a number is operated with & 0, and the answer is 0, then the number is even
// If a number is operated with & 0, and the answer is 1, then the number is odd

string getOddEven(int n){
  if(n & 1){
    return "Odd";
  }
  else{
    return "Even";
  }
}

// If a number is operated with >> 1, then the number is divided by 2
// If a number is operated with << 1, then the number is multiplied by 2

// Now, if we want to find the ith bit of a number, we can use the concept of MASKING and BITWISE AND
// We can use the formula :
// 1. We create a mask by using 1 << i (This will create a number with ith bit as 1 and all other bits as 0)
// 2. We then use the formula : (n & mask)
// 3. If the answer is 0, then the ith bit is 0
// 4. If the answer is 1, then the ith bit is 1

char getBit(int n,int i){
  int mask = (1<<i);
  int ans = n & mask;

  if(ans==0){
    return '0';
  }
  else{
    return '1';
  }
}

// Now, if we want to find the number of set bits in a number, we can use the concept of MASKING and BITWISE AND
// We can use the formula :
// 1. We will run a loop till n==0
// 2. We will find the last bit using n & 1
// 3. If the last bit is 1, we will increment the count
// 4. Then, we will right shift the number by 1

int countSetBits(int N){
    int count = 0;
    while(N>0){
        count += (N & 1);
        N = N>>1;
    }
    return count;
}


// If we want to set the ith bit of a number, we can use the concept of MASKING and BITWISE OR
// We can use the formula :
// 1. We create a mask by using 1 << i (This will create a number with ith bit as 1 and all other bits as 0)
// 2. We then use the formula : (n | mask)
// 3. This will set the ith bit of the number to 1

int setKthBit(int N, int K){
    int mask = 1<<K;
    N = N | mask;
    return N;
}

// Another apporach to count set bits fastly is (n & (n-1))
// This will clear the last set bit of the number
// So, we can run a loop till n!=0 and keep clearing the last set bit
// The number of times we clear the last set bit will be the number of set bits in the number
// This is way faster than the previous approach

int countSetBitsFast(int N){
    int count = 0;
    while(N>0){
        N = N & (N-1);
        count++;
    }
    return count;
}

// If we want to clear the ith bit of a number, we can use the concept of MASKING and BITWISE AND
// We can use the formula :
// 1. We create a mask by using ~(1 << i) (This will create a number with ith bit as 0 and all other bits as 1)
// 2. We then use the formula : (n & mask)
// 3. This will clear the ith bit of the number

int clearBit(int N,int K){
  int mask = (1<<K);
  mask = ~mask; // negation effectivekly flips all bits
  N = N & mask;
  return N;
}

// If we want to clear last K bits of a number, we can use the concept of MASKING and BITWISE AND
// We can use the formula :
// 1. We create a mask by using (-1 << K) (This will create a number with last K bits as 0 and all other bits as 1) (as -1 is all 1's)
// 2. We then use the formula : (n & mask)
// 3. This will clear the last K bits of the number

int clearKBits(int N,int K){
  int mask = (-1<<K);
  N = N & mask;
  return N;
}

// Now, to clear bits in a range from i to j, we can use the concept of MASKING and BITWISE AND
// We can use the formula :
// 1. We create two masks by using (-1 << (i+1)) and ~(1 << j) (This will create a number with ith to jth bits as 0 and all other bits as 1)
// 2. We then use the formula : (n & mask)
// 3. This will clear the bits in the range i to j of the number
int clearBitsRange(int n, int i, int j){
  int mask1 = (-1<<(i+1)); // V.IMP to shift (i+1) times
  int mask2 = ~(-1<<j);

  int mask = mask1 | mask2;

  n = n & mask;

  return n;
}

// If we want to update the ith bit of a number, we can use the concept of MASKING and BITWISE OR
// We can use the formula :
// 1. We create a mask by using ~(1 << i) (This will create a number with ith bit as 0 and all other bits as 1)
// 2. We then use the formula : (n & mask)
// 3. This will clear the ith bit of the number

int updateBit(int N,int K,int target){
  N = clearBit(N,K);
  int mask = (target<<K); 
  N = N | mask;
  return N;
}


// Q1. Single Number (LC-136)
int singleNumber(vector<int>& nums) {
    // Will be done using XOR operator
    int ans = 0;
    for(int i=0;i<nums.size();i++){
        ans = ans ^ nums[i];
    }
    return ans;
}

// Q2. Power of Two (LC-231)
bool isPowerOfTwo(int n) {
    int setBits = countSetBits(n);
    if(setBits==1){ // As all numbers which are in form 2^n have exactly one set bit
        return true;
    }
    else{
        return false;
    }

    // Another approach
    // if(n==0 || n==-2147483648) return false; // Base Case Handling
    // int ans = n & (n-1);
    // if(ans==0) return true;
    // else return false;
}

// Also, this can be done using the concept of BITWISE AND
// If a number is power of 2, then it will have only 1 set bit
// So, if we do n & (n-1) and the answer is 0, then the number is power of 2. Any number (n) when done & with (n-1) will clear the last set bit. 
// So, if the answer is 0 i.e. all set bits are clear, then the number is power of 2.

// Q3. Fast Expontiation using bitwise operators (LC-50)


// Q4. Power Set of a string (GFG) or (LC-78)
vector<string> AllPossibleStrings(string s){
    int n = s.length();
    vector<string> ans;
  
    for(int num = 0;num<(1<<n);num++){
      // Isse we get all possible numbers jinke corresponding subsequences banta hai
      // Abh, in curr num jaha par bhi set bit hai, uss index ka char include kar lo and push to final ans
  
      string temp = "";
      for(int i=0;i<n;i++){
        char ch = s[i];
        // Abh agar ith index pe set bit hai, store it in curr subsequence
        if(num & (1<<i)){ // will tell number ki ith bit konsi hai
          temp.push_back(ch);
        }
      }
      
      if(temp=="") continue;
      ans.push_back(temp);
    }
    
    sort(ans.begin(),ans.end());
    return ans;
}
