#include "list.h"

/***********  Array List  **********/
vector<int> LC1313::decompressRLElist(vector<int>& nums) {
    // 给了一个压缩后的数组，压缩的方法是将相同连续的数字的个数和其本身组成个数对儿，放到压缩数组中，以此类推。现在让我们解压缩成原来的数组，
    // 没啥太大的难度，就是每次取出两个数字，前一个数字是次数，后一个是数字本身，用一个 for 循环，就可以生成给定次数个数字，用这种方法就可以
    // 解压缩出原数组了
    vector<int> res;
    for(int i=0; i<nums.size(); i+=2)
        for(int j=0; j<nums[i]; ++j)
            res.push_back(nums[i+1]);
    return res;
}

vector<int> LC1304::sumZero(int n) {
    // 给了一个正整数n，让返回一个长度为n的数组，要求是没有重复数字且数字之和为0。
    // 在数组的两端往中间更新，新建一个大小为n的数组，初始化均为0，两端分别赋值为1和 -1，然后往中间一步，赋值为2和 -2，直到中间的位置。
    // 若最中间只有一个数字，则保持为0不变，不会产生重复也不影响数字和
//    vector<int> res(n);
//    int l=0, r=n-1, v=1;
//    while(l<r) {
//        res[l++] = v;
//        res[r--] = -v;
//        ++v;
//    }
//    return res;

    // 从数组的第二个数字开始赋值为 1，2，3...，然后第一个位置放后面所有数字之和的相反数，这样整个数组和还是0，同样也可以达到要求
    vector<int> res(n);
    for(int i=1; i<n; ++i) {
        res[i] = i;
        res[0] -= i;
    }
    return res;
}

vector<int> LC1299::replaceElements(vector<int>& arr) {
    // 给了一个数组 arr，说是让把每个数字更新为其右边的数字中最大的一个，最后一个数字变为 -1。既然是一道 Easy 的题目，就不用担心解法会太复
    // 杂，一般都是较短的行数就能搞定的。让求每个数字右边的数字中最大的一个，当然不能每次都遍历右边所有的数字来找最大值，虽说是 Easy 题目，
    // 但最好也别这么暴力地解，多少还是要给 OJ 一些尊重的。从左往右不好使的话，可以调个头，从右往左去更新，这样就简单的多了，最后一个数字直
    // 接更新为 -1，然后只要维护一个从右往左的当前最大值，每次用来更新右往左的对应位置即可，基本没什么难度，只要能想到换个方向更新，基本就迎
    // 刃而解了
//    int n=arr.size(), cm=INT_MIN;
//    vector<int> res(n);
//    res[n-1] = -1;
//    for(int i=n-2; i>=0; --i) {
//        cm = std::max(cm, arr[i+1]);
//        res[i] = cm;
//    }
//    return res;

    // 不新增一個vector，在原本輸入的vector做處理。
    int n=arr.size();
    if(!n) return arr;

    int cm=arr[n-1];
    arr[n-1] = -1;
    for(int i=n-2; i>=0; --i) {
        int tmp = arr[i];
        arr[i] = cm;
        cm = std::max(cm, tmp);
    }
    return arr;
}

int LC1295::findNumbers(vector<int>& nums) {
    // 给了一个数组，让找出多少个偶数位的数字，所谓偶数位的数字，就是说该多位数要有偶数个位，比如个数位就不是偶数位数字，而十位数就是。
    // 其实这道题就是考察如何统计整数的位数，比较简单直接的方法就是进行一个 while 循环，每次都除以 10，直到原数字变为0为止，这样就知道位数
    // 了。可以对数组中的每个数字都进行如下的操作，就可以知道是否是偶数位的数字了
//    int res=0;
//    for(auto num:nums) {
//        int cnt =0;
//        while(num) {
//            ++cnt;
//            num/=10;
//        }
//        res += !(cnt & 1);
//    }
//    return res;

    // 运用到了对数计算，数字进行以10为底的对数运算，若得到奇数，则表示原数字是偶数位的，这样就省去了 while 循环的操作，可以进行快速的判断
    int res=0;
    for(auto num:nums)
        res += (int)std::log10(num) & 1;
    return res;

    // 由于题目中给定了数字的范围，不超过 10^5，那么偶数位的数字其实是有固定的范围的，分别为 [10, 99]，[1000, 9999]，和 100000，
    // 只要对这些范围进行直接判断，就知道是否是偶数位了
//    int res=0;
//    for(auto num:nums)
//        if((num>9 && num<100)||(num>999 && num<10000)||(num==100000)) ++res;
//    return res;
}

int LC1281::subtractProductAndSum(int n) {
    // 给了一个正整数n，让求其每一位的数字的乘积减去每一位数字的和，并不算一道难题，只要知道如何取出每一位上的数字基本上就可以秒解，也符合
    // 其 Easy 的身价。取每一位上的数字就用一个 while 循环，只要n大于0就一直循环，通过对 10 取余就可以取出个位上的数字，将其乘到 prod 中，
    // 加到 sum 中，然后n自除以 10，就可以去掉已经取出的数字，然后再进行上述的操作，直到每一位的数字都被取出并处理了，最后返回 prod 减去
    // sum 的值即可
    int p=1, s=0;
    while(n) {
        int d = n%10;
        p *= d;
        s += d;
        n /= 10;
    }
    return p-s;
}

