
#include "bit.h"

/***********  Easy  **********/
bool LC0231::isPowerOfTwo(int n) {
    // 2的次方数都只有一个1，剩下的都是0，所以我们的解题思路就有了，我们只要每次判断最低位是否为1，然后向右移位，最后统计1的个数即可判断是否
    // 是2的次方数
//    int cnt=0;
//    while(n>0) {
//        cnt += (n & 1);
//        n>>=1;
//    }
//    return cnt==1;

    // 如果一个数是2的次方数的话，根据上面分析，那么它的二进数必然是最高位为1，其它都为0，那么如果此时我们减1的话，则最高位会降一位，
    // 其余为0的位现在都为变为1，那么我们把两数相与，就会得到0
    return (n>0) && !(n & (n-1));
}

int LC0191::hammingWeight(uint32_t n) {
    // Write a function that takes an unsigned integer and returns the number of ’1' bits it has (also known as
    // cthe Hamming weight).
    int res=0;
    for(int i=0; i<32; i++) {
        res += (n>>i & 1);
    }
    return res;
}

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