//
// Created by steve on 2021-08-11.
//

#include "list.h"

ListNode* LC0021::mergeTwoLists(ListNode* l1, ListNode* l2) {
    //time(N), iterative
    ListNode head(0);
    ListNode *tail=&head;
    while(l1 && l2) {
        if(l1->val < l2->val) {
            tail->next = l1;
            l1 = l1->next;
        } else {
            tail->next = l2;
            l2 = l2->next;
        }
        tail=tail->next;
    }
    if(l1) tail->next=l1;
    if(l2) tail->next=l2;
    return head.next;

    //time(N), recursive
    if(l1==nullptr || l2==nullptr) return l1==nullptr ? l2 : l1;
    if(l1->val < l2->val) {
        l1->next = mergeTwoLists(l1->next , l2);
        return l1;
    } else {
        l2->next = mergeTwoLists(l1, l2->next);
        return l2;
    }
}

// find target-nums[i], save nums[i]
vector<int> LC0001::twoSum_1(vector<int>& nums, int target) {
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
vector<int> LC0001::twoSum_2(vector<int>& nums, int target) {
    unordered_map<int, int> t;

    for(auto i=0 ; i<nums.size() ; i++) {
        auto diff = target - nums[i];
        if(t.count(nums[i]))
            return {t[nums[i] ], i};
        t[diff] = i;
    }
    return {};
}