int LC1266::minTimeToVisitAllPoints(vector<vector<int>>& points) {
    // 给了一堆二维平面上的点，让按照顺序去连接点，这里的连线不但可以走水平和竖直，还能走斜线，都算作一步，问按顺序连上所有的点需要多少步。
    // 这里让按顺序连点也就简单了不少，也算对得起 Easy 的身价，只要分析出两个点之间的最小步数怎么算就可以解题了。题目中说可以水平，竖直，
    // 和对角线走，那么就按照题目中的例子来分析吧，若仔细观察可以发现，假如两个点的横纵坐标的差值相等的话（都是绝对值），那么只要纯走对角线
    // 就行了，比如 [3,4] 和 [-1,0] 这两个点，若差值不相等的话，则同时要走对角线和横纵边，比如 [1,1] 和 [3,4] 这两个点，但是步数不会超
    // 过较长的那条边，想想是为啥？因为要达到目标点，横纵方向都要走完差值，走对角线可以同时走横纵方向，但要走的步数也绝不会小于较大的差值，
    // 不然的话在该方向没法走完之间的距离，同时也不应该大于较大的差值，否则走的就不是最优解的话。所以两个点之间的步数就是其横纵坐标各自的差的
    // 绝对值中的较大一个，两两之间计算一下，累加起来即为所求
    int res=0;
    for(int i=0; i<points.size()-1; ++i)
        res += std::max(std::abs(points[i][0]-points[i+1][0]), std::abs(points[i][1]-points[i+1][1]));
    return res;
}

int LC1252::oddCells(int m, int n, vector<vector<int>>& indices) {
    // 给了一个大小为 m by n 的矩阵，初始化均为0，又给了一个坐标数组 indices，说是对于其中的每个坐标 (r, c)，将对应的行和列上的数字分别
    // 自增1，最后问数组中有多少个数字是奇数。当然最简单暴力的解法就是就是遍历每个坐标，分别将对应的行列上的数字自增1，然后最后再判断奇偶，
    // 虽然这是一道 Easy 的题目，但博主还是怀疑这种方法可能会超时，所以根本就没有尝试。对于每个坐标都遍历一次行和列，实在是不太高效，因为该
    // 行和该列可能后面还会多次出现，有没有办法能够一次性统计出某行某列到底需要更新多少次呢？答案是肯定的，这里可以建立两个数组 rowCnt 和
    // colCnt，分别来统计某行和某列需要更新的次数。之后遍历整个初始数组，对于任意位置 (i, j)，去 rowCnt 和 colCnt 中取出行i和列j需要的
    // 更新次数，二者之和就是当前位置需要增加的数字，直接判断奇偶，奇数的话加到结果 res 中即可
    int res=0;
    vector<int> r(m), c(n);
    for(auto i:indices) {
        ++r[i[0]];
        ++c[i[1]];
    }
    for(int i=0; i<m; ++i)
        for(int j=0; j<n; ++j)
            res += (r[i] + c[j])%2;
    return res;
}

vector<int> LC1103::distributeCandies(int candies, int num_people) {
    // 有一些糖果要发给n个人，第一轮是第一个人发一个，第二个人发两个，第n个人发n个，第二轮是第一个人发 n+1 个，第二个人发 n+2 个，
    // 第n个人发 2n 个，以此类推，直到发到某个人时不够目标个数，此时将剩余的糖全给该人，并停止分发。，问最终每个人会得到多少个糖。
    // 用变量i表示当前人得到的糖数减1，这里减1的原因是想将其也当作数组坐标来用，因为数组坐标都是从0开始的。虽然之后i会累加到很大，
    // 但是只要对n取余，就是正确的坐标位置，此时该人得到的糖果个数为当前剩余的糖果个数 candies 和 i+1 之间的较小值，然后 candies
    // 需要减去 i+1，for 循环的执行条件是 candies 大于0，这样当糖果发完了之后就退出了
    vector<int> res(num_people);
    for(int i=0; candies>0; i++) {
        res[i%num_people] += std::min(candies, i+1);
        candies -= (i+1);
    }
    return res;
}

int LC1184::distanceBetweenBusStops(vector<int>& distance, int start, int destination) {
    // 有n个公交站形成了一个环，它们之间的距离用一个数组 distance 表示，其中 distance[i] 表示公交站i和 (i+1)%n 之间的距离。说是公交可以
    // 顺时针和逆时针的开，问给定的任意起点和终点之间的最短距离。对于一道 Easy 题的身价，没有太多的技巧而言，主要就是考察了一个循环数组，求任
    // 意两个点之间的距离，由于两个方向都可以到达，那么两个方向的距离加起来就正好是整个数组之和，所以只要求出一个方向的距离，另一个用总长度减
    // 去之前的距离就可以得到。所以这里先求出所有数字之和，然后要求出其中一个方向的距离，由于处理循环数组比较麻烦，所以这里希望 start 小于
    // destination，可以从二者之间的较小值遍历到较大值，累加距离之和，然后比较这个距离和，跟总距离减去该距离所得结果之间的较小值返回即可
//    int sum = std::accumulate(distance.begin(), distance.end(), 0);
//    int dis = 0;
//    for(int i=std::min(start, destination); i<std::max(start,destination); ++i)
//        dis += distance[i];
//    return std::min(dis, sum-dis);

    // 只要一次遍历就可以完成，因为最终都要是要遍历所有的站点距离，当这个站点在 [start, destination) 范围内，就累加到 sum1 中，否则就
    // 累加到 sum2 中。不过要要注意的是要确保 start 小于 destination，所以可以开始做个比较，若不满足则交换二者。最终返回 sum1 和
    // sum2 中较小者即可
    int sum1=0, sum2=0, n=distance.size();
    if(start > destination) std::swap(start, destination);
    for(int i=0; i<n; ++i) {
        if(i>=start && i<destination) sum1 += distance[i];
        else sum2 += distance[i];
    }
    return std::min(sum1, sum2);
}

