
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
/*陣列裡每個字符出現的頻率是否都不同*/
struct LC1207 { bool uniqueOccurrences(vector<int>& arr); };
/*找出能從特定字串裡的字符拼出目標字串的數量*/
struct LC1189 { int maxNumberOfBalloons(string text); };
/*找出能從特定字串裡的字符拼出字串的長度*/
struct LC1160 { int countCharacters(vector<string>& words, string chars); };
/*找出domino pair的對數*/
struct LC1128 { int numEquivDominoPairs(vector<vector<int>>& dominoes); };
/*根據另一陣列裡的相對順序排做排序*/
struct LC1122 { vector<int> relativeSortArray(vector<int>& arr1, vector<int>& arr2); };
/*找出出現在所有字串的字符*/
struct LC1002 { vector<string> commonChars(vector<string>& words); };
/*法官不相信任何人，任何人相信法官，找出誰是法官*/
struct LC0997 { int findJudge(int n, vector<vector<int>>& trust); };
/*找出重複出現n次的值*/
struct LC0961 { int repeatedNTimes(vector<int>& nums); };
/*陣列裡同值分組且每組一樣數量*/
struct LC0914 { bool hasGroupsSizeX(vector<int>& deck); };
/*两人交换一類糖果，使得交换后两人的糖果总重量相同*/
struct LC0888 { vector<int> fairCandySwap(vector<int>& aliceSizes, vector<int>& bobSizes); };
/*字串只做一次兩字符swap是否可等於另一字串*/
struct LC0859 { bool buddyStrings(string s, string goal); };
/*找出不同摩斯密碼表示的數量*/
struct LC0804 { int uniqueMorseRepresentations(vector<string>& words); };
/*找出同時出現在兩字串的字符個數*/
struct LC0771 { int numJewelsInStones(string jewels, string stones); };
/*求最小能拼出目標字串的字串*/
struct LC0748 { string shortestCompletingWord(string licensePlate, vector<string>& words); };
/*求最小包含出現頻率最高之元素子陣列長度*/
struct LC0697 { int findShortestSubArray(vector<int>& nums); };
/*給定方向陣列判斷最終是否能走回原點*/
struct LC0657 { bool judgeCircle(string moves); };
/*找出1～n的陣列裡重複的數和消失的那"個"數字*/
struct LC0645 { vector<int> findErrorNums(vector<int>& nums); };
/*從兩個字串陣列裡找出相同字串的最小index*/
struct LC0599 { vector<string> findRestaurant(vector<string>& list1, vector<string>& list2); };
/*陣列裡最長harmonious子陣列長度*/
struct LC0594 { int findLHS(vector<int>& nums); };
/*在給定條件下能選擇的種類數*/
struct LC0575 { int distributeCandies(vector<int>& candyType); };
/*給定的字符串是否能只用鍵盤的某一行打完*/
struct LC0500 { vector<string> findWords(vector<string>& words); };
/*找出給定子陣列在原陣列中右邊更大的值*/
struct LC0496 { vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2); };
/*找出1～n的陣列裡消失的那"些"數字*/
struct LC0448 { vector<int> findDisappearedNumbers(vector<int>& nums); };
/*回傳能建立最長的回文字串長度*/
struct LC0409 { int longestPalindrome(string s); };
/*把字串裡的母音對調*/
struct LC0345 { string reverseVowels(string s); };
/*判斷隨機加入字串的字符為何*/
struct LC0389 { char findTheDifference(string s, string t); };
/*找出一字串裡第一個不重複的字符的index*/
struct LC0387 { int firstUniqChar(string s); };
/*判斷一字串是否能從另一字串重建*/
struct LC0383 { bool canConstruct(string ransomNote, string magazine); };
/*找出同時存在兩陣列的子陣列，子陣列無需去重*/
struct LC0350 { vector<int> intersect(vector<int>& nums1, vector<int>& nums2); };
/*找出同時存在兩陣列的子陣列，子陣列需去重*/
struct LC0349 { vector<int> intersection(vector<int>& nums1, vector<int>& nums2); };
/*找出0～n的陣列裡消失的那"個"數字*/
struct LC0268 { int missingNumber(vector<int>& nums); };
/*判斷一個字串是否是另一字串的anagram*/
struct LC0242 { bool isAnagram(string s, string t); };
/*在指定距離內是否有兩數相同*/
struct LC0219 { bool containsNearbyDuplicate(vector<int>& nums, int k); };
/*判斷一陣列裡是否有值重複出現*/
struct LC0217 { bool containsDuplicate(vector<int>& nums); };
/*判斷兩字串是否isomorphic*/
struct LC0205 { bool isIsomorphic(string s, string t); };
/*判斷一個數字是否是happy number*/
struct LC0202 { bool isHappy(int n); };
/*回傳數量超過一半的那個數*/
struct LC0169 { int majorityElement(vector<int>& nums); };
/*用陣列代表一大數，回傳其加1的陣列*/
struct LC0066 { vector<int> plusOne(vector<int>& digits); };
/*移除指定的值並不改變陣列相對位置*/
struct LC0027 { int removeElement(vector<int>& nums, int val); };
/*將重複的字符替換成指定的字符*/
struct LC0026 { int removeDuplicates(vector<int>& nums); };
/*找出陣列裡兩個合為指定值的index*/
struct LC0001 { vector<int> twoSum(vector<int>& nums, int target); };

