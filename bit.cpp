
#include "bit.h"

/***********  Easy  **********/
int LC1342::numberOfSteps(int num) {
    // 使用遞歸的方式
    if(num==0 || num==1)
        return num;
    return numberOfSteps(num/2) + ((num%2) ? 2 : 1);
    // 按題意操作，每操作一次計數+1
//    int cnt=0;
//    while(num) {
//        if(!(num%2))
//            num>>=1;
//        else
//            num--;
//        cnt++;
//    }
//    return cnt;
}

int LC1009::bitwiseComplement(int n) {
    // 下面的这种解法用到了一些补码的性质，那就是一个二进制数加上其补码，则每个位置上都会变成1，且位数和原数相同。这样的话我们
    // 就可以先求出这个各位上全是1的数，然后再做减法，就可以得到补码了
    int sum=1;
    while(n>sum) sum = (sum<<1) + 1; // 做shift需用括號括起來
    return sum^n; // or sum-n;

    // 这道题让求十进制整数的补码，我们都知道补码是二进制中的一个概念，就是每一位上的数都跟原数是相反的，这里所谓的十进制的补码，
    // 其实就是先转为二进制，再求补码，再转回十进制数。既然是求补码，最直接的方法就是从低到高，一位一位的取出来，然后进行取反。
    // 对于一个十进制数取其二进制数的最低位的方法，就是‘与’上一个1，然后取反，取反就是‘异或’上一个1，接着就是左移对应的位数，
    // 可以用一个变量i来统计当前处理到第几位了，然后直接左移i位就行了。之后N要右移一位，i自增1即可
//    if(!n) return 1;
//    int res=0;
//    for(int i=0; n; i++, n>>=1)
//        res += ((n & 1) ^ 1) << i;
//    return res;
}

int LC0868::binaryGap(int n) {
    // 也可以只用一个循环来完成，而且不用 pos 数组，只用一个变量 last 来记录上一个遍历到的 '1' 的位置，初始化为 -1。那么在遍历的过程中，
    // 若遇到了 '1'，则判断 last 是否大于等于0，是的话则表示之前已经遇到了 '1'，那么当前位置i减去 last，即为两个 '1' 之间的距离，
    // 用来更新结果 res，然后再更新 last 为当前位置i，继续遍历即可
    int res=0, last=-1;
    for(int i=0; i<32; i++) {
        if((n>>i) & 1) {
            if(last != -1)
                res = std::max(res, i-last);
            last = i;
        }
    }
    return res;

    // 这道题给了我们一个正整数，问其二进制表示数中两个 '1' 之间的最大距离是多少。比如整数 22 的二进制为 10110，那么可以看出前两个 '1'
    // 之间的距离最大，所以返回2即可。其实这道题的考察点就是如何按位取数，对一个二进制数直接与 '1'，就可以提取出最低位，然后和0比较大小，
    // 就知道最低位是0还是1了。当然为了每一位的是0还是1，一般有两种处理方法，一种是直接将原数字右移一位，则之前的最低位被移除了，再和 '1'
    // 相与即可，直到原数字变为0停止。另一种方法是直接右移固定的位数再与 '1'，因为整型数只有 32 位，所以可以直接取出任意位上的数字。那
    // 么既然要求两个 '1' 之间的最大距离，那么只要关心 '1' 的位置即可，一种比较直接的思路就是先遍历一遍各位上的数字，将所有 '1' 的坐标
    // 位置都保存到一个数组 pos 之中，然后再遍历这个 pos 数组，计算相邻两个数字的差，即两个 '1' 之间的距离，更新结果 res 即可得到最大距离
//    vector<int> pos;
//    for(int i=0; i<32; i++)
//        if((n>>i) & 1) pos.push_back(i);
//    int res = 0;
//    for(int i=1; i<pos.size(); i++)
//        res = std::max(res, pos[i]-pos[i-1]);
//    return res;
}

int LC0762::countPrimeSetBits(int left, int right) {
    // 由于题目中给了数的大小范围 R <= 10^6 < 2^20，那么我们统计出来的非零位个数cnt只需要检测是否是20以内的质数即可，
    // 所以我们将20以内的质数都放入一个HashSet中，然后统计出来cnt后，直接在HashSet中查找有没有即可
    int res = 0;
    unordered_set<int> primes{2, 3, 5, 7, 11, 13, 17, 19};
    for(int i=left; i<=right; i++) {
        int cnt = 0;
        for(int j=i; j>0; j>>=1)
            cnt += (j&1);
        res += primes.count(cnt);
    }
    return res;

    // 这道题给了我们一个整数范围[L, R]，让我们统计其中有多个整数，其二进制表示中非零位个数为质数。参考题目中的例子不难理解题意，
    // 那么博主最先想到的就是暴力搜索啊，毕竟是到Easy题嘛，可能不需要太多的技巧。我们遍历整数范围[L, R]中的每一个数字，
    // 然后先统计出所有非零位个数cnt，通过和1相与，再右移一位的方式。然后就是来判断这个cnt是否是质数，判断的方法就是就是从其平方开始，
    // 一个一个的除，如果一直到2都没有约数，那么就是质数啦，结果res累加1，
//    int res = 0;
//    for(int i=left; i<=right; i++) {
//        int num = i, cnt = 0;
//        while(num) {
//            if(num & 1) cnt++;
//            num >>= 1;
//        }
//        bool is_prime = true;
//        for(int i=std::sqrt(cnt); i>1; i--){
//            if(!(cnt%i))
//                { is_prime=false; break; } // 即使一行也要用大括號
//        }
//        if(is_prime && cnt!=1) res++;
//    }
//    return res;
}

