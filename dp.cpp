
#include "dp.h"

/***********  Dynamic Programming  **********/
LC0303::LC0303(vector<int>& nums) {
    // 这道题让我们检索一个数组的某个区间的所有数字之和，题目中给了两条条件，首先数组内容不会变化，其次有很多的区间和检索。那么我们用传统的遍
    // 历相加来求每次区间和检索，十分的不高效，而且无法通过 OJ。所以这道题的难点就在于是否能想到来用建立累计直方图的思想来建立一个累计和的
    // 数组dp，並通过增加一位 dp 的长度，来避免在 sumRange 中检测i是否为0
    dp.push_back(0);
    for(int i=1; i<=nums.size(); i++)
        dp.push_back(dp[i-1]+nums[i-1]);
}

int LC0303::sumRange(int left, int right) {
    return dp[right+1]-dp[left];
}

//LC0070 run;
//cout << run.climbStairs(45) << endl;
int LC0070::climbStairs(int n) {
    //iterative
    if(!n) return 0;
    if(1==n) return 1;
    if(2==n) return 2;

    int sPr1=2, sPr2=1, sCur=0;
    for(int i=3 ; i<=n ; i++) {
        sCur=sPr1+sPr2;
        sPr2=sPr1; sPr1=sCur;
    }
    return sCur;

    //recursive, time consuming
    if(!n) return 0;
    if(1==n) return 1;
    if(2==n) return 2;
    return climbStairs(n-1) + climbStairs(n-2);
}

//LC0053 run;
//vector<int> nums{-2,1,-3,4,-1,2,1,-5,4};
//cout << run.maxSubArray(nums) << endl;
int LC0053::maxSubArray(vector<int>& nums) {
    if(!nums.size()) return 0;
    if(1==nums.size()) return nums[0];

    int sCur=0, sPre=nums[0], vMax=nums[0];
    for(auto it=next(nums.begin()) ; it!=nums.end() ; it++) {
        sCur = max(sPre+*it, *it);
        vMax = max(vMax, sCur);
        sPre = sCur;
    }
    return vMax;
}

/***********  Greedy  **********/
int LC0455::findContentChildren(vector<int>& g, vector<int>& s) {
    // 这道题给了我们一堆cookie，每个cookie的大小不同，还有一堆小朋友，每个小朋友的胃口也不同的，问我们当前的cookie最多能满足几个小朋友。
    // 这是典型的利用贪婪算法的题目，我们可以首先对两个数组进行排序，让小的在前面。然后我们先拿最小的cookie给胃口最小的小朋友，看能否满足，
    // 能的话，我们结果res自加1，然后再拿下一个cookie去满足下一位小朋友；如果当前cookie不能满足当前小朋友，那么我们就用下一块稍大一点的
    // cookie去尝试满足当前的小朋友。当cookie发完了或者小朋友没有了我们停止遍历。
    //
    // 用变量j既可以表示小朋友数组的坐标，同时又可以表示已满足的小朋友的个数，因为只有满足了当前的小朋友，才会去满足下一个胃口较大的小朋友
    int j=0;
    sort(g.begin(), g.end());
    sort(s.begin(), s.end());
    for(int i=0; i<s.size() && j<g.size(); i++)
        if(s[i]>=g[j]) j++;
    return j;
}