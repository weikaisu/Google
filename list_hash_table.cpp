#include "list.h"

/***********  Hash Table  **********/
int LC1684::countConsistentStrings(string allowed, vector<string>& words) {
    // Input: allowed = "ab", words = ["ad","bd","aaab","baa","badab"]
    // Output: 2
    // Explanation: Strings "aaab" and "baa" are consistent since they only contain characters 'a' and 'b'.
    // You are given a string allowed consisting of distinct characters and an array of strings words.
    // A string is consistent if all characters in the string appear in the string allowed.
    // Return the number of consistent strings in the array words.
    // 用std::count_if, 更快
    array<bool,128> set; set.fill(false);
    for(auto &c:allowed)
        set[c] = true;
    return std::count_if(words.begin(), words.end(), [&](const string& word) -> bool {
        for(auto & w:word)
            if(!set[w]) return false;
        return true;
    });

    // 用std::all_of
//    array<int, 128> set; set.fill(0);
//    for(auto &c:allowed)
//        set[c] = 1;
//    int res=0;
//    for(auto &w:words)
//        res += std::all_of(w.begin(), w.end(), [&](char c) -> bool { return set[c]; });
//    return res;
}
bool LC1207::uniqueOccurrences(vector<int>& arr) {
    // 这道题给了一个整型数组，问每个数字出现的次数都否都不同。用个 HashMap 来统计每个数字出现的次数，然后再用个 HashSet 来判断某个次数是
    // 否之前出现过了，若出现过了，则返回 false，否则最终返回 true 即可
    unordered_map<int,int> m;
    unordered_set<int> s;
    for(auto &e:arr) ++m[e];
    for(auto &e:m) {
        if(s.count(e.second)) return false;
        s.insert(e.second);
    }
    return true;
}

int LC1189::maxNumberOfBalloons(string text){
    // 找出能從特定字串裡的字符拼出目標字串的數量
    // 用一个 HashMap 来建立每个字符和其出现次数之间的映射就可以了。balloon 中的字符 b，a，n 分别出现了一次，l和o出现了两次，怎么算最多
    // 能拼成多个 balloon 呢，当然要找这些字符出现次数最少的那个，就像木桶盛水一样，最短的那个板子决定了盛水总量。然后遍历 balloon
    // 中的每个字符，取其中的最小值，注意对于l和o字符要将次数除以2，因为它们分别都出现了2次，最终返回这个最小值即可

    // 較慢，可能是用到了除法和min
//    array<int,32> m; m.fill(0);
//    for(auto &c:text) ++m[c - 'a'];
//    int res = INT_MAX;
//    for(auto &c:string("balloon")) {
//        if (c == 'l' || c == 'o') res = min(res, m[c - 'a'] / 2);
//        else res = min(res, m[c - 'a']);
//    }
//
//    return res;

    // 較快
    array<int,32> m; m.fill(0);
    int res = 0;
    for(auto &c:text) ++m[c - 'a'];
    while(true) {
        if((m['b'-'a']-=1) < 0 || (m['a'-'a']-=1) <0 || (m['l'-'a']-=2) < 0 || (m['o'-'a']-=2) < 0 || (m['n'-'a']-=1) < 0)
            break;
        res++;
    }
    return res;
}

int LC1160::countCharacters(vector<string>& words, string chars) {
    // 找出能從特定字串裡的字符拼出字串的長度
    // 一个单纯的字母统计问题，建立 chars 字符串中每个字母和其出现次数之间的映射，然后遍历每个单词，拷贝一个 chars 字符串的 HashMap，
    // 然后遍历当前单词的每个字母，对应字母的映射值减1，若为负数了，表示 chars 中缺少必要的单词，标记为 false。若最终为 true，
    // 则将当前单词的长度加入结果 res 中即可
    // 由於只有小寫字母，用大小26的陣列即可，而用大小32的速度會快很多。
    array<int,32> map; map.fill(0);
    int res = 0;
    for(auto &c:chars) ++map[c-'a'];
    for(auto &w:words) {
        array<int,32> m = map;
        bool good = true;
        for(auto &c:w)
            if(--m[c-'a']<0) {good=false;break;}
        if(good) res+=w.size();
    }
    return res;
}

