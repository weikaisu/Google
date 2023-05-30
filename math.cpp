
#include "math.h"

bool LC0326::isPowerOfThree(int n) {
    // 让我们判断一个数是不是3的次方数，在LeetCode中，有一道类似的题目Power of Two，那道题有个非常简单的方法，由于2的次方数实在太有特点，
    // 最高位为1，其他位均为0，所以特别容易，而3的次方数没有显著的特点，最直接的方法就是不停地除以3，看最后的迭代商是否为1，要注意考虑输入是
    // 负数和0的情况
    while(n>1) {
        if(n%3) return false;
        else n/=3;
    }
    return n==1;

    // 不用循环，那么有一个投机取巧的方法，由于输入是int，正数范围是0-231，在此范围中允许的最大的3的次方数为319=1162261467，那么我们只
    // 要看这个数能否被n整除即可
//    return (n>0 && 1162261467%n == 0);

    // 利用对数的换底公式来做，高中学过的换底公式为logab = logcb / logca，那么如果n是3的倍数，则log3n一定是整数，我们利用换底公式可以写
    // 为log3n = log10n / log103，注意这里一定要用10为底数，不能用自然数或者2为底数，否则当n=243时会出错，原因请看这个帖子。现在问题就
    // 变成了判断log10n / log103是否为整数，在c++中判断数字a是否为整数，我们可以用 a - int(a) == 0 来判断
//    return (n>0 && !(std::log10(n)/std::log10(3) - int(std::log10(n)/std::log10(3)) ));
}

bool LC0292::canWinNim(int n) {
    // 给我们一堆石子，每次可以拿一个两个或三个，两个人轮流拿，拿到最后一个石子的人获胜，现在给我们一堆石子的个数，问我们能不能赢。那么我们
    // 就从最开始分析，由于是我们先拿，那么3个以内(包括3个)的石子，我们直接赢，如果共4个，那么我们一定输，因为不管我们取几个，下一个人一次
    // 都能取完。如果共5个，我们赢，因为我们可以取一个，然后变成4个让别人取，根据上面的分析我们赢，所以我们列出1到10个的情况如下
    // 1    Win
    // 2    Win
    // 3    Win
    // 4    Lost
    // 5    Win
    // 6    Win
    // 7    Win
    // 8    Lost
    // 9    Win
    // 10   Win
    // 由此我们可以发现规律，只要是4的倍数个，我们一定会输，所以对4取余即可

    return n%4;

    // 讨论：我们来generalize一下这道题，当可以拿1～n个石子时，那么个数为(n+1)的整数倍时一定会输，我们试着证明一下这个结论，
    // 若当前共有m*(n+1)个石子，那么：
    //
    // 当m=1时，即剩n+1个的时候，肯定会输，因为不管你取1～n中的任何一个数字，另一个人都可以取完。
    //
    // 当m>1时，即有m*(n+1)的时候，不管你先取1～n中的任何一个数字x，另外一个人一定会取n+1-x个，这样总数就变成了(m-1)*(n+1)，
    // 第二个人就一直按这个策略取，那么直到剩n+1个的时候，就便变成m=1的情况，一定会输。
}

bool LC0263::isUgly(int n) {
    // 这道题让我们检测一个数是否为丑陋数，所谓丑陋数就是其质数因子只能是 2，3，5。那么最直接的办法就是不停的除以这些质数，如果剩余的数字
    // 是1的话就是丑陋数了。
    // 此方法性能較好，可以當非丑陋数時會更快回傳。
    while (n >= 2) {
        if (n%2 == 0) n /= 2;
        else if (n%3 == 0) n /=3;
        else if (n%5 == 0) n /=5;
        else return false;
    }
    return n == 1;

    // 也可以换一种写法，分别不停的除以 2，3，5，并且看最后剩下来的数字是否为1即可
//    if(n <= 0) return false;
//    while(n%2 == 0) n/=2;
//    while(n%3 == 0) n/=3;
//    while(n%5 == 0) n/=5;
//    return n==1;
}

