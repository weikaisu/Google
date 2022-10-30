
#ifndef GOOGLE_SEARCH_H
#define GOOGLE_SEARCH_H

#include "main.h"
using namespace std;

/***********  Easy  **********/
/* Binary Search */
struct LC0035 { int searchInsert(vector<int>& nums, int target); };

/* Depth First Search */
struct LC0784 { vector<string> letterCasePermutation(string s); };
struct LC0733 { vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int color); };
struct LC0693 { bool hasAlternatingBits(int n); };
struct LC0476 { int findComplement(int num); };
struct LC0461 { int hammingDistance(int x, int y); };
struct LC0077 { vector<vector<int>> combine(int n, int k); };
struct LC0046 { vector<vector<int>> permute(vector<int>& nums); };
// tree.h
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
