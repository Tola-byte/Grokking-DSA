// Given an array of integers nums and an integer target, return indices of the two numbers such that they add up to target.

// You may assume that each input would have exactly one solution, and you may not use the same element twice.

// You can return the answer in any order.

 

// Example 1:

// Input: nums = [2,7,11,15], target = 9
// Output: [0,1]
// Explanation: Because nums[0] + nums[1] == 9, we return [0, 1].
// Example 2:

// Input: nums = [3,2,4], target = 6
// Output: [1,2]
// Example 3:

// Input: nums = [3,3], target = 6
// Output: [0,1]

// Solution. 

// since we would be trying to get the index of the values that sums up, then we can use an hashmap.

// so we have loop through the array and then calculate the needed value to meet target, if that value exists in the hashmap we return the 
// iterator getting its value and its index , because two sum is asking if we have seen a number before, if yes, return its index. 

// time complexity is O(n)

#include <iostream>

class Solution{
    public:
     std::vector<int> twoSum(std::vector<int>& nums, int target) {

        // define map
        std::unordered_map<int, int> mapToStoreValues;

        //looping through.

        for (int i = 0; i < nums.size(); ++i){
            int neededValueToHitTarget = target - nums[i];

            auto iterator = mapToStoreValues.find(neededValueToHitTarget); // unordered_map returns an iterator

            if( iterator != mapToStoreValues.end()){ // if not found, returns mapToVlues.end(), 
                return {iterator -> second, i};
            };
            mapToStoreValues[nums[i]] = i; // here we assigning an index to a value


            // add
        }

        return {};

     }
};

