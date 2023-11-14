
#include "dp.h"

/***********  Dynamic Programming  **********/
int LC1137::tribonacci(int n) {
    // let first=0, second=1, third=1. return first + second + third
    int first=0, second=1, third=1;
    if(n<2) return n;
    for(int i=2; i<n; i++) { // i從2開始，表示n要從3開始才會做計算
        int t = first;
        first = second;
        second = third;
        // 先存後加，n-1進來時算的是第n個值
        third = t + first + second;
    }
    return third;
}

bool LC1025::divisorGame(int n) {
    // 最初有一个数字N，每次每个人选一个小于N且能整除N的数字x，并将N替换为 N-x，依次进行，直到某个人没法进行了，则算输了。
    // 现在给个任意的N，且爱丽丝先走，问爱丽丝能否赢得游戏。先来分析一个下得到什么数字的时候会输，答案是当N变成1的时候，
    // 此时没法找到小于N的因子了，则输掉游戏。博主看到题后的第一个反应就是用递归，因为调用递归得到的结果是对手的胜负，若递归返回 false，
    // 则说明当前选手赢了，反之则当前选手输了。这里的 dp 数组定义很直接，dp[i] 表示起始数字为i时爱丽丝是否会赢，大小为 N+1，
    // 更新时从2开始就行，因为0和1都是 false，从2更新到N，对于每个数字，都从1遍历到该数字，找小于该数的因子，不能整除的直接跳过，
    // 能整除的看 dp[i-j] 的值，若为 false，则 dp[i] 更新为 true，并 break 掉即可
//    vector<bool> dp(n+1);
//    for(int i=2; i<=n; i++)
//        for(int j=1; j<i; j++) {
//            if(i%j) continue;
//            if(!dp[i-j]) {
//                dp[i] = true;
//                break;
//            }
//        }
//    return dp[n];
    // 直接判断奇偶即可，若N是偶数爱丽丝一定能赢，奇数一定会输。博主大概讲一下原因吧，前面提到过了，若某个人拿到了1，则表示输了，
    // 所以当拿到2的时候，一定会赢，因为取个因数1，然后把剩下的1丢给对手就赢了。对于大于2的N，最后都会先减小到2，所以其实这个游戏就是个
    // 争2的游戏。对于一个奇数N来说，小于N的因子x一定也是个奇数，则留给对手的 N-x 一定是个偶数。而对于偶数N来说，我们可以取1，然后变成一
    // 个奇数丢给对手，所以拿到偶数的人，将奇数丢给对手后，下一轮自己还会拿到偶数，这样当N不断减小后，最终一定会拿到2，所以会赢
    return !(n%2);
}

int LC0746::minCostClimbingStairs(vector<int>& cost) {
    // 这道题应该算是之前那道 Climbing Stairs 的拓展，这里不是求步数，而是每个台阶上都有一个 cost，让我们求爬到顶端的最小 cost 是多少。
    // 换汤不换药，还是用动态规划 Dynamic Programming 来做。这里定义一个一维的 dp数组，其中 dp[i] 表示爬到第i层的最小 cost，然后来想
    // dp[i] 如何推导。来思考一下如何才能到第i层呢？是不是只有两种可能性，一个是从第 i-2 层上直接跳上来，一个是从第 i-1 层上跳上来。不会
    // 再有别的方法，所以 dp[i] 只和前两层有关系，可以写做如下：
    //
    //dp[i] = min(dp[i- 2] + cost[i - 2], dp[i - 1] + cost[i - 1])
    int n=cost.size();
    if(!n) return 0;
    if(n==1) return cost[0];
    if(n==2) return std::min(cost[0], cost[1]); // 回傳的是前兩個的min

    int sPr1=cost[1], sPr2=cost[0], sCur;
    for(int i=2; i<n; i++) {
        sCur = std::min(sPr1, sPr2) + cost[i];
        sPr2 = sPr1; sPr1 = sCur;
    }
    return std::min(sPr1, sPr2); // 回傳的是前兩個的min
}

