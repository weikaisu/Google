
#include "math.h"

bool LC1037::isBoomerang(vector<vector<int>>& points) {
    // 定义了一种回旋镖就是不在同一条直线上的三个点，现在给了同一平面上的三个点，让判断能否组成一个回旋镖。实际上就是初中的几何问题，判断三点
    // 是否共线，忘记了的话估计不太容易做出来，虽然只是道 Easy 的题目。我们都知道两点能确定一条直线，那么对于三个点 p1，p2，和 p3，
    // 只要 p1 和 p2 连接而成的直线和 p1 和 p3 连接而成的直线重合，则表示三点共线。如何判断直线重合呢，最简单的方法就是看斜率是否相等，
    // 知道了两个点求斜率也很简单，只要满足 (y3 - y1) / (x3 - x1) = (y2 - y1) / (x2 - x1)，就表示三点共线，换成乘法形式的就是
    // (y3 - y1) * (x2 - x1) = (y2 - y1) * (x3 - x1)，而题目中说的回旋镖就是三点不共线的情况，将这里的等号换成不等号即可
    return ((points[2][1] - points[0][1]) * (points[1][0] - points[0][0])) !=
           ((points[1][1] - points[0][1]) * (points[2][0] - points[0][0]));
}

bool LC0836::isRectangleOverlap(vector<int>& rec1, vector<int>& rec2) {
    // 求两个矩形是否是重叠，矩形的表示方法是用两个点，左下和右上点来定位的。
    // rec1 [x1, y1, x2, y2], rec2 [x3, y3, x4, y4]
    // 两个矩形在矩形1的右上角重叠 x1<x4 && x3<x2 && y1<y4 && y3<y2
    return rec1[0] < rec2[2] && rec2[0] < rec1[2] && rec1[1] < rec2[3] && rec2[1] < rec1[3];
    // 两个矩形在矩形1的左上角重叠 x3<x2 && x1<x4 && y1<y4 && y3<y2
    // 两个矩形在矩形1的左下角重叠 x3<x2 && x1<x4 && y3<y2 && y1<y4
    // 两个矩形在矩形1的右下角重叠 x1<x4 && x3<x2 && y3<y2 && y1<y4
    // 上面四种情况的满足条件其实都是相同的，只不过顺序调换了位置，所以我们只要一行就可以解决问题了
}

vector<int> LC0728::selfDividingNumbers(int left, int right) {
    // 找一个给定范围内的所有的自整除数字，所谓的自整除数字就是该数字可以整除其每一个位上的数字。既然这道题是Easy类，那么一般来说不需要
    // 用tricky的方法，直接暴力搜索就行了，遍历区间内的所有数字，然后调用子函数判断其是否是自整除数，是的话就加入结果res中。在子函数中，
    // 我们先把数字转为字符串，然后遍历每个字符，只要其为0，或者num无法整除该位上的数字，就返回false，循环结束后返回true
    vector<int> res;
    for(int num=left; num<=right; ++num) {
        int n=0;
        for (n = num; n > 0; n /= 10)
            if((n%10==0) || (num%(n%10) != 0)) break;
        if(n==0) res.push_back(num);
    }
    return res;
}

bool LC0507::checkPerfectNumber(int num) {
    // 让我们判断给定数字是否为完美数字，并给来完美数字的定义，就是一个整数等于除其自身之外的所有的因子之和。那么由于不能包含自身，所以n必
    // 定大于1。其实这道题跟之前的判断质数的题蛮类似的，都是要找因子。由于1肯定是因子，可以提前加上，那么我们找其他因子的范围是[2, sqrt(n)]。
    // 我们遍历这之间所有的数字，如果可以被n整除，那么我们把i和num/i都加上，对于n如果是平方数的话，那么我们此时相同的因子加来两次，所以我们
    // 要判断一下，如果相等，就不再加 num/i。实际上，符合要求的完美数字很少，根本就没有完全平方数，我们根本就不用担心会加两次，当然，这都是
    // 从结果分析的，为了严格按照题目的要求，还是加上判断吧。还有就是我们也可以在遍历的过程中如果累积和sum大于n了，直接返回false，但是感觉
    // 加了也没咋提高运行时间，所以干脆就不加了。在循环结束后，我们首先判断num是否为1，因为题目中说了不能加包括本身的因子，然后我们再看sum
    // 是否和num相等
    int sum=1;
    for (int i=2; i*i<=num; i++)
        if (num % i == 0)
            sum += (i + ((num / i == i) ? 0 : num / i));
    return num!=1 && sum==num;

    // 在给定的n的范围内其实只有五个符合要求的完美数字，于是就有这种枚举的解法
    // return num == 6 || num == 28 || num == 496 || num == 8128 || num == 33550336;
}