int LC1128::numEquivDominoPairs(vector<vector<int>>& dominoes) {
    // 这道题给了一个多米诺数组，每个多米诺有两个数字，现在让找有多少个相同的多米诺，由于多米诺可以旋转，所以这里两个数字的顺序并不重要。
    // 虽然说是一道简单的题目，但是暴力搜索法还是不可取的，太不高效了，最好的还是直接统计相同的牌的数量，再来计算相同的 pair 对儿个数。
    // 若多米诺不能翻转，直接进行统计就行了，现在能翻转，就要统一用个方法来标记翻转后相同的多米诺，这里可以始终将小的放在前面。
    // 又由于数字只有1到9，所以可以把较小的数字编码到十位上，较大的数字编码到个位上，这样组成的两位数就可以表示独特的多米诺了。
    // 统计完相同的多米诺个数之后就可以计算相同的 pair 对儿了，若有n个相同的多米诺，则共有 n(n-1)/2 个相同的 pair 对儿，
    // 这样就可以算出总共相同的 pair 对儿个数了

    // C n 取 2 = n(n-1)/2
//    unordered_map<int,int> dict;
//    int res = 0;
//    for(auto &p:dominoes)
//        ++dict[ 10*min(p[0],p[1]) + max(p[0],p[1])];
//    for(auto &d:dict)
//        res += (d.second)*(d.second-1)/2; // C n 取 2
//    return res;

    // n(n-1)/2 = 1+2+3+...(n-1)
    unordered_map<int,int> dict;
    int res = 0;
    for(auto &p:dominoes)
        res += dict[ 10*min(p[0],p[1]) + max(p[0],p[1])]++;
    return res;
}
vector<int> LC1122::relativeSortArray(vector<int>& arr1, vector<int>& arr2) {
    // 根據另一陣列裡的相對順序排做排序
    // 有两个数组 arr1 和 arr2，其中 arr2 中的所有数字均在 arr1 中，现在让给 arr1 重新排序，使得其按照 arr2 中数字的顺序排列，将不在
    // arr2 中的数字按照大小顺序排在末尾，题目中给的例子可以很好的帮助我们理解题意。由于 arr1 中可能出现重复数字，而相同的数字是要排在一起
    // 的，所以需要统计 arr1 中每个数字出现的次数，又因为最后还需要将不在 arr2 中的数字按顺序排列，那么这里用个 TreeMap 是坠好的，
    // 既能统计个数，又能排序，简直太棒了。用 TreeMap 统计好 arr1 中数字的个数之后，然后遍历 arr2，将其中每个数字在之前的 TreeMap
    // 中找到对应的次数，并在结果 res 中加入相同次数的数字进去，之后在 TreeMap 中移除该数字。这样遍历完 arr2 之后，在 TreeMap
    // 中剩下的数字就是仅存在于 arr1 的，且还是有序的，可以直接按顺序加入到结果 res 中即可
    vector<int>  res;
    map<int,int> m;
    for(auto e:arr1) ++m[e];
    for(auto e:arr2) {
        for(int i=0; i<m[e]; i++)
            res.push_back(e);
        m.erase(e);
    }
    for(auto e:m)
        for(int i=0; i<e.second; i++)
            res.push_back(e.first);
    return res;
}

vector<string> LC1002::commonChars(vector<string>& words) {
    // 找出出現在所有字串的字符
    // 用一个数组 cnt 来记录相同的字母出现的次数，初始化为整型最大值，然后遍历所有的单词，对于每个单词，新建一个大小为 26 的数组t，
    // 并统计每个字符出现的次数，然后遍历0到25各个位置，取 cnt 和 t 对应位置上的较小值来更新 cnt 数组，这样得到就是在所有单词里都出现的
    // 字母的个数，最后再把这些字符转为字符串加入到结果 res 中即可
    array<int,128> map; map.fill(INT_MAX);
    array<int,128> cnt;
    vector<string>res;
    for(auto &w:words) {
        cnt.fill(0);
        for(auto c: w) ++cnt[c];
        for(int i=97; i<=122; i++)
            map[i] = min(map[i], cnt[i]);
    }
    for(int i=97; i<=122; i++)
        while(map[i]--)
            //for(int j=0; j<map[i]; j++)
            res.push_back(string(1, char(i)));

    return res;
}
int LC0997::findJudge(int n, vector<vector<int>>& trust) {
    // 跟之前那道Find the Celebrity 非常相似，那道题是所有人都认识名人，但是名人不认识任何人。而这里是法官不相信人任何人，
    // 而所有人都相信法官，不同的是在于给的数据结构不同，名人那道是给了个 API 判断是否认识，而这里给了个信任数组，那么解法就稍有不同了。
    // 由于信任是有方向的，所以是一个有向图，因为法官不相信任何人，所以其没有出度，而所有人都信任他，则入度满值。
    // 最简单直接的方法就是统计每个结点的出度和入度，然后找出那个出度为0，入度为 N-1 的结点即可
    vector<int> in(n+1,0), out(n+1,0);

    for(auto &v:trust) {
        ++out[v[0]];
        ++in[v[1]];
    }
    for(int i=1; i<=n; i++)
        if(!out[i] && in[i]==n-1) return i;

    return -1;
}
int LC0961::repeatedNTimes(vector<int>& nums) {
    // 找出重複出現n次的值
    // 使用一个 HashMap 来统计每个数字出现的个数，只要某个数字出现了 N 次即符合题意返回即可。但这里我们可以进一步的优化一下，
    // 由于只有一个数字有重复，其他的都是不重复的，所以只要发现某个数字出现次数大于1次，就可以直接返回了
    unordered_map<int,int> map;
    for(auto &n:nums)
        if(++map[n]>1) return n;
    return -1;
}