int LC0509::fib(int n) {
    // f(n) = f(n-1) + f(n-2)
//    if(n<=1) return n;
//    int sCurr=0, sPre1=1, sPre2=0;
//    for (int i=2; i<=n; i++) {
//        sCurr = sPre1 + sPre2;
//        sPre2 = sPre1;
//        sPre1 = sCurr;
//    }
//    return sCurr;

    // let first=0, second=1. return first + second
    int first=0, second=1;
    if(n<1) return n;
    for(int i=1; i<n; i++) { // i從1開始，表示n要從2開始才會做計算
        int tmp = first;
        first = second;
        // 先存後加，n-1進來時算的是第n個值
        second = tmp + first;
    }
    return second;
}

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
    // 假设梯子有n层，那么如何爬到第n层呢，因为每次只能爬1或2步，那么爬到第n层的方法要么是从第 n-1 层一步上来的，要不就是从 n-2 层2步
    // 上来的，所以递推公式非常容易的就得出了：dp[n] = dp[n-1] + dp[n-2]
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
    // 求最大子数组之和
    if(!nums.size()) return 0;
    if(1==nums.size()) return nums[0];

    int sCur=0, sPre=nums[0], vMax=nums[0];
    for(auto it=next(nums.begin()) ; it!=nums.end() ; it++) {
        sCur = max(sPre+*it, *it); // 如果前面累積的再加上當前的較小，則從當前的重新開始累計
        vMax = max(vMax, sCur); // 如果當前累積的是更大的值，則取代vMAX
        sPre = sCur; // 當前的存到已累加的
    }
    return vMax;
}

string LC0005::longestPalindrome(string s) {
    // Given a string s, return the longest palindromic substring in s.
    // Input: s = "babad"
    // Output: "bab"
    // Explanation: "aba" is also a valid answer.
    // 维护一个二维数组 dp，其中 dp[i][j] 表示字符串区间 [i, j] 是否为回文串，当 i = j 时，只有一个字符，肯定是回文串，如果 i = j + 1，
    // 说明是相邻字符，此时需要判断 s[i] 是否等于 s[j]，如果i和j不相邻，即 i - j >= 2 时，除了判断 s[i] 和 s[j] 相等之外，
    // dp[i + 1][j - 1] 若为真，就是回文串
    if (s.empty()) return "";
    int n = s.size(), left = 0, len = 1;
    vector<vector<bool>> dp(n, vector<bool>(n));
    for (int i = 0; i < n; ++i) {
        dp[i][i] = true;
        for (int j = 0; j < i; ++j) {
            dp[i][j] = (s[i]==s[j] && (i-j<2 || dp[i-1][j+1]));
            if(dp[i][j] && len < i-j+1) {
                len = i - j + 1;
                left = j;
            }
        }
    }
    return s.substr(left, len);
}

/***********  Greedy  **********/
int LC1221::balancedStringSplit(string s) {
    // 这道题给了一个只有L和R两个字符的字符串，并且定义了一种平衡字符串，即L和R的个数相同，现在问最多能将字符串分为多少个这样的平衡字符串。
    // 博主看到这题以后第一反应就觉得这是一道验证合法括号个数的题目，就像之前的那道 Valid Parentheses，这里的L就可以看作是左括号，R可以看
    // 作是右括号，其实这道题比验证合法括号更简单一些，因为合法括号不仅仅需要左右括号个数相同，而且任何时候右括号的个数不能多于左括号，而这道
    // 题并没有这个限制。这里只需要一个 cnt 变量来记录L的个数，遇到L则 cnt 自增1，遇到R则 cnt 自减1。每次检测一下，若某个状态 cnt 为0了，
    // 则说明此时L和R个数相等了，结果 res 自增1即可
    int res = 0, cnt = 0;
    for(auto &c:s) {
        (c=='L') ? cnt++ : cnt-- ;
        if(!cnt) res++;
    }
    return res;
}

int LC1217::minCostToMoveChips(vector<int>& position) {
    // 有一堆筹码，第i个筹码所在的位置是 position[i]，现在需要将所有的筹码移动到一摞，规则是：左右移动两个位置没有 cost，左右移动一个位置
    // 需要花费1个 cost，问移动到同一摞需要的最少花费是多少。最终结果位置必定在某一个已经存在的筹码的位置，那么这里其实就可以遍历所有给定筹
    // 码的位置，然后统计每个位置的花费。但其实这里还可以进一步优化，若有很多筹码都在同一个位置，那么显然按筹码遍历就不是很高效了，因为同一摞
    // 的筹码可以一起移动，则花费可以一起计算。这里用一个 HashMap 统计每个位置上的筹码个数，这样就可以把相同位置上的筹码摞到一起了。然后就可
    // 以遍历每一个位置了，对于遍历到的位置，再遍历其他所有的位置，统计花费，这样只要找到距离目标奇数位置，就可以把整个一摞的花费一起加上了。
    // 最后每次更新结果 res 即可
//    unordered_map<int, int> posCnt;
//    int res=INT_MAX;
//    for(int &p:position) ++posCnt[p];
//    for(auto &a:posCnt) {
//        int sum=0;
//        for(auto &b:posCnt) {
//            if((b.first-a.first)%2 == 0) continue;
//            sum += b.second;
//        }
//        res = std::min(res, sum);
//    }
//    return res;

    // 因为距离为偶数的筹码可以事先移动到一摞，而所有奇数位置的筹码互相之间都是相距偶数的距离，所有偶数位置的筹码互相之间也都是相距偶数的距离。
    // 这样所有筹码就可以在花费为0的情况下归为相邻的两大摞，则总花费其实就是个数较小的那一摞
    int odd=0, even=0;
    for(int &p:position)
        (p & 1) ? ++odd : ++even;
    return std::min(odd, even);
}

