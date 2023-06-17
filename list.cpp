
#include "list.h"

// 可顯示字元編號範圍是32-126（0x20-0x7E），共95個字元。
// 大寫：65~90, 小寫：97~122
// 跟char有關的hash table都可以用 array<int,128> map; map.fill(0);來放

/***********  Hash Table  **********/
int LC1684::countConsistentStrings(string allowed, vector<string>& words) {
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
    // 如果两边都是元音字母，那么我们交换
    // 然後還剩下其中一個是，或兩邊都不是
    // 如果左邊是，右邊一定不是 -> r--
    // 剩下左邊一定都不是的情況(左不是右是、左不是右不是) -> l++
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
    // 用哈希表建立每个字符和其出现次数的映射，然后按顺序遍历字符串，找到第一个出现次数为1的字符，返回其位置即可
    array<int,128> map; map.fill(0);
    for(auto c:s) ++map[c];
    for(int i=0; i<s.size(); i++)
        if(map[s[i]]==1) return i;
    return -1;
}

bool LC0383::canConstruct(string ransomNote, string magazine) {
    // 用哈希Map统计字符的个数
    array<int,128> map; map.fill(0);
    for(auto c:magazine) ++map[c];
    for(auto c:ransomNote)
        if(--map[c] < 0) return false;
    return true;
}

vector<int> LC0350::intersect(vector<int>& nums1, vector<int>& nums2) {
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
}

