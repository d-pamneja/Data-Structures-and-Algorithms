# include <iostream>
# include <vector>
using namespace std;

void mergeArrays(vector<int> &arr,int low,int mid,int high){
    vector<int> temp;
    int left = low;
    int right = mid+1;


    while(left<=mid && right<=high){
        if(arr[left]<arr[right]){
            temp.push_back(arr[left++]);
        }
        else{
            temp.push_back(arr[right++]);
        }
    }

    while(left<=mid){
        temp.push_back(arr[left++]);
    }

    while(right<=high){
        temp.push_back(arr[right++]);
    }


    for(int i=low;i<=high;i++){
        arr[i] = temp[i - low];
    }
}

void SortMerge(vector<int> &arr,int low,int high){
    // Base Case
    if(low>=high) return;

    int mid = ((high - low)/2) + low;

    // Recursive Call
    SortMerge(arr,low,mid);
    SortMerge(arr,mid+1,high);

    // Merge Call
    mergeArrays(arr,low,mid,high);
}

void mergeSort(vector < int > & arr, int n) {
    if(n <= 1) return;

    int low = 0;
    int high = arr.size() -1;

    SortMerge(arr,low,high);

}