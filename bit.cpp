
#include "bit.h"

vector<int> LC2595::evenOddBit(int n) {
    /*求一數積偶位數各有多少是1*/
    // Input: n = 17
    // Output: [2,0]
    // Explanation: The binary representation of 17 is 10001.
    // It contains 1 on the 0th and 4th indices.
    // There are 2 even and 0 odd indices.
    // You are given a positive integer n.
    // Let even denote the number of even indices in the binary representation of n (0-indexed) with value 1.
    // Let odd denote the number of odd indices in the binary representation of n (0-indexed) with value 1.
    // Return an integer array answer where answer = [even, odd].
    // Input: n = 17
    // Output: [2,0]
    // Explanation: The binary representation of 17 is 10001.
    // It contains 1 on the 0th and 4th indices.
    // There are 2 even and 0 odd indices.
    // 循環32次，每次向右shift i位跟1做and，然後看這第i位是odd or even去累加。當n為0時可以提早結束。
    int even=0, odd=0;
    for(int i=0; i<32 && n; i++, n>>=1) {
        if(n & 1)
            (i & 1) ? odd++ : even++;
    }
    return {even, odd};
}

int LC2220::minBitFlips(int start, int goal) {
    /*求最少flip次數將start變成goal的值*/
    // Input: start = 10, goal = 7 Output: 3
    // Explanation: The binary representation of 10 and 7 are 1010 and 0111 respectively. We can convert 10 to 7 in 3 steps:
    // Flip the first bit from the right: 1010 -> 1011.
    // Flip the third bit from the right: 1011 -> 1111.
    // Flip the fourth bit from the right: 1111 -> 0111.
    // It can be shown we cannot convert 10 to 7 in less than 3 steps. Hence, we return 3.

    // A bit flip of a number x is choosing a bit in the binary representation of x and flipping
    // it from either 0 to 1 or 1 to 0.
    // For example, for x = 7, the binary representation is 111 and we may choose any bit (including
    // any leading zeros not shown) and flip it. We can flip the first bit from the right to get 110,
    // flip the second bit from the right to get 101, flip the fifth bit from the right (a leading zero)
    // to get 10111, etc.
    // Given two integers start and goal, return the minimum number of bit flips to convert start to goal.
    // 找出兩數之間有多少bit不一樣，就表示可以最少flip幾次而獲得目標數，也就是兩數XOR後的值有多少1。
    // 由於是兩個整數做XOR，總共會有32bit，可以利用bitset來統計XOR之後1的個數
    return bitset<32>(start ^ goal).count();
}

bool LC2206::divideArray(vector<int>& nums) {
    /*判斷一陣列是否能分成n對pair，每對值相同*/
    // Input: nums = [3,2,3,2,2,2] Output: true
    // Explanation:
    // There are 6 elements in nums, so they should be divided into 6 / 2 = 3 pairs.
    // If nums is divided into the pairs (2, 2), (3, 3), and (2, 2), it will satisfy all the conditions.
    // You are given an integer array nums consisting of 2 * n integers.
    // You need to divide nums into n pairs such that:
    // Each element belongs to exactly one pair.
    // The elements present in a pair are equal.
    // Return true if nums can be divided into n pairs, otherwise return false.
    // 不能直接把nums內所有值XOR起來為看是否為0，例如6,17,12,4,20,11全部XOR起來會是0。
    // LC0136可以這麼做是因為題目已經表明只有一個數字是不一樣的。
    // 但可以先sort過後在兩兩XOR起來
    std::sort(nums.begin(), nums.end());
    for(int i=1; i<nums.size(); i+=2) {
        if(nums[i] ^ nums[i-1]) return false;
    }
    return true;

    // use hash table
//    unordered_map<int, int> map;
//    for(int &num:nums) ++map[num];
//    for(auto &m:map) if(m.second % 2 ) return false;
//    return true;
}

int LC1863::subsetXORSum(vector<int>& nums) {
    /*求陣列所有subset做XOR之和*/
    // Input: nums = [1,3]
    // Output: 6
    // Explanation: The 4 subsets of [1,3] are:
    // The empty subset has an XOR total of 0.
    // [1] has an XOR total of 1.
    // [3] has an XOR total of 3.
    // [1,3] has an XOR total of 1 XOR 3 = 2.
    // 0 + 1 + 3 + 2 = 6
    // The XOR total of an array is defined as the bitwise XOR of all its elements, or 0 if the array is empty.
    // For example, the XOR total of the array [2,5,6] is 2 XOR 5 XOR 6 = 1.
    // Given an array nums, return the sum of all XOR totals for every subset of nums.
    // Note: Subsets with the same elements should be counted multiple times.
    // An array a is a subset of an array b if a can be obtained from b by deleting some (possibly zero) elements of b.
    // 先枚舉出所有subset，各subset再做XOR，把各subset XOR出來的值加總起來。
    // iterative way
//    int res=0, n=nums.size(), tot=(1<<n); // 總共有2的n次方種排列組合
//    for(int i=0; i<tot; i++) { // 每一種排列組合
//        int xorsum=0;
//        for(int j=0; j<n; j++)
//            if((i>>j) & 1) xorsum ^= nums[j]; // 這一次在第j個bit若是1表示這次的排列組合有出現
//        res += xorsum;
//    }
//    return res;

    // 遞歸算從第i個到最後，每次包含和不包含這第i個的情況
    // recursive way
    int res=0, n=nums.size();
    function<void(int,int)> fun = [&](int cur, int xorsum) {
        if(cur == n) { res += xorsum; return;}
        fun(cur+1, xorsum^nums[cur]); // 包含
        fun(cur+1, xorsum); // 不包含
    };
    fun(0,0);
    return res;
}

