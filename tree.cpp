#include "tree.h"

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

    /*   Let us create below tree
    *       1
    *     /   \
    *    2    2
    *   /  \ /  \
    *  3   4 4    3
    */
    root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(2);
    root->left->left = new TreeNode(3);
    root->left->right = new TreeNode(4);
    root->right->left = new TreeNode(4);
    root->right->right = new TreeNode(3);
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

void TreeNode::TraversePreOrder(TreeNode *root) {
    if(!root) return;
    cout << root->val << endl;
    if(root->left) TraverseInOrder(root->left);
    if(root->right) TraverseInOrder(root->right);
}

void TreeNode::TraverseInOrder(TreeNode *root) {
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
    // 僅依序印出，不需一層一層列印node
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

    queue<TreeNode*> q; // 用來放每一層node
    stack<TreeNode*> s; // 從root往下走訪時存入stack之後可先取出bottom nodes
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