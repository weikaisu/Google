#include "search.h"

/***********  Binary Search  **********/
int LC1351::countNegatives(vector<vector<int>>& grid) {
    // 给了一个有序的二维数组，这里的排序方式是每行都是递减的，同时每列也都是递减的，现在让找出数组中负数的个数。当然你可以遍历整个数组，
    // 然后统计出负数个数，那么这样的话数组有序的条件就没有被使用，题目中的 Follow up 让在 O(n + m) 的时间复杂度下完成。既然每行每列都
    // 是递减的，那么数组的左上角就是整个数组最大的数，右下角一定是最小的数，若整个数组有正有负的话，左上角就是正数，右下角就是负数
    // 每一行做一次binary search找出第一個負數的位置，就可以得到那行有多少負數。
    int res=0;
    int m=grid.size(), n=grid[0].size();
    for(int i=0; i<m; ++i) {
        int q=0, p=n-1, idx=-1;
        while(q<=p) {
            int mid = q + (p-q)/2;
            if(grid[i][mid] < 0) {
                idx = mid; // 是負數的話就可以更新idx
                p = mid - 1;
            } else {
                q = mid + 1;
            }
        }
        if(idx != -1) res += (n-idx);
    }
    return res;
}

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
    long l=1, r=num+1l, target=num; // x值可能很大，需用long
    while(l<r) {
        long m = l+(r-l)/2;
        if(m*m > target) r=m;
        else if(m*m < target) l=m+1;
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
    // 第二类
    // 有一系列版本，其中有一个版本是坏的，而且后面跟着的全是坏的，给了一个 API 函数可以用来判定当前版本是否是坏的，让我们尽可能少的调用这个
    // API，找出第一个坏版本。那么这种搜索题最先开始考虑用二分查找法把，效率高嘛。由于这题很有规律，好版本和坏版本一定有个边界，那么用二分法
    // 来找这个边界，对 mid 值调用API函数，如果是坏版本，说明边界在左边，则把 mid 赋值给 right，如果是好版本，则说明边界在右边，则把
    // mid+1 赋给 left，最后返回 left 即可。需要注意的是，OJ 里有个坑，那就是如果 left 和 right 都特别大的话，那么 left+right 可能
    // 会溢出，这里处理方法就是变成 left + (right - left) / 2，很好的避免的溢出问题
    int q=0, p=n;
    while(q<p) {
        int m = q + (p-q)/2;
        if(!isBadVersion(m)) q=m+1;
        else p=m;
    }
    return p;

    // 如果习惯了二分搜索法从0开始找，可以用下面的方法
//    int l=0, r=n-1;
//    while(l<r) {
//        int m=l+(r-l)/2;
//        if(isBadVersion(m+1)) r=m;
//        else l=m+1;
//    }
//    return l+1;
}

int LC0069::mySqrt(int x) {
    // 第三类的变形
    // 找最后一个不大于目标值的数，这里细心的童鞋可能会有疑问，在总结贴中第三类博主的 right 用的是开区间，那么这里为啥 right
    // 初始化为x，而不是 x+1 呢？因为总结帖里的 left 和 right 都是数组下标，这里的 left 和 right 直接就是数字本身了，一个数字的平方根
    // 是不可能比起本身还大的，所以不用加1，还有就是这里若x是整型最大值，再加1就会溢出。最后就是返回值是 right-1，因为题目中说了要把小数部
    // 分减去，只有减1才能得到正确的值
    if(x<=1) return x; // 後面會除m，這邊得把小於1的情況排除，否則會有除0的情況
    int q=1, p=x/2 + 1; // 左閉右開，平方根一定小於等於x/2
    while(q<p) {
        int m = q + (p-q)/2;
        if(m <= x/m) q=m+1;
        else p=m;
    }
    return p-1;
}

//LC0035 run;
//vector<int> nums{1,3,5,6};
//int target=5;
//cout << run.searchInsert(nums, target) << endl;
int LC0035::searchInsert(vector<int>& nums, int target) {
    // 第二类
    // Given a sorted array and a target value, return the index if the target is found. If not, return the index
    // where it would be if it were inserted in order.
    // 遍历一遍原数组，若当前数字大于或等于目标值，则返回当前坐标，如果遍历结束了，说明目标值比数组中任何一个数都要大，则返回数组长度n即可
    // 更好的方式是用binary search

    int q=0, p=nums.size();
    while(q<p) {
        int m = q + (p-q)/2;
        if(nums[m] < target) q=m+1;
        else p=m;
    }
    return p;
}