bool LC0914::hasGroupsSizeX(vector<int>& deck) {
    // 基于最大公约数 Greatest Common Divisor 的解法，写起来很简洁，但需要记住最大公约函数的写法，或者直接使用内置的 gcd 函数（
    // 感觉有点耍赖哈～）。其实原理都差不多，这里是找每种牌数之间的最大公约数，只要这个 gcd 是大于1的，就表示可以找到符合题意的X
//    int res=0;
//    unordered_map<int, int> map;
//    for(auto num:deck) ++map[num];
//    for(auto m:map)
//        res = std::gcd(res, m.second);
//    return res>1;

    //輾轉相除法
    function<int(int,int)> gcd = [&](int x, int y) -> int {
        return x==0 ? y : gcd(y%x, x);
    };
    unordered_map<int,int> map;
    int res=0;
    for(auto num:deck) ++map[num];
    for(auto m:map)
        res = gcd(res, m.second);
    return res>1;
}

vector<int> LC0888::fairCandySwap(vector<int>& aliceSizes, vector<int>& bobSizes) {
    // 这道题说爱丽丝和鲍勃两人有不同大小的糖果，现在要让两人交换一類糖果，使得交换后两人的糖果总重量相同，
    // 而且限定了两人初始时的糖果总量不相同，并且一定会有解。若我们仔细观察题目中给的例子，可以发现所有例子中起始时 Alice 和 Bob
    // 两人的糖果总重量的差值一定时偶数，这是 make sense 的，因为最终两人的糖果总量时要相同的，那么起始时的重量差就应该能平均分为两部分，
    // 一部分来弥补轻的一方，一部分来抵消重的一方。那么有了这个 diff，我们只需要在两个数组中查找差值为 diff 的两个数字了，其实就是 Two Sum
    // 的变种，使用一个 HashSet 先来保存数组 A 中所有的数字，然后遍历数组B中的每个数字 num，查找 HashSet 中否存在 num+diff 即可
    int diff = (accumulate(aliceSizes.begin(), aliceSizes.end(), 0) - accumulate(bobSizes.begin(), bobSizes.end(), 0))/2;
    unordered_set<int> set(aliceSizes.begin(), aliceSizes.end());
    for(auto &n:bobSizes)
        if(set.count(n+diff)) return  {n+diff, n};
    return {};
}

bool LC0859::buddyStrings(string s, string goal) {
    // 字串只做一次兩字符swap是否可等於另一字串
    // 首先字符串A和B长度必须要相等，不相等的话直接返回 false。假如起始时A和B就完全相等，那么只有当A中有重复字符出现的时候，
    // 才能返回 true。快速检测重复字符的方法就是利用 HashSet 的自动去重复功能，将A中所有字符存入 HashSet 中，若有重复字符，
    // 那么最终 HashSet 的大小一定会小于原字符串A的长度。对于A和B长度相等，但是字符串本身不相等的一般情况，
    // 我们可以记录出所有对应字符不相同的位置，放到一个数组 diff 中，最终判断 diff 数组的长度是否为2，
    // 且判断交换位置后是否跟B中对应的位置上的字符相同即可
    if(s.size() != goal.size()) return false;
    if(s==goal && unordered_set<char>(s.begin(), s.end()).size() < s.size()) return true;

    vector<int> diff;
    for(int i =0; i<s.size(); i++) {
        if(s[i]!=goal[i]) diff.push_back(i);
    }
    return diff.size()==2 && s[diff[0]]==goal[diff[1]] && s[diff[1]]==goal[diff[0]];
}

int LC0804::uniqueMorseRepresentations(vector<string>& words) {
    // 给了我们所有字母的摩斯码的写法，然后给了我们一个单词数组，问我们表示这些单词的摩斯码有多少种。因为某些单词的摩斯码表示是相同的，
    // 比如gin和zen就是相同的。最简单直接的方法就是我们求出每一个单词的摩斯码，然后将其放入一个HashSet中，利用其去重复的特性，
    // 从而实现题目的要求，最终HashSet中元素的个数即为所求，
    array<string, 26> morse{".-","-...","-.-.","-..",".","..-.","--.","....","..",".---","-.-",".-..","--","-.","---",".--.","--.-",".-.","...","-","..-","...-",".--","-..-","-.--","--.."};
    unordered_set<string> s;
    for(auto& w:words) {
        string r = "";
        for(auto& c:w) r += morse[c-'a'];
        s.insert(r);
    }
    return s.size();
}

