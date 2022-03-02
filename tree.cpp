
#include "tree.h"

bool LC0653::findTarget(TreeNode* root, int k) {
    // 遍历二叉树就行，然后用一个HashSet，在递归函数函数中，如果node为空，返回false。如果k减去当前结点值在HashSet中存在，直接返回true；
    // 否则就将当前结点值加入HashSet，然后对左右子结点分别调用递归函数并且或起来返回即可
    // recursive
//    auto fun = [&](const auto& self, TreeNode* node, int k, unordered_set<int> &s) -> bool {
//        if(!node) return false;
//        if(s.count(k-node->val)) return true;
//        s.insert(node->val);
//        return self(self, node->left, k, s) || self(self, node->right, k, s);
//    };
//
//    unordered_set<int> s;
//    return fun(fun, root, k, s);

    // iterative
    unordered_set<int> s;
    queue<TreeNode*> q{{root}};

    while(q.size()) {
        TreeNode * node = q.front(); q.pop();
        if(s.count(k-node->val)) return true;
        s.insert(node->val);
        if(node->left)  q.push(node->left);
        if(node->right) q.push(node->right);
    }
    return false;
}

vector<double> LC0637::averageOfLevels(TreeNode* root) {
    if(!root) return {};

    vector<double> ans;
    queue<TreeNode*> q;
    int level_size = 0;
    int level_cont = 0;

    q.push(root);

    while(level_size=level_cont=q.size()) {
        double accu = 0.0;
        while(level_size--) {
            TreeNode* node = q.front(); q.pop();
            accu += node->val;
            if(node->left) q.push(node->left);
            if(node->right) q.push(node->right);
        }
        ans.push_back(static_cast<double>(accu)/level_cont);
    }
    return ans;
}

TreeNode* LC0617::mergeTrees(TreeNode* root1, TreeNode* root2) {
    if(!root1) return root2; if(!root2) return root1;

    // merge root2 to root1
    TreeNode *root = root1;
    root->val   = root1->val + root2->val;
    root->left  = mergeTrees(root1->left,  root2->left);
    root->right = mergeTrees(root1->right, root2->right);
    return root;
}

string LC0606::tree2str(TreeNode* root) {
    if(!root) return "";

    const string m = to_string(root->val);
    const string l = tree2str(root->left);
    const string r = tree2str(root->right);

    // case : s
    if(!root->left && !root->right) return m;
    // case : s(l)
    if(!root->right) return m+"("+l+")";
    // general: s(l)(r)
    return m+"("+l+")"+"("+r+")";
}

int LC0543::diameterOfBinaryTree(TreeNode* root) {
    auto diameter = [](const auto &self, TreeNode *root, int &len) -> int {
        if(!root) return -1;
        int left_len  = self(self, root->left,  len) +1;
        int right_len = self(self, root->right, len) +1;
        len = max(len, left_len+right_len);
        return max(left_len, right_len);
    };

    int len = 0;
    diameter(diameter, root, len);
    return len;
}

int LC0404::sumOfLeftLeaves(TreeNode* root) {
    int sum = 0;
    if(!root) return sum;

    if(root->left && !root->left->left && !root->left->right)
        sum += root->left->val;
    return sum + sumOfLeftLeaves(root->left) + sumOfLeftLeaves(root->right);
}

//TreeNode *root;
//root->BuildTree(root);
//LC110 run;
//cout << run.isBalanced(root) << endl;
//root->CleanTree(root);
bool LC0110::isBalanced(TreeNode* root) {
    auto getTreeHeight = [](const auto &self, TreeNode* root, bool &isBalanse) -> int {
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

bool LC0100::isSameTree(TreeNode* p, TreeNode* q) {
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