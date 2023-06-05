
#include "dp.h"

/***********  Dynamic Programming  **********/

int LC0509::fib(int n) {
    // f(n) = f(n-1) + f(n-2)
    if(n<=1) return n;
    int sCurr=0, sPre1=1, sPre2=0;
    for (int i=2; i<=n; i++) {
        sCurr = sPre1 + sPre2;
        sPre2 = sPre1;
        sPre1 = sCurr;
    }
    return sCurr;
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

/***********  Greedy  **********/
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