
#include "search.h"

/***********  Binary Search  **********/
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

int LC0476::findComplement(int num) {
    // 由于位操作里面的取反符号～本身就可以翻转位，但是如果直接对num取反的话就是每一位都翻转了，
    // 而最高位1之前的0是不能翻转的，所以我们只要用一个mask来标记最高位1前面的所有0的位置，
    // 然后对mask取反后，与上对num取反的结果即可
    // mask需一開始所有bit都為1，得用unsigned的，否則complement operator會把sign bit翻轉
    unsigned int mask = UINT_MAX;
    while(mask & num) mask<<=1;
    return ~mask & ~num;

    // 这道题给了我们一个数，让我们求补数。通过分析题目汇总的例子，我们知道需要做的就是每个位翻转一下就行了，
    // 但是翻转的起始位置上从最高位的1开始的，前面的0是不能被翻转的，所以我们从高往低遍历，如果遇到第一个1了后，
    // 我们的flag就赋值为true，然后就可以进行翻转了，翻转的方法就是对应位异或一个1即可
//    bool flip = false;
//    for(int i=31; i>=0; i--) {
//        if(num & (1<<i)) flip = true;
//        if(flip) num ^= (1<<i);
//    }
//    return num;
}

int LC0461::hammingDistance(int x, int y) {
    // 遍历每一位的方法并不高效，还可以进一步优化，假如数为num, num & (num - 1)可以快速地移除最右边的bit 1，
    // 一直循环到num为0, 总的循环数就是num中bit 1的个数
    int z = x^y, res = 0;
    while(z) {
        res++;
        z &= (z-1);
    }
    return res;

    // 这道题让我求两个数字之间的汉明距离，题目中解释的很清楚了，两个数字之间的汉明距离就是其二进制数对应位不同的个数，
    // 那么最直接了当的做法就是按位分别取出两个数对应位上的数并异或，我们知道异或的性质上相同的为0，不同的为1，
    // 我们只要把为1的情况累加起来就是汉明距离了
//    int z = x^y, res = 0;
//    while(z) {
//        res += z&1;
//        z>>=1;
//    }
//    return res;
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