int LC0258::addDigits(int num) {
    // 求数根，所谓树根，就是将大于10的数的各个位上的数字相加，若结果还大于0的话，则继续相加，直到数字小于10为止
    while(num >= 10) {
        int sum=0;
        while(num) {
            sum += num%10;
            num /= 10;
        }
        num = sum;
    }
    return num;

    // 用recursive的方式
//    int res = 0;
//    while(num) {
//        res += num%10;
//        num /= 10;
//    }
//    if(res > 9) return addDigits(res);
//    else return res;

    // 先来观察1到20的所有的树根：
    // 1    1
    // 2    2
    // 3    3
    // 4    4
    // 5    5
    // 6    6
    // 7    7
    // 8    8
    // 9    9
    // 10    1
    // 11    2
    // 12    3
    // 13    4
    // 14    5
    // 15    6
    // 16    7
    // 17    8
    // 18    9
    // 19    1
    // 20    2
    //根据上面的列举，我们可以得出规律，每9个一循环，所有大于9的数的树根都是对9取余，那么对于等于9的数对9取余就是0了，为了得到其本身，而且同
    // 样也要对大于9的数适用，我们就用(n-1)%9+1这个表达式来包括所有的情况。还有个特殊情况需要考虑一下，当num为0的时候，那么就会出现 -1 % 9
    // 的情况，这个其实挺烦人的，因为C++和Java会给出商0余-1的结果，而Python会给出商-1余8的结果，博主搜了一下，好像是说当有一个负数存在的时
    // 候，C++/Java会尽可能让商大一些，而Python会让商小一些，所以结果不统一就神烦，那么只好做个额外判断了，特殊处理一下0的情况就OK了

    // return (num == 0) ? num : (num-1)%9 + 1;
}

//LC0171 run;
//string s = "A";
//cout << run.titleToNumber(s) << endl;
int LC0171::titleToNumber(string columnTitle) {
    // 这题实际上相当于一种二十六进制转十进制的问题
    // 26 -> 10
    // 其他進位轉十進位：將二進位數、十六進位數的各位數字分別乘以各自基數的(N-1)次方，其相加之和便是相應的十進位數，這是按權相加法。
    int n = columnTitle.size();
    double m = 1;
    double r = 0;

    while(n > 0) {
        r += (columnTitle[n-1]-'A'+1) * m;
        n--;
        m *= 26;
    }
    return static_cast<int> (r);
}

string LC0168::convertToTitle(int columnNumber) {
    // 这题实际上相当于一种十进制转二十六进制的问题
    // 10 -> 26
    // 整數部分用除基取余法，小數部分用乘基取整法，然後將整數與小數部分拼接成一個數作為轉換的最後結果
    // 先让n自减1，变成25，然后再对26取余，得到25，此时再加上字符A，就可以得到字符Z了。叼就叼在这对其他的不能整除26的数也是成立的，完美解决问题
    string res {};
    int n = columnNumber;
    while(n) {
        res += --n % 26 + 'A';
        n/=26;
    }
    return string(res.rbegin(), res.rend());

    // recursive way 結果是錯的，得先計算n%26再計算n/26%, 遞歸的話會顛倒！
//    int n = columnNumber;
//    //return n ? convertToTitle(n/26) + (char)(--n % 26 + 'A') : "";
//    string res {};
//    if(n) {
//        string l = convertToTitle(n/26);
//        string r = string(1, char(--n % 26 + 'A'));
//        res = l + r;
//    } else {
//        res = "";
//    }
//    return res;
}

//LC0007 run;
//cout << run.reverse(-2147483648) << endl;
int LC0007::reverse(int x) {
    int ans{0}, max{INT32_MAX/10}, min{INT32_MIN/10};
    while(x) {
        if( ans>max || ans<min ) return 0;
        ans = ans*10 + x%10;
        x/=10;
    }
    return ans;
}