string LC1763::longestNiceSubstring(string s) {
    /*求最長子字串字符大小寫全包含*/
    // Input: s = "YazaAay"
    // Output: "aAa"
    // Explanation: "aAa" is a nice string because 'A/a' is the only letter of the alphabet in s, and both 'A' and 'a' appear.
    // "aAa" is the longest nice substring.
    // A string s is nice if, for every letter of the alphabet that s contains, it appears both in uppercase and
    // lowercase. For example, "abABB" is nice because 'A' and 'a' appear, and 'B' and 'b' appear. However, "abA"
    // is not because 'b' appears, but 'B' does not.
    // Given a string s, return the longest substring of s that is nice. If there are multiple, return the substring
    // of the earliest occurrence. If there are none, return an empty string.

    // 用bit operation的方式 (只管有沒有，不管有的個數)
    int start=0, len=0, n=s.size();
    string res;
    for(int i=0; i<n; i++) {
        int uppercase=0, lowercase=0;
        for (int j=i; j<n; j++) {
            if(s[j]>='a') lowercase |= (1<<(s[j]-'a'));
            else uppercase |= (1<<(s[j]-'A'));
            if(j-i+1>len && !(lowercase^uppercase)) {
                start = i;
                len = j-i+1;
            }
        }
    }
    return len ? s.substr(start,len) : "";

    // 用兩個table各記下大小寫的個數，當兩個table相等就是一組nice string
//    int n=s.size();
//    string res;
//
//    for(int i=0; i<n; i++) {
//        array<int,26> u; u.fill(0);
//        array<int,26> l; l.fill(0);
//        for(int j=i; j<n; j++) {
//            const char c=s[j];
//            if(std::isupper(c)) u[c-'A'] = 1;
//            else l[c-'a'] = 1;
//            if(u==l && j-i+1 > res.size())
//                res = s.substr(i, j-i+1);
//        }
//    }
//    return res;

}

vector<int> LC1720::decode(vector<int>& encoded, int first) {
    /*用XOR來做編碼，求編碼前的原始資料*/
    // Input: encoded = [1,2,3], first = 1
    // Output: [1,0,2,1]
    // Explanation: If arr = [1,0,2,1], then first = 1 and encoded = [1 XOR 0, 0 XOR 2, 2 XOR 1] = [1,2,3]
    // There is a hidden integer array arr that consists of n non-negative integers.
    // It was encoded into another integer array encoded of length n - 1, such that encoded[i] = arr[i] XOR arr[i + 1].
    // For example, if arr = [1,0,2,1], then encoded = [1,2,3].
    // You are given the encoded array. You are also given an integer first, that is the first element of arr,
    // i.e. arr[0].
    // Return the original array arr. It can be proved that the answer exists and is unique.

    // a XOR b = c -> c XOR a = b, c XOR b = a
    // 把first讓入res的第一個，一路XOR回去
    vector<int> res(encoded.size()+1);
    res[0] = first;
    int i=1;
    for(auto &e:encoded) {
        res[i] = res[i - 1] ^ e;
        i++;
    }
    return res;
}

int LC1486::xorOperation(int n, int start){
    /*求n次做XOR運算後的值*/
    // Input: n = 5, start = 0
    // Output: 8
    // Explanation: Array nums is equal to [0, 2, 4, 6, 8] where (0 ^ 2 ^ 4 ^ 6 ^ 8) = 8.
    // Where "^" corresponds to bitwise XOR operator.
    // You are given an integer n and an integer start.
    // Define an array nums where nums[i] = start + 2 * i (0-indexed) and n == nums.length.
    // Return the bitwise XOR of all elements of nums.
    // 按題意依次處理。
    int res=0;
    for(int i=0; i<n; i++)
        res ^= (start + 2*i);
    return res;
}