int LC0771::numJewelsInStones(string jewels, string stones) {
    // 找出同時出現在兩字串的字符個數
    // 我们用HashSet来优化时间复杂度，将珠宝字符串J中的所有字符都放入HashSet中，然后遍历石头字符串中的每个字符，
    // 到HashSet中查找是否存在，存在的话计数器自增1即可
    int res = 0;
    array<int, 128> map; map.fill(0);
    for(auto c:jewels)
        map[c] = 1;
    for(auto c:stones)
        if(map[c]) res++;
    return res;
}

string LC0748::shortestCompletingWord(string licensePlate, vector<string>& words) {
    // 这道题给了我们一个车牌号，还有一些单词，让我们找出包含这个车牌号中所有字母的第一个最短的单词。车牌中的字母有大小写之分，
    // 但是单词只是由小写单词组成的，所以需要把车牌号中的所有大写字母都转为小写的，转换方法很简单，ASCII码加上32即可。
    // 我们建立车牌中各个字母和其出现的次数之间的映射，同时记录所有字母的个数total，然后遍历所有的单词，对于每个单词都要单独处理，
    // 我们遍历单词中所有的字母，如果其在车牌中也出现了，则对应字母的映射减1，同时还需匹配的字母数cnt也自减1，最后遍历字母完成后，
    // 如果cnt为0（说明车牌中所有的字母都在单词中出现了），并且结果res为空或长度大于当前单词word的话，更新结果即可
    string res = "";
    int total = 0;
    array<int,128> map; map.fill(0);
    for(auto c:licensePlate) {
        if(c>='a' && c<='z') {++map[c]; total++;}
        else if(c>='A' && c<='Z') {++map[c+32]; total++;}
    }
    for(auto w:words) {
        if(w.size()<total) continue;
        int t = total;
        array<int,128> m = map;
        for(auto c:w)
            if(--m[c]>=0) t--;
        if(!t && (res.empty() || res.size() > w.size()))
            res = w;
    }
    return res;
}

int LC0697::findShortestSubArray(vector<int>& nums) {
    // 求最小包含出現頻率最高之元素子陣列長度
    // 只用了一次遍历，思路跟上面的解法很相似，还是要建立数字出现次数的哈希表，还有就是建立每个数字和其第一次出现位置之间的映射，
    // 那么我们当前遍历的位置其实可以看作是尾位置，还是可以计算子数组的长度的。我们遍历数组，累加当前数字出现的次数，如果某个数字是第一次出现，
    // 建立该数字和当前位置的映射，如果当前数字的出现次数等于degree时，当前位置为尾位置，首位置在startIdx中取的，二者做差加1来更新结果res；
    // 如果当前数字的出现次数大于degree，说明之前的结果代表的数字不是出现最多的，直接将结果res更新为当前数字的首尾差加1的长度，
    // 然后degree也更新为当前数字出现的次数。
    int res=INT_MAX, degree=0;
    unordered_map<int, int> cnt, fst;

    for(int i=0; i<nums.size(); i++) {
        ++cnt[nums[i]];
        if(!fst.count(nums[i])) fst[nums[i]] = i;
        if(cnt[nums[i]] == degree)
            res = min(res, i-fst[nums[i]]+1);
        else if(cnt[nums[i]] > degree) {
            res = i-fst[nums[i]]+1;
            degree = cnt[nums[i]];
        }
    }
    return res;
}

vector<int> LC0645::findErrorNums(vector<int>& nums) {
    // 找出1～n的陣列裡重複的數和消失的那"個"數字
    // 遍历每个数字，然后将其应该出现的位置上的数字变为其相反数，这样如果我们再变为其相反数之前已经成负数了，说明该数字是重复数，
    // 将其将入结果res中，然后再遍历原数组，如果某个位置上的数字为正数，说明该位置对应的数字没有出现过，加入res中即可
    vector<int> res (2, -1);
    for(auto n:nums) {
        if(nums[abs(n)-1]<0) res[0]=abs(n);
        else nums[abs(n)-1] *= -1;
    }
    for(int i=0; i<nums.size(); i++)
        if(nums[i]>0) res[1]=i+1;
    return res;
}

