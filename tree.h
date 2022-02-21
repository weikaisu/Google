//
// Created by WeiKai Steve Su on 2022/2/20.
//

#ifndef GOOGLE_TREE_H
#define GOOGLE_TREE_H

#include <iostream>
#include <cmath>
#include <algorithm>
#include <queue>
#include <stack>

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
struct LC617 { TreeNode* mergeTrees(TreeNode* root1, TreeNode* root2); };
struct LC606 { string tree2str(TreeNode* root); };
struct LC543 { int diameterOfBinaryTree(TreeNode* root); };
struct LC404 { int sumOfLeftLeaves(TreeNode* root); };
struct LC110 { bool isBalanced(TreeNode* root); };
struct LC100 { bool isSameTree(TreeNode* p, TreeNode* q); };

/***********  Medium  **********/

#endif //GOOGLE_TREE_H
