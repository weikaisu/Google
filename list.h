
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
struct LC0697 { int findShortestSubArray(vector<int>& nums); };
struct LC0645 { vector<int> findErrorNums(vector<int>& nums); };
struct LC0599 { vector<string> findRestaurant(vector<string>& list1, vector<string>& list2); };
struct LC0594 { int findLHS(vector<int>& nums); };
struct LC0575 { int distributeCandies(vector<int>& candyType); };
struct LC0500 { vector<string> findWords(vector<string>& words); };
struct LC0496 { vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2); };
struct LC0448 { vector<int> findDisappearedNumbers(vector<int>& nums); };
struct LC0409 { int longestPalindrome(string s); };
struct LC0389 { char findTheDifference(string s, string t); };
struct LC0387 { int firstUniqChar(string s); };
struct LC0383 { bool canConstruct(string ransomNote, string magazine); };
struct LC0350 { vector<int> intersect(vector<int>& nums1, vector<int>& nums2); };
struct LC0349 { vector<int> intersection(vector<int>& nums1, vector<int>& nums2); };
struct LC0268 { int missingNumber(vector<int>& nums); };
struct LC0242 { bool isAnagram(string s, string t); };
struct LC0219 { bool containsNearbyDuplicate(vector<int>& nums, int k); };
struct LC0217 { bool containsDuplicate(vector<int>& nums); };
struct LC0205 { bool isIsomorphic(string s, string t); };
struct LC0202 { bool isHappy(int n); };
struct LC0169 { int majorityElement(vector<int>& nums); };
struct LC0066 { vector<int> plusOne(vector<int>& digits); };
struct LC0027 { int removeElement(vector<int>& nums, int val); };
struct LC0026 { int removeDuplicates(vector<int>& nums); };
struct LC0001 { vector<int> twoSum(vector<int>& nums, int target); };

struct LC1290 { int getDecimalValue(ListNode* head); };
struct LC0876 { ListNode* middleNode(ListNode* head); };
struct LC0237 { void deleteNode(ListNode* node); };
struct LC0234 { bool isPalindrome(ListNode* head); };
struct LC0206 { ListNode* reverseList(ListNode* head); };
struct LC0203 { ListNode* removeElements(ListNode* head, int val); };
struct LC0160 { ListNode *getIntersectionNode(ListNode *headA, ListNode *headB); };
struct LC0141 { bool hasCycle(ListNode *head); };
struct LC0083 { ListNode* deleteDuplicates(ListNode* head); };
struct LC0021 { ListNode* mergeTwoLists(ListNode* l1, ListNode* l2); };

/***********  Medium  **********/



#endif //GOOGLE_LIST_H
