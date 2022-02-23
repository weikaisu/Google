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
class LC0066 { public: vector<int> plusOne(vector<int>& digits); };
class LC0027 { public: int removeElement(vector<int>& nums, int val); };
class LC0026 { public: int removeDuplicates(vector<int>& nums); };
class LC0001 { public: vector<int> twoSum(vector<int>& nums, int target); };

class LC0234 { public: bool isPalindrome(ListNode* head); };
class LC0206 { public: ListNode* reverseList(ListNode* head); };
class LC0203 { public: ListNode* removeElements(ListNode* head, int val); };
class LC0160 { public: ListNode *getIntersectionNode(ListNode *headA, ListNode *headB); };
class LC0141 { public: bool hasCycle(ListNode *head); };
class LC0083 { public: ListNode* deleteDuplicates(ListNode* head); };
class LC0021 { public: ListNode* mergeTwoLists(ListNode* l1, ListNode* l2); };

/***********  Medium  **********/



#endif //GOOGLE_LIST_H
