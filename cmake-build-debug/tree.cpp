//
// Created by WeiKai Steve Su on 2022/2/20.
//

#include "tree.h"


bool LC100::SameTree(TreeNode* p, TreeNode* q) {
    if(!p&&!q) return true;
    if((!p||!q) || (p->val!=q->val)) return false;
    return SameTree(p->left, q->left) || SameTree(p->right, q->right);
}