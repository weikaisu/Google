
#include "bit.h"

/***********  Easy  **********/
int LC0136::singleNumber(vector<int>& nums) {
    // 用位操作 Bit Operation 逻辑异或来解此题
    int res = 0;
    for(auto &num:nums)
        res ^= num;
    return res;

    // 这道题给了我们一个非空的整数数组，说是除了一个数字之外所有的数字都正好出现了两次，让我们找出这个只出现一次的数字。题目中让我们在线性的
    // 时间复杂度内求解，那么一个非常直接的思路就是使用 HashSet，利用其常数级的查找速度。遍历数组中的每个数字，若当前数字已经在 HashSet 中
    // 了，则将 HashSet 中的该数字移除，否则就加入 HashSet。这相当于两两抵消了，最终凡事出现两次的数字都被移除了 HashSet，唯一剩下的那个
    // 就是单独数字了
//    unordered_set<int> s;
//    for(auto &num:nums) {
//        if(s.count(num)) s.erase(num);
//        else s.insert(num);
//    }
//    return *s.begin();
}