
#include "list.h"

// 可顯示字元編號範圍是32-126（0x20-0x7E），共95個字元。
// 跟char有關的hash table都可以用 array<int,128> map; map.fill(0);來放

/***********  Vector List  **********/
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

    //輾轉相除法
    auto gcd_divide = [](const auto &self, int x, int y)->int {
        return x==0 ? y : self(self, y%x, x);
    };

    unordered_map<int,int> map;
    int res = 0;
    for(auto &n:deck) ++map[n];
    for(auto &m:map)
        res = gcd_divide(gcd_divide, res, m.second);
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
//    unordered_set<int> set;
//    vector<int> res;
//    for(auto n:nums)
//        set.insert(n);
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

int LC0409::longestPalindrome(string s) {
    array<int,128> map; map.fill(0);
    int even=0, odd=0;
    for(auto c:s) ++map[c];
    for(auto v:map) {
        even += v&(~1); // 清掉last bit取得偶數值，累計多少偶數；
        odd  |= v&( 1); // 看是否有積數值可作為回文中間那一char
    }
    return even+odd;
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
    cout << endl;
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
    int sum=0, n=nums.size();

    for_each(nums.begin(), nums.end(), [&](int n) {sum+=n;});
    return (n*(n+1))/2 - sum;
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
    int c=1;
    for(int i=digits.size()-1 ; i>=0 ; i--) {
        int v = digits[i]+c;
        digits[i] = v % 10;
        c = v / 10;
    }
    if(c) digits.emplace(digits.begin(), c);
    return digits;
}

//LC0027 run;
//vector<int> n{0,1,2,2,3,0,4,2}; // val=2
//vector<int> n{3,2,2,3}; // val=3
//vector<int> n{1}; // val=1
//cout << run.removeElement(n, 1) << endl;
//for(auto i:n) cout << i << ' ';
//cout << endl;
int LC0027::removeElement(vector<int>& nums, int val) {
    int s=nums.size();
    int r=0;
    for(int i=0 ; i<nums.size() ; i++) {
        if(nums[i]==val)
            s--;
        else
            nums[r++]=nums[i];
    }
    return s;
}

//LC0026 run;
//vector<int> n{0,0,1,1,1,2,2,3,3,4};
//vector<int> n{1,1,2};
//cout << run.removeDuplicates(n) << endl;
//for(auto i:n) cout << i << ' ';
//cout << endl;
int LC0026::removeDuplicates(vector<int>& nums) {
    int s=nums.size(); if(s<=1) return s;
    int r=1, p=nums[0];
    for(int i=1 ; i<nums.size() ; i++) {
        if(p == nums[i])
            s--;
        else
            nums[r++]=nums[i];
        p=nums[i];
    }
    return s;
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
    // time(N), iterative
    ListNode *c=nullptr, *n=nullptr;
    while(head) {
        //把n指到head->next
        //把n放在head->next的位置
        n=head->next;
        head->next=c;
        c=head;
        head=n;
    }
    return c;

    // time(N), recursive
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
