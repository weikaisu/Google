#include "tree.h"

/***********  Binary Search Tree  **********/
int LC0938::rangeSumBST(TreeNode* root, int low, int high) {
    /*求BST在某範圍內結點之和*/
    // 由于 BST 具有 左<根<右 的特点，所以就可以进行剪枝，若当前结点值小于L，则说明其左子树所有结点均小于L，可以直接将左子树剪去；同理，
    // 若当前结点值大于R，则说明其右子树所有结点均大于R，可以直接将右子树剪去。否则说明当前结点值正好在区间内，将其值累加上，并分别对左右子
    // 结点调用递归函数即可
    // 遞歸
    // 1. 在每一個node看val不在範圍內的話則剪枝左或右子樹
    // 2. 回傳val(如果在範圍內)加上左右子樹累積的和
    function<int(TreeNode*)> fun = [&](TreeNode* node) -> int {
        if(node == nullptr) return 0;
        if(node->val < low) node->left = nullptr;
        if(node->val > high) node->right = nullptr;
        return ((node->val>=low && node->val<=high) ? node->val : 0) + fun(node->left) + fun(node->right);
    };
    return fun(root);
}

TreeNode* LC0897::increasingBST(TreeNode* root) {
    /*重新排序BST，最左結點變成root*/
    // 给了一棵二叉树，让我们对其进行重排序，使得最左结点变为根结点，而且整个树不能有左子结点，如题目中的例子所示，排序后的结果是一条向右下方
    // 延伸的直线。如果我们仔细观察题目中的例子，可以发现遍历顺序其实是 左->根->右，就是中序遍历的顺序，虽然题目中没说是二叉搜索树，但这并不
    // 影响我们进行中序遍历。我们先从最简单的例子开始分析，当 root 为空时，直接返回空，当 root 没有左右子结点时，也是直接返回 root。当 root
    // 只有一个左子结点时，我们此时要把其左子结点变为根结点，将原来的根结点变成其原来的左子结点的右子结点。但是如果 root 只有一个右子结点，
    // 还是保持原来的顺序不变，而若 root 同时具有左右子结点的话，还是要将左子结点变为根结点，然后把之前的根结点连到右子结点上，之前的右子结点
    // 还连在之前的根结点上，这个不用改变。我们可以发现，最麻烦的就是左子结点了，需要和其根结点交换位置，所以对于每个结点，我们需要知道其父结点
    // 的位置，那么就在递归函数的参数中传入一个 pre 结点，再对左右子结点调用递归函数时，都将其下一个要连接的结点传入，这个 pre 结点可能是当前
    // 结点或者当前结点的父结点。
    //
    // 在递归函数中，首先判空，若当前结点为空的话，直接返回 pre 结点，因为到空结点的时候，说明已经遍历到叶结点的下方了，那么 pre 就是这个叶结
    // 点了。由于是中序遍历，所以要先对左子结点调用递归函数，将返回值保存到一个新的结点 res 中，表示的意义是此时 node 的左子树已经全部捋直了，
    // 而且根结点就是 res，而且 node 结点本身也被连到了捋直后的左子树下，即此时左子结点和根结点已经完成了交换位子，当然要断开原来的连接，所以
    // 将 node->left 赋值为 nullptr。然后再对 node 的右子结点调用递归函数，注意此时的 pre 不能传入 node 本身，而是要传 node 结点的
    // pre 结点，这是因为右子结点后面要连接的是 node 的父结点
    // recursive way
    // 遞歸
    // 1. 在每一個node先處理左子node再處理右子node
    // 2. 左子node的pre是自己，右子node的pre是自己的父node(如此就可以把父node接到自己的右子node)
    // 3. 左子node的處理完後設成nullptr
    // 4. 回傳每個node的最左leaf node
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
        while(p) { // 在每個node循環找到最左leaf
            s.push(p);
            p = p->left;
        }
        p = s.top(); s.pop();
        pre->right = p;
        pre = pre->right; // pre代表新root，一路往右走
        p->left = nullptr;
        p = p->right; // p代表在每個node切換開始處理右子樹
    }
    return dummy->right;
}

int LC0783::minDiffInBST(TreeNode* root) {
    /*求BST任兩結點的最小差值*/
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
    /*在BST內搜索val*/
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
    /*判斷BST裡是否有兩結點之和為k*/
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
    /*求BST任兩結點的最小差值*/
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
    /*求BST裡所有的眾數(modes, the most frequently occurred elements)*/
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
    /*將有序陣列轉成BST*/
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