void LC1089::duplicateZeros(vector<int>& arr) {
    // 这道题给了一个数字数组，让将每个0都复制一个，然后将数字右移一位，数组的长度还是保持不变，右移出范围的数字就移除掉。这不是一道难题，比较
    // 直接的做法就是新建一个结果数组 res，然后遍历给定数组 arr，for 循环条件加上一个 res 的长度小于n，将当前遍历到的数字加入 res，然后判
    // 断若当前数字是0，且此时 res 长度小于n，则再加个0到 res 中，最后把 arr 更新为 res 即可
//    int n=arr.size();
//    vector<int> res;
//    for(int i=0; i<n && res.size()<n; i++) {
//        res.push_back(arr[i]);
//        if(arr[i]==0 && res.size()<n) res.push_back(0);
//    }
//    arr = res;

    // 不使用额外空间的解法，还是使用了双指针来做，j初始化为 arr 数组的长度加上其中0的个数，实际上就是在不右移的情况下得到的新的数组的长度，
    // i从 n-1 开始遍历到0，首先对j进行自减1，若此时j小于n了，说明已经到需要更新的地方了，将 arr[j] 赋值为 arr[i]，接下来处理0的情况，若
    // arr[i] 为0，且自减1后的j小于n，则将 arr[j] 赋值为0，还是不太理解整个过程的童鞋可以将例子1带入，一步一步来尝试运行，其实并不是很难理解
    int n=arr.size(), j=n+std::count(arr.begin(), arr.end(), 0);
    for(int i=n-1; i>=0; --i) {
        if(--j<n) arr[j] = arr[i];
        if(arr[i]==0 && --j<n) arr[j] = 0;
    }
}

vector<bool> LC1018::prefixesDivBy5(vector<int>& nums) {
    // 给了一个只由0和1组成的数组，问从0开始每个子数组表示的二进制数是否可以整除5，二进制数是从高位到低位的。既然是一道 Easy 的题目，也就不
    // 用太多的技巧，直接按顺序遍历即可。首先对于第一个数字，可以快速知道其是否可以整除5，当子数组新加一位，实际上相当于之前的数字左移了一位，
    // 也就相当于乘以了2，所以新的子数组表示的数字就是之前的数字乘以2再加上新加进来的数字，然后就可以判断是否可以整除5了。但是需要注意的一点
    // 是，由于A数组可能会很长，所以最终累加出来的数字可能会很大，超过整型最大值，甚至也超过长整型的最大值，为了避免这种情况，对每次累加出来
    // 的新数字都对5取余，这样就不会溢出了
    vector<bool> res;
    int val=0;
    for(int &num:nums) {
        val = (val<<1 | num) % 5;
        res.push_back(val%5 == 0);
    }
    return res;
}

vector<int> LC0989::addToArrayForm(vector<int>& num, int k) {
    // 给了一个数组A，说是可以表示一个正整数，高位在开头，又给了一个正数K，让用数组A表示的正整数加上K，并还用数组来表示相加的后的结果。这种
    // 用不同的数据结构玩加法的题，之前也出现过，比如 Add Two Numbers，Plus One，Add Binary，和 Add Strings。但其实都是万变不离其宗，
    // 都是要一位一位的相加，并且处理好进位的问题。这里由于高位是在数组开头，而相加是要从低位开始的，所以从数组的后面往前开始遍历，用当前位上
    // 的数字加上K，再对 10 取余，得到的就是相加后该位上的数字。只用一个循环搞定，并且直接更新数组A，不额外使用数组。那么循环条件就是K大于0，
    // 或进位值 carry 大于0。在循环中，先让 carry 加上K对 10 取余的值，此时若数组A的值还没有遍历完，即i大于等于0时，再加上 A[i]，此时
    // num 除以 10 就是更新后的 carry 值，对 10 取余就是当前位上的值。此时若i大于等于0，则更新 A[i] 为 num 值，且i自减1，否则将 num
    // 加到数组A的开头，然后K在自除以 10，最后返回数组A即可
    int i=num.size()-1, c=0;
    while(k || c) {
        int val = k%10 + c;
        if(i>=0) val += num[i];
        c = val/10;
        val %= 10;
        if(i>=0) { num[i] = val; i--;}
        else num.insert(num.begin(), val);
        k /= 10;
    }
    return num;
}

int LC0944::minDeletionSize(vector<string>& strs) {
    // 这道题给了一个字符串数组，里面的字符串长度均相同，这样如果将每个字符串看作一个字符数组的话，于是就可以看作的一个二维数组，题目要求所有
    // 列上的字符是非递减顺序的，问最少需要删掉多少列。这道题唯一的难点就是读懂晦涩的题意，估计是出自非母语之手的，其他的并没有太大的难度，就
    // 是一个按列来遍历二维数组的操作，若当前位置的字符小于等于下一行同列上的字符，则跳过继续比较下一行和下下一行上的字符。否则说明需要删掉该
    // 列，结果 res 自增1，且 break 掉当前列即可
    int m=strs.size(), n=strs[0].size(), res=0;
    for(int x=0; x<n; ++x)
        for(int y=0; y<m-1; ++y)
            if(strs[y][x] > strs[y+1][x]) {++res; break;}
    return res;
}

