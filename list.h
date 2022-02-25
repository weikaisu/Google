//
// Created by steve on 2021-08-11.
//

#ifndef GOOGLE_LIST_H
#define GOOGLE_LIST_H

#include "main.h"
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {};
    ListNode(int x, ListNode *next) : val(x), next(next) {};
};

class LinkedList {
private:
    ListNode *head, *tail;
public:
    LinkedList() : head(nullptr), tail(nullptr) {};

    void AddNode (int v) {
        ListNode *n = new ListNode(v);
        if(head==nullptr) {
            head=tail=n;
        } else {
            tail->next = n;
            tail =  tail->next;
        }
    }

    ListNode* GetListHead() { return head;};

    static void ShowLinkedList(ListNode *n) {
        if(!n) cout << "Error! nullptr ListNode" << endl;
        while(n!=nullptr) {
            cout << n->val << ' ';
            n=n->next;
        }
        cout << endl;
    }
};

/***********  Easy  **********/
class LC0409 { public: int longestPalindrome(string s); };
class LC0389 { public: char findTheDifference(string s, string t); };
class LC0387 { public: int firstUniqChar(string s); };
class LC0383 { public: bool canConstruct(string ransomNote, string magazine); };
class LC0350 { public: vector<int> intersect(vector<int>& nums1, vector<int>& nums2); };
class LC0349 { public: vector<int> intersection(vector<int>& nums1, vector<int>& nums2); };
class LC0268 { public: int missingNumber(vector<int>& nums); };
class LC0242 { public: bool isAnagram(string s, string t); };
class LC0219 { public: bool containsNearbyDuplicate(vector<int>& nums, int k); };
class LC0217 { public: bool containsDuplicate(vector<int>& nums); };
class LC0205 { public: bool isIsomorphic(string s, string t); };
class LC0202 { public: bool isHappy(int n); };
class LC0169 { public: int majorityElement(vector<int>& nums); };
class LC0066 { public: vector<int> plusOne(vector<int>& digits); };
class LC0027 { public: int removeElement(vector<int>& nums, int val); };
class LC0026 { public: int removeDuplicates(vector<int>& nums); };
class LC0001 { public: vector<int> twoSum(vector<int>& nums, int target); };

class LC1290 { public: int getDecimalValue(ListNode* head); };
class LC0876 { public: ListNode* middleNode(ListNode* head); };
class LC0237 { public: void deleteNode(ListNode* node); };
class LC0234 { public: bool isPalindrome(ListNode* head); };
class LC0206 { public: ListNode* reverseList(ListNode* head); };
class LC0203 { public: ListNode* removeElements(ListNode* head, int val); };
class LC0160 { public: ListNode *getIntersectionNode(ListNode *headA, ListNode *headB); };
class LC0141 { public: bool hasCycle(ListNode *head); };
class LC0083 { public: ListNode* deleteDuplicates(ListNode* head); };
class LC0021 { public: ListNode* mergeTwoLists(ListNode* l1, ListNode* l2); };

/***********  Medium  **********/



#endif //GOOGLE_LIST_H
