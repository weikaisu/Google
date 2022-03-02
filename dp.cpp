
#include "dp.h"

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
