
#include <numeric>
#include "tree.h"

/***********  Heap  **********/
vector<int> LC1337::kWeakestRows(vector<vector<int>>& mat, int k) {
    // You are given an m x n binary matrix mat of 1's (representing soldiers) and 0's (representing civilians).
    // The soldiers are positioned in front of the civilians. That is, all the 1's will appear to the left of all
    // the 0's in each row.
    // A row i is weaker than a row j if one of the following is true:
    // The number of soldiers in row i is less than the number of soldiers in row j.
    // Both rows have the same number of soldiers and i < j.
    // Return the indices of the k weakest rows in the matrix ordered from weakest to strongest.
    // Input: mat =
    //[[1,1,0,0,0],
    // [1,1,1,1,0],
    // [1,0,0,0,0],
    // [1,1,0,0,0],
    // [1,1,1,1,1]],
    // k = 3
    // Output: [2,0,3]
    // Explanation:
    // The number of soldiers in each row is:
    // - Row 0: 2
    // - Row 1: 4
    // - Row 2: 1
    // - Row 3: 2
    // - Row 4: 5
    // The rows ordered from weakest to strongest are [2,0,3,1,4].

    // use priority queue and merge soldier count and index into one number : cunt*100 + idx;
    const int m=mat.size();
    priority_queue<int, vector<int>, greater<int>> pq;
    vector<int> res(k);

    for(int i=0; i<m; i++)
        pq.push(std::accumulate(mat[i].begin(), mat[i].end(), 0) * 100 + i);

    for(int i=0; i<k; i++) {
        res[i] = pq.top() % 100;
        pq.pop();
    }

    return res;

//    // 算出每個row 1的個數，建立pair(1's, row), 調用std::sort即可根據pair的第一個欄位排序，如此得到前k名row的index
//    const int m=mat.size();
//    vector<int> res(k);
//    vector<pair<int, int>> v(m);
//
//    for(int i=0; i<m; i++) {
//        int n = std::accumulate(mat[i].begin(), mat[i].end(), 0);
//        v[i] = pair(n,i);
//    }
//
//    std::sort(v.begin(), v.end());
//
//    for(int i=0; i<k && i<m; i++)
//        res[i] = v[i].second;
//
//    return res;
}

// LC0703
struct KthLargest {
    // 让我们在数据流中求第K大的元素，跟之前那道Kth Largest Element in an Array很类似，但不同的是，那道题的数组是确定的，不会再增加元
    // 素，这样确定第K大的数字就比较简单。而这道题的数组是不断在变大的，所以每次第K大的数字都在不停的变化。那么我们其实只关心前K大个数字就可
    // 以了，所以我们可以使用一个最小堆来保存前K个数字，当再加入新数字后，最小堆会自动排序，然后把排序后的最小的那个数字去除，则堆中还是K个数
    // 字，返回的时候只需返回堆顶元素即可
    priority_queue<int, vector<int>, greater<int>> pq;
    int min_k;
    KthLargest(int k, vector<int>& nums) {
        min_k = k;
        for(int &num:nums) {
            pq.push(num);
            if(pq.size()>min_k) pq.pop();
        }
    };
    int add(int val) {
        pq.push(val);
        if(pq.size()>min_k) pq.pop();
        return pq.top();
    };

    // use multiset, 較慢
//    multiset<int> pq;
//    int min_k;
//    KthLargest(int k, vector<int>& nums) {
//        min_k = k;
//        for(int &num:nums) {
//            pq.insert(num);
//            if(pq.size()>min_k) pq.erase(pq.begin());
//        }
//    }
//    int add(int val) {
//        pq.insert(val);
//        if(pq.size()>min_k) pq.erase(pq.begin());
//        return *pq.begin();
//    }
};

int LC1046::lastStoneWeight(vector<int>& stones) {
    // 给了一堆重量不同的石头，每次选出两个最重的出来相互碰撞，若二者重量相同，则直接湮灭了，啥也不剩，否则剩一个重量为二者差值的石头。然后继
    // 续如此操作，直至啥也不剩（返回0），或者剩下一个石头（返回该石头的重量）。这道题是一道 Easy 的题目，没有太大的难度，主要就是每次要选出
    // 最大的两个数字，若是给数组排序，是可以知道最后两个数字是最大的，然是碰撞过后若有剩余，要将这个剩余的石头加到数组的合适位置，每次都排一
    // 次序显然时间复杂度太大。这里需要用一个更合理的数据结构，最大堆，在 C++ 中用优先队列实现的，每次加入一个新的石头，就会自动根据其重量加
    // 入到正确的位置。起始时将所有的石头加入优先队列中，然后进行循环，条件是队列中的石头个数大于1，然后取出队首两个石头，假如重量不等，则将
    // 差值加入队列。最终只需要判断队列是否为空，是的话返回0，否则返回队首元素
    priority_queue<int> pq;
    for(int &stone:stones) pq.push(stone);
    while(pq.size()>1) {
        int first  = pq.top(); pq.pop();
        int second = pq.top(); pq.pop();
        if(first>second) pq.push(first-second);
    }
    return pq.empty() ? 0 : pq.top();

    // use multiset, 不能用set，set裡同值只能有一個
//    multiset<int> pq;
//    for(int &stone:stones) pq.insert(stone);
//    while(pq.size()>1) {
//        // 最大的在最後面，要刪除時要刪std::prev(pq.end())
//        int first  = *pq.rbegin(); pq.erase(std::prev(pq.end()));
//        int second = *pq.rbegin(); pq.erase(std::prev(pq.end()));
//        if(first>second) pq.insert(first-second);
//    }
//    return pq.empty() ? 0 : *pq.begin();
}