bool LC1013::canThreePartsEqualSum(vector<int>& arr) {
    // 给了我们一个数组，问能不能将该数组分成非空的三个部分，且每个部分的和相同。其实就是分成三个子数组，既然每个部分的和相同，说明数组的数字
    // 总和一定是3的倍数，若不是，则一定无法分。先求出数组的数字之和，除以3就是每个部分之和 target，然后进行数组的遍历，用一个变量 cur 来累
    // 积当前和，cnt 来表示已经成功分割的部分。每次累加到 target 的时候，cnt 自增1，且 cur 清零0，最终只要 cnt 的个数大于等于3就可以返回
    // true。可能有的小朋友会问，为啥会出现大于3的情况，这是因为当 target 为0的时候，多个为0的子数组可以合并成为一个为0的子数组，比如
    // [10,-10,10,-10,10,-10,10,-10]，前四个数字组成一个为0的部分，后面四个数字分别组成两个为0的部分，还是符合题意的
    int sum=std::accumulate(arr.begin(), arr.end(), 0);
    if(sum%3 != 0) return false;
    sum /= 3;
    int cur=0, cnt=0;
    for(auto &num:arr) {
        cur += num;
        if(cur == sum) {
            cnt++;
            cur=0;
        }
    }
    return cnt>=3;
}

int LC1005::largestSumAfterKNegations(vector<int>& nums, int k) {
    // Given an integer array nums and an integer k, modify the array in the following way:
    // choose an index i and replace nums[i] with -nums[i].
    // You should apply this process exactly k times. You may choose the same index i multiple times.
    // Return the largest possible sum of the array after modifying it in this way.
    // Input: nums = [4,2,3], k = 1
    // Output: 5
    // Explanation: Choose index 1 and nums becomes [4,-2,3].
    // Example 2:
    // Input: nums = [3,-1,0,2], k = 3
    // Output: 6
    // Explanation: Choose indices (1, 2, 2) and nums becomes [3,1,0,2].
    // Example 3:
    // Input: nums = [2,-3,-1,5,-4], k = 2
    // Output: 13
    // Explanation: Choose indices (1, 4) and nums becomes [2,3,-1,5,4].
    // 先给数组排个序，这样所有的负数都在数组的前面了，然后此时将前K个负数翻转成正数，注意只是翻转负数，若负数的个数小于K，也不会翻转多余的正
    // 数。然后此时遍历数组，求数组之后，并且求此时数组中最小的数字，此时K还是有奇偶两种情况，当K是偶数的时候（包括0），直接返回数组之和，
    // 若是奇数的时候，此时说明数组中的负数已经全部翻转为了正数，那么最小的数也就是绝对值最小的数，减去其的2倍即可
    int res = 0, min=INT_MAX;

    std::sort(nums.begin(), nums.end());
    for(int i=0; k && i<nums.size() && nums[i]<0; i++, k--)
        nums[i] = -nums[i];
    for(auto &num:nums) {
        res += num;
        min = std::min(min, num);
    }
    return res - (k%2)*2*min;
}

int LC0976::largestPerimeter(vector<int>& nums) {
    // Given an integer array nums, return the largest perimeter of a triangle with a non-zero area,
    // formed from three of these lengths. If it is impossible to form any triangle of a non-zero area, return 0.
    // Input: nums = [2,1,2]
    // Output: 5
    // Input: nums = [1,2,1]
    // Output: 0
    // 三角形任意兩邊的和大於第三邊，任意兩邊的差小於第三邊。
    // 先把nums排序過，從最大的三個值開始檢查是否符合三角形邊長規則，若否則遞減一值

    // 给了个正整数数组，让从中选三个数当作三角形的三条边，问能组成的三角形的最大周长是多少。因为要组成三角形，所以必须要满足两边之和大于
    // 第三边这一条性质，我们并不用去检测所有的组合情况，而是只要判断较短的两边之和是否大于最长的那条边就可以了。虽然这道是 Easy 题目，但
    // 是 OJ 仍然不让用暴力搜索法，遍历任意三条边是会超时的。所以只能想优化的解法，既然要周长最长，则肯定是选较大的数字先测比较好。这里就
    // 先给数组排个序，然后从末尾开始，每次取出三个数字，先检测能否组成三角形，可以的话直接返回周长，不行的话就继续往前取，若都不行的话，就
    // 返回0
    std::sort(nums.begin(), nums.end());
    for(int i=nums.size()-1; i>=2; i--)
        if(nums[i] < nums[i-1] + nums[i-2])
            return nums[i] + nums[i-1] + nums[i-2];
    return 0;
}

