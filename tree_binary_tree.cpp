#include "tree.h"

/***********  Binary Tree  **********/
int LC1022::sumRootToLeaf(TreeNode* root) {
    // 给了一个结点值为0或1的二叉树，让返回所有从根结点到叶结点的路径组成的二进制数字的和。实际上就是一道变形的路径之和的题目，关于路径之和，
    // LeetCode 有很多道题目，比如 Path Sum IV，Path Sum III，Binary Tree Maximum Path Sum，Path Sum II，Path Sum，和
    // Minimum Path Sum 等等。还是要用递归来做，就使用先序遍历就可以了，使用一个变量 cur 记录从根结点到当前结点的路径的二进制数对应的十
    // 进制的值，每当新加一个结点时，当前的数字要左移一位，也就是乘以2，再加上当前的结点值。若当前结点是个叶结点，则说明一条完整的路径已经找
    // 到了，将数字加入结果 res，然后对左右子结点分别调用递归函数即可
//    int res=0;
//    function<void(TreeNode*, int)> fun = [&](TreeNode* node, int sum) {
//        if(node == nullptr) return;
//        sum = sum*2 + node->val;
//        if(!node->left && !node->right)
//            res += sum;
//        fun(node->left, sum);
//        fun(node->right, sum);
//    };
//    fun(root, 0);
//    return res;

    // 也可以写的更简洁一些，让 helper 函数返回路径之和的值，这样在更新完 cur 之和，只要判断是否是叶结点，是的话直接返回 cur，
    // 否则返回对左右子结点调用递归函数的返回值之和即可
    function<int(TreeNode*, int)> fun = [&](TreeNode* node, int sum) -> int {
        if(node == nullptr) return 0;
        sum = sum*2 + node->val;
        return node->left == node->right ? sum : fun(node->left, sum) + fun(node->right, sum);
    };
    return fun(root, 0);
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

TreeNode* LC0226::invertTree(TreeNode* root) {
    // 翻转二叉树，递归的方法，写法非常简洁，五行代码搞定，交换当前左右节点，并直接调用递归即可
//    if(!root) return nullptr;
//    TreeNode* node = root->left;
//    root->left = invertTree(root->right);
//    root->right = invertTree(node);
//    return root;

    // 非递归的方法也不复杂，跟二叉树的层序遍历一样，需要用queue来辅助，先把根节点排入队列中，然后从队中取出来，交换其左右节点，
    // 如果存在则分别将左右节点在排入队列中，以此类推直到队列中木有节点了停止循环，返回root即可
    if(root == nullptr) return root;
    queue<TreeNode*> q{{root}};
    while(q.size()) {
        TreeNode* node = q.front(); q.pop();
        TreeNode* tmp = node->left;
        node->left = node->right;
        node->right = tmp;
        if(node->left) q.push(node->left);
        if(node->right) q.push(node->right);
    }
    return root;
}

int LC0222::countNodes(TreeNode* root) {
    // 给定了一棵完全二叉树，让我们求其节点的个数。直接用递归来统计结点的个数，根本不需要考虑什么完全二叉树还是完美二叉树，递归在手，遇 tree 不愁。
    return root ? (1 + countNodes(root->left) + countNodes(root->right)) : 0;
}

vector<int> LC0145::postorderTraversal(TreeNode* root) {
    // 改变先序遍历的顺序来实现后序遍历。比起另一種方法會有較少的s.push，所以性能較好。
    if(!root) return {};
    vector<int> res;
    stack<TreeNode*> s;
    TreeNode* p = root;
    while(s.size() || p) {
        if(p) {
            s.push(p);
            res.insert(res.begin(), p->val);
            p = p->right;
        } else {
            p = s.top(); s.pop();
            p = p->left;
        }
    }
    return res;

    // 改变先序遍历的顺序来实现后序遍历，跟LC0144相同的作法，只是改用res.insert()的方式
//    if(!root) return {};
//    vector<int> res;
//    stack<TreeNode*> s({root});
//    while(s.size()) {
//        TreeNode* node=s.top(); s.pop();
//        res.insert(res.begin(), node->val);
//        if(node->left) s.push(node->left);
//        if(node->right) s.push(node->right);
//    }
//    return res;
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
    /*求2叉樹的最大深度*/
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
    if(!p && !q) return true;
    if(!p || !q || (p->val!=q->val)) return false;
    return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
}

vector<int> LC0094::inorderTraversal(TreeNode* root) {
    // 递归方法，十分直接，对左子结点调用递归函数，根节点访问值，右子节点再调用递归函数
//    if(root==nullptr) return {};
//    vector<int> res;
//    function<void(TreeNode*)> dfs = [&](TreeNode* root) -> void {
//        if(root->left) dfs(root->left);
//        res.push_back(root->val);
//        if(root->right) dfs(root->right);
//    };
//    dfs(root);
//    return res;

    // 从根节点开始，先将根节点压入栈，然后再将其所有左子结点压入栈，然后取出栈顶节点，保存节点值，再将当前指针移到其右子节点上，若存在右子节
    // 点，则在下次循环时又可将其所有左子结点压入栈中。这样就保证了访问顺序为左-根-右
    vector<int> res;
    stack<TreeNode*>  s;
    TreeNode *p = root;
    while(s.size() || p) {
        if(p) { // 當p有值時表示需先繼續走訪左子樹
            s.push(p);
            p = p->left;
        } else { // 當p無值時表示取val，並開始走訪右子樹
            p = s.top(); s.pop();
            res.push_back(p->val);
            p = p->right;
        }
    }
    return res;
}