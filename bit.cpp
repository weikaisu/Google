
#include "bit.h"

/***********  Easy  **********/
vector<string> LC0401::readBinaryWatch(int turnedOn) {
    // 利用到了bitset这个类，可以将任意进制数转为二进制，而且又用到了count函数，用来统计1的个数。那么时针从0遍历到11，分针从0遍历到59，
    // 然后我们把时针的数组左移6位加上分针的数值，然后统计1的个数，即为亮灯的个数，我们遍历所有的情况，当其等于num的时候，存入结果res中
    // 寫法漂亮但執行速度會慢些
    vector<string> res;
    for(int h=0; h<12; h++)
        for(int m=0; m<60; m++) {
            if(bitset<10>((h<<6)+m).count() == turnedOn)
                res.push_back(std::to_string(h) + ((m<10) ? ":0" : ":") + std::to_string(m));
        }
    return res;

    // 如果总共要取num个，我们在小时集合里取i个，算出和，然后在分钟集合里去num-i个求和，如果两个都符合题意，那么加入结果中即可
//    vector<string> res;
//    vector<int> hour{8, 4, 2, 1}, minute{32, 16, 8, 4, 2, 1};
//
//    function<vector<int>(vector<int>, int)> com = [&](vector<int> nums, int m) -> vector<int> {
//        int cur = 0;
//        vector<int> sel;
//        function<void(int, int)> dfs = [&](int depth, int start) {
//            if(depth == m)
//                {sel.push_back(cur); return;}
//            for(int i=start; i<nums.size(); i++) {
//                cur += nums[i];
//                dfs(depth+1, i+1);
//                cur -= nums[i];
//            }
//        };
//        dfs(0,0);
//        return sel;
//    };
//
//    for(int i=0; i<=turnedOn; i++) {
//        vector<int> hours = com(hour, i);
//        vector<int> minutes = com(minute, turnedOn-i);
//        for(auto &h:hours) {
//            if(h>11) continue;
//            for(auto &m:minutes) {
//                if(m>59) continue;
//                res.push_back(std::to_string(h) + ((m<10) ? ":0" : ":") + std::to_string(m));
//            }
//        }
//    }
//    return res;


}

bool LC0342::isPowerOfFour(int n) {
    // 这道题让我们判断一个数是否为4的次方数，那么最直接的方法就是不停的除以4，看最终结果是否为1
//    while(n && !(n%4))
//        n /= 4;
//    return n==1;

    // 在确定其是2的次方数了之后，发现只要是4的次方数，减1之后可以被3整除
    return n>0 && !(n&(n-1)) && !((n-1)%3);
}

vector<int> LC0338::countBits(int n) {
    // 利用了 built-in 的函数 bitset 的 count 函数可以直接返回1的个数
//    vector<int> res;
//    for(int i=0; i<=n; i++)
//        res.push_back(bitset<32>(i).count());
//    return res;

    // 规律是，从1开始，遇到偶数时，其1的个数和该偶数除以2得到的数字的1的个数相同，遇到奇数时，其1的个数等于该奇数除以2得到的数字的1的个数再加1
//    vector<int> res{0};
//    for(int i=1; i<=n; i++) {
//        if(!(i%2)) res.push_back(res[i/2]);
//        else res.push_back(res[i/2]+1);
//    }
//    return res;

    // 利用了 i&(i - 1)， 这个本来是用来判断一个数是否是2的次方数的快捷方法，比如8，二进制位 1000, 那么 8&(8-1) 为0，只要为0就是2的次方
    // 数, 那么我们现在来看一下0到 15 的数字和其对应的 i&(i - 1) 值, 可以发现每个第i值都是 i&(i-1) 对应的值加1
    vector<int> res(n+1,0);
    for(int i=1; i<=n; i++)
        res[i] = res[i&(i-1)]+1;
    return res;
}

bool LC0266::canPermutePalindrome(string s) {
    // Given a string, determine if a permutation of the string could form a palindrome.
    // 判断一个字符串的全排列有没有是回文字符串的
    // 建立一个 256 大小的 bitset，每个字母根据其 ASCII 码值的不同都有其对应的位置，然后我们遍历整个字符串，遇到一个字符，就将其对应的位
    // 置的二进制数 flip 一下，就是0变1，1变0，那么遍历完成后，所有出现次数为偶数的对应位置还应该为0，而出现次数为奇数的时候，对应位置就
    // 为1了，那么我们最后只要统计1的个数，就知道出现次数为奇数的字母的个数了，只要个数小于2就是回文数
    bitset<256> set;
    for(auto &c:s)
        set.flip(c);
    return set.count()<2;
}

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