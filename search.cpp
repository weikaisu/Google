﻿#include "search.h"

/***********  Depth First Search  **********/
int LC0999::numRookCaptures(vector<vector<char>>& board) {
    /*求給定象棋盤中車(rook)能吃到多少卒(pawn)*/
    // one white rook 'R' and some number of white bishops 'B', black pawns 'p', and empty squares '.'.
    // Input: board =
    // [[".",".",".",".",".",".",".","."],
    //  [".",".",".","p",".",".",".","."],
    //  [".",".",".","R",".",".",".","p"],
    //  [".",".",".",".",".",".",".","."],
    //  [".",".",".",".",".",".",".","."],
    //  [".",".",".","p",".",".",".","."],
    //  [".",".",".",".",".",".",".","."],
    //  [".",".",".",".",".",".",".","."]]
    // Output: 3
    // 这道题给了一个 8x8 大小的国际象棋棋盘，上面只能有三种棋子，分别是白方的车，白方的象，和黑方的兵，问白色方的车最多能吃到多个黑方的兵。
    // 在国际象棋中，车是可以上下左右走的，若某条路径上先遇到了白方的象，则该路上没法吃兵了，若先遇上了兵，可以吃，但此时后面若还有兵，不能
    // 连续吃。搞懂了题意其实很简单了，首先遍历棋盘，找到白方车的位置。利用深度优先遍历 DFS 的思想，用方向数组，每次加上方向的偏移，若没有越
    // 界，则判断，若是黑兵，则结果 res 加1，若不是点，则 break，这判断很精髓，覆盖了当前是白象或黑兵的情况，保证了遇到了白象，或者已经吃了
    // 黑兵之后可以 break，然后继续增加偏移量直至退出循环
    int res=0, y0=0, x0=0;
    int m=board.size(), n=board[0].size();
    for(int y=0; y<m; y++)
        for(int x=0; x<n; x++)
            if(board[y][x] == 'R') {
                y0=y; x0=x; break;
            }
    vector<vector<int>> dirs{ {-1,0}, {1,0}, {0,-1}, {0,1} };
    for(auto &dir:dirs) {
        int y=y0+dir[0], x=x0+dir[1];
        while(y>=0 && y<m && x>=0 && x<n) {
            if(board[y][x] == 'p') ++res;
            if(board[y][x] != '.') break;
            y+=dir[0]; x+=dir[1];
        }
    }
    return res;
}

bool LC0993::isCousins(TreeNode* root, int x, int y) {
    /*判斷兩結點是否為表兄弟結點*/
    // Two nodes of a binary tree are cousins if they have the same depth with different parents.
    // 定义了一种二叉树数的表兄弟结点，就是不属于同一个父结点，但是深度相同，现在给了两个结点值，问它们代表的结点是否是表兄弟结点。由于表兄弟
    // 结点一定是属于同一层的，所以可以使用二叉树的层序遍历，就像之前那道 Binary Tree Level Order Traversal 一样。这里额外需要两个布尔
    // 型变量 isX，isY 来记录x和y是否已经遍历到了。由于是层序遍历，所以 while 中需要有个 for 循环，在循环中，取出队首结点，然后看结点值是
    // 否等于x或y，是的话标记布尔变量。然后检查当前结点的左右子结点是否分别是x和y，是的话直接返回 false。否则将左右子结点排入队列之中，若存
    // 在的话。当前层遍历完了之后，检查 isX 和 isY 的值，若同时为 true，表示存在表兄弟结点，返回 true。若只有一个为 true 的话，说明二者不
    // 在同一层，直接返回 false
    // iterative way
//    bool isX=false, isY=false;
//    queue<TreeNode*> q{{root}};
//    while(q.size()) {
//        for(int i=q.size(); i>0; --i) {
//            TreeNode* node = q.front(); q.pop();
//            if(node->val == x) isX = true;
//            if(node->val == y) isY = true;
//            if(node->left && node->right) {
//                int left = node->left->val, right = node->right->val;
//                if((left==x && right==y)||(left==y && right==x)) return false;
//            }
//            if(node->left) q.push(node->left);
//            if(node->right) q.push(node->right);
//        }
//        if(isX && isY) return true;
//        if(isX || isY) return false;
//    }
//    return false;

    // recursive way
    int depthX=0, depthY=0;
    bool isSameParent=false;

    function<void(TreeNode*, int)> dfs = [&](TreeNode* node, int depth) {
        if(node->val == x) depthX = depth;
        if(node->val == y) depthY = depth;
        if(node->left && node->right) {
            int left = node->left->val, right = node->right->val;
            if((left==x && right==y)||(left==y && right==x)) isSameParent = true;
        }
        if(node->left) dfs(node->left, depth+1);
        if(node->right) dfs(node->right, depth+1);
    };
    dfs(root, 0);
    return !isSameParent && depthX == depthY;
}

