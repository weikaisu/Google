//
// Created by steve on 2021-08-25.
//

#include "dp.h"

//LC0053 run;
//vector<int> nums{-2,1,-3,4,-1,2,1,-5,4};
//int target=5;
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
