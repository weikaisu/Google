﻿
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

/*********** Hash Table ***********/
/*求合法(字元都是來自allowed)字串的數量*/
struct LC1684 { int countConsistentStrings(string allowed, vector<string>& words); };
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
/*找出陣列裡三數相乘之最大值*/
struct LC0628 { int maximumProduct(vector<int>& nums); };
/*從兩個字串陣列找到idx之和最小的相同字串*/
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
/*把字串裡的母音對調*/
struct LC0345 { string reverseVowels(string s); };
/*t是s重排後加上一字符產生，找出那一字符*/
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
/*找出陣列裡兩個合為target的idx*/
struct LC0001 { vector<int> twoSum(vector<int>& nums, int target); };

/*********** Two Pointers ***********/
/*將陣列裡所有0移到後面*/
struct LC0283 { void moveZeroes(vector<int>& nums); };
/*字串是否回文*/
//struct LC0125 { bool isPalindrome(string s); }; // string.h
/*移除指定的值並不改變陣列相對位置*/
struct LC0027 { int removeElement(vector<int>& nums, int val); };
/*去除重複的字符*/
struct LC0026 { int removeDuplicates(vector<int>& nums); };

/*********** Array List ***********/
/*給定一個壓縮後的陣列，將其解壓縮*/
struct LC1313 { vector<int> decompressRLElist(vector<int>& nums); };
/*回傳一有n個數值的陣列，陣列值的和為0*/
struct LC1304 { vector<int> sumZero(int n); };
/*將陣列裡每個數字更新為其右邊數字裡最大的數*/
struct LC1299 { vector<int> replaceElements(vector<int>& arr);};
/*求一陣列裡有多少個位數為偶數*/
struct LC1295 { int findNumbers(vector<int>& nums); };
/*求一數所有位數"積"跟"和"的差值*/
struct LC1281 { int subtractProductAndSum(int n); };
/*求經過所有點需花的時間*/
struct LC1266 { int minTimeToVisitAllPoints(vector<vector<int>>& points); };
/*矩陣經過一系列操作後會產生奇數的數量*/
struct LC1252 { int oddCells(int m, int n, vector<vector<int>>& indices); };
/*candies顆糖分給num_people人，求最後每人得幾顆*/
struct LC1103 { vector<int> distributeCandies(int candies, int num_people); };
/*給定站與站之間距離的矩陣，回傳指定起訖站之間的最短距離*/
struct LC1184 { int distanceBetweenBusStops(vector<int>& distance, int start, int destination); };
/*重複矩陣裡的0值*/
struct LC1089 { void duplicateZeros(vector<int>& arr); };
/*01陣列每個子陣列是否能被5整除*/
struct LC1018 { vector<bool> prefixesDivBy5(vector<int>& nums); };
/*矩陣num跟整數k做相加*/
struct LC0989 { vector<int> addToArrayForm(vector<int>& num, int k); };
/*刪除字符沒有排序好的column*/
struct LC0944 { int minDeletionSize(vector<string>& strs); };
/*判斷一陣列是否是合法的山型陣列*/
struct LC0941 { bool validMountainArray(vector<int>& arr); };
/*給定一時間t，求[t-3000, t]時間範圍內有多少次ping*/
struct LC0933 { queue<int>q; LC0933(){}; int ping(int t); };
/*求陣列值經過處理後最大/小值之間的差值*/
struct LC0908 { int smallestRangeI(vector<int>& nums, int k); };
/*判斷一陣列是否單調遞增或遞減*/
struct LC0896 { bool isMonotonic(vector<int>& nums); };
/*有backspace字符的兩list是否是相同的字串*/
struct LC0844 { bool backspaceCompare(string s, string t); };
/*回傳連續字符起訖idx*/
struct LC0830 { vector<vector<int>> largeGroupPositions(string s); };
/*回傳每個idx離特定字符最近的距離*/
struct LC0821 { vector<int> shortestToChar(string s, char c); };
/*給定一系列二維平面的點，求能維出最大三角形面積*/
struct LC0812 { double largestTriangleArea(vector<vector<int>>& points); };
/*回傳一段文字可分幾行、最後一行長度*/
struct LC0806 { vector<int> numberOfLines(vector<int>& widths, string s); };
/*給定一陣列，回傳其左右子陣列值和相等的idx*/
struct LC0724 { int pivotIndex(vector<int>& nums); };
/*給定一系列操作，回傳累積後的分數*/
struct LC0682 { int calPoints(vector<string>& operations); };
/*找出最長連續增長子序列，並回傳其長度*/
struct LC0674 { int findLengthOfLCIS(vector<int>& nums); };
/*找出平均值最大的子陣列，並回傳其值*/
struct LC0643 { double findMaxAverage(vector<int>& nums, int k); };
/*在一系列操作後，二維陣列裡最大數的個數*/
struct LC0598 { int maxCount(int m, int n, vector<vector<int>>& ops); };
/*反轉一句話裡的每一個單詞*/
struct LC0557 { string reverseWords(string s); };
/*統計出勤紀錄判斷是否合格*/
struct LC0551 { bool checkRecord(string s); };
/*每2k個字符反轉k個字符*/
struct LC0541 { string reverseStr(string s, int k); };
/*求矩陣裡最長連續1的長度*/
struct LC0485 { int findMaxConsecutiveOnes(vector<int>& nums); };
/*回傳陣列裡第三大的數*/
struct LC0414 { int thirdMax(vector<int>& nums); };
/*反轉字符陣列*/
struct LC0344 { void reverseString(vector<char>& s); };
/*找出各連續子陣列的範圍*/
struct LC0228 { vector<string> summaryRanges(vector<int>& nums); };
/*回傳數量超過一半的那個數*/
struct LC0169 { int majorityElement(vector<int>& nums); };
/*求買賣股票最大獲利值，能買賣多次*/
struct LC0122 { int maxProfit(vector<int>& prices); };
/*求買賣股票最大獲利值，只能買賣一次*/
struct LC0121 { int maxProfit(vector<int>& prices); };
/*回傳第numRows層的Pascal三角形的值*/
struct LC0119 { vector<int> getRow(int rowIndex); };
/*產生numRows層的Pascal三角形*/
struct LC0118 { vector<vector<int>> generate(int numRows); };
/*用陣列代表一大數，回傳其加1的陣列*/
struct LC0066 { vector<int> plusOne(vector<int>& digits); };