vector<string> LC0506::findRelativeRanks(vector<int>& score) {
    // 这道题给了我们一组分数，让我们求相对排名，前三名分别是金银铜牌，后面的就是名次数，利用map的自动排序的功能，不过map是升序排列的，所以
    // 我们遍历的时候就要从最后面开始遍历，最后一个是金牌，然后往前一次是银牌，铜牌，名次数等
//    vector<string> res(score.size(), "");
//    map<int,int> m;
//    for(int i=0; i<score.size(); i++)
//        m[score[i]]=i;
//    int cnt=1;
//    for(auto it=m.rbegin(); it!=m.rend(); it++) {
//        if(cnt==1) res[it->second] = "Gold Medal";
//        else if(cnt==2) res[it->second] = "Silver Medal";
//        else if(cnt==3) res[it->second] = "Bronze Medal";
//        else res[it->second] = to_string(cnt);
//        cnt++;
//    }
//    return res;

    // 建立一个坐标数组，不过排序的时候比较的不是坐标，而是该坐标位置上对应的数字，后面的处理方法和之前的并没有什么不同
    int n = score.size();
    vector<string> res(n,"");
    vector<int> idx(n);
    for(int i=0; i<n; i++) idx[i]=i;
    sort(idx.begin(), idx.end(), [&](int i, int j){return score[i]>score[j];});
    for(int i=0; i<n; i++) {
        if(i==0) res[idx[i]] = "Gold Medal";
        else if(i==1) res[idx[i]] = "Silver Medal";
        else if(i==2) res[idx[i]] = "Bronze Medal";
        else res[idx[i]] = to_string(i+1);
    }
    return res;
}

/***********  Binary Tree  **********/
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

/***********  Binary Search Tree  **********/
int LC0938::rangeSumBST(TreeNode* root, int low, int high) {
    // 由于 BST 具有 左<根<右 的特点，所以就可以进行剪枝，若当前结点值小于L，则说明其左子树所有结点均小于L，可以直接将左子树剪去；同理，
    // 若当前结点值大于R，则说明其右子树所有结点均大于R，可以直接将右子树剪去。否则说明当前结点值正好在区间内，将其值累加上，并分别对左右子
    // 结点调用递归函数即可
    function<int(TreeNode*)> fun = [&](TreeNode* node) -> int {
        if(node == nullptr) return 0;
        if(node->val < low) node->left = nullptr;
        if(node->val > high) node->right = nullptr;
        return ((node->val>=low && node->val<=high) ? node->val : 0) + fun(node->left) + fun(node->right);
    };
    return fun(root);
}

