//
// Created by WeiKai Steve Su on 2022/2/20.
//

#ifndef GOOGLE_TREE_H
#define GOOGLE_TREE_H

#include <iostream>
#include <cmath>
#include <algorithm>

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

};

class tree {};

/***********  Easy  **********/
struct LC110 { bool isBalanced(TreeNode* root); };
struct LC100 { bool isSameTree(TreeNode* p, TreeNode* q); };

/***********  Medium  **********/

#endif //GOOGLE_TREE_H
