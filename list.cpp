//
// Created by steve on 2021-08-11.
//

#include "list.h"

//LC0066 run;
//vector<int> nums{9,9,9}, ans;
//ans=run.plusOne(nums);
//for(auto n:nums) cout << n << ' ';
//cout << endl;
/***********  Vector List  **********/
vector<int> LC0066::plusOne(vector<int>& digits) {
    int c=1;
    for(int i=digits.size()-1 ; i>=0 ; i--) {
        int v = digits[i]+c;
        digits[i] = v % 10;
        c = v / 10;
    }
    if(c) digits.emplace(digits.begin(), c);
    return digits;
}

//LC0027 run;
//vector<int> n{0,1,2,2,3,0,4,2}; // val=2
//vector<int> n{3,2,2,3}; // val=3
//vector<int> n{1}; // val=1
//cout << run.removeElement(n, 1) << endl;
//for(auto i:n) cout << i << ' ';
//cout << endl;
int LC0027::removeElement(vector<int>& nums, int val) {
    int s=nums.size();
    int r=0;
    for(int i=0 ; i<nums.size() ; i++) {
        if(nums[i]==val)
            s--;
        else
            nums[r++]=nums[i];
    }
    return s;
}

//LC0026 run;
//vector<int> n{0,0,1,1,1,2,2,3,3,4};
//vector<int> n{1,1,2};
//cout << run.removeDuplicates(n) << endl;
//for(auto i:n) cout << i << ' ';
//cout << endl;
int LC0026::removeDuplicates(vector<int>& nums) {
    int s=nums.size(); if(s<=1) return s;
    int r=1, p=nums[0];
    for(int i=1 ; i<nums.size() ; i++) {
        if(p == nums[i])
            s--;
        else
            nums[r++]=nums[i];
        p=nums[i];
    }
    return s;
}

vector<int> LC0001::twoSum(vector<int>& nums, int target) {
    unordered_map<int, int> t;

    // find target-nums[i], save nums[i]
    for(auto i=0 ; i<nums.size(); i++) {
        auto diff = target - nums[i];
        if(t.count(diff))
            return {t[diff], i};
        t[nums[i]]=i;
    }
    return {};

    // find nums[i], save target-nums[i]
    for(auto i=0 ; i<nums.size() ; i++) {
        auto diff = target - nums[i];
        if(t.count(nums[i]))
            return {t[nums[i] ], i};
        t[diff] = i;
    }
    return {};
}


/***********  Linked List  **********/

bool LC0141::hasCycle(ListNode *head) {
    // time(N) space(N)
    unordered_set<ListNode*> t;
    while(head!=nullptr) {
        if(t.count(head)) return true;
        else {
            t.insert(head);
            head=head->next;
        }
    }
    return false;

    // fast/slow pointers, no extra space
    ListNode *fast, *slow;
    fast=slow=head;
    while(fast) {
        if(fast->next==nullptr) return false;
        if((fast=fast->next->next)==(slow=slow->next)) return true;
    }
    return false;
}

//LinkedList l;
//l.AddNode(1); l.AddNode(2); l.AddNode(3);
//l.AddNode(4); l.AddNode(5); l.AddNode(6);
//LC0206 run;
//ListNode* r = run.reverseList(l.GetListHead());
//LinkedList().ShowLinkedList(r);
ListNode* LC0206::reverseList(ListNode* head) {
    // time(N), iterative
    ListNode *c=nullptr, *n=nullptr;
    while(head) {
        //把n指到head->next
        //把n放在head->next的位置
        n=head->next;
        head->next=c;
        c=head;
        head=n;
    }
    return c;

    // time(N), recursive
    if(head==nullptr || head->next==nullptr) return head;
    ListNode *h = reverseList(head->next);
    head->next->next = head;
    head->next = nullptr;
    return h;
}

//LinkedList l1, l2;
//l1.AddNode(1); l1.AddNode(2); l1.AddNode(4);
//l2.AddNode(1); l2.AddNode(3); l2.AddNode(4);
//LC0021 run;
//ListNode* r = run.mergeTwoLists(l1.GetListHead(), l2.GetListHead());
//LinkedList().ShowLinkedList(r);
ListNode* LC0021::mergeTwoLists(ListNode* l1, ListNode* l2) {
    // time(N), iterative
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

    // time(N), recursive
    if(l1==nullptr || l2==nullptr) return l1==nullptr ? l2 : l1;
    if(l1->val < l2->val) {
        l1->next = mergeTwoLists(l1->next , l2);
        return l1;
    } else {
        l2->next = mergeTwoLists(l1, l2->next);
        return l2;
    }
}