bool LC0941::validMountainArray(vector<int>& arr) {
    // 定义了一种山形数组，长度大于等于3，并且存在一个峰值，左右两边的数字都必须严格递减，不允许有相等的值存在。就是说从开头遍历，一定是严格递
    // 增的，直到到达峰值，然后严格递减到末尾，那么可以从开头进行 while 循环，若当前数字小于右边的数字，则i自增1，为了避免溢出，i只能遍历到
    // 倒数第二个数字，这样当循环结束的时候，i指向的数字是大于等于右边的数字，是潜在的峰值，当然这里是不能相等的，但此时不需要判断。同样的操作
    // 反向来一遍，j从最后一个数字遍历到第二个数字，若当前数字小于其左边的数字时，则j自减1，这样循环结束后，j指向的数字是大于等于左边的数字的，
    // 也是潜在的峰值。接下来就要比较这两个峰值是否指向同一个数字，同时i指向的数字不能是第一个，j指向的数字不能是最后一个数字，因为必须要有上坡
    // 和下坡的存在
    int n=arr.size(), i=0, j=n-1;
    while(i<n-1 && arr[i]<arr[i+1]) ++i;
    while(j>0 && arr[j]<arr[j-1]) --j;
    return i!=0 && j!=n-1 && i==j;
}

int LC0933::ping(int t) {
    // 实现一个 RecentCounter 类，里面有一个 ping 函数，输入给定了一个时间t，让我们求在 [t-3000, t] 时间范围内有多少次 ping。题目中限
    // 定了每次的给的时间一定会比上一次的时间大，而且只关心这个大小为 3001 的时间窗口范围内的次数，则利用滑动窗口 Sliding Window 来做就是
    // 个很不错的选择。由于数字是不断加入的，可以使用一个 queue，每当要加入一个新的时间点t时，先从队列开头遍历，若前面的时间不在当前的时间窗
    // 口内，则移除队列。之后再将当前时间点t加入，并返回队列的长度即可
    q.push(t);
    while(q.front() < t-3000) q.pop();
    return q.size();
}

int LC0908::smallestRangeI(vector<int>& nums, int k) {
    // 给了一个非负数的数组，和一个非负数K，说是数组中的每一个数字都可以加上 [-K, K] 范围内的任意一个数字，问新数组的最大值最小值之间的差值
    // 最小是多少。这道题的难度是 Easy，理论上应该是可以无脑写代码的，但其实很容易想的特别复杂。本题的解题标签是 Math，这种类型的题目基本上
    // 就是一种脑筋急转弯的题目，有时候一根筋转不过来就怎么也做不出来。首先来想，既然是要求新数组的最大值和最小值之间的关系，那么肯定是跟原数
    // 组的最大值最小值有着某种联系，原数组的最大值最小值我们可以很容易的得到，只要找出了跟新数组之间的联系，问题就能迎刃而解了。题目中说了每
    // 个数字都可以加上 [-K, K] 范围内的数字，当然最大值最小值也可以，如何让二者之间的差值最小呢？当然是让最大值尽可能变小，最小值尽可能变大
    // 了，所以最大值 mx 要加上 -K，而最小值 mn 要加上K，然后再做减法，即 (mx-K)-(mn+K) = mx-mn-2K，这就是要求的答案啦
    int mx=nums[0], mn=nums[0];
    for(auto &num:nums) {
        mx = std::max(mx, num);
        mn = std::min(mn, num);
    }
    return std::max(0, mx-mn-2*k);

    // 也可以使用 STL 自带的求最大值最小值的函数，从而一行搞定。max_element/min_element記得要deference
//    return std::max(0, *std::max_element(nums.begin(), nums.end()) - *std::min_element(nums.begin(), nums.end())-2*k);
}

bool LC0896::isMonotonic(vector<int>& nums) {
    // 判断一个数组是否单调，单调数组就是说这个数组的数字要么是递增的，要么是递减的，不存在一会儿递增一会儿递减的情况，即不会有山峰存在。
    // 这里不是严格的递增或递减，是允许有相同的数字的。那么我们直接将相邻的两个数字比较一下即可，使用两个标识符，inc 和 dec，初始化均为
    // true，我们开始时假设这个数组既是递增的又是递减的，当然这是不可能的，我们会在后面对其进行更新。在遍历数组的时候，只要发现某个数字大
    // 于其身后的数字了，那么 inc 就会赋值为 false，同理，只要某个数字小于其身后的数字了，dec 就会被赋值为 false，所以在既有递增又有递
    // 减的数组中，inc 和 dec 都会变为 false，而在单调数组中二者之间至少有一个还会保持为 true
    bool inc=true, dec=true;
    for(int i=1; i<nums.size(); i++) {
        inc &= nums[i]>=nums[i-1];
        dec &= nums[i]<=nums[i-1];
        if(!inc && !dec) return false;
    }
    return true;

    // 没有用 bool 型的，而是用了整型数字来记录递增和递减的个数，若是单调数组，那么最终在 inc 和 dec 中一定会有一个值是等于数组长度的
//    int inc=1, dec=1; // 初始值是1，最後才會是跟n做比較
//    int n=nums.size();
//    for(int i=1; i<n; i++) {
//        inc += nums[i]>=nums[i-1];
//        dec += nums[i]<=nums[i-1];
//    }
//    return (inc==n || dec==n);
}

