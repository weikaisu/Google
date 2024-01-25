
#ifndef GOOGLE_TREE_H
#define GOOGLE_TREE_H

#include <iostream>
#include <cmath>
#include <algorithm>
#include <queue> // queue and priority
#include <stack>
#include <unordered_set>
#include <string>
#include <functional>
#include <set>
#include <vector>
#include <numeric>

using namespace std;

class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};

struct TreeNode {
    int val;
    int height; // for AVLTree
    TreeNode* left;
    TreeNode* right;
    TreeNode* parent;

    TreeNode(int x) : val(x), height(1), left(nullptr), right(nullptr), parent(nullptr) {};
    void BuildTree(TreeNode *&root);
    void CleanTree(TreeNode  *root);
    void TraverseInOrder(TreeNode *root);
    void TraversePreOrder(TreeNode *root);
    void TraversePostOrder(TreeNode *root);
    void TraverseLevelOrder(TreeNode *root);
    void TraverseTopDown(TreeNode *root);
    void TraverseBottomUp(TreeNode *root);
};

class tree {};

/***********  Binary Tree  **********/
/*求所有從root到leaf組成二進制數字的和*/
struct LC1022 { int sumRootToLeaf(TreeNode* root); };
/*求tree裡各level的平均值*/
struct LC0637 { vector<double> averageOfLevels(TreeNode* root); };
/*合併兩tree，新結點值為兩tree同位置結點值之和*/
struct LC0617 { TreeNode* mergeTrees(TreeNode* root1, TreeNode* root2); };
/*求先序走訪tree後組成的字串*/
struct LC0606 { string tree2str(TreeNode* root); };
/*求tree的直徑*/
struct LC0543 { int diameterOfBinaryTree(TreeNode* root); };
/*求tree所有left leaves之和*/
struct LC0404 { int sumOfLeftLeaves(TreeNode* root); };
/*求所有從root到leaf構成的路徑*/
struct LC0257 { vector<string> binaryTreePaths(TreeNode* root); };
/*鏡相（左右）翻轉二叉樹*/
struct LC0226 { TreeNode* invertTree(TreeNode* root); };
/*求tree的結點個數*/
struct LC0222 { int countNodes(TreeNode* root); };
/*後序遍歷tree*/
struct LC0145 { vector<int> postorderTraversal(TreeNode* root); };
/*前序遍歷tree*/
struct LC0144 { vector<int> preorderTraversal(TreeNode* root); };
/*判斷tree是否平衡*/
struct LC0110 { bool isBalanced(TreeNode* root); };
/*求2叉樹的最大深度*/
struct LC0104 { int maxDepth(TreeNode* root); };
/*判斷tree是否平衡*/
struct LC0101 { bool isSymmetric(TreeNode* root); };
/*判斷兩tree是否一樣*/
struct LC0100 { bool isSameTree(TreeNode* p, TreeNode* q); };
/*中序遍歷tree*/
struct LC0094 { vector<int> inorderTraversal(TreeNode* root); };
/***********  Binary Search Tree  **********/
/*求BST在某範圍內結點之和*/
struct LC0938 { int rangeSumBST(TreeNode* root, int low, int high); };
/*重新排序BST，最左結點變成root*/
struct LC0897 { TreeNode* increasingBST(TreeNode* root); };
/*求BST任兩結點的最小差值*/
struct LC0783 { int minDiffInBST(TreeNode* root); };
/*在BST內搜索val*/
struct LC0700 { TreeNode* searchBST(TreeNode* root, int val); };
/*判斷BST裡是否有兩結點之和為k*/
struct LC0653 { bool findTarget(TreeNode* root, int k); };
/*求BST任兩結點的最小差值*/
struct LC0530 { int getMinimumDifference(TreeNode* root); };
/*求BST裡所有的眾數(modes, the most frequently occurred elements)*/
struct LC0501 { vector<int> findMode(TreeNode* root); };
/*將有序陣列轉成BST*/
struct LC0108 { TreeNode* sortedArrayToBST(vector<int>& nums); };

/*********** Complete Binary Tree ***********/
/*
 * A binary tree in which every level, except possibly the last, is completely filled, and all nodes are as far left
 * as possible
 */
/*********** Perfect Binary Tree ***********/
/*
 * A tree with all leaf nodes at the same depth. All internal nodes have degree 2
 */
/*********** Full Binary Tree ***********/
/*
 * A tree in which every node other than the leaves has two children
 */
/*********** Heap ***********/
/*
 * A specialized tree-based data structure which is essentially an almost complete[1] tree that satisfies the heap property:
 * In a max heap, for any given node C, if P is a parent node of C, then the key (the value) of P is greater than or equal to the key of C.
 * In a min heap, the key of P is less than or equal to the key of C
 */
/*回傳前k行最弱的rows*/
struct LC1337 { vector<int> kWeakestRows(vector<vector<int>>& mat, int k); };
/*從陣列裡持續挑兩數出來相減，問最後減剩的值*/
struct LC1046 { int lastStoneWeight(vector<int>& stones); };
/*求第K大的元素*/
// struct LC0703 KthLargest { KthLargest(int k, vector<int>& nums); int add(int val); };
/*給定分數陣列，找出相對排名*/
struct LC0506 { vector<string> findRelativeRanks(vector<int>& score); };

/*********** Trie (Prefix tree or Digital Tree ) ***********/
/*
 * A type of k-ary search tree, a tree data structure used for locating specific keys from within a set.
 * These keys are most often strings, with links between nodes defined not by the entire key, but by individual characters.
 * In order to access a key (to recover its value, change it, or remove it), the trie is traversed depth-first,
 * following the links between nodes, which represent each character in the key.
 */

/*********** Segment tree (Statistic tree) */
/*
 * Used for storing information about intervals, or segments.
 * It allows querying which of the stored segments contain a given point.
 * In principle, a static structure; that is, it's a structure that cannot be modified once it's built
 */

/*********** Fenwick tree (Binary indexed tree) ***********/
 /*
  * A data structure that can efficiently update elements and calculate prefix sums in a table of numbers
  */

#endif //GOOGLE_TREE_H