int LC0628::maximumProduct(vector<int>& nums) {
    // 找出陣列裡三數相乘之最大值
    // 这道题博主刚开始看的时候，心想直接排序，然后最后三个数字相乘不就完了，心想不会这么Easy吧，果然被OJ无情打脸，没有考虑到负数和0的情况。
    // 这道题给了数组的范围，至少三个，那么如果是三个的话，就无所谓了，直接相乘返回即可，但是如果超过了3个，而且有负数存在的话，情况就可能不一
    // 样，我们来考虑几种情况，如果全是负数，三个负数相乘还是负数，为了让负数最大，那么其绝对值就该最小，而负数排序后绝对值小的都在末尾，所以
    // 是末尾三个数字相乘，这个跟全是正数的情况一样。那么重点在于前半段是负数，后半段是正数，那么最好的情况肯定是两个最小的负数相乘得到一个正
    // 数，然后跟一个最大的正数相乘，这样得到的肯定是最大的数，所以我们让前两个数相乘，再和数组的最后一个数字相乘，就可以得到这种情况下的最大
    // 的乘积。实际上我们并不用分情况讨论数组的正负，只要把这两种情况的乘积都算出来，比较二者取较大值，就能涵盖所有的情况，从而得到正确的结果
    int n = nums.size();
    sort(nums.begin(), nums.end());
    return max(nums[0]*nums[1]*nums[n-1], nums[n-3]*nums[n-2]*nums[n-1]);

    // 找出3个最大的数和一个最大的和两个最小的，相乘对比也能得到结果，而且是O(n)的时间复杂度
//    int max1 = INT_MIN, max2 = INT_MIN, max3 = INT_MIN;
//    int min1 = INT_MAX, min2 = INT_MAX;
//    for(auto &num:nums) {
//        if(num>max1) {
//            max3=max2; max2=max1; max1=num;
//        } else if (num>max2) {
//            max3=max2; max2=num;
//        } else if (num>max3) {
//            max3=num;
//        }
//
//        if(num<min1) {
//            min2=min1; min1=num;
//        } else if (num<min2) {
//            min2=num;
//        }
//    }
//    return max(max1*max2*max3, min1*min2*max1);
}

vector<string> LC0599::findRestaurant(vector<string>& list1, vector<string>& list2) {
    // 这道题给了我们两个字符串数组，让我们找到坐标位置之和最小的相同的字符串。那么对于这种数组项和其坐标之间关系的题，
    // 最先考虑到的就是要建立数据和其位置坐标之间的映射。我们建立list1的值和坐标的之间的映射，然后遍历list2，
    // 如果当前遍历到的字符串在list1中也出现了，那么我们计算两个的坐标之和，如果跟我们维护的最小坐标和mn相同，
    // 那么将这个字符串加入结果res中，如果比mn小，那么mn更新为这个较小值，然后将结果res清空并加入这个字符串
    vector<string> res;
    unordered_map<string, int> m;
    int mm = INT_MAX;
    for(int i=0; i<list1.size(); i++) m[list1[i]] = i;
    for(int i=0; i<list2.size(); i++) {
        if(m.count(list2[i])) {
            int sum = i + m[list2[i]];
            if(sum == mm)
                res.push_back(list2[i]);
            else if(sum < mm) {
                mm = sum;
                res = {list2[i]};
            }
        }
    }
    return res;
}

int LC0594::findLHS(vector<int>& nums) {
    // 陣列裡最長harmonious子陣列長度
    // 遍历每个数字时，先累加其映射值，然后查找该数字加1是否存在，存在的话用 freq[num] 和 freq[num+1] 的和来更新结果 res，
    // 同时，还要查找该数字减1是否存在，存在的话用 freq[num] 和 freq[num-1] 的和来更新结果 res
    int res = 0 ;
    unordered_map<int, int> map;
    for(auto num:nums) {
        ++map[num];
        if(map.count(num+1))
            res = max(res, map[num]+map[num+1]);
        if(map.count(num-1))
            res = max(res, map[num]+map[num-1]);
    }
    return res;
}

int LC0575::distributeCandies(vector<int>& candyType) {
    // 这道题给我们一堆糖，每种糖的个数不定，分给两个人，让我们求其中一个人能拿到的最大的糖的种类数。那么我们想，
    // 如果总共有n个糖，平均分给两个人，每人得到n/2块糖，那么能拿到的最大的糖的种类数也就是n／2种，不可能再多，
    // 只可能再少。那么我们要做的就是统计出总共的糖的种类数，如果糖的种类数小于n/2，说明拿不到n/2种糖，
    // 最多能拿到的种类数数就是当前糖的总种类数，我们利用集合set的自动去重复特性来求出糖的种类数， 然后跟n/2比较，取二者之中的较小值返回即可

//    unordered_set<int> s;
//    for(auto type: candyType)
//        s.insert(type);
//    return min(s.size(), candyType.size()/2);

    return min(unordered_set<int>(candyType.begin(), candyType.end()).size(), candyType.size()/2);
}

