
#ifndef GOOGLE_SEARCH_H
#define GOOGLE_SEARCH_H

#include "main.h"
#include "tree.h"
using namespace std;

/***********  Easy  **********/
/* Binary Search */
struct LC0704 { int search(vector<int>& nums, int target); };
struct LC0441 { int arrangeCoins(int n); };
struct LC0374 { int guessNumber(int n); };
struct LC0367 { bool isPerfectSquare(int num); };
struct LC0278 { int firstBadVersion(int n); };
struct LC0035 { int searchInsert(vector<int>& nums, int target); };

/* Depth First Search */
struct LC0784 { vector<string> letterCasePermutation(string s); };
struct LC0733 { vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int color); };
struct LC0077 { vector<vector<int>> combine(int n, int k); };
struct LC0046 { vector<vector<int>> permute(vector<int>& nums); };
// tree.h
struct LC0590 { vector<int> postorder(Node* root); };
struct LC0589 { vector<int> preorder(Node* root); };
struct LC0572 { bool isSubtree(TreeNode* root, TreeNode* subRoot); };
struct LC0563 { int findTilt(TreeNode* root); };
struct LC0559 { int maxDepth(Node* root); };
struct LC0530 { int getMinimumDifference(TreeNode* root); };
struct LC0501 { vector<int> findMode(TreeNode* root); };
// struct LC0104 { int maxDepth(TreeNode* root); };

/* Breadth First Search */
// tree.h
// struct LC0101 { bool isSymmetric(TreeNode* root); };
// struct LC0100 { bool isSameTree(TreeNode* p, TreeNode* q); };

struct Search {
    /* Depth First Search */
    void Permutation(vector<int> nums, int m);
    void Combination(vector<int> nums, int m);
};

/***********  Medium  **********/


#endif //GOOGLE_SEARCH_H
