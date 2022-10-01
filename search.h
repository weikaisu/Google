
#ifndef GOOGLE_SEARCH_H
#define GOOGLE_SEARCH_H

#include "main.h"
using namespace std;

/***********  Easy  **********/
/* Linear Search */
struct LC0784 { vector<string> letterCasePermutation(string s); };
struct LC0006 { string convert(string s, int numRows); };

/* Binary Search */
struct LC0035 { int searchInsert(vector<int>& nums, int target); };

/* DF Search */
struct LCSearch {
    void permutation(vector<int> nums, int n, int m);
    void combination(vector<int> nums, int n, int m);
};

/* BF Search */
// tree.h
// struct LC0100 { bool isSameTree(TreeNode* p, TreeNode* q); };
// struct LC0101 { bool isSymmetric(TreeNode* root); };
/***********  Medium  **********/


#endif //GOOGLE_SEARCH_H
