
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

/*求有序矩陣裡負數的個數*/
struct LC1351 { int countNegatives(vector<vector<int>>& grid); }; // 第二类
/*求有序字母陣列中第一個大於target的字母*/
struct LC0744 { char nextGreatestLetter(vector<char>& letters, char target); };
/*從有序陣列中找target，若無回傳-1*/
struct LC0704 { int search(vector<int>& nums, int target); };
/*n個硬幣按規律排列求可排幾列*/
struct LC0441 { int arrangeCoins(int n); };
/*猜介於1～n之間的一數*/
struct LC0374 { int guessNumber(int n); };
/*求一數是否為完全平方數*/
struct LC0367 { bool isPerfectSquare(int num); };
/*找出同時存在兩陣列的子陣列，子陣列無需去重*/
// struct LC0349 { vector<int> intersection(vector<int>& nums1, vector<int>& nums2); } // list.h 第一类
/*給一系列版本求從那一版本之後是壞的*/
struct LC0278 { int firstBadVersion(int n); }; // 第二类
/*找出0～n的陣列裡消失的那"個"數字*/
// struct LC0268 { int missingNumber(vector<int>& nums); } // list.h, // 第三类
/*求平方根*/
struct LC0069 { int mySqrt(int x); }; // 第三类的变形
/*從有序陣列中找第一個大於等於target，若無回傳數組長度n*/
struct LC0035 { int searchInsert(vector<int>& nums, int target); }; // 第二类

/*********** Depth First Search ***********/
/*求給定象棋盤中車(rook)能吃到多少卒(pawn)*/
struct LC0999 { int numRookCaptures(vector<vector<char>>& board); };
/*判斷兩結點是否為表兄弟結點*/
struct LC0993 { bool isCousins(TreeNode* root, int x, int y); };
/*判斷樹裡所有結點值是否均相同*/
struct LC0965 { bool isUnivalTree(TreeNode* root); };
/*字母大小寫排列組合*/
struct LC0784 { vector<string> letterCasePermutation(string s); };
/*找矩陣中相同區間問題，給一起使座標將相鄰相同的值做修改*/
struct LC0733 { vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int color); };
/*n取k做組合*/
struct LC0077 { vector<vector<int>> combine(int n, int k); };
/*給一陣列裡元素所有的排列*/
struct LC0047 { vector<vector<int>> permuteUnique(vector<int>& nums); };
/*n取n做排列*/
struct LC0046 { vector<vector<int>> permute(vector<int>& nums); };
/*求電話按鍵上的字母組合*/
struct LC0017 { vector<string> letterCombinations(string digits); };
// tree.h
/*判斷兩顆樹是否相似*/
struct LC0872 { bool leafSimilar(TreeNode* root1, TreeNode* root2); };
/*求樹的後序遍歷結果*/
struct LC0590 { vector<int> postorder(Node* root); };
/*求樹的前序遍歷結果*/
struct LC0589 { vector<int> preorder(Node* root); };
/*判斷一樹是否為另一樹的子樹*/
struct LC0572 { bool isSubtree(TreeNode* root, TreeNode* subRoot); };
/*求樹的坡度*/
struct LC0563 { int findTilt(TreeNode* root); };
/*求n叉樹的最大深度*/
struct LC0559 { int maxDepth(Node* root); };
/*求2叉樹的最大深度*/
// struct LC0104 { int maxDepth(TreeNode* root); };

/*********** Breadth First Search ***********/
/*找二叉樹裡第二小的結點*/
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
