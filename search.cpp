
#include "search.h"

/***********  Binary Search  **********/
char LC0744::nextGreatestLetter(vector<char>& letters, char target) {
    // 了我们一堆有序的字母，然后又给了我们一个target字母，让我们求字母数组中第一个大于target的字母，数组是循环的，如果没有，那就返回第一
    // 个字母。像这种在有序数组中找数字，二分法简直不要太适合啊。题目中说了数组至少有两个元素，那么我们首先用数组的尾元素来跟target比较，
    // 如果target大于等于尾元素的话，直接返回数组的首元素即可。否则就利用二分法来做，这里是查找第一个大于目标值的数组，博主之前做过二分法的
    // 总结，参见这个帖子LeetCode Binary Search Summary 二分搜索法小结
    if(target >= letters.back()) return letters[0];
    int n=letters.size(), l=0, r=n;
    while(l<r) {
        int m=l+(r-l)/2;
        if(target >= letters[m]) l=m+1;
        else r=m;
    }
    return letters[r]; //回傳的是r

    // 用STL自带的upper_bound函数来做，这个就是找第一个大于目标值的数字，如果返回end()，说明没找到，返回首元素即可
//    auto it = std::upper_bound(letters.begin(), letters.end(), target);
//    return it==letters.end() ? *letters.begin() : *it;
}

int LC0704::search(vector<int>& nums, int target) {
    // Given a sorted (in ascending order) integer array nums of n elements and a target value, write a function to
    // search target in nums. If target exists, then return its index, otherwise return -1.
    int l=0, r=nums.size();
    while(l<r) {
        int m=l+(r-l)/2;
        if(target == nums[m]) return m;
        else if(target > nums[m]) l=m+1;
        else r=m;
    }
    return -1;
}

int LC0441::arrangeCoins(int n) {
    // 给了我们n个硬币，让我们按一定规律排列，第一行放1个，第二行放2个，以此类推，问我们有多少行能放满。通过分析题目中的例子可以得知最后一
    // 行只有两种情况，放满和没放满。由于是按等差数列排放的，我们可以快速计算出前i行的硬币总数。我们先来看一种O(n)的方法，非常简单粗暴，
    // 就是从第一行开始，一行一行的从n中减去，如果此时剩余的硬币没法满足下一行需要的硬币数了，我们之间返回当前行数即可
//    int cur=1, rem=n-1;
//    while(rem>=cur+1) {
//        cur++;
//        rem-=cur;
//    }
//    return (n==0) ? 0 : cur;

    // 用到了二分搜索法，我们搜索前i行之和刚好大于n的临界点，这样我们减一个就是能排满的行数，注意我们计算前i行之和有可能会整型溢出，所以我
    // 们需要将变量都定义成长整型
    if(n<=1) return n;
    long l=0, r=n;
    while(l<r) {
        long m=l+(r-l)/2;
        if(n >= m*(m+1)/2) l=m+1;
        else r=m;
    }
    return l-1;

    // 一种数学解法O(1)，充分利用了等差数列的性质，我们建立等式, n = (1 + x) * x / 2, 我们用一元二次方程的求根公式可以得到
    // x = (-1 + sqrt(8 * n + 1)) / 2, 然后取整后就是能填满的行数，一行搞定
    // return (int)((-1 + sqrt(1 + 8 * (long)n)) / 2);
}

int guess(int num) {
    /* -1 : My number is lower
        1 : My number is higher
        0 : Congrats! You got it! */
    return 0;
};
int LC0374::guessNumber(int n) {
    // 猜价格的问题，根据对方说高了还是低了来缩小范围，虽然是道 Easy 题，无脑线性遍历还是会超时 Time Limit Exceeded，所以更快速的方法
    // 就是折半搜索法，原理很简单，属于博主之前的总结帖 LeetCode Binary Search Summary 二分搜索法小结 中的第四类-用子函数当作判断关系
    if (!guess(n)) return n;
    int l=1, r=n;
    while (l<n) {
        int m=l+(r-l)/2, t=guess(m);
        if (t==1) l=m+1;
        else if (t==-1) r=m;
        else return m;
    }
    return l;
}

