
#ifndef GOOGLE_SEARCH_H
#define GOOGLE_SEARCH_H

#include "main.h"
#include "tree.h"
using namespace std;

/*********** Binary Search ***********/
/*
 * 第一类：查找(=, return m) T，m<T
 * 第二类：查找第一个不小于(>=, return p) T，最后一个小于(<, return p-1) T，lower_bound，m<T
 * 第三类：查找第一个大于T(>, return p) ，最后一个不大于(<=, return p-1) T，upper_bound，m<=T
 * 第四类：用子函数当作判断关系（通常由 mid 计算得出）
 * 第五类：其他（通常 T 值不固定）
 *
 * 二、三还有各自的扩展，应用场景最多，也是最重要的两类
 * 一、四、五较少
 * 一最简单，四、五最难
 *
 * */

//int find_1(vector<int>& nums, int target) {
//    int q = 0, p = nums.size();
//    while (q < p) {
//        int m = q + (p - q) / 2;
//        if (nums[m] == target) return m;
//        else if (nums[m] < target) q = m + 1;  // 因為是遞增，這裡更新的是q
//        else p = m;
//    }
//    return -1;
//}
//
//int find_2(vector<int>& nums, int target) {
//    int q = 0, p = nums.size();
//    while (q < p) {
//        int m = q + (p - q) / 2;
//        if (nums[m] < target) q = m + 1;  // 因為是遞增，這裡更新的是q
//        else p = m;
//    }
//    return p;
//}
//
//int find_3(vector<int>& nums, int target) {
//    int q = 0, p = nums.size();
//    while (q < p) {
//        int m = q + (p - q) / 2;
//        if (nums[m] <= target) q = m + 1;  // 因為是遞增，這裡更新的是q
//        else p = m;
//    }
//    return p;
//}

struct LC1351 { int countNegatives(vector<vector<int>>& grid); }; // 第二类
struct LC0744 { char nextGreatestLetter(vector<char>& letters, char target); };
struct LC0704 { int search(vector<int>& nums, int target); };
struct LC0441 { int arrangeCoins(int n); };
struct LC0374 { int guessNumber(int n); };
struct LC0367 { bool isPerfectSquare(int num); };
// struct LC0349 { vector<int> intersection(vector<int>& nums1, vector<int>& nums2); } // list.h 第一类
struct LC0278 { int firstBadVersion(int n); }; // 第二类
// struct LC0268 { int missingNumber(vector<int>& nums); } // list.h, // 第三类
struct LC0069 { int mySqrt(int x); }; // 第三类的变形
struct LC0035 { int searchInsert(vector<int>& nums, int target); }; // 第二类

/*********** Depth First Search ***********/
struct LC0999 { int numRookCaptures(vector<vector<char>>& board); };
struct LC0993 { bool isCousins(TreeNode* root, int x, int y); };
struct LC0965 { bool isUnivalTree(TreeNode* root); };
struct LC0784 { vector<string> letterCasePermutation(string s); };
struct LC0733 { vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int color); };
struct LC0077 { vector<vector<int>> combine(int n, int k); };
struct LC0047 { vector<vector<int>> permuteUnique(vector<int>& nums); };
struct LC0046 { vector<vector<int>> permute(vector<int>& nums); };
struct LC0017 { vector<string> letterCombinations(string digits); };
// tree.h
struct LC0872 { bool leafSimilar(TreeNode* root1, TreeNode* root2); };
struct LC0590 { vector<int> postorder(Node* root); };
struct LC0589 { vector<int> preorder(Node* root); };
struct LC0572 { bool isSubtree(TreeNode* root, TreeNode* subRoot); };
struct LC0563 { int findTilt(TreeNode* root); };
struct LC0559 { int maxDepth(Node* root); };
// struct LC0104 { int maxDepth(TreeNode* root); };

/*********** Breadth First Search ***********/
struct LC0671 { int findSecondMinimumValue(TreeNode* root); };
// tree.h
// struct LC0101 { bool isSymmetric(TreeNode* root); };
// struct LC0100 { bool isSameTree(TreeNode* p, TreeNode* q); };

struct Search {
    /* Depth First Search */
    void Permutation(vector<int> nums, int m);
    void Combination(vector<int> nums, int m);
};



#endif //GOOGLE_SEARCH_H