bool LC0965::isUnivalTree(TreeNode* root) {
    /*判斷樹裡所有結點值是否均相同*/
    // 定义了一种单值二叉树，需要二叉树中所有的结点值相同。先给了一棵二叉树，问是不是单值二叉树。其实就是考察遍历二叉树，当然递归的方法在写法
    // 上最简单了。这里可以将每个结点值都跟根结点值进行比较，只要任意一个不相同，则表示不是单值二叉树。
    // recursive way
//    if(!root) return true;
//    if(root->left && root->left->val != root->val) return false;
//    if(root->right && root->right->val != root->val) return false;
//    return isUnivalTree(root->left) && isUnivalTree(root->right);

    // iterative way
    if(!root) return true;
    queue<TreeNode*> q{{root}};
    while(q.size()) {
        TreeNode* node = q.front(); q.pop();
        if(node->val != root->val) return false;
        if(node->left) q.push(node->left);
        if(node->right) q.push(node->right);
    }
    return true;
}

// LC0784 run;
// vector<string> ans=run.letterCasePermutation("a1b2");
// for(auto a:ans) cout << a << endl;
vector<string> LC0784::letterCasePermutation(string s) {
    /*字母大小寫排列組合*/
    // Input: s = "a1b2"
    // Output: ["a1b2","a1B2","A1b2","A1B2"]
    // 给了我们一个只包含字母和数字的字符串，让我们将字母以大小写进行全排列
    vector<string> ans;
    function<void(int)> dfs = [&](int d) {
        if(d==s.size()) { ans.push_back(s); return; }
//        dfs(d+1);

        if(!isalpha(s[d])) { return; }
        s[d]^=32;
        dfs(d+1);
        s[d]^=32;
    };
    dfs(0);
    return ans;
}

vector<vector<int>> LC0733::floodFill(vector<vector<int>>& image, int sr, int sc, int color) {
    /*找矩陣中相同區間問題，給一起使座標將相鄰相同的值做修改*/
    // sr = 1, sc = 1, color = 2
    // [[1,1,1],   [[2,2,2],
    //  [1,1,0], -> [2,2,0],
    //  [1,0,1]]    [2,0,1]]
    // Explanation: From the center of the image with position (sr, sc) = (1, 1) (i.e., the red pixel), all pixels
    // connected by a path of the same color as the starting pixel (i.e., the blue pixels) are colored with the new color.
    // Note the bottom corner is not colored 2, because it is not 4-directionally connected to the starting pixel.
    // 这道题给了一个用二维数组表示的图像，不同的数字代表不同的颜色，给了一个起始点坐标，还有一个新的颜色，让我们把起始点的颜色以及其相邻的
    // 同样的颜色都换成新的颜色。实际上就是一个找相同区间的题，可以用 BFS 或者 DFS 来做。先来看 BFS 的解法，使用一个队列 queue 来辅助，
    // 首先将给定点放入队列中，然后进行 while 循环，条件是 queue 不为空，然后进行类似层序遍历的方法，取出队首元素，将其赋值为新的颜色，
    // 然后遍历周围四个点，如果不越界，且周围的颜色跟起始颜色相同的话，将位置加入队列中
//    int color_ori = image[sr][sc];
//    if(color_ori == color) return image;
//    int m = image.size(), n = image[0].size();
//    queue<pair<int,int>> q{{{sr,sc}}};
//    while(q.size()) {
//        pair<int,int> p = q.front(); q.pop();
//        int r = p.first, c = p.second;
//        image[r][c] = color;
//        if(r-1>=0 && image[r-1][c]==color_ori) q.push({r-1,c});
//        if(r+1<m && image[r+1][c]==color_ori) q.push({r+1,c});
//        if(c-1>=0 && image[r][c-1]==color_ori) q.push({r,c-1});
//        if(c+1<n && image[r][c+1]==color_ori) q.push({r,c+1});
//    };
//    return image;

    // DFS 的写法相对简洁一些，首先判断如果给定位置的颜色跟新的颜色相同的话，直接返回，否则就对给定位置调用递归函数。在递归函数中，如果越界
    // 或者当前颜色跟起始颜色不同，直接返回。否则就给当前位置赋上新的颜色，然后对周围四个点继续调用递归函数
    int color_ori = image[sr][sc];
    if(color_ori == color) return image;
    int m = image.size(), n = image[0].size();
    function<void(int, int)> dfs = [&](int r, int c) -> void {
        image[r][c] = color;
        if(r-1>=0 && image[r-1][c]==color_ori) dfs(r-1,c);
        if(r+1<m  && image[r+1][c]==color_ori) dfs(r+1,c);
        if(c-1>=0 && image[r][c-1]==color_ori) dfs(r,c-1);
        if(c+1<n  && image[r][c+1]==color_ori) dfs(r,c+1);
    };
    dfs(sr,sc);
    return image;
}