bool LC0367::isPerfectSquare(int num) {
    // 给了我们一个数，让我们判断其是否为完全平方数，使用二分查找法来做，要查找的数为 mid*mid
    int l=0, r=num;
    while (l<=r) {
        long m=l+(r-l)/2, mm=m*m; // 處理平方，用long避免overflow
        if (num > mm) l=m+1;
        else if (num < mm) r=m-1;
        else return true;
    }
    return false;

    // 从1搜索到 sqrt(num)，看有没有平方正好等于 num 的数
//    for (int i=1; i<=num/i; i++)
//        if (i*i==num) return true;
//    return false;
}
bool isBadVersion(int version) {return true;};
int LC0278::firstBadVersion(int n) {
    // 有一系列版本，其中有一个版本是坏的，而且后面跟着的全是坏的，给了一个 API 函数可以用来判定当前版本是否是坏的，让我们尽可能少的调用这个
    // API，找出第一个坏版本。那么这种搜索题最先开始考虑用二分查找法把，效率高嘛。由于这题很有规律，好版本和坏版本一定有个边界，那么用二分法
    // 来找这个边界，对 mid 值调用API函数，如果是坏版本，说明边界在左边，则把 mid 赋值给 right，如果是好版本，则说明边界在右边，则把
    // mid+1 赋给 left，最后返回 left 即可。需要注意的是，OJ 里有个坑，那就是如果 left 和 right 都特别大的话，那么 left+right 可能
    // 会溢出，这里处理方法就是变成 left + (right - left) / 2，很好的避免的溢出问题
    int l=1, r=n;
    while(l<r) {
        int m = l+(r-l)/2;
        if(isBadVersion(m)) r=m;
        else l=m+1;
    }
    return l;

    // 如果习惯了二分搜索法从0开始找，可以用下面的方法
//    int l=0, r=n-1;
//    while(l<r) {
//        int m=l+(r-l)/2;
//        if(isBadVersion(m+1)) r=m;
//        else l=m+1;
//    }
//    return l+1;
}

//LC0035 run;
//vector<int> nums{1,3,5,6};
//int target=5;
//cout << run.searchInsert(nums, target) << endl;
int LC0035::searchInsert(vector<int>& nums, int target) {
    int l=0, r=nums.size();

    while(l<r) {
        int m=l+(r-l)/2;
        if(target>nums[m]) l=m+1;
        else if(target<nums[m]) r=m;
        else return m;
    }
    return l;
}

/***********  Depth First Search  **********/
int LC0999::numRookCaptures(vector<vector<char>>& board) {
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

// LC0784 run;
// vector<string> ans=run.letterCasePermutation("a1b2");
// for(auto a:ans) cout << a << endl;
// Input: s = "a1b2"
// Output: ["a1b2","a1B2","A1b2","A1B2"]
vector<string> LC0784::letterCasePermutation(string s) {
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

vector<vector<int>> LC0046::permute(vector<int>& nums) {
    // N個裡面取M個，這裡N等於M，可以利用原本的nums當作cur
    // 每兩兩swap就是一種可能的組合。
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

vector<int> LC0590::postorder(Node* root) {
    vector<int> res;
    return res;
}

vector<int> LC0589::preorder(Node* root) {
    vector<int> res;
    return res;
}

bool LC0572::isSubtree(TreeNode* root, TreeNode* subRoot) {
    bool res;
    return res;
}

int LC0563::findTilt(TreeNode* root) {
    int res;
    return res;
}

int LC0559::maxDepth(Node* root) {
    int res;
    return res;
}

int LC0530::getMinimumDifference(TreeNode* root) {
    int res;
    return res;
}

vector<int> LC0501::findMode(TreeNode* root) {
    vector<int> res;
    return res;
}

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