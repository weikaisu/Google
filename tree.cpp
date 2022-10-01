
#include "tree.h"

TreeNode* LC0700::searchBST(TreeNode* root, int val) {
    // 这道题让我们搜索一个二叉搜索树，既然是二叉搜索树，而不是普通的二叉树，那么我们肯定要利用二叉搜索树特定的性质来解题，即左<根<右。那么就
    // 是说任意一个结点的左子树中的所有结点均小于当前结点，其右子树中的所有结点均大于当前结点。那么这不就是一个天然的二分么，当仁不让的二分搜
    // 索法呼之欲出啊。首先判空，如果当前结点不存在，直接返回空。如果当前结点值等于目标值，返回当前结点。接下来就看如果当前结点值大于目标值，
    // 则对左子结点调用递归函数，否则就对右子结点调用递归函数
//    if(root==nullptr) return nullptr;
//    if(val == root->val) return root;
//    return (val > root->val) ? searchBST(root->right, val) : searchBST(root->left, val);

    // 使用迭代形式来解，使用一个while循环，思路都是一样的，如果当前结点存在，且结点值不等于目标值，那么若结点值大于目标值，则当前结点指向其
    // 左子结点，否则指向其右子结点
    while(root && root->val != val) {
        root = (val > root->val) ? root->right : root->left;
    }
    return root;
}

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

vector<string> LC0257::binaryTreePaths(TreeNode* root) {
    // 给我们一个二叉树，让返回所有根到叶节点的路径，跟之前那道 Path Sum II 很类似，比那道稍微简单一些，不需要计算路径和，
    // 只需要无脑返回所有的路径即可，那么思路还是用递归来解，博主之前就强调过，玩树的题目，十有八九都是递归，而递归的核心就是不停的 DFS
    // 到叶结点，然后在回溯回去。在递归函数中，当遇到叶结点的时候，即没有左右子结点，那么此时一条完整的路径已经形成了，
    // 加上当前的叶结点后存入结果 res 中，然后回溯。注意这里结果 res 需要 reference，而 out 是不需要引用的，不然回溯回去还要删除新添加
    // 的结点，很麻烦。为了减少判断空结点的步骤，我们在调用递归函数之前都检验一下非空即可，代码而很简洁
    vector<string> res;
    if(!root) return {};
    if(!root->left && !root->right) return {to_string(root->val)};
    for(auto s: binaryTreePaths(root->left))
        res.push_back(to_string(root->val) + "->" + s);
    for(auto s: binaryTreePaths(root->right))
        res.push_back(to_string(root->val) + "->" + s);
    return res;
}

