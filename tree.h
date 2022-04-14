
#ifndef GOOGLE_TREE_H
#define GOOGLE_TREE_H

#include <iostream>
#include <cmath>
#include <algorithm>
#include <queue>
#include <stack>
#include <unordered_set>

using namespace std;

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
struct LC0110 { bool isBalanced(TreeNode* root); };
struct LC0100 { bool isSameTree(TreeNode* p, TreeNode* q); };
struct LC0094 { vector<int> inorderTraversal(TreeNode* root); };

/***********  Medium  **********/

#endif //GOOGLE_TREE_H