TreeNode* LC0897::increasingBST(TreeNode* root) {
    // 给了一棵二叉树，让我们对其进行重排序，使得最左结点变为根结点，而且整个树不能有左子结点，如题目中的例子所示，排序后的结果是一条向右下方
    // 延伸的直线。如果我们仔细观察题目中的例子，可以发现遍历顺序其实是 左->根->右，就是中序遍历的顺序，虽然题目中没说是二叉搜索树，但这并不
    // 影响我们进行中序遍历。我们先从最简单的例子开始分析，当 root 为空时，直接返回空，当 root 没有左右子结点时，也是直接返回 root。当 root
    // 只有一个左子结点时，我们此时要把其左子结点变为根结点，将原来的根结点变成其原来的左子结点的右子结点。但是如果 root 只有一个右子结点，
    // 还是保持原来的顺序不变，而若 root 同时具有左右子结点的话，还是要将左子结点变为根结点，然后把之前的根结点连到右子结点上，之前的右子结点
    // 还连在之前的根结点上，这个不用改变。我们可以发现，最麻烦的就是左子结点了，需要和其根结点交换位置，所以对于每个结点，我们需要知道其父结点
    // 的位置，那么就在递归函数的参数中传入一个 pre 结点，再对左右子结点调用递归函数时，都将其下一个要连接的结点传入，这个 pre 结点可能是当前
    // 结点或者当前结点的父结点。
    //
    //在递归函数中，首先判空，若当前结点为空的话，直接返回 pre 结点，因为到空结点的时候，说明已经遍历到叶结点的下方了，那么 pre 就是这个叶结
    // 点了。由于是中序遍历，所以要先对左子结点调用递归函数，将返回值保存到一个新的结点 res 中，表示的意义是此时 node 的左子树已经全部捋直了，
    // 而且根结点就是 res，而且 node 结点本身也被连到了捋直后的左子树下，即此时左子结点和根结点已经完成了交换位子，当然要断开原来的连接，所以
    // 将 node->left 赋值为 nullptr。然后再对 node 的右子结点调用递归函数，注意此时的 pre 不能传入 node 本身，而是要传 node 结点的
    // pre 结点，这是因为右子结点后面要连接的是 node 的父结点
    // recursive way
//    function<TreeNode*(TreeNode*, TreeNode*)> fun = [&](TreeNode* node, TreeNode* pre) -> TreeNode* {
//        if(node == nullptr) return pre;
//        TreeNode* res = fun(node->left, node);
//        node->left = nullptr;
//        node->right = fun(node->right, pre);
//        return res;
//    };
//    return fun(root, nullptr);

    // 采用中序遍历的迭代形式，使用栈来辅助。由于根结点可能会产生变化，所以我们需要一个 dummy 结点，还需要一个 pre 结点。在 while 循环中，
    // 先找到最左结点，把路径上的所有结点都压入栈，然后取出栈顶元素，将其连到 pre 的右子结点上，并将 pre 更新为其右子结点，然后断开栈顶元素
    // 的左子结点连接，并将其移动到右子结点上，并继续循环，最终返回 dummy 的右子结点即可
    // iterative way
    TreeNode *dummy = new TreeNode(-1), *pre = dummy, *p=root;
    stack<TreeNode*> s;
    while(s.size() || p) {
        while(p) {
            s.push(p);
            p = p->left;
        }
        p = s.top(); s.pop();
        pre->right = p;
        pre = pre->right;
        p->left = nullptr;
        p = p->right;
    }
    return dummy->right;
}

int LC0783::minDiffInBST(TreeNode* root) {
    // the same as LC0530
    // recursive way
//    int mn=INT_MAX;
//    TreeNode* pre=nullptr;
//    function<void(TreeNode*)> fun = [&](TreeNode* node) {
//        if(node == nullptr) return;
//        fun(node->left);
//        if(pre)
//            mn = std::min(mn, node->val - pre->val);
//        pre = node;
//        fun(node->right);
//    };
//    fun(root);
//    return mn;

    // iterative way
    int mn=INT_MAX;
    TreeNode *pre=nullptr, *p=root;
    stack<TreeNode*> s;
    while(s.size() || p) {
        while(p) {
            s.push(p);
            p = p->left;
        }
        p = s.top(); s.pop();
        if(pre)
            mn = std::min(mn, p->val - pre->val);
        pre = p;
        p = p->right;
    }
    return mn;

}

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

int LC0530::getMinimumDifference(TreeNode* root) {
    // 给了我们一棵二叉搜索树，让我们求任意个节点值之间的最小绝对差。由于BST的左<根<右的性质可知，如果按照中序遍历会得到一个有序数组，那么最
    // 小绝对差肯定在相邻的两个节点值之间产生。所以我们的做法就是对BST进行中序遍历，然后当前节点值和之前节点值求绝对差并更新结果res。这里需
    // 要注意的就是在处理第一个节点值时，由于其没有前节点，所以不能求绝对差。这里我们用变量pre来表示前节点值，这里由于题目中说明了所以节点值
    // 不为负数，所以我们给pre初始化-1，这样我们就知道pre是否存在。如果没有题目中的这个非负条件，那么就不能用int变量来，必须要用指针，通过
    // 来判断是否为指向空来判断前结点是否存在。还好这里简化了问题，用-1就能搞定了，这里我们先来看中序遍历的递归写法
    // recursive way
//    int mn=INT_MAX;
//    TreeNode* pre=nullptr;
//    function<void(TreeNode*)> fun = [&](TreeNode* node) {
//        if(node == nullptr) return;
//        fun(node->left);
//        if(pre)
//            mn = std::min(mn, node->val-pre->val);
//        pre = node;
//        fun(node->right);
//    };
//    fun(root);
//    return mn;

    // iterative way
    int mn=INT_MAX;
    TreeNode *pre=nullptr, *p=root;
    stack<TreeNode*> s;
    while(s.size() || p) {
        while(p) {
            s.push(p);
            p = p->left;
        }
        p = s.top(); s.pop();
        if(pre)
            mn = std::min(mn, p->val - pre->val);
        pre = p;
        p = p->right;
    }
    return mn;
}

