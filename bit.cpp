
#include "bit.h"

/***********  Easy  **********/
uint32_t LC0190::reverseBits(uint32_t n) {
    // 把要翻转的数从右向左一位位的取出来，如果取出来的是1，将结果 res 左移一位并且加上1；如果取出来的是0，将结果 res 左移一位，
    // 然后将n右移一位即可
//    uint32_t res = 0;
//    for(int i=0; i<32; i++) {
//        res <<= 1;
//        if(n & 1) res++;
//        n>>=1;
//    }
//    return res;

    // 不更新n的值，而是直接将n右移i位，然后通过 ‘与’ 1来提取出该位，加到左移一位后的结果 res 中即可
    uint32_t res=0;
    for(int i=0; i<32; i++)
        res = (res<<1) | (n>>i & 1);
    return res;
}

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