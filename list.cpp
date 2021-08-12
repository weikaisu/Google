//
// Created by steve on 2021-08-11.
//

#include "list.h"

// find target-nums[i], save nums[i]
vector<int> LC0001::twoSum_1(vector<int>& nums, int target){
    unordered_map<int, int> t;

    for(auto i=0 ; i<nums.size(); i++) {
        auto diff = target - nums[i];
        if(t.count(diff))
            return {t[diff], i};
        t[nums[i]]=i;
    }
    return {};
}
// find nums[i], save target-nums[i]
vector<int> LC0001::twoSum_2(vector<int>& nums, int target){
    unordered_map<int, int> t;

    for(auto i=0 ; i<nums.size() ; i++) {
        auto diff = target - nums[i];
        if(t.count(nums[i]))
            return {t[nums[i] ], i};
        t[diff] = i;
    }
    return {};
}