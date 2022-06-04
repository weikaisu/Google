
#include "dp.h"

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