vector<int> LC0501::findMode(TreeNode* root) {
    // 求二分搜索树中的众数，这里定义的二分搜索树中左根右结点之间的关系是小于等于的，有些题目中是严格小于的，所以一定要看清题目要求。所谓的
    // 众数就是出现最多次的数字，可以有多个，那么这道题比较直接点思路就是利用一个哈希表来记录数字和其出现次数之前的映射，然后维护一个变量mx
    // 来记录当前最多的次数值，这样在遍历完树之后，根据这个mx值就能把对应的元素找出来。那么用这种方法的话就不需要用到二分搜索树的性质了，随
    // 意一种遍历方式都可以
    // recursive way
//    vector<int> res;
//    int mode = INT_MIN;
//    unordered_map<int, int> map;
//    function<void(TreeNode*)> fun = [&](TreeNode* node) {
//        if(node == nullptr) return node;
//        fun(node->left);
//        ++map[node->val];
//        mode = std::max(mode, map[node->val]);
//        fun(node->right);
//        return node;
//    };
//    fun(root);
//    for(auto &m:map)
//        if(m.second == mode)
//            res.push_back(m.first);
//    return res;

    // iterative way
//    if(root == nullptr) return {};
//    vector<int> res;
//    int mode=INT_MIN;
//    unordered_map<int, int> map;
//    stack<TreeNode*> s;
//    TreeNode* p=root;
//    while(s.size() || p) {
//        while(p) {
//            s.push(p);
//            p = p->left;
//        }
//        p = s.top(); s.pop();
//        ++map[p->val];
//        mode = std::max(mode, map[p->val]);
//        p = p->right;
//    }
//    for(auto &m:map)
//        if(m.second == mode)
//            res.push_back(m.first);
//    return res;

    // 题目中的follow up说了让我们不用除了递归中的隐含栈之外的额外空间，那么我们就不能用哈希表了，不过这也不难，由于是二分搜索树，那么我们
    // 中序遍历出来的结果就是有序的，这样我们只要比较前后两个元素是否相等，就等统计出现某个元素出现的次数，因为相同的元素肯定是都在一起的。我
    // 们需要一个结点变量pre来记录上一个遍历到的结点，然后mx还是记录最大的次数，cnt来计数当前元素出现的个数，我们在中序遍历的时候，如果pre
    // 不为空，说明当前不是第一个结点，我们和之前一个结点值比较，如果相等，cnt自增1，如果不等，cnt重置1。如果此时cnt大于了mx，那么我们清空
    // 结果res，并把当前结点值加入结果res，如果cnt等于mx，那我们直接将当前结点值加入结果res，然后mx赋值为cnt。最后我们要把pre更新为当前结点
    // recursive way
//    vector<int> res;
//    int mode=INT_MIN, cnt=1;
//    TreeNode* pre=nullptr;
//    function<void(TreeNode*)> fun = [&](TreeNode* node) {
//        if(node == nullptr) return;
//        fun(node->left);
//        if(pre)
//            cnt = (node->val == pre->val) ? cnt+1 : 1;
//        if(cnt >= mode) {
//            if(cnt > mode) res.clear();
//            res.push_back(node->val);
//            mode = cnt;
//        }
//        pre = node;
//        fun(node->right);
//    };
//    fun(root);
//    return res;

    // iterative way
    vector<int> res;
    int mode=INT_MIN, cnt=1;
    TreeNode *pre=nullptr, *p=root;
    stack<TreeNode*> s;
    while(s.size() || p) {
        while(p) {
            s.push(p);
            p = p->left;
        }
        p = s.top(); s.pop();
        if(pre)
            cnt = (p->val == pre->val) ? cnt+1 : 1;
        if(cnt >= mode) {
            if(cnt > mode) res.clear();
            res.push_back(p->val);
            mode = cnt;
        }
        pre = p;
        p = p->right;
    }
    return res;
}

TreeNode* LC0108::sortedArrayToBST(vector<int>& nums) {
    // 将有序数组转为二叉搜索树，所谓二叉搜索树，是一种始终满足左<根<右的特性，如果将二叉搜索树按中序遍历的话，得到的就是一个有序数组了。那么
    // 反过来，我们可以得知，根节点应该是有序数组的中间点，从中间点分开为左右两个有序数组，在分别找出其中间点作为原中间点的左右两个子节点，这
    // 不就是是二分查找法的核心思想么。所以这道题考的就是二分查找法
    function<TreeNode*(int l, int r)> fun = [&](int l, int r) -> TreeNode* {
        if(l>r) return nullptr;
        int m = l + (r-l)/2;
        TreeNode* cur = new TreeNode(nums[m]);
        cur->left = fun(l, m-1);
        cur->right = fun(m+1, r);
        return cur;
    };
    return fun(0, nums.size()-1); // 是要建tree，不是搜尋，沒有左壁右開
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