vector<string> LC0500::findWords(vector<string>& words) {
    // 給定的字符串是否能只用鍵盤的某一行打完
    // 把键盘的三行字符分别保存到三个set中，然后遍历每个单词中的每个字符，分别看当前字符是否在三个集合中，
    // 如果在，对应的标识变量变为1，我们统计三个标识变量之和就知道有几个集合参与其中了
    unordered_set<char> row1 {'q','w','e','r','t','y','u','i','o','p'};
    unordered_set<char> row2 {'a','s','d','f','g','h','j','k','l'};
    unordered_set<char> row3 {'z','x','c','v','b','n','m'};
    vector<string> res;
    for(auto word:words) {
        int r1=0, r2=0, r3=0;
        for(auto w:word) {
            if(w < 'a') w+=32;  // 大寫的字母變成小寫
            if(row1.count(w)) r1 = 1;
            if(row2.count(w)) r2 = 1;
            if(row3.count(w)) r3 = 1;
            if(r1 + r2 + r3 >1) break;
        }
        if(r1 + r2 + r3 == 1) res.push_back(word);
    }
    return res;
}

vector<int> LC0496::nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
    // 给了我们一个数组，又给了该数组的一个子集合，让我们求集合中每个数字在原数组中右边第一个较大的数字。
    // 建立每个数字和其右边第一个较大数之间的映射，没有的话就是-1。我们遍历原数组中的所有数字，如果此时栈不为空，
    // 且栈顶元素小于当前数字，说明当前数字就是栈顶元素的右边第一个较大数，那么建立二者的映射，并且去除当前栈顶元素，
    // 最后将当前遍历到的数字压入栈。当所有数字都建立了映射，那么最后我们可以直接通过哈希表快速的找到子集合中数字的右边较大值
    vector<int> res;
    stack <int> s;
    unordered_map<int, int> m;
    for(auto num:nums2) {
        while(s.size() && s.top()<num) {
            m[s.top()] = num; s.pop();
        }
        s.push(num);
    }
    for(auto num:nums1) {
        res.push_back(m.count(num) ? m[num] : -1);
    }
    return res;
}

vector<int> LC0448::findDisappearedNumbers(vector<int>& nums) {
    // 找出1～n的陣列裡消失的那"些"數字
    // 使用額外的空間作hash table來紀錄出現過的
//    unordered_set set(nums.begin(), nums.end());
//    vector<int> res;
//    for(int i=1; i<=nums.size(); i++)
//        if(!set.count(i)) res.push_back(i);
//    return res;

    // 不使用額外空間。
    // 将nums[i]置换到其对应的位置nums[nums[i]-1]上去，比如对于没有缺失项的正确的顺序应该是[1, 2, 3, 4, 5, 6, 7, 8]，
    // 而我们现在却是[4,3,2,7,8,2,3,1]，我们需要把数字移动到正确的位置上去，比如第一个4就应该和7先交换个位置，以此类推，
    // 最后得到的顺序应该是[1, 2, 3, 4, 3, 2, 7, 8]，我们最后在对应位置检验，如果nums[i]和i+1不等，那么我们将i+1存入结果res中即可
    vector<int> res;
    for(int i=0; i<nums.size(); i++)
        if(nums[i]!=nums[nums[i]-1]) {
            swap(nums[i], nums[nums[i] - 1]);
            i--;
        }
    for(int i=0; i<nums.size(); i++)
        if(nums[i] != i+1) res.push_back(i+1);
    return res;
}

string LC0345::reverseVowels(string s) {
    // 把字串裡的母音對調
    // 如果两边都是元音字母，那么我们交换 然後還剩下其中一個是，或兩邊都不是
    // 如果左邊是，右邊一定不是 -> r-- 剩下左邊一定都不是的情況(左不是右是、左不是右不是) -> l++
    array<int,128> map; map.fill(0);
    map['a'] = map['e'] = map['i'] = map['o'] = map['u'] = map['A'] = map['E'] = map['I'] = map['O'] = map['U'] = 1;
    int l=0, r=s.size()-1;
    while(l<r) {
        if(map[s[l]] && map[s[r]])
            swap(s[l++],s[r--]);
        else if(map[s[l]])
            r--;
        else
            l++;
    }
    return s;
}

char LC0389::findTheDifference(string s, string t) {
    // Input: s = "abcd" t = "abcde"
    // Output: e
    // 判斷隨機加入字串的字符為何
    // 用哈希表来建立字符和个数之间的映射，如果在遍历t的时候某个映射值小于0了，那么返回该字符即可
//    array<int,128> map; map.fill(0);
//    for(auto c:s) ++map[c];
//    for(auto c:t)
//        if(--map[c] < 0) return c;
//    return 0;

    // 使用位操作Bit Manipulation来做，利用异或的性质，相同位返回0，这样相同的字符都抵消了，剩下的就是后加的那个字符
    char res = 0;
    for(auto c:s) res ^= c;
    for(auto c:t) res ^= c;
    return res;
}

