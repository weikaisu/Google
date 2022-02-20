//
// Created by WeiKai Steve Su on 2022/2/20.
//

#include "tree.h"

//TreeNode *root;
//root->BuildTree(root);
//LC110 run;
//cout << run.isBalanced(root) << endl;
//root->CleanTree(root);
bool LC110::isBalanced(TreeNode* root) {
    auto getTreeHeight = [](const auto &self, TreeNode* root, bool &isBalanse)->int {
        if(!root) return 0;
        int lHeight = self(self, root->left, isBalanse);
        int rHeight = self(self, root->right, isBalanse);
        if(abs(lHeight-rHeight)>1) isBalanse=false;
        return max(lHeight, rHeight)+1;
    };

    if(!root) return true;
    bool isBalance = true;
    getTreeHeight(getTreeHeight, root, isBalance);
    return isBalance;
}

bool LC100::isSameTree(TreeNode* p, TreeNode* q) {
    if(!p&&!q) return true;
    if((!p||!q) || (p->val!=q->val)) return false;
    return isSameTree(p->left, q->left) || isSameTree(p->right, q->right);
}

void TreeNode::BuildTree(TreeNode *&root) {
    /*   Let us create below tree
    *       3
    *     /   \
    *    9    20
    *        /  \
    *       15   7
    */
    root = new TreeNode(3);
    root->left = new TreeNode(9);
    root->right = new TreeNode(20);
    root->right->left = new TreeNode(15);
    root->right->right = new TreeNode(7);
};

void TreeNode::CleanTree(TreeNode *root) {
    // traverse the tree in post order to free each tree node.
    if(!root) return;
    if(root->left)  CleanTree(root->left);
    if(root->right) CleanTree(root->right);
    // cout << "delete " << root->val << endl;
    delete root;
    root = nullptr;
}

void TreeNode::TraverseInOrder(TreeNode *root) {
    if(!root) return;
    cout << root->val << endl;
    if(root->left) TraverseInOrder(root->left);
    if(root->right) TraverseInOrder(root->right);
}

void TreeNode::TraversePreOrder(TreeNode *root) {
    if(!root) return;
    if(root->left) TraversePreOrder(root->left);
    cout << root->val << endl;
    if(root->right) TraversePreOrder(root->right);
}

void TreeNode::TraversePostOrder(TreeNode *root) {
    if(!root) return;
    if(root->left) TraversePostOrder(root->left);
    if(root->right) TraversePostOrder(root->right);
    cout << root->val << endl;
}

void TreeNode::TraverseLevelOrder(TreeNode *root) {
    if(!root) return;

    queue<TreeNode*> q;
    q.push(root);
    while(q.size()) {
        TreeNode *node = q.front(); q.pop();
        cout << node->val << endl;
        if(node->left) q.push(node->left);
        if(node->right) q.push(node->right);
    }
}

void TreeNode::TraverseTopDown(TreeNode *root) {
    if(!root) return;

    queue<TreeNode*> q;
    int level_size = 0;

    q.push(root);
    while(level_size = q.size()) {
        while(level_size--) {
            TreeNode* node = q.front(); q.pop();
            cout << node->val << " ";
            if(node->left) q.push(node->left);
            if(node->right) q.push(node->right);
        }
        cout << endl;
    }
}

void TreeNode::TraverseBottomUp(TreeNode *root) {
    if(!root) return;

    queue<TreeNode*> q;
    stack<TreeNode*> s;
    int level_size = 0;

    q.push(root);
    while(level_size=q.size()) {
        while(level_size--) {
            TreeNode* node = q.front(); q.pop();
            s.push(node);
            if(node->right) q.push(node->right);
            if(node->left) q.push(node->left);
        }
        s.push(nullptr);
    }

    while(s.size()) {
        TreeNode *node = s.top(); s.pop();
        if(!node) cout << endl;
        else cout << node->val << " ";
    }
}