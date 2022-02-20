//
// Created by WeiKai Steve Su on 2022/2/20.
//

#ifndef GOOGLE_TREE_H
#define GOOGLE_TREE_H

struct TreeNode {
    int val;
    int height;
    TreeNode* left;
    TreeNode* right;
    TreeNode* parent;

    TreeNode(int x) : val(x), height(1), left(nullptr), right(nullptr), parent(nullptr) {};
};

class tree {};

struct LC100 { bool SameTree(TreeNode* p, TreeNode* q); };


#endif //GOOGLE_TREE_H