bool LC0242::isAnagram(string s, string t) {
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

/***********  Two Pointers  **********/
void LC0283::moveZeroes(vector<int>& nums) {
    // 这道题让我们将一个给定数组中所有的0都移到后面，把非零数前移，要求不能改变非零数的相对应的位置关系，而且不能拷贝额外的数组，那么只能用
    // 替换法in-place来做，需要用两个指针，一个不停的向后扫，找到非零位置，然后和前面那个指针交换位置即可
    // 用快慢指針
    int slow=0;
    for(int fast=0; fast<nums.size(); ++fast)
        if(nums[fast]) std::swap(nums[slow++], nums[fast]);
}

//LC0027 run;
//vector<int> n{0,1,2,2,3,0,4,2}; // val=2
//vector<int> n{3,2,2,3}; // val=3
//vector<int> n{1}; // val=1
//cout << run.removeElement(n, 1) << endl;
//for(auto i:n) cout << i << ' ';
//cout << endl;
int LC0027::removeElement(vector<int>& nums, int val) {
    // 除一个数组中和给定值相同的数字，并返回新的数组的长度。
    // fast開始掃，若不是指定的值的話表示可以留在nums裡，就會往slow放。若是指定的值，slow則不會++，準備下次被覆蓋。
    int slow=0;
    for(int fast=0; fast<nums.size(); ++fast)
        if(nums[fast] != val) nums[slow++] = nums[fast];
    return slow;
}

//LC0026 run;
//vector<int> n{0,0,1,1,1,2,2,3,3,4};
//vector<int> n{1,1,2};
//cout << run.removeDuplicates(n) << endl;
//for(auto i:n) cout << i << ' ';
//cout << endl;
int LC0026::removeDuplicates(vector<int>& nums) {
    // 使用快慢指针来记录遍历的坐标，最开始时两个指针都指向第一个数字，如果两个指针指的数字相同，则快指针向前走一步，如果不同，则两个指针都向
    // 前走一步，这样当快指针走完整个数组后，慢指针当前的坐标加1就是数组中不同数字的个数
    int slow=0;
    // fast每次進一步，slow若一直跟fast指到的是一樣的，就會不動。當不一樣時再把fast指到的放到slow的下一個，下一個一定是跟slow本身一樣
    // 才會使得之前slow不動。
    for(int fast=0; fast<nums.size(); fast++)
        if(nums[fast] != nums[slow]) nums[++slow] = nums[fast];
    return nums.size() ? slow+1 : 0;

    // 用变量i表示当前覆盖到到位置，由于不能有重复数字，则只需要用当前数字 num 跟上一个覆盖到到数字 nums[i-1] 做个比较，只要 num 大，
    // 则一定不会有重复（前提是数组必须有序）
//    int i=0;
//    for(int &num:nums)
//        if(i<1 || num > nums[i-1])
//            nums[i++] = num;
//    return i;
}

/***********  Array List  **********/
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

/***********  Matrix  **********/
string LC1275::tictactoe(vector<vector<int>>& moves) {
    // 关于井字棋游戏的，这个游戏简单容易上手，是课间十五分钟必备游戏之一，游戏规则很简单，一个人画叉，一个人画圆圈，只要有三个相连的位置，
    // 包括对角线就算赢。而这道题给了两个玩家的若干操作，让判断当前的棋盘状态，是哪一方赢了，还是没下完，或者是平局。判赢的条件就是找到任意行
    // 或列，或者对角线有三个相同的符号，若找不到有可能是平局或者没下完，只要判断总步数是否为9，就知道有没有下完了。由于给定的是两个玩家按顺
    // 序落子的位置，一个比较直接的方法就是分别还原出两个玩家在棋盘上的落子，分别还原出两个 3 by 3 的棋盘的好处是可以不用区分到底是叉还是圆
    // 圈，只要找三个连续的落子位置就行了，而且可以把查找逻辑放到一个子函数中进行复用。在子函数中，判断各行各列是否有连续三个落子，以及两条对
    // 角线，若有的话返回 true，否则 false。然后分别对还原出来的数组A和B调用子函数，若有返回的 true，则返回对应的A或B。否则就判断 moves
    // 数组的长度，若等于9，返回平局 Draw，反之为 Pending
    function<bool(vector<vector<bool>>)> win = [&](vector<vector<bool>> m) -> bool {
        for(int i=0; i<3; ++i) {
            if(m[i][0] && m[i][1] && m[i][2]) return true;
            if(m[0][i] && m[1][i] && m[2][i]) return true;
        }
        if(m[0][0] && m[1][1] && m[2][2]) return true;
        if(m[2][0] && m[1][1] && m[0][2]) return true;
        return false;
    };

    vector<vector<bool>> A(3, vector<bool>(3, false)), B=A;

    for(int i=0; i<moves.size(); ++i)
        if(i & 1) B[moves[i][0]][moves[i][1]] = true;
        else A[moves[i][0]][moves[i][1]] = true;
    if(win(A)) return "A";
    if(win(B)) return "B";
    return (moves.size() == 9) ? "Draw" : "Pending";
}

vector<vector<int>> LC1260::shiftGrid(vector<vector<int>>& grid, int k) {
    // 移动一个二维数组，移动方法是水平移动，即每个元素向右平移一位，行末尾的元素移动到下一行的开头，数组最后一个元素移动到开头的第一个元素，
    // 像这样移动k次，返回最终的数组。由于要移动k次，若每次都更新一遍数组的值，实在是不高效，最好直接能计算出最终状态的值，那么关注点就是计算
    // 一个元素水平移动k次的新位置。由于是二维数组，所以总是存在一个换行的问题，比较麻烦，一个很好的 trick 就是先将数组拉平，变成一维数组，
    // 这样移动k位就很方便，唯一需要注意是加k后可能超过一维数组的范围，需要当作循环数组来处理。明白了思路，代码就很好写了，新建一个和原数组同
    // 等大小的数组 res，然后遍历原数组，对于每个位置 (i, j)，计算其在拉平后的一维数组中的位置 i*n + j，然后再加上平移k，为了防止越界，最
    // 后再对 m*n 取余，得到了其在一维数组中的位置，将其转回二维数组的坐标，并更新结果 res 中的对应位置即可
    int m=grid.size(), n=grid[0].size(), len=m*n;
    if(!(k%len)) return grid; // k是len的倍數，等於沒有shift
    k %= len; // k簡化成len的餘數即可
    vector<vector<int>> res(m, vector<int>(n));

    for(int y=0; y<m; ++y)
        for(int x=0; x<n; ++x) {
            int idx = (y*n + x + k) % len;
            res[idx/n][idx%n] = grid[y][x];
        }
    return res;
}

int LC0892::surfaceArea(vector<vector<int>>& grid) {
    // 给了我们一个二维数组 grid，其中 grid[i][j] 表示在位置 (i,j) 上累计的小正方体的个数，实际上就像搭积木一样，由这些小正方体来组成一个
    // 三维的物体，这里让我们求这个三维物体的表面积。我们知道每个小正方体的表面积是6，若在同一个位置累加两个，表面积就是10，三个累加到了一起
    // 就是14，其实是有规律的，n个小正方体累在一起，表面积是 4n+2。现在不仅仅是累加在一个小正方体上，而是在 nxn 的区间，累加出一个三维物体。
    // 由于之前做过那道三维物体投影的题 Projection Area of 3D Shapes，所以博主很思维定势的想到是不是也跟投影有关，然后又想当然的认为三维
    // 物体每一个面的面积就是该方向的投影，那么我们把三个方向的投影之和算出来，再乘以2不就是表面积了么？实际上这种方法是错误的，就拿题目中的例
    // 子4来说，当中间的小方块缺失了之后，实际上缺失的地方会产生出四个新的面，而这四个面是应该算在表面积里的，但是用投影的方法是没法算进去的。
    // 无奈只能另辟蹊径，实际上这道题正确的思路是一个位置一个位置的累加表面积，就类似微积分的感觉
    
    // 当n个小正方体累到一起的表面积是
    // 4n+1，而这个n就是每个位置的值 grid[i][j]，当你在旁边紧挨着再放一个累加的物体时，二者就会产生重叠，重叠的面数就是二者较矮的那堆正方体
    // 的个数再乘以2，明白了这一点，我们就可以从 (0,0) 位置开始累加，先根据 grid[0][0] 的值算出若仅有该位置的三维物体的表面积，然后向 (0,1)
    // 位置遍历，同样要先根据 grid[0][1] 的值算出若仅有该位置的三维物体的表面积，跟之前 grid[0][0] 的累加，然后再减去遮挡住的面积，通过
    // min(grid[0][0],grid[0][1])x2 来得到，这样每次可以计算出水平方向的遮挡面积，同时还需要减去竖直方向的遮挡面积
    // min(grid[i][j],grid[i-1][j])x2，这样才能算出正确的表面积
    int m=grid.size(), res=0;
    for(int y=0; y<m; y++)
        for(int x=0; x<m; x++) {
            int val = grid[y][x];
            if(val) res += 4*val + 2;
            if(y) res -= std::min(val, grid[y-1][x]) * 2;
            if(x) res -= std::min(val, grid[y][x-1]) * 2;
        }
    return res;
}

int LC0883::projectionArea(vector<vector<int>>& grid) {
    // 给了我们一个二维数组 grid，用来表示一个 3D 物体形状，表示方法是 grid[i][j] 表示在 (i, j) 位置上的高度，就像垒积木一样，累出了一个
    // 三维物体。然后让我们计算三个方向的投影面积之和，所谓的三个方向分别是上方 Top，前方 Front，和侧方 Side。用过一些三维建模软件（例如
    // Maya， 3DMax）的同学，对这个应该不陌生。我们先来考虑正上方投影面积如何计算，由于题目中说了 grid 数组的宽和高相等，那么上方投影就是一
    // 个正方形，前提是每个 grid[i][j] 的值都大于0的话。因为若 grid 数组中有0存在，则表示正方形投影会缺少了一块。由于这个大的正方形投影是
    // 由 nxn 个小的正方形组成，那么实际上我们只要统计出小正方形的个数，那么大正方形投影的面积也就知道了（是不有点微积分的感觉）。所以我们在
    // 遍历的过程中，只要判断若 grid[i][j] 大于0，则结果 res 自增1即可。下面再来考虑另外两个方向的投影怎么计算，另两个方向的投影的可能是
    // 不规则图形，参见题目中给的那个图，如果仔细观察的话，其投影图像的每个阶段的高其实就是各行或各列中的最大值，这也不难理解，就像城市中耸立
    // 的高度不同的大楼，若要描出城市的轮廓，那么描出来的肯定都是每个位置上最高建筑物的轮廓。那么问题就变成了累加各行各列的最大值。我们实际上
    // 在一次遍历中就能完成，使用了一个小 trick，那就是在第二层 for 循环中，行最大值 rowMax 就是不断用 grid[i][j] 来更新，而列最大值
    // colMax 就是不断用 grid[j][i] 来更新，巧妙的交换i和j，实现了目标。然后分别把更新出来的行列最大值加到结果 res 中即可
    int m=grid.size();
    int res=0;
    for(int y=0; y<m; y++) {
        int rowMax=0, colMax=0;
        for (int x = 0; x < m; x++) {
            if(grid[y][x]) res++;
            rowMax = std::max(rowMax, grid[y][x]);
            colMax = std::max(colMax, grid[x][y]);
        }
        res += rowMax + colMax;
    }
    return res;
}

vector<vector<int>> LC0867::transpose(vector<vector<int>>& matrix) {
    // 转置一个矩阵，在大学的线性代数中，转置操作应该说是非常的常见。所谓矩阵的转置，就是把 mxn 的矩阵变为 nxm 的，并且原本在 A[i][j] 位置
    // 的数字变到 A[j][i] 上即可，非常的简单直接。而且由于此题又限定了矩阵的大小范围为 [1, 1000]，所以不存在空矩阵的情况，因而不用开始时对
    // 矩阵进行判空处理，直接去获取矩阵的宽和高即可。又因为之前说了转置会翻转原矩阵的宽和高，所以我们新建一个 nxm 的矩阵，然后遍历原矩阵中的每
    // 个数，将他们赋值到新矩阵中对应的位置上即可
    int m=matrix.size(), n=matrix[0].size();
    vector<vector<int>> res(n, vector<int>(m));
    for(int y=0; y<m; y++)
        for(int x=0; x<n; x++)
            res[x][y] = matrix[y][x];
    return res;
}

vector<vector<int>> LC0832::flipAndInvertImage(vector<vector<int>>& image) {
    // 这道题让我们翻转图像，翻转的方法是对于二维数组的每一行，先将所有元素位置翻转一下，然后再按顺序将每个像素值取个反。既然要求这么直接明了，
    // 那么就按照其说的一步一步来呗，首先翻转每一行，记得一定要加 ‘&’ 号，不然原数组不会被修改。然后在遍历每个数字，让其或上1，达到取反的目的，
    // 当然还是必须要加 ‘&’ 号，最后返回修改后的A数组即可
//    for(auto &row:image)
//        std::reverse(row.begin(), row.end());
//    for(auto &row:image)
//        for(auto &e:row)
//            e ^= 1;
//    return image;

    // 上面的方法虽然直接了当，但是毕竟修改了原数组A，再来看一种不修改的方法，这里我们新建一个跟A一样长的二维数组，只不过里面的各行还是空的。
    // 然后我们遍历A数组的各行，但在遍历各行上的数字时，我们采用从后往前的遍历顺序，然后对于每个数字取反在加入结果res中，这样直接将翻转和取
    // 反同时完成了
    int n=image.size();
    vector<vector<int>> res(n);
    for(int y=0; y<n; y++)
        for(int x=n-1; x>=0; x--)
            res[y].push_back(!image[y][x]); // push_back到第y row
    return res;
}

bool LC0766::isToeplitzMatrix(vector<vector<int>>& matrix) {
    // 这道题让我们验证一个矩阵是否是托普利兹矩阵Toeplitz Matrix，所谓的这个托普利兹矩阵，就是看每条从左上到右下的对角线是否是值都相等。
    // 注意矩阵的行数列数不一定相等，要验证所有的对角线。那么其实这道题的本质是让我们斜向遍历矩阵，就是按对角线来。按正常顺序来遍历数组，
    // 对于每个遍历到的数字，都跟其右下方的数字对比，如果不相同，直接返回false即可。为了防止越界，我们不遍历最后一行和最后一列，遍历完成后，
    // 返回true
    for(int y=0; y<matrix.size()-1; y++)
        for(int x=0; x<matrix[0].size()-1; x++)
            if(matrix[y][x] != matrix[y+1][x+1]) return false;
    return true;
}

vector<vector<int>> LC0661::imageSmoother(vector<vector<int>>& img) {
    // 给一个图片进行平滑处理，一般来说都是用算子来跟图片进行卷积，但是由于这道题只是个Easy的题目，我们直接用土办法就能解了，就直接对于每一个
    // 点统计其周围点的个数，然后累加像素值，做个除法就行了，注意边界情况的处理
    if(img.empty() || img[0].empty()) return {};
    const int m=img.size(), n=img[0].size();
    vector<vector<int>> res=img, dirs{ {-1,-1}, {0,-1}, {1,-1}, {-1,0}, {1,0}, {-1,1}, {0,1}, {1,1} }; // {x, y}
    for(int y=0; y<m; y++)
        for(int x=0; x<n; x++) {
            int val = img[y][x], cnt = 1;
            for(auto dir:dirs) {
                int col=x+dir[0], raw=y+dir[1];
                if(col<0 || col>=n || raw<0 || raw>=m) continue;
                val+=img[raw][col];
                cnt++;
            }
            res[y][x] = val/cnt;
        }
    return res;
}

vector<vector<int>> LC0566::matrixReshape(vector<vector<int>>& mat, int r, int c) {
    // 遍历拉直后的一维数组的坐标，然后分别转换为两个二维数组的坐标进行赋值
    int m=mat.size(), n=mat[0].size();
    if(m*n != r*c) return mat;
    vector<vector<int>> res(r, vector<int>(c));
    for(int i=0; i<r*c; i++)
        res[i/c][i%c]=mat[i/n][i%n];
    return res;
}

int LC0463::islandPerimeter(vector<vector<int>>& grid) {
    // 这道题给了我们一个格子图，若干连在一起的格子形成了一个小岛，规定了图中只有一个相连的岛，且岛中没有湖，让我们求岛的周长。我们知道一个格
    // 子有四条边，但是当两个格子相邻，周围为6，若某个格子四周都有格子，那么这个格子一条边都不算在周长里。那么我们怎么统计出岛的周长呢？
    // 对于每个岛屿格子先默认加上四条边，然后检查其左面和上面是否有岛屿格子，有的话分别减去两条边，这样也能得到正确的结果
    if(grid.empty() || grid[0].empty()) return 0;
    int res=0, m=grid.size(), n=grid[0].size();
    for(int i=0; i<m; i++)
        for(int j=0; j<n; j++) {
            if(!grid[i][j]) continue;
            res+=4;
            if(i && grid[i-1][j]) res-=2;
            if(j && grid[i][j-1]) res-=2;
        }
    return res;
}

/***********  Linked List  **********/

//LinkedList l2;
//l2.AddNode(1); l2.AddNode(0); l2.AddNode(1);
//LC1290 run;
//cout << run.getDecimalValue(l2.GetListHead()) << endl;
int LC1290::getDecimalValue(ListNode* head) {
    auto fun = [](const auto &self, ListNode* node, int &m) -> int {
        if(!node->next) return node->val;
        int v =  self(self, node->next, m);
        m*=2;
        return node->val*m + v;
    };

    if(!head) return 0;
    int m = 1;
    return fun(fun, head, m);
}

ListNode* LC0876::middleNode(ListNode* head) {
    ListNode *slow=head, *fast=head;

    while(fast->next && fast->next->next) {
        slow = slow->next;
        fast = fast->next->next;
    }

    return fast->next ? slow->next : slow;
}

void LC0237::deleteNode(ListNode* node) {
    // 先把当前节点的值用下一个节点的值覆盖了，然后我们删除下一个节点即可
    ListNode *n = node->next;
    node->val = n->val;
    node->next = n->next;
    delete n;
}

bool LC0234::isPalindrome(ListNode* head) {
    if(!head || !head->next) return true;
    stack<int> s;

    // 先按顺序把所有的结点值都存入到一个栈 stack 里，然后利用栈的后入先出的特性，
    // 就可以按顺序从末尾取出结点值了，此时再从头遍历一遍链表，就可以比较回文的对应位置了，
    // 若不同直接返回 false 即可
//    ListNode* node = head;
//    while(node) {
//        s.push(node->val);
//        node = node->next;
//    }
//    while(head) {
//        int v = s.top(); s.pop();
//        if(v != head->val) return false;
//        head = head->next;
//    }
//    return true;

    // use fast/slow pointer
    ListNode *slow=head, *fast=head;
    s.push(slow->val);
    while(fast->next && fast->next->next) {
        slow = slow->next;
        fast = fast->next->next;
        s.push(slow->val);
    }
    if(!fast->next) s.pop();
    while(slow->next) {
        slow = slow->next;
        int v = s.top(); s.pop();
        if(v != slow->val) return false;
    }
    return true;
}

//LinkedList l;
//l.AddNode(1); l.AddNode(2); l.AddNode(3);
//l.AddNode(4); l.AddNode(5); l.AddNode(6);
//LC0206 run;
//ListNode* r = run.reverseList(l.GetListHead());
//LinkedList::ShowLinkedList(r);
ListNode* LC0206::reverseList(ListNode* head) {
    // 在原链表之前建立一个空的cur，因为首节点会变，然后从head开始，将之后的一个节点移到cur之后，重复此操作直到head成为末节点为止
    // iterative way
    ListNode* cur=nullptr;
    while(head) {
        ListNode* tmp = head->next;
        head->next = cur;
        cur = head;
        head = tmp;
    }
    return cur;

    // 递归解法，代码量更少，递归解法的思路是，不断的进入递归函数，直到head指向倒数第二个节点，因为head指向空或者是最后一个结点都直接返回了，
    // newHead则指向对head的下一个结点调用递归函数返回的头结点，此时newHead指向最后一个结点，然后head的下一个结点的next指向head本身，这
    // 个相当于把head结点移动到末尾的操作，因为是回溯的操作，所以head的下一个结点总是在上一轮被移动到末尾了，但head之后的next还没有断开，
    // 所以可以顺势将head移动到末尾，再把next断开，最后返回newHead即可
    // recursive way
    if(head==nullptr || head->next==nullptr) return head;
    ListNode *h = reverseList(head->next);
    head->next->next = head;
    head->next = nullptr;
    return h;
}
//LinkedList l1;
//l1.AddNode(1); l1.AddNode(2); l1.AddNode(6); l1.AddNode(3); l1.AddNode(4); l1.AddNode(5); l1.AddNode(6);
//LC0203 run;
//ListNode* r = run.removeElements(l2.GetListHead(), 7);
//LinkedList::ShowLinkedList(r);
ListNode* LC0203::removeElements(ListNode* head, int val) {
    if(!head) return head;

    ListNode dummy(0);
    ListNode *pre = &dummy;
    dummy.next = head;

    while(head) {
        if(head->val == val) {
            ListNode *node = head;
            pre->next = head->next;
            head = head->next;
            delete node;
        } else {
            pre = head;
            head = head->next;
        }
    }

    return dummy.next;
}

ListNode* LC0160::getIntersectionNode(ListNode *headA, ListNode *headB) {
    if(!headA || !headB) return nullptr;

    // slower way
//    unordered_set <ListNode*> set;
//    while(headA) {
//        set.emplace(headA);
//        headA = headA->next;
//    }
//    while(headB) {
//        if(set.count(headB)) return headB;
//        set.emplace(headB);
//        headB = headB->next;
//    }
//    return nullptr;

    // faster way
    // 如果两个链长度相同的话，那么对应的一个个比下去就能找到，所以只需要把长链表变短即可。
    // 具体算法为：分别遍历两个链表，得到分别对应的长度。然后求长度的差值，把较长的那个链表向后移动这个差值的个数，然后一一比较即可
//    auto diff = [](ListNode* l1, ListNode* l2) -> int  {
//        int len1 = 0;
//        while(l1) {
//            l1 = l1->next;
//            len1++;
//        }
//        int len2 = 0;
//        while(l2) {
//            l2 = l2->next;
//            len2++;
//        }
//        return len1-len2;
//    };
//
//    int n = diff(headA, headB);
//    if(n>0)
//        while(n-- > 0)
//            headA = headA->next;
//    else
//        while(n++ < 0)
//            headB = headB->next;
//
//    while(headA && headB && headA!=headB) {
//        headA = headA->next;
//        headB = headB->next;
//    }
//    return (headA && headB) ? headA : nullptr;

    // tricky way
    // 虽然题目中强调了链表中不存在环，但是可以用环的思想来做，
    // 这里让两条链表分别从各自的开头开始往后遍历，当其中一条遍历到末尾时，
    // 跳到另一个条链表的开头继续遍历。两个指针最终会相等，而且只有两种情况，一种情况是在交点处相遇，
    // 另一种情况是在各自的末尾的空节点处相等。为什么一定会相等呢，因为两个指针走过的路程相同，
    // 是两个链表的长度之和，所以一定会相等。这个思路真的很巧妙，而且更重要的是代码写起来特别的简洁
    ListNode *a=headA, *b=headB;
    while(a!=b) {
        a = a ? a->next : headB;
        b = b ? b->next : headA;
    }
    return a;
}

bool LC0141::hasCycle(ListNode *head) {
    // time(N) space(N)
    unordered_set<ListNode*> set;
    while(head!=nullptr) {
        if(set.count(head)) return true;
        else {
            set.insert(head);
            head=head->next;
        }
    }
    return false;

    // fast/slow pointers, no extra space
    ListNode *fast, *slow;
    fast=slow=head;
    while(fast) {
        if(fast->next==nullptr) return false;
        if((fast=fast->next->next)==(slow=slow->next)) return true;
    }
    return false;
}

//LinkedList l1;
//l1.AddNode(1); l1.AddNode(2); l1.AddNode(5); l1.AddNode(2); l1.AddNode(2);
//LC0083 run;
//ListNode* r = run.deleteDuplicates(l1.GetListHead());
//LinkedList::ShowLinkedList(r);
ListNode* LC0083::deleteDuplicates(ListNode* head) {
    if(!head || !head->next) return head;

    unordered_set<int> set;
    set.insert(head->val);
    ListNode* tail = head;

    while(tail->next) {
        if(!set.count(tail->next->val)) {
            set.insert(tail->next->val);
            tail = tail->next;
        } else {
            ListNode* node = tail->next;
            tail->next = tail->next->next;
            delete node;
        }
    }

    return head;
}

//LinkedList l1, l2;
//l1.AddNode(1); l1.AddNode(2); l1.AddNode(4);
//l2.AddNode(1); l2.AddNode(3); l2.AddNode(4);
//LC0021 run;
//ListNode* r = run.mergeTwoLists(l1.GetListHead(), l2.GetListHead());
//LinkedList::ShowLinkedList(r);
ListNode* LC0021::mergeTwoLists(ListNode* l1, ListNode* l2) {
    // time(N), iterative
    ListNode head(0);
    ListNode *tail=&head;
    while(l1 && l2) {
        if(l1->val < l2->val) {
            tail->next = l1;
            l1 = l1->next;
        } else {
            tail->next = l2;
            l2 = l2->next;
        }
        tail=tail->next;
    }
    if(l1) tail->next=l1;
    if(l2) tail->next=l2;
    return head.next;

    // time(N), recursive
    if(l1==nullptr || l2==nullptr) return l1==nullptr ? l2 : l1;
    if(l1->val < l2->val) {
        l1->next = mergeTwoLists(l1->next , l2);
        return l1;
    } else {
        l2->next = mergeTwoLists(l1, l2->next);
        return l2;
    }
}

int StackArithmetic::priority(char c) {
    if(priority_map.count(c))
        return priority_map[c];
    else
        return -1;
}

string StackArithmetic::toPostFix(string str) {
    stack<char> s;
    string res;
    char e;
    for(auto &c:str) {
        switch(c) {
            case '(':
                s.push(c);
                break;
            case ')':
                while(s.size() && (e=s.top() != '(')) {
                    res+=c;
                    s.pop();
                }
                break;
            case '+':
            case '-':
            case '*':
            case '/':
                while(priority(e=s.top()) >= priority(c)) {
                    res+=e;
                    s.pop();
                }
                break;
            default:
                if(isdigit(c))
                    res+=c;
                break;
        }
    }
    while(s.size()) {
        res+=s.top();
        s.pop();
    }

    return res;
}

int StackArithmetic::calculate(string str) {
    priority_map['(']=0; priority_map['+']=1; priority_map['-']=1; priority_map['*']=2; priority_map['/']=2;

    stack<int> s;
    int v = 0;
    for(auto &c:str) {
        if(isdigit(c)) {
            v = v*10 + (c-'0'); continue;
        }
        if(v) {
            s.push(v);
            v = 0;
        }

        int z = 0;
        int y = s.top(); s.pop();
        int x = s.top(); s.pop();

        switch(c) {
            case '+': z=x+y; break;
            case '-': z=x-y; break;
            case '*': z=x*y; break;
            case '/': z=x/y; break;
        }

        s.push('0'+z);
    }
    return s.top()-'0';
}

/***********  Linked List  **********/
ListNode* LC0002::addTwoNumbers(ListNode* l1, ListNode* l2) {
    // 建立一个新链表，然后把输入的两个链表从头往后撸，每两个相加，添加一个新节点到新链表后面。为了避免两个输入链表同时为空，
    // 我们建立一个 dummy 结点，将两个结点相加生成的新结点按顺序加到 dummy 结点之后，由于 dummy 结点本身不能变，所以用一个指针 cur
    // 来指向新链表的最后一个结点。好，可以开始让两个链表相加了，这道题好就好在最低位在链表的开头，所以可以在遍历链表的同时按从低到高的顺
    // 序直接相加。while 循环的条件两个链表中只要有一个不为空行，由于链表可能为空，所以在取当前结点值的时候，先判断一下，若为空则取0，
    // 否则取结点值。然后把两个结点值相加，同时还要加上进位 carry。然后更新 carry，直接 sum/10 即可，然后以 sum%10 为值建立一个新结点，
    // 连到 cur 后面，然后 cur 移动到下一个结点。之后再更新两个结点，若存在，则指向下一个位置。while 循环退出之后，
    // 最高位的进位问题要最后特殊处理一下，若 carry 为1，则再建一个值为1的结点
    ListNode *dummy = new ListNode(-1), *cur = dummy;
    int c = 0;
//    while(l1 || l2) {
//        int val1 = l1 ? l1->val : 0;
//        int val2 = l2 ? l2->val : 0;
//        int sum = val1 + val2 + c;
//        cur->next = new ListNode(sum % 10);
//        c = sum/10;
//        cur = cur->next;
//        l1 = l1 ? l1->next : nullptr;
//        l2 = l2 ? l2->next : nullptr;
//    }
//    if(c) cur->next = new ListNode(c);

    while(l1 || l2 || c){
        int sum = (l1 ? l1->val : 0) + (l2 ? l2->val : 0) + c;
        c = sum/10;
        cur->next = new ListNode(sum%10);
        cur = cur->next;
        l1 = l1 ? l1->next : nullptr;
        l2 = l2 ? l2->next : nullptr;
    }
    return dummy->next;
}