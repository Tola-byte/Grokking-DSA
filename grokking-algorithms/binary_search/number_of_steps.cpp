// The binary_search function takes a sorted array and an item. If the item is in the array, the function returns its position.
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int binary_search(std::vector<int> stacks , int value){

    int low = 0; // from index 0
    int high = stacks.size() - 1; // last index.

   while (low <= high){
    int mid = ceil((low + high)/2);
    int valueOfMidIndex = stacks[mid];
    if(valueOfMidIndex == value){
        return mid;
    }
    else if (valueOfMidIndex > value){
        high = mid - 1;
    }
    else low = mid + 1;
   }
   return 0;



}

// write a function that takes in an array and returns smallest value in it. 

int getSmallestInArray(std::vector<int>stacks){
    int smallest = stacks[0];
    int smallest_index = 0;

    for(int i=0; i < stacks.size(); ++i){
        if(stacks[i] < smallest){
            smallest = stacks[i];
            smallest_index = i;
        }
    }
    return smallest;
}

// we want to get sum of items in an array using recursive
int getSumOfArray(std::vector<int>stacks){
    if(stacks.size() == 0 && stacks.empty()){
        return 0;
    };
   int lastValue = stacks.back();
   stacks.pop_back();
   return lastValue + getSumOfArray(stacks);
}

// 2. 4.2 Write a recursive function to count the number of 
// items in a list.
// 3. 4.3 Write a recursive function to find the maximum 
// number in a list.
// 4. 4.4 Remember binary search from chapter 1? It’s a 
// divide-and-conquer algorithm, too. Can you come up 
// with the base case and recursive case for binary 
// search?


// write out quicksort function here

std::vector<int> quickSortArray(std::vector<int> stacks){
    if(stacks.size() < 2) return stacks;
    int pivot = stacks.back();

    std::vector<int> lessValues, greaterValues, finalValues;
    // std::vector<int> greaterValues = {};
     //std::vector<int> finalValues = {};
    for( int i = 0; i < pivot; i++){
        lessValues.push_back(i);
    }
     for( int i = 0; i > pivot; i++){
        greaterValues.push_back(i);
    }
    lessValues.push_back(pivot);

    finalValues.reserve(lessValues.size() + greaterValues.size());           // avoid reallocations
    finalValues.insert(finalValues.end(), lessValues.begin(), lessValues.end());    // append a
    finalValues.insert(finalValues.end(), greaterValues.begin(), greaterValues.end());

    return quickSortArray(finalValues);
    //+ quickSortArray(greaterValues);

}

int main() {
    // cout << binary_search({1,3,4,5}, 4) << endl;
    auto sorted = quickSortArray({10,3,4});
    //cout<< sorted << endl;
    return 0;
}