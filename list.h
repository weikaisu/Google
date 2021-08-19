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
        while(n!=nullptr) {
            cout << n->val << ' ';
            n=n->next;
        }
        cout << endl;
    }
};

/***********  Easy **********/
class LC0021 { public: ListNode* mergeTwoLists(ListNode* l1, ListNode* l2); };
class LC0001 {
public:
    vector<int> twoSum_1(vector<int>& nums, int target);
    vector<int> twoSum_2(vector<int>& nums, int target);
};

/***********  Medium **********/

#endif //GOOGLE_LIST_H