bool LC0844::backspaceCompare(string s, string t) {
    // 我们使用常数级的空间复杂度，就是说不能新建空的字符串来保存处理之后的结果，那么只能在遍历的过程中同时进行比较，只能使用双指针同时
    // 遍历S和T串了。我们采用从后往前遍历，因为退格是要删除前面的字符，所以倒序遍历要好一些。用变量i和j分别指向S和T串的最后一个字符的位置，
    // 然后还需要两个变量 cnt1 和 cnt2 来分别记录S和T串遍历过程中连续出现的井号的个数，因为在连续井号后，要连续删除前面的字母，
    // 如何知道当前的字母是否是需要删除，就要知道当前还没处理的退格符的个数。好，现在进行 while 循环，条件是i和j至少有一个要大于等于0，
    // 然后对S串进行另一个 while 循环，条件是当i大于等于0，且当前字符是井号，或者 cnt1 大于0，若当前字符是退格符，则 cnt1 自增1，
    // 否则 cnt1 自减1，然后i自减1，这样就相当于跳过了当前的字符，不用进行比较。对T串也是做同样的 while 循环处理。之后若i和j有一个小于0了，
    // 那么可以根据i和j是否相等的情况进行返回。否则再看若S和T串当前的字母不相等，则返回 false，因为当前位置的退格符已经处理完了，剩下的字母
    // 是需要比较相等的，若不相等就可以直接返回 false 了。最后当外层的 while 循环退出后，返回i和j是否相等
    int i=s.size()-1, j=t.size()-1, cnts=0, cntt=0;
    while(i>=0 || j>=0) {
        while (i >= 0 && (s[i] == '#' || cnts > 0)) s[i--] == '#' ? ++cnts : --cnts;
        while (j >= 0 && (t[j] == '#' || cntt > 0)) t[j--] == '#' ? ++cntt : --cntt;
        if (i < 0 || j < 0) return i == j;
        if (s[i--] != t[j--]) return false;
    }
    return i==j;

    // 新建一个结果 res 的空串，然后遍历输入字符串，当遇到退格符的时候，判断若结果 res 不为空，则将最后一个字母去掉；若遇到的是字母，
    // 则直接加入结果 res 中即可。这样S和T串同时处理完了之后，再进行比较即可
//    string strs{}, strt{};
//    for(auto &c:s) c=='#' ? strs.size() ? strs.pop_back() : void() : strs.push_back(c);
//    for(auto &c:t) c=='#' ? strt.size() ? strt.pop_back() : void() : strt.push_back(c);
//    return strs==strt;
}

vector<vector<int>> LC0830::largeGroupPositions(string s) {
    // 这道题给了我们一个全小写的字符串，说是重复出现的字符可以当作一个群组，如果重复次数大于等于3次，可以当作一个大群组，
    // 让我们找出所有大群组的起始和结束位置。那么实际上就是让我们计数连续重复字符的出现次数，由于要连续，所以我们可以使用双指针来做，
    // 一个指针指向重复部分的开头，一个往后遍历计数，只要不相同了就停止，然后看次数是否大于等3，是的话就将双指针位置存入结果res中，并更新指针
    vector<vector<int>> res;
    int n = s.size(), i=0, j=0;
    while(j<n) {
        while(j<n && s[j]==s[i]) j++;
        if(j-i>2) res.push_back({i,j-1});
        i=j;
    }
    return res;
}

vector<int> LC0821::shortestToChar(string s, char c) {
    // 对于每个是字符C的位置，然后分别像左右两边扩散，不停是更新距离，这样当所有的字符C的点都扩散完成之后，
    // 每个非字符C位置上的数字就是到字符C的最短距离了
    int n=s.size();
    vector<int> res(n,n);
    for(int i=0; i<n; i++) {
        if(s[i] != c) continue;
        res[i] = 0;
        for(int j=i-1; j>=0 && s[j]!=c; j--) {
            res[j] = min(res[j], i-j);
        }
        for(int j=i+1; j<n && s[j]!=c; j++) {
            res[j] = min(res[j], j-i);
        }
    }
    return res;

    // 下面这种方法也是建立距离场的思路，不过更加巧妙一些，只需要正反两次遍历就行。首先进行正向遍历，若当前位置是字符C，那么直接赋0，
    // 否则看如果不是首位置，那么当前位置的值等于前一个位置的值加1。这里不用和当前的值进行比较，因为这个算出来的值不会大于初始化的值。
    // 然后再进行反向遍历，要从倒数第二个值开始往前遍历，用后一个值加1来更新当前位置的值，此时就要和当前值做比较，取较小的那个
//    int n=s.size();
//    vector<int> res(n,n);
//    for(int i=0; i<n; i++) {
//        if(s[i]==c) res[i]=0;
//        else if(i>0) res[i]=res[i-1]+1;
//    }
//    for(int i=n-2; i>=0; i--)
//        res[i] = min(res[i], res[i+1]+1);
//    return res;
}

double LC0812::largestTriangleArea(vector<vector<int>>& points) {
    // 这道题给了我们一系列的二维平面上的点，让我们找出任意三个点能组成的最大三角形的面积。那么我们只能遍历所有的三角形面积，然后找出最大的那
    // 个。貌似这道题也没有啥特别简便的方法，不遍历不行啊。
    double res=0;
    for(auto &i:points)
        for(auto &j:points)
            for(auto &k:points)
                res = std::max(res, 0.5*std::abs(i[0] * j[1] +
                                                 j[0] * k[1] +
                                                 k[0] * i[1] -
                                                 i[0] * k[1] -
                                                 k[0] * j[1] -
                                                 j[0] * i[1] ));
    return res;
}