vector<vector<int>> LC0077::combine(int n, int k) {
    /*n取k做組合*/
    // Input: n = 4, k = 2
    // Output: [[1, 2], [1, 3], [1, 4], [2, 3], [2, 4], [3, 4]]
    // Explanation : There are 4 choose 2 = 6 total combinations.
    // Note that combinations are unordered, i.e., [1, 2] and [2, 1] are considered to be the same combination.
    vector<int> cur;
    vector<vector<int>> res;

    function<void(int, int)> dfs = [&](int depth, int start) {
        if(depth == k)
            { res.push_back(cur); return; }
        for(int i=start; i<=n; i++) {
            cur.push_back(i);
            dfs(depth+1, i+1);
            cur.pop_back();
        }
    };
    dfs(0, 1); // 因為是1~n，所以start是從1開始。
    return res;
}

vector<vector<int>> LC0047::permuteUnique(vector<int>& nums) {
    /*給一陣列裡元素所有的排列*/
    // Input: nums = [1,1,2]
    // Output: [[1,1,2], [1,2,1], [2,1,1]]
    int n = nums.size();
    vector<vector<int>> res;
    vector<int> cur;
    vector<bool> used(n, false);
    std::sort(nums.begin(), nums.end());

    function<void(int)> dfs = [&](int pos) {
        if(pos==n)
            { res.push_back(cur); return; }
        for(int i=0; i<n; i++) {
            // 第一個，已經有放進curr裡了
            if(used[i]) continue;
            // 第二個，排序後前面一個同樣的值一定會被先用到，當會出現跟前面一樣，前面卻是沒有used時就表示這一組已經放進res過了
            if(i>0 && nums[i]==nums[i-1] && !used[i-1])continue;
            used[i] = true;
            cur.push_back(nums[i]);
            dfs(pos+1);
            cur.pop_back();
            used[i] = false;
        }
    };

    dfs(0);
    return res;
}

vector<vector<int>> LC0046::permute(vector<int>& nums) {
    /*n取n做排列*/
    // N個裡面取M個，這裡N等於M，可以利用原本的nums當作cur
    // 每兩兩swap就是一種可能的組合。
    // 可以每兩兩swap是因為N等於M
    int n = nums.size();
    vector<vector<int>> res;

    function<void(int)> dfs = [&](int depth) {
        if(depth == n)
            { res.push_back(nums); return; }
        for(int i=depth; i<n; i++) {
            std::swap(nums[depth], nums[i]);
            dfs(depth+1);
            std::swap(nums[depth], nums[i]);
        }
    };
    dfs(0);
    return res;

//    int n = nums.size();
//    vector<bool> used(n, false);
//    vector<int> cur;
//    vector<vector<int>> res;
//
//    function<void(int)> dfs = [&](int depth) {
//        if(depth == n)
//            {res.push_back(cur); return;}
//        for(int i=0; i<n; i++) {
//            if(used[i]) continue;
//            cur.push_back(nums[i]); used[i] = true;
//            dfs(depth+1);
//            cur.pop_back(); used[i] = false;
//        }
//    };
//
//    dfs(0);
//    return res;
}