// Array List
/*刪除字符沒有排序好的column*/
struct LC0944 { int minDeletionSize(vector<string>& strs); };
/*有backspace字符的兩list是否是相同的字串*/
struct LC0844 { bool backspaceCompare(string s, string t); };
/*有幾組連續字符*/
struct LC0830 { vector<vector<int>> largeGroupPositions(string s); };
/*每個離特定字符最近的距離*/
struct LC0821 { vector<int> shortestToChar(string s, char c); };
/*一段文字可分幾行*/
struct LC0806 { vector<int> numberOfLines(vector<int>& widths, string s); };
/*頂多刪一字符可成回文*/
struct LC0680 { bool validPalindrome(string s); };
/*反轉一句話裡的每一個單詞*/
struct LC0557 { string reverseWords(string s); };
/*統計出勤紀錄判斷是否合格*/
struct LC0551 { bool checkRecord(string s); };
/*每2k個字符反轉k個字符*/
struct LC0541 { string reverseStr(string s, int k); };
/*求二為陣列裡小島的周長*/
struct LC0463 { int islandPerimeter(vector<vector<int>>& grid); };
/*回傳陣列裡第三大的數*/
struct LC0414 { int thirdMax(vector<int>& nums); };
/*反轉字符陣列*/
struct LC0344 { void reverseString(vector<char>& s); };
/*將陣列裡所有0移到後面*/
struct LC0283 { void moveZeroes(vector<int>& nums); };
/*找出各連續子陣列的範圍*/
struct LC0228 { vector<string> summaryRanges(vector<int>& nums); };

// Link List
/*二進位轉十進位*/
struct LC1290 { int getDecimalValue(ListNode* head); };
/*回傳正中間的node*/
struct LC0876 { ListNode* middleNode(ListNode* head); };
/*刪除特定node*/
struct LC0237 { void deleteNode(ListNode* node); };
/*node是否回文*/
struct LC0234 { bool isPalindrome(ListNode* head); };
/*反轉linked list*/
struct LC0206 { ListNode* reverseList(ListNode* head); };
/*移除指定值的所有node*/
struct LC0203 { ListNode* removeElements(ListNode* head, int val); };
/*找到兩條list交叉的node*/
struct LC0160 { ListNode *getIntersectionNode(ListNode *headA, ListNode *headB); };
/*判斷list是否有cycle*/
struct LC0141 { bool hasCycle(ListNode *head); };
/*刪除重複值的node*/
struct LC0083 { ListNode* deleteDuplicates(ListNode* head); };
/*合併兩條list*/
struct LC0021 { ListNode* mergeTwoLists(ListNode* l1, ListNode* l2); };

struct StackArithmetic {
    unordered_map<char,int> priority_map;
    int priority(char c);
    int calculate(string str);
    string toPostFix(string str);
};

/***********  Medium  **********/

// Link List
struct LC0002 { ListNode* addTwoNumbers(ListNode* l1, ListNode* l2); };



#endif //GOOGLE_LIST_H