vector<int> LC0806::numberOfLines(vector<int>& widths, string s) {
    // 这道题给了我们一个字符串，让我们把里面的字母写下来，规定了每一行的长度为100，然后每个字母的长度可以在widths数组中查询，
    // 说是如果某一个字母加上后超过了长度100的限制，那么就移动到下一行，问我们最终需要多少行，和最后一行的长度。这道题并没有太大的难度和技巧，
    // 就是楞头写呗，遍历所有的字母，然后查表得到其宽度，然后看加上这个新宽度是否超了100，超了的话，行数计数器自增1，
    // 并且当前长度为这个字母的长度，因为另起了一行。如果没超100，那么行长度就直接加上这个字母的长度。遍历完成后返回行数和当前行长度即可
    int l=1, n=0;
    for(auto &c:s) {
        int w = widths[c - 'a'];
        l = (n+w>100) ? l+1 : l;
        n = (n+w>100) ? w : n+w;
    }
    return vector<int> {l,n};
}

int LC0724::pivotIndex(vector<int>& nums) {
    // 给了我们一个数组，让我们求一个中枢点，使得该位置左右两边的子数组之和相等。这道题难度不大，直接按题意去搜索就行了，因为中枢点可能出现的
    // 位置就是数组上的位置，所以我们搜索一遍就可以找出来，我们先求出数组的总和，然后维护一个当前数组之和curSum，然后对于遍历到的位置，用总
    // 和减去当前数字，看得到的结果是否是curSum的两倍，是的话，那么当前位置就是中枢点，返回即可；否则就将当前数字加到curSum中继续遍历，遍
    // 历结束后还没返回，说明没有中枢点，返回-1即可
    int cur=0, sum=std::accumulate(nums.begin(), nums.end(), 0);
    for(int i=0; i<nums.size(); i++) {
        if(sum-nums[i]==2*cur) return i;
        cur += nums[i];
    }
    return -1;
}

int LC0682::calPoints(vector<string>& operations) {
    // Integer (one round's score): Directly represents the number of points you get in this round.
    // "+" (one round's score): Represents that the points you get in this round are the sum of the last two validround's points.
    // "D" (one round's score): Represents that the points you get in this round are the doubled data of the last valid round's points.
    // "C" (an operation, which isn't a round's score): Represents the last valid round's points you get were invalid and should be removed.
    // 直接按照题目的描述来分情况处理即可，博主开始在取数组的最后一个数和倒数第二个数的时候还做了数组为空检测，但是的貌似这道题默认
    // 输入都是合法的，不会存在上一轮不存在还要取值的情况，那就不用检测
    vector<int> v;
    for(auto &op:operations) {
        if(op == "+") {
            v.push_back(v[v.size()-1] + v[v.size()-2]);
        }else if(op == "D") {
            v.push_back(v[v.size()-1] * 2);
        }else if(op == "C") {
            v.pop_back();
        } else {
            v.push_back(std::stoi(op));
        }
    }
    return std::accumulate(v.begin(), v.end(), 0);
}

bool LC0657::judgeCircle(string moves) {
    // 使用了哈希表来建立字符和其出现的次数之间的映射，最后直接比较对应的字符出现的次数是否相等即可
    array<int,26> map; map.fill(0);
    for(auto &c:moves)
        ++map[c-'A'];
    return map['U'-'A']==map['D'-'A'] && map['L'-'A']==map['R'-'A'];

    // 使用两个计数器，如果是U，则cnt1自增1；如果是D，cnt1自减1。同理，如果是L，则cnt1自增1；如果是R，cnt1自减1。
    // 最后只要看cnt1和cnt2是否同时为0即可
//    int u=0, l=0;
//    for(auto &c:moves) {
//        if(c=='U') u++;
//        else if(c=='D') u--;
//        else if(c=='L') l++;
//        else if(c=='R') l--;
//    }
//    return !u && !l ;
}

int LC0674::findLengthOfLCIS(vector<int>& nums) {
    // 这道题让我们求一个数组的最长连续递增序列，由于有了连续这个条件，跟之前那道 Number of Longest Increasing Subsequence 比起来，
    // 其实难度就降低了很多。可以使用一个计数器，如果遇到大的数字，计数器自增1；如果是一个小的数字，则计数器重置为1。用一个变量 cur 来表示
    // 前一个数字，初始化为整型最大值，当前遍历到的数字 num 就和 cur 比较就行了，每次用 cnt 来更新结果 res
//    int res=0, cnt=0, cur=INT_MAX;
//    for(auto &num:nums) {
//        if(num>cur) cnt++;
//        else cnt=1;
//        res = std::max(res, cnt);
//        cur = num;
//    }
//    return res;

    // 下面这种方法的思路和上面的解法一样，由於每次都和前面一个数字来比较，是可以省略cur變數。注意处理无法取到钱一个数字的情况
    int res=1, cnt=1;
    for(int i=1; i<nums.size(); ++i)
        (nums[i]>nums[i-1]) ? res = std::max(res, ++cnt) : cnt=1;
    return res;
}

double LC0643::findMaxAverage(vector<int>& nums, int k) {
    // 这道题给了我们一个数组nums，还有一个数字k，让我们找长度为k且平均值最大的子数组。由于子数组必须是连续的，所以我们不能给数组排序。计算
    // 子数组之和的常用方法应该是建立累加数组，然后我们可以快速计算出任意一个长度为k的子数组，用来更新结果res，从而得到最大的那个
//    const int n=nums.size();
//    vector<int> sum(n);
//
//    sum[0] = nums[0];
//    for(int i=1; i<n; i++)
//        sum[i] = sum[i-1] + nums[i];
//
//    double mx = sum[k-1]; // 需用double
//    for(int i=k; i<n; i++)
//        mx = std::max(mx, (double)sum[i]-sum[i-k]); // 需用double
//
//    return mx/k;

    // 由于这道题子数组的长度k是确定的，所以我们其实没有必要建立整个累加数组，而是先算出前k个数字的和，然后就像维护一个滑动窗口一样，将窗口向
    // 右移动一位，即加上一个右边的数字，减去一个左边的数字，就等同于加上右边数字减去左边数字的差值，然后每次更新结果res即可
    // 需用double
    double sum=std::accumulate(nums.begin(), nums.begin()+k, 0), res=sum;
    for(int i=k; i<nums.size(); i++) {
        sum += nums[i] - nums[i-k];
        res = std::max(res, sum);
    }
    return res/k;
}