/*********** Link List ***********/
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
/*兩個list相加*/
struct LC0002 { ListNode* addTwoNumbers(ListNode* l1, ListNode* l2); };

/*********** Matrix ***********/
/*
 *   **** x
 *   *
 *   *
 *   y
 *
 *   一行一行處理：
 *   for(y)
 *      for(x)
 *          array[y][x]
 *
 *   一列一列處理：
 *   for(x)
 *      for(y)
 *          array[y][x]
 */

/*回傳前k行最弱的rows*/
// struct LC1337 { vector<int> kWeakestRows(vector<vector<int>>& mat, int k); }; // tree.h
/*井字遊戲給定一系列操作，求誰贏或平手*/
struct LC1275 { string tictactoe(vector<vector<int>>& moves); };
/*矩陣內元素向右移動k次*/
struct LC1260 { vector<vector<int>> shiftGrid(vector<vector<int>>& grid, int k); };
/*求給定矩陣大小內每個元素局離rCenter/cCenter的距離*/
// struct LC1030 { vector<vector<int>> allCellsDistOrder(int rows, int cols, int rCenter, int cCenter); }; // sort.h
/*求給定象棋盤中車(rook)能吃到多少卒(pawn)*/
// struct LC0999 { int numRookCaptures(vector<vector<char>>& board); }; // search.h
/*求一個三維積木堆的表面積*/
struct LC0892 { int surfaceArea(vector<vector<int>>& grid); };
/*求一三維物體在三個方向投影面積之和*/
struct LC0883 { int projectionArea(vector<vector<int>>& grid); };
/*求轉置後的矩陣*/
struct LC0867 { vector<vector<int>> transpose(vector<vector<int>>& matrix); };
/*求矩陣水平方向翻轉後每個元素取反數*/
struct LC0832 { vector<vector<int>> flipAndInvertImage(vector<vector<int>>& image); };
/*問一矩陣每條從左上到右下對角線的值是否都相等*/
struct LC0766 { bool isToeplitzMatrix(vector<vector<int>>& matrix); };
/*找矩陣中相同區間問題，給一起使座標將相鄰相同的值做修改*/
// struct LC0733 { vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int color); }; // search.h
/*求矩陣每一元素跟相鄰元素算平均*/
struct LC0661 { vector<vector<int>> imageSmoother(vector<vector<int>>& img); };
/*重塑矩陣大小*/
struct LC0566 { vector<vector<int>> matrixReshape(vector<vector<int>>& mat, int r, int c); };
/*求二為陣列裡小島的周長*/
struct LC0463 { int islandPerimeter(vector<vector<int>>& grid); };