vector<string> LC0017::letterCombinations(string digits) {
    /*求電話按鍵上的字母組合*/
    // 求电话号码的字母组合，即数字2到9中每个数字可以代表若干个字母，然后给一串数字，求出所有可能的组合
    // Given a string containing digits from 2-9 inclusive, return all possible letter combinations that the number
    // could represent. Return the answer in any order.
    // Input: digits = "23"
    // Output: ["ad","ae","af","bd","be","bf","cd","ce","cf"]
    if(digits.empty()) return {};
    vector<string> map{"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
    vector<string> res;
    // vector<bool> used(nums.size(), false); 不需要used是因為for裡面每個位置要挑出來的字母來自不同的集合，不需要記是否用過
    // vector<int> cur; 把cur當作參數傳

    function<void(int,string)> dfs = [&](int pos, string cur) {
        if(pos == digits.size()) { res.push_back(cur); return; }
        string str = map[digits[pos]-'0'];
        for(int i=0; i<str.size(); i++)
            dfs(pos+1, cur+str[i]);
    };

    dfs(0, ""); // 字串可以直接用""來表示初始化一個空字串，vector無法如此，因此當要傳的是vector時需先宣告
    return res;

    // iterative way
    // 用迭代 Iterative 来解，在遍历 digits 中所有的数字时，先建立一个临时的字符串数组cur，然后跟上面解法的操作一样，通过数字到 dict
    // 中取出字符串 str，然后遍历取出字符串中的所有字符，再遍历当前结果 res 中的每一个字符串，将字符加到后面，并加入到临时字符串数组cur中。
    // 取出的字符串 str 遍历完成后，将临时字符串数组赋值给结果 res
//    if(digits.empty()) return {};
//    vector<string> map{"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
//    vector<string> res{""}; // res後續不是藉由push_back放入，需先初始化
//    for(int i=0; i<digits.size(); i++) {
//        vector<string> cur;
//        string str = map[digits[i]-'0'];
//        for(int j=0; j<str.size(); j++)
//            for(string s:res) cur.push_back(s+str[j]);
//        res = cur;
//    }
//    return res;
}

bool LC0872::leafSimilar(TreeNode* root1, TreeNode* root2) {
    /*判斷兩顆樹是否相似*/
    // 定义了一种叶相似树，就是说若两棵树的叶结点按照从左向右的顺序取出来排成序列，若两个序列相同，则说明二者是叶结点相似树。其实本质就是按从
    // 左到右的顺序打印二叉树的叶结点呗，那么根据这种顺序，我们采用先序遍历遍历比较好，遇到叶结点后直接将叶结点存入数组中，那么对于两个树遍历
    // 后就分别得到两个包含叶结点的数组，最后再比较一下这两个数组是否相同即可
    vector<int> leaf1, leaf2;
    function<void(TreeNode*, vector<int>&)> dfs = [&](TreeNode* node, vector<int> &leaf) {
        if(!node->left && !node->right) {
            leaf.push_back(node->val);
            return;
        }
        if(node->left) dfs(node->left, leaf);
        if(node->right) dfs(node->right, leaf);
    };

    dfs(root1, leaf1);
    dfs(root2, leaf2);
    return leaf1 == leaf2;
}

vector<int> LC0590::postorder(Node* root) {
    /*求樹的後序遍歷結果*/
    // 求N叉树的后序遍历，由于有了之前那道 Binary Tree Postorder Traversal 的基础，了解了二叉树的后序遍历，则N叉树的后序遍历也就没有
    // 那么难了。首先还是用递归来做，在递归函数中，判空后，遍历子结点数组，对所有的子结点调用递归函数，然后在 for 循环之外在将当前结点值加入
    // 结果 res 数组，这样才能保证是后序遍历的顺序
    // recursive way
//    vector<int> res;
//    function<void(Node*)> dfs = [&](Node* node) {
//        if(!node) return;
//        for(auto &child:node->children)
//            dfs(child);
//        res.push_back(node->val);
//    };
//    dfs(root);
//    return res;

    // 使用迭代的方法来做，这里有个小 trick，写法跟先序遍历十分的像，不同的就是每次把从 stack 中取的结点的值都加到结果 res 的最前面，
    // 还有就是遍历子结点数组的顺序是正常的顺序，而前序遍历是从子结点数组的后面往前面遍历，这点区别一定要注意
    // iterative way
    if(!root) return {};
    vector<int> res;
    stack<Node*> s{{root}};
    while(s.size()) {
        Node *node = s.top(); s.pop();
        res.insert(res.begin(), node->val);
        for(auto &child:node->children)
            s.push(child);
    }
    return res;
}

vector<int> LC0589::preorder(Node* root) {
    /*求樹的前序遍歷結果*/
    // 求N叉树的前序遍历，有之前那道Binary Tree Preorder Traversal的基础，知道了二叉树的前序遍历的方法，很容易就可以写出N叉树的前序遍
    // 历。先来看递归的解法，主要实现一个递归函数即可，判空之后，将当前结点值加入结果res中，然后遍历子结点数组中所有的结点，对每个结点都调
    // 用递归函数即可
    // recursive way
//    vector<int> res;
//    function<void(Node*)> dfs = [&](Node* node) {
//        if(!node) return;
//        res.push_back(node->val);
//        for(auto &child:node->children)
//            dfs(child);
//    };
//    dfs(root);
//    return res;

    // 使用迭代的解法来做，使用栈stack来辅助，需要注意的是，如果使用栈的话，我们遍历子结点数组的顺序应该是从后往前的，因为栈是后进先出的顺序，
    // 所以需要最先遍历的子结点应该最后进栈
    // iterative way
    if(!root) return {};
    vector<int> res;
    stack<Node*> s{{root}};
    while(s.size()) {
        Node* node = s.top(); s.pop();
        res.push_back(node->val);
        for(int i=node->children.size()-1; i>=0; i--)
            s.push(node->children[i]);
    }
    return res;
}

bool LC0572::isSubtree(TreeNode* root, TreeNode* subRoot) {
    /*判斷一樹是否為另一樹的子樹*/
    // 这道题让我们求一个数是否是另一个树的子树，从题目中的第二个例子中可以看出，子树必须是从叶结点开始的，中间某个部分的不能算是子树，
    // 那么我们转换一下思路，是不是从s的某个结点开始，跟t的所有结构都一样，那么问题就转换成了判断两棵树是否相同，也就是Same Tree的问题了，
    // 这点想通了其实代码就很好写了，用递归来写十分的简洁，我们先从s的根结点开始，跟t比较，如果两棵树完全相同，那么返回true，否则就分别对s的
    // 左子结点和右子结点调用递归再次来判断是否相同，只要有一个返回true了，就表示可以找得到
//    function<bool(TreeNode*, TreeNode*)> isSameTree = [&](TreeNode* p, TreeNode* q) -> bool {
//        if(!p && !q) return true;
//        if(!p || !q || p->val != q->val) return false;
//        return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
//    };
//
//    if(!root) return false;
//    if(isSameTree(root, subRoot)) return true;
//    return isSubtree(root->left, subRoot) || isSubtree(root->right, subRoot);

    // 用到了之前那道Serialize and Deserialize Binary Tree的解法，思路是对s和t两棵树分别进行序列化，各生成一个字符串，如果t的字符串
    // 是s的子串的话，就说明t是s的子树，但是需要注意的是，为了避免出现[12], [2], 这种情况，虽然2也是12的子串，但是[2]却不是[12]的子树，
    // 所以我们再序列化的时候要特殊处理一下，就是在每个结点值前面都加上一个字符，比如','，来分隔开，那么[12]序列化后就是",12,#"，而[2]序
    // 列化之后就是",2,#"，这样就可以完美的解决之前的问题了
    function<void(TreeNode*, ostringstream&)> serialize = [&](TreeNode* node, ostringstream &os) {
        if(!node) os << ",#";
        else {
            os << "," << node->val;
            serialize(node->left, os);
            serialize(node->right, os);
        }
    };
    ostringstream os1, os2;
    serialize(root, os1);
    serialize(subRoot, os2);
    return os1.str().find(os2.str()) != std::string::npos;

}

int LC0563::findTilt(TreeNode* root) {
    /*求樹的坡度*/
    // 求二叉树的坡度，某个结点的坡度的定义为该结点的左子树之和与右子树之和的差的绝对值，这道题让我们求所有结点的坡度之和。我开始的想法就是
    // 老老实实的按定义去做，用先序遍历，对于每个遍历到的结点，先计算坡度，根据定义就是左子树之和与右子树之和的差的绝对值，然后返回的是当前结
    // 点的tilt加上对其左右子结点调用求坡度的递归函数即可。其中求子树之和用另外一个函数来求，也是用先序遍历来求结点之和，为了避免重复运算，
    // 这里用哈希表来保存已经算过的结点
//    unordered_map<TreeNode*, int> map;
//    function<int(TreeNode*)> subNodeSum = [&](TreeNode* node) -> int {
//        if(node == nullptr) return 0;
//        if(map.count(node)) return map[node];
//        return map[node] = node->val + subNodeSum(node->left) + subNodeSum(node->right);
//    };
//
//    if(root == nullptr) return 0;
//    int tilt = std::abs(subNodeSum(root->left) - subNodeSum(root->right));
//    return tilt + findTilt(root->left) + findTilt(root->right);

    // 用后序遍历来做，因为后序遍历的顺序是左-右-根，那么就会从叶结点开始处理，这样我们就能很方便的计算结点的累加和，同时也可以很容易的根据子树和来计算tilt
    int sum=0;
    function<int(TreeNode*)> fun = [&](TreeNode* node) ->int {
        if(node == nullptr) return 0;
        int left = fun(node->left);
        int right = fun(node->right);
        sum += std::abs(left-right);
        return node->val + left + right;
    };
    fun(root);
    return sum;
}

int LC0559::maxDepth(Node* root) {
    /*求n叉樹的最大深度*/
    // 求一个N叉树的最大深度
    // recursive way
//    int mx=1;
//    if(root == nullptr) return 0;
//    for(auto child:root->children)
//        mx = std::max(mx, maxDepth(child)+1);
//    return mx;

    // iterative way, 用queue, BFS來計算有多少level來得到最大深度
    if(root == nullptr) return 0;
    int level=0;
    queue<Node*> q{{root}};
    while(q.size()) {
        for(int i=q.size(); i>0; --i) {
            Node* node = q.front(); q.pop();
            for(auto child:node->children)
                if(child) q.push(child);
        }
        ++level;
    }
    return level;
}

/*********** Breadth First Search ***********/
int LC0671::findSecondMinimumValue(TreeNode* root) {
    /*找二叉樹裡第二小的結點*/
    // 找二叉树中的第二小的结点值，并且给该二叉树做了一些限制，比如对于任意一个结点，要么其没有子结点，要么就同时有两个子结点，而且父结点值是
    // 子结点值中较小的那个，当然两个子结点值可以相等。那么直接上暴力搜索呗，根据该树的附加条件可知，根结点一定是最小的结点值first，那么我们
    // 只要找出第二小的值second即可，初始化为整型的最大值。然后对根结点调用递归函数，将first和second当作参数传进去即可。在递归函数中，如果
    // 当前结点为空，直接返回，若当前结点孩值不等于first，说明其肯定比first要大，然后我们看其是否比second小，小的话就更新second，然后对当
    // 前结点的左右子结点分别调用递归函数即可
    // 32 bits INT範圍為-2147483648 ~ 2147483647
    // recursive way
//    int first=root->val, second=INT_MAX;
//    bool found=false;
//
//    function<void(TreeNode*)> fun = [&](TreeNode* node) {
//        if(!node) return;
//        if(node->val != first) {
//            second = std::min(second, node->val);
//            found = true;
//        }
//        fun(node->left);
//        fun(node->right);
//    };
//    fun(root);
//    return found ? second : -1;

    // iterative way
    int first=root->val, second=INT_MAX;
    bool found=false;
    queue<TreeNode*> q{{root}};

    while(q.size()) {
        TreeNode* node = q.front(); q.pop();
        if(node->val != first) {
            second = std::min(second, node->val);
            found = true;
        }
        if(node->left) q.push(node->left);
        if(node->right) q.push(node->right);
    }

    return found ? second : -1;
}

/*********** Search ***********/
// N個裡面取M個，N是nums的大小，所以不需要另外當參數傳，緊需要傳M即可
void Search::Permutation(vector<int> nums, int m) {
    vector<vector<int>> res;
    vector<int> cur;
    vector<bool> used(nums.size(), false);

    function<void(int)> dfs = [&](int depth) {
        if(depth == m)
            {res.push_back(cur); return;}
        for(int i=0; i<nums.size(); i++) {
            if(used[i]) continue;
            cur.push_back(nums[i]); used[i] = true;
            dfs(depth+1);
            cur.pop_back(); used[i] = false;
        }
    };

    dfs(0);

    for(auto &v:res) {
        for(auto &e:v) cout << e << ' ';
        cout << endl;
    }
    cout<<"P("<<nums.size()<<","<<m<<")="<<res.size()<<endl;
}

// N個裡面取M個，N是nums的大小，所以不需要另外當參數傳，緊需要傳M即可
void Search::Combination(vector<int> nums, int m) {
    vector<vector<int>> res;
    vector<int> cur;

    function<void(int, int)> dfs = [&](int depth, int start) {
        if(depth == m)
            {res.push_back(cur); return;}
        for(int i=start; i<nums.size(); i++) {
            cur.push_back(nums[i]);
            dfs(depth+1, i+1);
            cur.pop_back();
        }
    };

    dfs(0, 0);

    for(auto &v:res) {
        for(auto &e:v) cout << e << ' ';
        cout << endl;
    }
    cout<<"C("<<nums.size()<<","<<m<<")="<<res.size()<<endl;
}

/***********  Breadth First Search  **********/