int LC0598::maxCount(int m, int n, vector<vector<int>>& ops) {
    // 每次在 ops 中给定我们一个横纵坐标，将这个子矩形范围内的数字全部自增1，让我们求最大数字的个数。原数组初始化均为0，那么如果 ops 为空，
    // 没有任何操作，那么直接返回 m*n 即可，每次用 ops 中的值来更新m和n，取其中较小值，这样遍历完成后，m和n就是最大数矩阵的边界了
    for(auto &op:ops) {
        m = min(m, op[0]);
        n = min(n, op[1]);
    }
    return m*n;
}

string LC0557::reverseWords(string s) {
    // 用两个指针，分别指向每个单词的开头和结尾位置，确定了单词的首尾位置后，再用两个指针对单词进行首尾交换即可，有点像验证回文字符串的方法
    int start=0, end=0, n = s.size();
    while(start<n && end<n) {
        while(end<n && s[end]!=' ') end++;
        for(int i=start, j=end-1; i<j;  )
            swap(s[i++], s[j--]);
        start = ++end;
    }
    return s;
}

bool LC0551::checkRecord(string s) {
    // 判断学生的出勤率是否是优秀，判断标准是不能缺勤两次和不能连续迟到三次，那么最直接的方法就是分别记录缺勤和连续迟到的次数，
    // 如果当前遇到缺勤，那么缺勤计数器自增1，如果此时次数大于1了，说明已经不是优秀了，直接返回false，否则连续迟到计数器清零。
    // 如果当前遇到迟到，那么连续迟到计数器自增1，如果此时连续迟到计数器大于1了，说明已经不是优秀了，直接返回false。如果遇到正常出勤了，
    // 那么连续迟到计数器清零
    int a=0, l=0;
    for(auto c:s) {
        if (c == 'L') {
            if (++l > 2) return false;
        } else {
            l=0;
            if(c=='A' && ++a > 1) return false;
        }
    }
    return true;

    // 使用正则匹配来做的解法，我们找出不合题意的情况，然后取反即可，正则匹配式是A.*A|LLL，其中.*表示有零个或者多个，
    // 那么A.*A就是至少有两A的情况，LLL是三个连续的迟到，|表示两个是或的关系，只要能匹配出任意一种情况，就会返回false
    // !處理時間會長很多!
    // return !regex_search(s, regex("A.*A|LLL"));
}

string LC0541::reverseStr(string s, int k) {
    // 每2k个字符来遍历原字符串s，然后进行翻转，翻转的结尾位置是取i+k和末尾位置之间的较小值
    for(int i=0; i<s.size(); i+=2*k) {
        reverse(s.begin()+i, min(s.begin()+i+k, s.end()));
    }
    return s;
}

int LC0485::findMaxConsecutiveOnes(vector<int>& nums) {
    // 求最大连续1的个数。历一遍数组，用一个计数器 cnt 来统计1的个数，方法是如果当前数字为0，那么 cnt 重置为0，如果不是0，cnt 自增1，
    // 然后每次更新结果 res 即可
    int res=0, cnt=0;
    for(auto &n:nums) {
        if(n)
        { cnt++; }
        else
        { res = max(res,cnt); cnt=0; }
    }
    return max(res,cnt); // 最後可能連續1結束，需再做一次max

    // 由于是个二进制数组，所以数组中的数字只能是0或1，那么连续1的和跟个数相等，所以可以计算和，通过加上 num，再乘以 num 来计算，如果当前数
    // 字是0，那么 sum 就被重置为0，还是要更新结果 res
//    int res=0, sum=0;
//    for(auto &n:nums) {
//        sum = (sum+n)*n;
//        res = max(res, sum);
//    }
//    return res;
}

int LC0414::thirdMax(vector<int>& nums) {
    // 这道题让我们求数组中第三大的数，如果不存在的话那么就返回最大的数，题目中说明了这里的第三大不能和第二大相同，必须是严格的小于，而并非小
    // 于等于。这道题并不是很难，如果知道怎么求第二大的数，那么求第三大的数的思路都是一样的。那么我们用三个变量first, second, third来分别
    // 保存第一大，第二大，和第三大的数，然后我们遍历数组，如果遍历到的数字大于当前第一大的数first，那么三个变量各自错位赋值，如果当前数字大
    // 于second，小于first，那么就更新second和third，如果当前数字大于third，小于second，那就只更新third，注意这里有个坑，就是初始化要
    // 用长整型long的最小值，否则当数组中有INT_MIN存在时，程序就不知道该返回INT_MIN还是最大值first了
    long first=LONG_MIN, second=LONG_MIN, third=LONG_MIN;
    for(auto &n:nums) {
        if(n > first) {
            third=second;
            second=first;
            first=n;
        } else if(n > second && n < first) {
            third=second;
            second=n;
        } else if(n > third && n < second) {
            third=n;
        }
    }
    return (third==LONG_MIN || third==second) ? first : third;
}