string LC0504::convertToBase7(int num) {
    // 给了我们一个数，让我们转为七进制的数，而且这个可正可负。那么我们想如果给一个十进制的100，怎么转为七进制。我会先用100除以49，
    // 商2余2。在除以7，商0余2，于是就得到七进制的202。其实我们还可以反过来算，先用100除以7，商14余2，然后用14除以7，商2余0，
    // 再用2除以7，商0余2，这样也可以得到202。这种方法更适合于代码实现，要注意的是，我们要处理好负数的情况
//    if(!num) return "0";
//    string res{};
//    bool sign = num > 0;
//    num = std::abs(num);
//    while(num) {
//        res = std::to_string(num%7) + res;
//        num /= 7;
//    }
//    return sign ? res : "-" + res;

    // recursive way, 兩者跑起來性能一樣
    if(num < 0) return "-" + convertToBase7(std::abs(num));
    if(num < 7) return std::to_string(num);
    return convertToBase7(num/7) + std::to_string(num%7);
}

vector<int> LC0492::constructRectangle(int area) {
    // 根据面积来求出矩形的长和宽，要求长和宽的差距尽量的小，那么就是说越接近正方形越好。那么我们肯定是先来判断一下是不是正方行，对面积开方，
    // 如果得到的不是整数，说明不是正方形。那么我们取最近的一个整数，看此时能不能整除，如果不行，就自减1，再看能否整除。最坏的情况就是面积是
    // 质数，最后减到了1，那么返回结果即可
//    int r = std::sqrt(area);
//    while(area%r != 0) r--;
//    return {area/r, r};

    // 不想用开方运算sqrt的话，那就从1开始，看能不能整除，循环的终止条件是看平方值是否小于等于面积。會比使用sqrt性能更好。
    int res=1;
    for (int i=1; i*i<=area; i++)
        if(area%i == 0) res=i;
    return {area/res, res};
}

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

//cout << run.romanToInt("MCMXCIV") << endl;
int LC0013::romanToInt(string s) {
    // Given a roman numeral, convert it to an integer.
    unordered_map<char, int> map {
            {'M', 1000}, {'D', 500},
            {'C', 100},  {'L', 50},
            {'X', 10},   {'V', 5},
            {'I', 1} };

    int res=0, n=s.size();
    for(int i=0; i<n-1; ++i) {
        char c=s[i], c_nxt=s[i+1];
        if(map[c] < map[c_nxt]) res -= map[c];
        else res += map[c];
    }
    return res + map[s[n-1]];
}

//cout << run.isPalindrome(1000000001) << endl;
bool LC0009::isPalindrome(int x) {
    if(x<0) return false;

    int front=x, back=0;
    while(x>0 && back<INT_MAX/10) { // 下一行要*10，所以這一行檢查是否小於INT_MAX/32
        back = back*10 + x%10;
        x/=10;
    }
    return front == back;
}

int LC0007::reverse(int x) {
    // Given a signed 32-bit integer x, return x with its digits reversed. If reversing x causes the value to go outside
    // the signed 32-bit integer range [-231, 231 - 1], then return 0.
    // Input: x = 123
    // Output: 321
    // Input: x = -123
    // Output: -321
    int res=0;
    while(x) {
        if(std::abs(res) > INT_MAX/10) return 0; // 下一行要*10，所以這一行檢查是否小於INT_MAX/32
        res = res*10 + x%10;
        x /= 10;
    }
    return res;
}