struct StackArithmetic {
    unordered_map<char,int> priority_map;
    int priority(char c);
    int calculate(string str);
    string toPostFix(string str);
};

// LC0706 Design HashMap
// LC0705 Design HashSet
// LC0232 Implement Queue using Stacks
// LC0225 Implement Stack using Queues

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
//        return -1;--
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

// LC0232
class MyQueue {
public:
    MyQueue() {}

    // 使用了两个栈intS和revS，其中新进栈的都先缓存在intS中，要pop和peek的时候，才将intS中所有元素移到revS中操作
    void push(int x) {
        intS.push(x);
    }

    void reverse_stack() {
        if(revS.size()) return;
        while(intS.size()) {
            revS.push(intS.top()); intS.pop();
        }
    }

    int pop() {
        reverse_stack();
        int v = revS.top(); revS.pop();
        return v;
    }

    int peek() {
        reverse_stack();
        return revS.top();
    }

    bool empty() {
        return intS.empty() && revS.empty();
    }

private:
    stack<int> intS, revS;
};

// LC0225
class MyStack {
public:
    MyStack() {}

    // 两种解法对于不同的输入效果不同，解法一花在 top() 函数上的时间多，所以适合于有大量 push () 操作，而 top() 和 pop() 比较少
    // 的输入。而第二种解法在 push() 上要花大量的时间，所以适合高频率的 top() 和 pop()，较少的 push()。两种方法各有千秋，互有利弊

    // 只要实现对了 push() 函数，后面三个直接调用队列的函数即可。这种方法的原理就是每次把新加入的数插到前头，这样队列保存的顺序和栈的
    // 顺序是相反的，它们的取出方式也是反的，那么反反得正，就是我们需要的顺序了。我们可以使用一个辅助队列，把q的元素也逆着顺序存入到辅
    // 助队列中，此时加入新元素x，再把辅助队列中的元素存回来，这样就是我们要的顺序了。当然，我们也可以直接对队列q操作，在队尾加入了新元
    // 素x后，将x前面所有的元素都按顺序取出并加到队列到末尾，这样下次就能直接取出x了，符合栈到后入先出到特性，其他三个操作也就直接调用队
    // 列的操作即可
    void push(int x) {
        intQ.push(x);
        for(int i=0; i<intQ.size()-1; i++) {
            intQ.push(intQ.front()); intQ.pop();
        }
    }

    int pop() {
        int v = intQ.front(); intQ.pop();
        return v;
    }

    int top() {
        return intQ.front();
    }

    bool empty() {
        return intQ.empty();
    }

    // 用队列来实现栈，队列和栈作为两种很重要的数据结构，它们最显著的区别就是，队列是先进先出，而栈是先进后出。题目要求中又给定了限制条件
    // 只能用 queue 的最基本的操作，像 back() 这样的操作是禁止使用的。那么怎么样才能让先进先出的特性模拟出先进后出呢，这里就需要另外一
    // 个队列来辅助操作，我们总共需要两个队列，其中一个队列用来放最后加进来的数，模拟栈顶元素。剩下所有的数都按顺序放入另一个队列中。当
    // push() 操作时，将新数字先加入模拟栈顶元素的队列中，如果此时队列中有数字，则将原本有的数字放入另一个队中，让新数字在这队中，用来模
    // 拟栈顶元素。当 top() 操作时，如果模拟栈顶的队中有数字则直接返回，如果没有则到另一个队列中通过平移数字取出最后一个数字加入模拟栈顶
    // 的队列中。当 pop() 操作时，先执行下 top() 操作，保证模拟栈顶的队列中有数字，然后再将该数字移除即可。当 empty() 操作时，当两个
    // 队列都为空时，栈为空。
//    void push(int x) {
//        lastQ.push(x);
//        if(lastQ.size()>1) {
//            intQ.push(lastQ.front()); lastQ.pop();
//        }
//    }
//
//    int pop() {
//        int v = top(); lastQ.pop();
//        return v;
//    }
//
//    int top() {
//        if(lastQ.empty()) {
//            for(int i=0; i<intQ.size()-1; i++) {
//                intQ.push(intQ.front()); intQ.pop();
//            }
//            lastQ.push(intQ.front()); intQ.pop();
//        }
//        return lastQ.front();
//    }
//
//    bool empty() {
//        return intQ.empty() && lastQ.empty();
//    }

private:
    queue<int> intQ, lastQ;
};

#endif //GOOGLE_LIST_H