vector<int> LC0144::preorderTraversal(TreeNode* root) {
    // 使用了一个辅助结点p，这种写法其实可以看作是一个模版，对应的还有中序和后序的模版写法，形式很统一，方便于记忆。辅助结点p初始化为根结点，
    // while 循环的条件是栈不为空或者辅助结点p不为空，在循环中首先判断如果辅助结点p存在，那么先将p加入栈中，然后将p的结点值加入结果 res 中，
    // 此时p指向其左子结点。否则如果p不存在的话，表明没有左子结点，取出栈顶结点，将p指向栈顶结点的右子结点
    if(!root) return {};
    vector<int> res;
    stack<TreeNode*> s;
    TreeNode* p = root;
    while(s.size() || p) {
        if(p) {
            s.push(p);
            res.push_back(p->val);
            p = p->left;
        } else {
            p = s.top(); s.pop();
            p = p->right;
        }
    }
    return res;

    // 用到stack来辅助运算。由于先序遍历的顺序是"根-左-右", 算法为：
    //1. 把根节点 push 到栈中
    //2. 循环检测栈是否为空，若不空，则取出栈顶元素，保存其值，然后看其右子节点是否存在，若存在则 push 到栈中。再看其左子节点，若存在，则 push 到栈中。
    /*if(!root) return {};
    vector<int> res;
    stack<TreeNode*> s{{root}};
    while(s.size()) {
        TreeNode* n=s.top(); s.pop();
        res.push_back(n->val);
        if(n->right) s.push(n->right);
        if(n->left) s.push(n->left);
    }
    return res;*/
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

int LC0104::maxDepth(TreeNode* root) {
    // 求二叉树的最大深度问题用到深度优先搜索 Depth First Search，递归的完美应用，跟求二叉树的最小深度问题原理相同
    if(!root) return 0;
    return 1 + std::max(maxDepth(root->left), maxDepth(root->right));

    // 使用层序遍历二叉树，然后计数总层数，即为二叉树的最大深度，注意 while 循环中的 for 循环的写法有个 trick，一定要将 q.size() 放在
    // 初始化里，而不能放在判断停止的条件中，因为q的大小是随时变化的，所以放停止条件中会出错
//    if(!root) return 0;
//    int res = 0;
//    std::queue<TreeNode*> q {{root}};
//    while(q.size()) {
//        res++;
//        for(int i=q.size(); i>0; i--) {
//            TreeNode* node = q.front(); q.pop();
//            if(node->left) q.push(node->left);
//            if(node->right) q.push(node->right);
//        }
//    }
//    return res;
}

bool LC0101::isSymmetric(TreeNode* root) {
    // 判断二叉树是否是平衡树，比如有两个节点n1, n2，我们需要比较n1的左子节点的值和n2的右子节点的值是否相等，同时还要比较n1的右子节点的
    // 值和n2的左子结点的值是否相等，以此类推比较完所有的左右两个节点。
    function<bool(TreeNode*, TreeNode*)> bfs = [&](TreeNode* l, TreeNode* r) -> bool {
        if(!l && !r) return true;
        if(!l || !r || l->val!=r->val) return false;
        return bfs(l->left, r->right) && bfs(l->right, r->left);
    };

    if(!root) return true;
    return bfs(root->left, root->right);

    // 借助队列queue
//    queue<TreeNode*> q;
//    if(!root) return true;
//
//    q.push(root->left);
//    q.push(root->right);
//    while(q.size()) {
//        TreeNode* l = q.front(); q.pop();
//        TreeNode* r = q.front(); q.pop();
//        if(!l && !r) continue;
//        if(!l || !r || l->val!=r->val) return false;
//        q.push(l->left);
//        q.push(r->right);
//        q.push(l->right);
//        q.push(r->left);
//    }
//    return true;
}

bool LC0100::isSameTree(TreeNode* p, TreeNode* q) {
    if(!p&&!q) return true;
    if((!p||!q) || (p->val!=q->val)) return false;
    return isSameTree(p->left, q->left) || isSameTree(p->right, q->right);
}

vector<int> LC0094::inorderTraversal(TreeNode* root) {
    // 递归方法，十分直接，对左子结点调用递归函数，根节点访问值，右子节点再调用递归函数
//    if(root==nullptr) return {};
//    vector<int> res;
//    auto dfs = [&](const auto &self, TreeNode* root) -> void {
//        if(root->left) self(self, root->left);
//        res.push_back(root->val);
//        if(root->right) self(self, root->right);
//    };
//    dfs(dfs, root);
//    return res;

    // 从根节点开始，先将根节点压入栈，然后再将其所有左子结点压入栈，然后取出栈顶节点，保存节点值，再将当前指针移到其右子节点上，若存在右子节
    // 点，则在下次循环时又可将其所有左子结点压入栈中。这样就保证了访问顺序为左-根-右
    vector<int> res;
    stack<TreeNode*>  s;
    TreeNode *p = root;
    while(s.size() || p) {
        if(p) {
            s.push(p);
            p = p->left;
        } else {
            p = s.top(); s.pop();
            res.push_back(p->val);
            p = p->right;
        }
    }
    return res;
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