void LC0344::reverseString(vector<char>& s) {
    int l=0, r=s.size()-1;
    while(l<r)
        swap(s[l++],s[r--]);
}

vector<string> LC0228::summaryRanges(vector<int>& nums) {
    // 这道题给定我们一个有序数组，让我们总结区间，具体来说就是让我们找出连续的序列，然后首尾两个数字之间用个“->"来连接，那么我只需遍历一遍数
    // 组即可，每次检查下一个数是不是递增的，如果是，则继续往下遍历，如果不是了，我们还要判断此时是一个数还是一个序列，一个数直接存入结果，
    // 序列的话要存入首尾数字和箭头“->"。我们需要两个变量i和j，其中i是连续序列起始数字的位置，j是连续数列的长度，当j为1时，说明只有一个数字，
    // 若大于1，则是一个连续序列
    vector<string> res;
    int i=0, n=nums.size();
    while(i<n) {
        int j=1;
        while(i+j<n && (long)nums[i+j]-nums[i]==j) j++; //需要用long是因為可能有正大數減負大數的情況
        res.push_back(j==1 ? to_string(nums[i]) : to_string(nums[i]) + "->" + to_string(nums[i+j-1]));
        i+=j;
    }
    return res;
}

int LC0169::majorityElement(vector<int>& nums) {
    // 将第一个数字假设为过半数，然后把计数器设为1，比较下一个数和此数是否相等，若相等则计数器加一，
    // 反之减一。然后看此时计数器的值，若为零，则将下一个值设为候选过半数。以此类推直到遍历完整个数组，
    // 当前候选过半数即为该数组的过半数。
    // 为啥遇到不同的要计数器减1呢，为啥减到0了又要更换候选者呢？首先是有那个强大的前提存在，
    // 一定会有一个出现超过半数的数字存在，那么如果计数器减到0了话，说明目前不是候选者数字的个数已经跟候选者的出现个数相同了，
    // 那么这个候选者已经很 weak，不一定能出现超过半数，此时选择更换当前的候选者。那有可能你会有疑问，
    // 那万一后面又大量的出现了之前的候选者怎么办，不需要担心，如果之前的候选者在后面大量出现的话，其又会重新变为候选者，
    // 直到最终验证成为正确的过半数
    int val=0, cnt=0;
    for(auto n:nums) {
        if(!cnt) {
            val = n;
            cnt++;
        } else {
            (val==n) ? cnt++ : cnt--;
        }
    }
    return val;
}

int LC0122::maxProfit(vector<int>& prices) {
    // 由于可以无限次买入和卖出。我们都知道炒股想挣钱当然是低价买入高价抛出，那么这里我们只需要从第二天开始，如果当前价格比之前价格高，则把差
    // 值加入利润中，因为我们可以昨天买入，今日卖出，若明日价更高的话，还可以今日买入，明日再抛出。以此类推，遍历完整个数组后即可求得最大利润
    int prf=0;
    for(int i=0; i<prices.size()-1; ++i)
        if(prices[i+1] > prices[i])
            prf += (prices[i+1] - prices[i]);
    return prf;
}

int LC0121::maxProfit(vector<int>& prices) {
    // 只需要遍历一次数组，用一个变量记录遍历过数中的最小值，然后每次计算当前值和这个最小值之间的差值最为利润，然后每次选较大的利润来更新。
    // 当遍历完成后当前利润即为所求
    int buy=INT_MAX, prf=0;
    for(int &price:prices) {
        buy = std::min(buy, price);
        prf = std::max(prf, price-buy);
    }
    return prf;
}

vector<int> LC0119::getRow(int rowIndex) {
    // 除了第一个和最后一个数字之外，其他的数字都是上一行左右两个值之和。那么我们只需要两个 for 循环，除了第一个数为1之外，后面的数都是上一次
    // 循环的数值加上它前面位置的数值之和，不停地更新每一个位置的值，便可以得到第n行的数字
    vector<int> res(rowIndex+1, 0);
    res[0] = 1;
    for(int i=1; i<=rowIndex; ++i)
        for(int j=i; j>=1; --j)
            res[j] += res[j-1];
    return res;
}

vector<vector<int>> LC0118::generate(int numRows) {
    // 杨辉三角是二项式系数的一种写法，如果熟悉杨辉三角的五个性质，那么很好生成，可参见我的上一篇博文Pascal's Triangle II。具体生成算是：
    // 每一行的首个和结尾一个数字都是1，从第三行开始，中间的每个数字都是上一行的左右两个数字之和。
    vector<vector<int>> res(numRows, vector<int>());
    for(int i=0; i<numRows; ++i) {
        res[i].resize(i+1, 1);
        for(int j=1; j<i; ++j)
            res[i][j] = res[i-1][j] + res[i-1][j-1];
    }
    return res;
}

//LC0066 run;
//vector<int> nums{9,9,9}, ans;
//ans=run.plusOne(nums);
//for(auto n:nums) cout << n << ' ';
//cout << endl;
vector<int> LC0066::plusOne(vector<int>& digits) {
    // 将一个数字的每个位上的数字分别存到一个一维向量中，最高位在最开头，我们需要给这个数字加一，即在末尾数字加一
    // 将 carry 初始化为1，然后相当于 digits 加了一个0，处理方法跟之前那道题一样
    int c=1, n=digits.size();
    for(int i=n-1; i>=0; --i) {
        c += digits[i];
        digits[i] = c%10;
        c /= 10;
        if(!c) return digits; // 沒有可進的位，那就可以先return了
    }
    if(c)
        digits.emplace(digits.begin(), c);
    return digits;
}