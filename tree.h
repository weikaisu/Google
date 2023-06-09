
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

/***********  Easy  **********/
struct LC0700 { TreeNode* searchBST(TreeNode* root, int val); };
struct LC0653 { bool findTarget(TreeNode* root, int k); };
struct LC0637 { vector<double> averageOfLevels(TreeNode* root); };
struct LC0617 { TreeNode* mergeTrees(TreeNode* root1, TreeNode* root2); };
struct LC0606 { string tree2str(TreeNode* root); };
struct LC0543 { int diameterOfBinaryTree(TreeNode* root); };
struct LC0404 { int sumOfLeftLeaves(TreeNode* root); };
struct LC0257 { vector<string> binaryTreePaths(TreeNode* root); };
struct LC0226 { TreeNode* invertTree(TreeNode* root); };
struct LC0145 { vector<int> postorderTraversal(TreeNode* root); };
struct LC0144 { vector<int> preorderTraversal(TreeNode* root); };
struct LC0110 { bool isBalanced(TreeNode* root); };
struct LC0104 { int maxDepth(TreeNode* root); };
struct LC0101 { bool isSymmetric(TreeNode* root); };
struct LC0100 { bool isSameTree(TreeNode* p, TreeNode* q); };
struct LC0094 { vector<int> inorderTraversal(TreeNode* root); };

/* Heap
 * A specialized tree-based data structure which is essentially an almost complete[1] tree that satisfies the heap property:
 * In a max heap, for any given node C, if P is a parent node of C, then the key (the value) of P is greater than or equal to the key of C.
 * In a min heap, the key of P is less than or equal to the key of C*/
// LC0703
//struct KthLargest { KthLargest(int k, vector<int>& nums); int add(int val); };
struct LC1046 { int lastStoneWeight(vector<int>& stones); };
/*給定分數陣列，找出相對排名*/
struct LC0506 { vector<string> findRelativeRanks(vector<int>& score); };

/* Trie (Prefix tree or Digital Tree )
 * A type of k-ary search tree, a tree data structure used for locating specific keys from within a set.
 * These keys are most often strings, with links between nodes defined not by the entire key, but by individual characters.
 * In order to access a key (to recover its value, change it, or remove it), the trie is traversed depth-first,
 * following the links between nodes, which represent each character in the key.*/

/* Segment tree (Statistic tree)
 * Used for storing information about intervals, or segments.
 * It allows querying which of the stored segments contain a given point.
 * In principle, a static structure; that is, it's a structure that cannot be modified once it's built*/

/* Fenwick tree (Binary indexed tree)
 * A data structure that can efficiently update elements and calculate prefix sums in a table of numbers */

#endif //GOOGLE_TREE_H
