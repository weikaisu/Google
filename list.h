
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
// LC0706
//MyHashMap map;
//map.put(1,1);
//map.put(2,2);
//map.get(1);
//map.get(3);
//map.put(2,1);
//map.get(2);
//map.remove(2);
//map.get(2);
struct MyHashMap {
    MyHashMap() {
        t.fill(-1);
    }
    void put(int key, int value) {
        t[key]=value;
    }
    int get(int key) {
        return t[key];
    }
    void remove(int key) {
        t[key]=-1;
    }
private:
    array<int, 1000001> t;
};
//struct MyHashMap {
//    MyHashMap() {
//
//    }
//    void put(int key, int value) {
//        auto& l = t[key%1000];
//        for(auto& [k,v]:l) {
//            if (k == key) v=value;
//            return;
//        }
//        l.push_front(make_pair (key,value));
//    }
//    int get(int key) {
//        auto& l = t[key%1000];
//        for(auto& [k,v]:l) {
//            if(k == key) return v;
//        }
//        return -1;
//    }
//    void remove(int key) {
//        auto& l = t[key%1000];
//        for (auto it=l.begin(); it!=l.end(); ++it)
//            if(it->first == key) {
//                l.remove(*it);
//                break;
//            }
//    }
//private:
//    //const static int m=1024;
//    array<forward_list<pair<int,int>>, 1000> t;
//};

// LC0705
struct MyHashSet {
    // 範圍是[0, 1000000]，用array搭配list來優化空間
    MyHashSet() {};
    void add(int key) {
        auto l = t[key%1000];
        for(auto e:l)
            if(e == key) return;
        t[key%1000].push_front(key);
    };
    void remove(int key) {
        t[key%1000].remove(key);
    };
    bool contains(int key) {
        auto l = t[key%1000];
        for(auto e:l)
            if(e == key) return true;
        return false;
    };
private:
    array<forward_list<int>, 1000> t;
};

// Hash Table
struct LC1160 { int countCharacters(vector<string>& words, string chars); };
struct LC1128 { int numEquivDominoPairs(vector<vector<int>>& dominoes); };
struct LC1122 { vector<int> relativeSortArray(vector<int>& arr1, vector<int>& arr2); };
struct LC1002 { vector<string> commonChars(vector<string>& words); };
struct LC0997 { int findJudge(int n, vector<vector<int>>& trust); };
struct LC0961 { int repeatedNTimes(vector<int>& nums); };
struct LC0914 { bool hasGroupsSizeX(vector<int>& deck); };
struct LC0888 { vector<int> fairCandySwap(vector<int>& aliceSizes, vector<int>& bobSizes); };
struct LC0859 { bool buddyStrings(string s, string goal); };
struct LC0804 { int uniqueMorseRepresentations(vector<string>& words); };
struct LC0771 { int numJewelsInStones(string jewels, string stones); };
struct LC0748 { string shortestCompletingWord(string licensePlate, vector<string>& words); };
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

// Link List
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