int LC0387::firstUniqChar(string s) {
    // 找出一字串裡第一個不重複的字符的index
    // 用哈希表建立每个字符和其出现次数的映射，然后按顺序遍历字符串，找到第一个出现次数为1的字符，返回其位置即可
    array<int,128> map; map.fill(0);
    for(auto c:s) ++map[c];
    for(int i=0; i<s.size(); i++)
        if(map[s[i]]==1) return i;
    return -1;
}

bool LC0383::canConstruct(string ransomNote, string magazine) {
    // 判斷一字串是否能從另一字串重建
    // Given an arbitrary ransom note string and another string containing letters from all the magazines, write a
    // function that will return true if the ransom  note can be constructed from the magazines; otherwise,
    // it will return false.
    // 用哈希Map统计字符的个数
    array<int,128> map; map.fill(0);
    for(auto c:magazine) ++map[c];
    for(auto c:ransomNote)
        if(--map[c] < 0) return false;
    return true;
}

vector<int> LC0350::intersect(vector<int>& nums1, vector<int>& nums2) {
    // 找两个数组交集的部分（不包含重复数字）
    // 允许返回重复的数字，而且是尽可能多的返回，之前那道题是说有重复的数字只返回一个就行。那么这道题用 HashMap 来建立 nums1
    // 中字符和其出现个数之间的映射, 然后遍历 nums2 数组，如果当前字符在 HashMap 中的个数大于0，则将此字符加入结果 res 中，
    // 然后 HashMap 的对应值自减1
    unordered_map<int,int> map;
    vector<int> res;

    for(auto n:nums1) ++map[n];
    for(auto n:nums2)
        if(map[n]-- > 0) res.push_back(n);
    return res;
}

vector<int> LC0349::intersection(vector<int>& nums1, vector<int>& nums2) {
    // 找两个数组交集的部分（不包含重复数字）
    // 用个 HashSet 把 nums1 都放进去，然后遍历 nums2 的元素，如果在 HashSet 中存在，
    // 说明是交集的部分，加入结果的 HashSet 中，最后再把结果转为 vector 的形式即可
    unordered_set<int> res, set(nums1.begin(), nums1.end());
    for(auto n:nums2)
        if(set.count(n)) res.insert(n);
    return vector<int>(res.begin(), res.end());
}

//LC0268 run;
//vector<int> v {3,0,1};
//cout << run.missingNumber(v);
int LC0268::missingNumber(vector<int>& nums) {
    // Given an array containing n distinct numbers taken from 0, 1, 2, ..., n, find the one that is missing
    // from the array.
    // For example. Given nums = [0, 1, 3] return 2.

    // 用等差数列的求和公式求出0到n之间所有的数字之和，然后再遍历数组算出给定数字的累积和，然后做减法，差值就是丢失的那个数字
//    int n = nums.size(), sum=0;
//    std::for_each(nums.begin(), nums.end(), [&](int num){sum+=num;});
//    return (n*(1+n))/2 - sum;

    // by sorting
    int n = nums.size();
    std::sort(nums.begin(), nums.end());
    for(int i=0; i<n; i++)
        if(nums[i]!=i) return i;
    return n;

    // by binary search 第三类
//    std::sort(nums.begin(), nums.end());
//    int q=0, p=nums.size();
//    while(q<p) {
//        int m = q + (p-q)/2;
//        if(nums[m] <= m) q=m+1;
//        else p=m;
//    }
//    return p;
}

bool LC0242::isAnagram(string s, string t) {
    // Given two strings s and t , write a function to determine if t is an anagram of s. For example,
    // s = "anagram", t = "nagaram", return true.
    // s = "rat", t = "car", return false.
    // 先判断两个字符串长度是否相同，不相同直接返回false。然后把s中所有的字符出现个数统计起来，
    // 存入一个大小为26的数组中，因为题目中限定了输入字符串为小写字母组成。然后我们再来统计t字符串，如果发现不匹配则返回false。
    if(s.size()!=t.size()) return false;

    array<int, 26> set; set.fill(0);
    for(auto c:s)
        ++set[c-'a'];
    for(auto c:t) {
        if(--set[c-'a'] < 0) return false;
    }
    return true;
}