vector<int> LC0942::diStringMatch(string s) {
    // 这道题给了一个只有 'D' 和 'I' 两个字母组成的字符串，表示一种 pattern，其中 'D' 表示需要下降 Decrease，即当前数字大于下个数字，
    // 同理，'i' 表示需要上升 Increase，即当前数字小于下个数字，让返回符合这个要求的任意一个数组，还有个要求是该数组必须是 [0, n]
    // 之间的所有数字的一种全排列，其中n是给定 pattern 字符串的长度。这表明了返回数组不能有重复数字，这里一会上升一会下降的，很容易产生重复
    // 数字，难不成还要不停的检测是否有重复数字么，不，这样太麻烦了，必须想一种生成方法来保证绝对不会有重复数字。对于上升来说，可以从0开始累
    // 加，而对于下降来说，则可以从n开始下降，这样保证了在结束之前二者绝不会相遇，到最后一个数字的时候二者相同，再将这个相同数字加入即可，
    // 因为返回的数组的个数始终会比给定字符串长度大1个
    vector<int> res;
    int l=0, r=s.size();
    for(auto &c:s) {
        if(c == 'I') res.push_back(l++);
        else res.push_back(r--);
    }
    res.push_back(l);
    return res;
}

bool LC0860::lemonadeChange(vector<int>& bills) {
    // 这道题说是有很多柠檬，每个卖5刀，顾客可能会提供5刀，10刀，20刀的钞票，我们刚开始的时候并没有零钱，只有收到顾客的5刀，或者 10 刀可以
    // 来给顾客找钱，当然如果第一个顾客就给 10 刀或者 20 刀，那么是无法找零的，这里就问最终是否能够都成功找零。
    // 只关心当前还剩余的5刀和 10 刀钞票的个数，用两个变量 five 和 ten 来记录。然后遍历所有的钞票，假如遇到5刀钞票，则 five 自增1，若遇
    // 到 10 刀钞票，则需要找零5刀，则 five 自减1，ten 自增1。否则遇到的就是 20 刀的了，若还有 10 刀的钞票话，就先用 10 刀找零，则 ten
    // 自减1，再用一张5刀找零，five 自减1。若没有 10 刀了，则用三张5刀找零，five 自减3。找零了后检测若此时5刀钞票个数为负数了，则直接返
    // 回 false
    int five=0, ten=0;
    for(auto &bill:bills) {
        if(bill == 5) five++;
        else if(bill == 10) {
            five--;
            ten++;
        }
        else if(bill == 20) {
            if(ten > 0) { ten--; five--; }
            else { five-=3;}
        }
        if(five < 0) return false;
    }
    return true;
}

bool LC0717::isOneBitCharacter(vector<int>& bits) {
    // 这道题说有两种特殊的字符，一种是两位字符，只能是二进制的11和10，另一种是单个位字符，只能是二进制的0。现在给了我们一个只包含0和1的数
    // 组，问我们能否将其正确的分割，使得最后一个字符是个单个位字符。这道题可以使用贪婪算法来做，因为两种字符互不干扰，只要我们遍历到了数字1，
    // 那么其必定是两位字符，所以后面一位也得跟着，而遍历到了数字0，那么就必定是单个位字符。所以我们可以用一个变量i来记录当前遍历到的位置，
    // 如果遇到了0，那么i自增1，如果遇到了1，那么i自增2，我们循环的条件是i < n-1，即留出最后一位，所以当循环退出后，当i正好停留在n-1上，
    // 明最后一位是单独分割开的，因为题目中限定了最后一位一定是0，所以没必要再判断了
    int n=bits.size(), i=0;
    while(i<n-1) {
        if(bits[i] == 0) i++;
        else i+=2;
    }
    return i==n-1;

    // 直接用一行代替了if..else..语句，相当巧妙，当bits[i]为0时，i还是相当于自增了1，当bits[i]为1时，i相当于自增了2，
    // 最后还是在循环跳出后检测i是否为n-
//    int n = bits.size(); int i = 0;
//    while(i<n-1)
//        i += bits[i] + 1;
//    return i==n-1;

    // recursive way
//    int n=bits.size();
//    function<bool(int)> fun = [&](int i)->bool {
//        if(i==n) return false;
//        if(i==n-1) return bits[i]==0;
//        if(bits[i]==0) return fun(i+1);
//        return fun(i+2);
//    };
//    return fun(0);
}