int LC1342::numberOfSteps(int num) {
    /*偶數除2，積數減1，給定一數求多少步驟可變0*/
    // Input: num = 14 Output: 6
    // Explanation:
    // Step 1) 14 is even; divide by 2 and obtain 7.
    // Step 2) 7 is odd; subtract 1 and obtain 6.
    // Step 3) 6 is even; divide by 2 and obtain 3.
    // Step 4) 3 is odd; subtract 1 and obtain 2.
    // Step 5) 2 is even; divide by 2 and obtain 1.
    // Step 6) 1 is odd; subtract 1 and obtain 0.
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
    /*求陣列裡有幾組數字相加後能被60整除*/
    // Input: time = [30,20,150,100,40]
    // Output: 3
    // Explanation: Three pairs have a total duration divisible by 60:
    // (time[0] = 30, time[2] = 150): total duration 180
    // (time[1] = 20, time[3] = 100): total duration 120
    // (time[1] = 20, time[4] = 40): total duration 60
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
    /*求一整數二進制兩個1之間最大距離*/
    // Input: 5 Output: 2
    // Explanation: 5 in binary is 0b101.
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
    /*給定一範圍，統計有多少整數其二進制1的個數為質數*/
    // Input: L = 6, R = 10 Output: 4
    // Explanation:
    // 6 -> 110 (2 set bits, 2 is prime)
    // 7 -> 111 (3 set bits, 3 is prime)
    // 9 -> 1001 (2 set bits , 2 is prime)
    // 10-> 1010 (2 set bits , 2 is prime)
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
    /*判斷一個數的二進制1和0是否交替出現*/
    // Input: 5 Output: True
    // Explanation: The binary representation of 5 is: 101
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
    /*求一個數的補數*/
    // Input: 5
    // Output: 2
    // Explanation: The binary representation of 5 is 101 (no leading zero bits), and its complement is 010. So you need to output 2.
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
    /*兩數之間二進制對應位數不同的個數*/
    // Input: x = 1, y = 4 Output: 2
    // Explanation:
    // 1   (0 0 0 1)
    // 4   (0 1 0 0)
    //        ↑   ↑
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

int LC0409::longestPalindrome(string s) {
    /*回傳能建立最長的回文字串長度*/
    // Input: s = "abccccdd" Output: 7
    // Explanation: One longest palindrome that can be built is "dccaccd", whose length is 7.
    // 给了一个字符串，让我们找出可以组成的最长的回文串的长度，由于字符顺序可以打乱，所以问题就转化为了求偶数个字符的个数，了解回文串的都知道，
    // 回文串主要有两种形式，一个是左右完全对称的，比如noon, 还有一种是以中间字符为中心，左右对称，比如 bob，level 等，那么统计出来所有偶数
    // 个字符的出现总和，然后如果有奇数个字符的话，取出其最大偶数，然后最后结果加1即可
    array<int,128> map; map.fill(0);
    int even=0, odd=0;
    for(auto c:s) ++map[c];
    for(auto v:map) {
        even += v&(~1); // 清掉last bit取得偶數值，累計多少偶數；
        odd  |= v&( 1); // 看是否有積數值可作為回文中間那一char
    }
    return even+odd;
}

string LC0405::toHex(int num) {
    /*將十進位整數轉成十六進位表示*/
    // Input: 26
    // Output: "1a"

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

    //-8 1000
    //-7 1001
    //-6 1010
    //-5 1011
    //-4 1100
    //-3 1101
    //-2 1110
    //-1 1111
    // 0 0000
    // 1 0001
    // 2 0010
    // 3 0011
    // 4 0100
    // 5 0101
    // 6 0110
    // 7 0111

    // 從大數開始除起，餘數可以一直往結果的字串前面串接，連續除基數，餘數是需不斷往結果的字串前面插入，以6為例。
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
    /*給一二進制手錶的亮燈數，列出可能的時間*/
    // Input: n = 1
    // Output: ["1:00", "2:00", "4:00", "8:00", "0:01", "0:02", "0:04", "0:08", "0:16", "0:32"]
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
    /*判斷一個數是否為4的次方數*/
    // 这道题让我们判断一个数是否为4的次方数，那么最直接的方法就是不停的除以4，看最终结果是否为1
//    while(n>0 && !(n%4))
//        n /= 4;
//    return n==1;

    // 在确定其是2的次方数了之后，发现只要是4的次方数，减1之后可以被3整除
    return n>0 && !(n&(n-1)) && !((n-1)%3);
}

vector<int> LC0338::countBits(int n) {
    /*統計0到n每個數二進制1的個數*/
    // Input: 5
    // Output: [0,1,1,2,1,2]
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
    /*判斷一個字串是否重排後可形成回文*/
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
    /*判斷一個數是否為2的次方數*/
    // Input: 16
    // Output: true
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
    /*求整數裡有多少bit是1*/
    // Input:  00000000000000000000000000001011
    // Output: 3
    // Write a function that takes an unsigned integer and returns the number of ’1' bits it has (also known as
    // cthe Hamming weight).
    int res=0;
    for(int i=0; i<32; i++) {
        res += (n>>i & 1);
    }
    return res;
}

uint32_t LC0190::reverseBits(uint32_t n) {
    /*反轉整數裡bits的位置*/
    // Input:  11111111111111111111111111111101
    // Output: 10111111111111111111111111111111
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
    /*找出陣列裡唯一出現一次的數字*/
    // Input: [4,1,2,1,2]
    // Output: 4
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