bool LC0219::containsNearbyDuplicate(vector<int>& nums, int k) {
    // 是之前那道 Contains Duplicate 的延伸，不同之处在于那道题只要判断下数组中是否有重复值，而这道题限制了数组中只许有一组重复的数字，
    // 而且其坐标差不能超过k。首先需要一个 HashMap，来记录每个数字和其坐标的映射，然后需要一个变量d来记录第一次出现重复数字的坐标差。由于
    // 题目要求只能有一组重复的数字，所以在遇到重复数字时，首先判断d是否已经存了值，如果d已经有值了，说明之前有过了重复数字，则直接返回 false
    // 即可。如果没有，则此时给d附上值。在网上看到有些解法在这里就直接判断d和k的关系然后返回结果了，其实这样是不对的。因为题目要求只能有一组
    // 重复数，就是说如果后面又出现了重复数，就没法继续判断了。所以正确的做法应该是扫描完整个数组后在判断，先看d有没有存入结果，如果没有，则
    // 说明没出现过重复数， 返回 false 即可。如果d有值，再跟k比较，返回对应的结果。
    unordered_map<int, int> map;
    for(int i=0; i<nums.size(); i++) {
        if(map.count(nums[i]) && i-map[nums[i]] <=k) return true;
        map[nums[i]] = i;
    }
    return false;
}

bool LC0217::containsDuplicate(vector<int>& nums) {
    // Given an array of integers, find if the array contains any duplicates. Your function should return true
    // if any value appears at least twice in the array, and it should return false if every element is distinct.
    unordered_set <int> set;
    for(auto n:nums) {
        if(set.count(n)) return true;
        set.insert(n);
    }
    return false;
}

//LC0205 run;
//cout << run.isIsomorphic("ab", "aa") << endl;
bool LC0205::isIsomorphic(string s, string t) {
    // 求同构字符串，就是说原字符串中的每个字符可由另外一个字符替代，可以被其本身替代，相同的字符一定要被同一个字符替代，
    // 且一个字符不能被多个字符替代，即不能出现一对多的映射
    // 原字符串中的每个字符可由另外一个字符替代，可以被其本身替代，相同的字符一定要被同一个字符替代，
    // 且一个字符不能被多个字符替代，即不能出现一对多的映射。根据一对一映射的特点，需要用两个 HashMap
    // 分别来记录原字符串和目标字符串中字符出现情况，由于 ASCII 码只有 256 个字符，所以可以用一个 256
    // 大小的数组来代替 HashMap，并初始化为0，遍历原字符串，分别从源字符串和目标字符串取出一个字符，
    // 然后分别在两个数组中查找其值，若不相等，则返回 false，若相等，将其值更新为 i + 1
    array<int, 256> sa; sa.fill(-1);
    array<int, 256> st; st.fill(-1);

    for(int i=0; i<s.size(); i++) {
        if(sa[s[i]]!=st[t[i]]) return false;
        sa[s[i]] = st[t[i]] = i;
    }
    return true;
}

bool LC0202::isHappy(int n) {
    // 定义了一种快乐数，就是说对于某一个正整数，如果对其各个位上的数字分别平方，然后再加起来得到一个新的数字，再进行同样的操作，如果最终结果变成了1，
    // 则说明是快乐数，如果一直循环但不是1的话，就不是快乐数，那么现在任意给我们一个正整数，让我们判断这个数是不是快乐数，题目中给的例子19是快乐数
    // 我们可以用 HashSet 来记录所有出现过的数字，然后每出现一个新数字，
    // 在 HashSet 中查找看是否存在，若不存在则加入表中，若存在则跳出循环，并且判断此数是否为1，
    // 若为1返回true，不为1返回false
//    unordered_set<int> set;
//    while(n!=1) {
//        int sum = 0;
//        while(n) {
//            sum += pow(n%10,2);
//            n /=10;
//        }
//        if(set.count(sum)) return false;
//        set.insert(sum);
//        n=sum;
//    }
//    return true;

    // 可以不用 HashSet 来做，我们并不需要太多的额外空间，关于非快乐数有个特点，循环的数字中必定会有4
    while(n!=1 && n!=4) {
        int sum = 0;
        while(n) {
            sum += pow(n%10, 2);
            n /= 10;
        }
        n = sum;
    }
    return n==1;
}

vector<int> LC0001::twoSum(vector<int>& nums, int target) {
    unordered_map<int, int> t;

    // find target-nums[i], save nums[i]
    for(auto i=0 ; i<nums.size(); i++) {
        auto diff = target - nums[i];
        if(t.count(diff))
            return {t[diff], i};
        t[nums[i]]=i;
    }
    return {};

    // find nums[i], save target-nums[i]
    for(auto i=0 ; i<nums.size() ; i++) {
        auto diff = target - nums[i];
        if(t.count(nums[i]))
            return {t[nums[i] ], i};
        t[diff] = i;
    }
    return {};
}