bool LC0680::validPalindrome(string s) {
    // 这道题的字符串中只含有小写字母，而且这道题允许删除一个字符，那么当遇到不匹配的时候，我们到底是删除左边的字符，还是右边的字符呢，
    // 我们的做法是两种情况都要算一遍，只要有一种能返回true，那么结果就返回true。我们可以写一个子函数来判断字符串中的某一个范围内的
    // 子字符串是否为回文串
    auto isValid = [](string &s, int l, int r) {
        while(l<r)
            if(s[l++]!=s[r--]) return false;
        return true;
    };

    int l=0, r=s.size()-1;
    while(l<r) {
        if(s[l]!=s[r])
            return isValid(s, l+1, r) || isValid(s, l, r-1);
        l++; r--;
    }
    return true;
}

bool LC0605::canPlaceFlowers(vector<int>& flowerbed, int n) {
    // 这道题给了我们一个01数组，其中1表示已经放了花，0表示可以放花的位置，但是有个限制条件是不能有相邻的花。那么我们来看如果是一些简单的例
    // 子，如果有3个连续的零，000，能放几盆花呢，其实是要取决约左右的位置的，如果是10001，那么只能放1盆，如果左右是边界的花，那么就能放
    // 两盆，101。可以直接通过修改flowerbed的值来做，我们遍历花床，如果某个位置为0，我们就看其前面一个和后面一个位置的值，注意处理首位置和
    // 末位置的情况，如果pre和next均为0，那么说明当前位置可以放花，我们修改flowerbed的值，并且n自减1，最后看n是否小于等于0
    for(int i=0; i<flowerbed.size(); i++) {
        if(!n) return true;
        if(!flowerbed[i]) {
            int pre = (!i) ? 0 : flowerbed[i-1];
            int nxt = (i==flowerbed.size()-1) ? 0 : flowerbed[i+1];
            if(pre+nxt == 0) {
                flowerbed[i]=1;
                n--;
            }
        }
    }
    return n<=0;
}

int LC0561::arrayPairSum(vector<int>& nums) {
    // 这道题让我们分割数组，两两一对，让每对中较小的数的和最大。这题难度不大，用贪婪算法就可以了。由于我们要最大化每对中的较小值之和，那么肯
    // 定是每对中两个数字大小越接近越好，因为如果差距过大，而我们只取较小的数字，那么大数字就浪费掉了。明白了这一点，我们只需要给数组排个序，
    // 然后按顺序的每两个就是一对，我们取出每对中的第一个数即为较小值累加起来即可
    int res = 0;
    sort(nums.begin(), nums.end());
    for(int i=0; i<nums.size(); i+=2)
        res+=nums[i];
    return res;
}

int LC0495::findPoisonedDuration(vector<int>& timeSeries, int duration) {
    // 使用贪心算法，比较相邻两个时间点的时间差，如果小于duration，就加上这个差，如果大于或等于，就加上duration即可
    if(timeSeries.empty()) return 0;
    int res = 0;
    for(int i=1; i<timeSeries.size(); i++) {
        int diff = timeSeries[i]-timeSeries[i-1];
        res += (diff<duration) ? diff : duration;
    }
    return res + duration;
}

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

int LC0011::maxArea(vector<int>& height) {
    // You are given an integer array height of length n. There are n vertical lines drawn such that the two endpoints
    // of the ith line are (i, 0) and (i, height[i]).
    // Find two lines that together with the x-axis form a container, such that the container contains the most water.
    // Return the maximum amount of water a container can store.
    // Input: height = [1,8,6,2,5,4,8,3,7]
    // Output: 49
    // Explanation: The above vertical lines are represented by array [1,8,6,2,5,4,8,3,7]. In this case, the max area
    // of water (blue section) the container can contain is 49.
    // 水的容量為兩邊中較小的高度x水底板的寬度，一開始從0, n-1最大底板寬度開始算起，當縮小底板寬度時選擇高度較小的一邊縮，看是否能更新到高度
    // 再高一點。進一步的優化為，遇到相同高度時直接更新，不需要再計算水容量來做比較。

    int res=0, l=0, r=height.size()-1;
    while(l<r) {
        int h = std::min(height[l], height[r]);
        res = std::max(res, h*(r-l));
        while(l<r && h==height[l]) l++;
        while(l<r && h==height[r]) r--;
    }
    return res;
}