bool LC0693::hasAlternatingBits(int n) {
    // 先将n右移两位，再和原来的n亦或，得到的新n其实就是除了最高位，其余都是0的数，然后再和自身减1的数相‘与’，如果是0就返回true，
    // 反之false。比如n是10101，那么n/4是101，二者相‘亦或’，得到10000，此时再减1，为1111，二者相‘与’得0，
    return 0 == ((n^=(n>>2)) & (n-1));

    // 利用判斷全1的技巧，及利用了0和1的交替的特性，进行错位相加，从而组成全1的二进制数，然后再用一个检测全1的二进制数的trick，就是‘与’上加1后的数，
    // 因为全1的二进制数加1，就会进一位，并且除了最高位，其余位都是0，跟原数相‘与’就会得0，所以我们可以这样判断。比如n是10101，
    // 那么n>>1就是1010，二者相加就是11111，再加1就是100000，二者相‘与’就是0，
    // 需先cast成long long避免n+(n>>1)時overflow
//    return ( ((long long)n + (n>>1)) & ((long long)n + (n>>1) + 1) ) == 0;

    // 我们不需要用if条件来判断，而是可以通过‘亦或’1的方式来将0和1互换，当然我们也可以通过d = 1 - d 来达到同样的效果，但还是
    // 写成‘亦或’1比较叼，while循环的条件是最低位等于d，而d不停的在0和1之间切换，n每次也向右平移一位，这样能交替检测0和1，
    // 循环退出后，如果n为0，则返回true，反之则返回false
//    int d = n & 1;
//    while(d == (n & 1)) {
//        d ^= 1;
//        n >>= 1;
//    }
//    return n == 0;

    // 这道题让我们判断一个二进制数的1和0是否是交替出现的，博主开始也美想到啥简便方法，就一位一位来检测呗，用个变量bit来记录上一
    // 个位置的值，初始化为-1，然后我们用‘与’1的方法来获取最低位的值，如果是1，那么当此时bit已经是1的话，说明两个1相邻了，返回false，
    // 否则bit赋值为1。同理，如果是0，那么当此时bit已经是0的话，说明两个0相邻了，返回false，否则bit赋值为0。判断完别忘了将n向
    // 右移动一位。如果while循环退出了，返回true
//    int bit = -1;
//    while(n) {
//        if(n & 1) {
//            if(bit == 1) return false;
//            bit = 1;
//        } else {
//            if(bit == 0) return false;
//            bit = 0;
//        }
//        n >>= 1;
//    }
//    return true;
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

string LC0405::toHex(int num) {
    // 0000 1100 ( 12)
    // 1111 0100 (-12)
    // 1111 0011 (1's complement)
    // 1111 0100 (2's complement)

    // https://ithelp.ithome.com.tw/articles/10229609

    // Two's Complement
    // The complement or negation of a two's complement number x is 2^n-x.
    // The unsigned sum of an n-bit number and its negative is 2^n.
    // Two's complement is created to preserve arithmetics in binary, so that you can add positive and
    // negative numbers using the same ALU's
    //
    // One's Complement
    // The complement or negation of a one's complement number x is 2^n-x-1. The negative of a one's complement is found
    // by inverting each bit, from 0 to 1 and from 1 to 0.

    // 從大數開始除起，餘數可以一直往結果的字串後面串接，連續除基數，餘數是需不斷往結果的字串前面插入，以6為例。
    // 6/2 = 3~0
    // 3/2 = 1~1
    // 1/2 = 0~1

    // 采取位操作的思路，每次取出最右边四位，如果其大于等于10，找到对应的字母加入结果，反之则将对应的数字加入结果，然后num像右平移四位，
    // 循环停止的条件是num为0，或者是已经循环了7次
    if(!num) return "0";
    string res {};
    string t = "0123456789abcdef";
    for(int i=0; i<8 && num; i++) {
       res = t[(num & 0xf)] + res;
       num >>= 4;
    }
    return res;
}

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
    // vector<string> res;
    vector<int> hour{8, 4, 2, 1}, minute{32, 16, 8, 4, 2, 1};

    function<vector<int>(vector<int>, int)> com = [&](vector<int> nums, int m) -> vector<int> {
        int cur = 0;
        vector<int> sel;
        function<void(int, int)> dfs = [&](int depth, int start) {
            if(depth == m)
                {sel.push_back(cur); return;}
            for(int i=start; i<nums.size(); i++) {
                cur += nums[i];
                dfs(depth+1, i+1);
                cur -= nums[i];
            }
        };
        dfs(0,0);
        return sel;
    };

    for(int i=0; i<=turnedOn; i++) {
        vector<int> hours = com(hour, i);
        vector<int> minutes = com(minute, turnedOn-i);
        for(auto &h:hours) {
            if(h>11) continue;
            for(auto &m:minutes) {
                if(m>59) continue;
                res.push_back(std::to_string(h) + ((m<10) ? ":0" : ":") + std::to_string(m));
            }
        }
    }
    return res;

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