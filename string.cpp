
#include "string.h"

int LC0929::numUniqueEmails(vector<string>& emails) {
    // 邮件名里可能会有两个特殊符号，点和加号，对于点采取直接忽略的做法，对于加号则是忽略其后面所有的东西，现在问我们有多少个不同的邮箱。
    // 没有太多的技巧，就直接遍历一下所有的字符，遇到点直接跳过，遇到 '+' 或者 '@' 直接 break 掉。注意这里其实有个坑，就是域名中也可能有点，
    // 而这个点是不能忽略的，所以要把 '@' 及其后面的域名都提取出来，连到之前处理好的账号后面，一起放到一个 HashSet 中，
    // 利用其可以去重复的特性，最终剩余的个数即为所求
    unordered_set<string> set;
    for(auto &email:emails) {
        string addr;
        for(auto &c:email) {
            if(c == '.') continue;
            if(c == '+' || c== '@') break;
            addr.push_back(c);
        }
        addr += email.substr(email.find('@'));
        set.insert(addr);
    }
    return set.size();
}

vector<string> LC0884::uncommonFromSentences(string s1, string s2) {
    // 把每个单词都提取出来，然后统计其在两个句子中出现的个数，若最终若某个单词的统计数为1，则其一定是符合题意的。
    // 所以我们可以先将两个字符串拼接起来，中间用一个空格符隔开，这样提取单词就更方便一些。在 Java 中，可以使用 split()
    // 函数来快速分隔单词，但是在 C++ 中就没这么好命，只能使用字符串流 istringstream，并用一个 while 循环来一个一个提取。
    // 当建立好了单词和其出现次数的映射之后，再遍历一遍 HashMap，将映射值为1的单词存入结果 res 即可
    unordered_map<string,int> map;
    vector<string> res;
    istringstream in(s1 + ' ' + s2);
    for(string w; in>>w; ) ++map[w];
    for(auto &w : map)
        if(w.second==1) res.push_back(w.first);
    return res;
}

string LC0819::mostCommonWord(string paragraph, vector<string>& banned) {
    // 给了我们一个字符串，是一个句子，里面有很多单词，并且还有标点符号，然后又给了我们一个类似黑名单功能的一个字符串数组，
    // 让我们在返回句子中出现的频率最高的一个单词。要求非常简单明了，那么思路也就简单粗暴一些吧。
    // 因为我们返回的单词不能是黑名单中的，所以我们对于每一个统计的单词肯定都需要去黑名单中检查，为了提高效率，
    // 我们可以把黑名单中所有的单词放到一个HashSet中，这样就可以常数级时间内查询了。然后要做的就是处理一下字符串数组，
    // 因为字符串中可能有标点符号，所以我们先过滤一遍字符串，这里我们使用了系统自带的两个函数isalpha()和tolower()函数，
    // 其实自己写也可以，就放到一个子函数处理一下也不难，这里就偷懒了，遍历每个字符，如果不是字母，就换成空格符号，如果是大写字母，
    // 就换成小写的。然后我们又使用一个C++中的读取字符串流的类，Java中可以直接调用split函数，叼的飞起。但谁让博主固执的写C++呢，
    // 也无所谓啦，习惯就好，这里我们也是按照空格拆分，将每个单词读出来，这里要使用一个mx变量，统计当前最大的频率，
    // 还需要一个HashMap来建立单词和其出现频率之间的映射。然后我们看读取出的单词，如果不在黑名单中内，并且映射值加1后大于mx的话，
    // 我们更新mx，并且更新结果res即可
    unordered_set<string> set (banned.begin(), banned.end());
    unordered_map<string,int> map;
    string res = "";
    int mx = 0;
    for(auto &c:paragraph) c = isalpha(c) ? tolower(c) : ' ';
    istringstream in(paragraph);
    for(string w; in>>w; )
        if(!set.count(w) && ++map[w] > mx) {
            mx = map[w];
            res = w;
        }
    return res;
}

//LC0290 run;
//cout << run.wordPattern("abba", "dog cat cat dog") << endl;
bool LC0290::wordPattern(string pattern, string s) {
    // 首先检查其是否在 HashMap 中出现，若出现，其映射的单词若不是此时对应的单词，则返回 false。
    // 如果没有在 HashMap 中出现，我们还要遍历一遍 HashMap，看新遇到的单词是否已经是其中的映射，
    // 若已经有其他映射，直接返回 false，如果没有，再跟新遇到的字符建立映射。最后循环退出后，要检查此时的 i 是否和 n 相同，
    // 这是检查一对一映射的最后一步，因为当 str 中的单词处理完了之后，pattern 中就不能有多余的字符了
    unordered_map<char, string> map;
    istringstream in(s);
    int i = 0;
    for(string word; in>>word; i++) {
        if(i>=pattern.size()) continue;
        if(map.count(pattern[i])) {
            if (map[pattern[i]] != word) return false;
        } else {
            for(auto m:map)
                if(m.second == word) return false;
            map[pattern[i]] = word;
        }
    }
    return i==pattern.size();
}

//LC0067 run;
//cout << run.addBinary("11","1");
string LC0067::addBinary(string a, string b) {
    int i=a.size()-1, j=b.size()-1, c=0;
    string ans;

    while( i>=0 || j>=0 || c) {
        c += i>=0 ? a[i--]-'0' : 0;
        c += j>=0 ? b[j--]-'0' : 0;
        ans = to_string(c%2) + ans;
        c = c/2;
    }
    return ans;
}

//LC0058 run;
//cout << run.lengthOfLastWord("luffy is still joyboy") << endl;
int LC0058::lengthOfLastWord(string& s) {
    int last=0, curr=0;
    for(auto c:s) {
        if(' '==c) {
            if(curr) last=curr;
            curr=0;
        }
        else curr++;
    }
    return curr ? curr : last;
}

//LC0028 run;
//cout << run.strStr("hello", "ll") << endk;
int LC0028::strStr(string haystack, string needle) {
    if(!needle.size()) return 0;

    int m = haystack.size();
    int n = needle.size();
    if(m==n) return haystack==needle ? 0 : -1;

    for(int i=0 ; i<=m-n ; i++) {
        int j;
        for(j=0 ; j<n ; j++) {
            if(haystack[i+j]!=needle[j]) break;
        }
        if(j==n) return i;
    }
    return -1;

    // simplified
    for(int i=0 ; ; i++) {
        for(int j=0 ; ; j++) {
            if(j==needle.size())  return i;
            if(i+j==haystack.size()) return -1;
            if(haystack[i+j] != needle[j]) break;
        }
    }
    return -1;
}

//LC0020 run;
//string s{"()[]{}"};
//cout << run.isValid(s) << endl;
//https://www.techiedelight.com/convert-char-to-string-cpp/
bool LC0020::isValid(string s) {
    deque<char> dq;
    set<string> t{"{}", "[]", "()"};

    for(auto c:s) {
        dq.push_front(c);
        if(dq.size()>=2) {
            auto it = dq.begin();
            if(t.count(string(1,*(it+1)) + string(1, *(it)))) {
                dq.pop_front();
                dq.pop_front();
            }
        }
    }
    return dq.size()==0;
    //cout << "type: "<< typeid(*(it+1)).name() << endl;
}

//LC0014 run;
//vector<string> s{{"flower"},{"flow"},{"flight"}};
//cout << run.longestCommonPrefix(s) << endl;
string LC0014::longestCommonPrefix(vector<string>& strs) {
    string ans{""};
    int l_idx=0, c_idx=0;
    while(l_idx<strs.size() && c_idx<strs[l_idx].size()) {
        char p, c=strs[l_idx][c_idx];
        if(!l_idx) p=c;
        else if(p!=c) break;

        if(l_idx==strs.size()-1) {
            l_idx=0;
            c_idx++;
            ans+=p;
        } else {
            l_idx++;
        }
    }
    return ans;
}

//LC0013 run;
//cout << run.romanToInt("MCMXCIV") << endl;
int LC0013::romanToInt(string s) {
    unordered_map<char, int> t {
        {'M', 1000}, {'D', 500},
        {'C', 100},  {'L', 50},
        {'X', 10},   {'V', 5},
        {'I', 1} };

    int ans=0;
    for(int i=0 ; i<s.size()-1 ; i++) {
        char c=s[i], c_nxt=s[i+1];
        if(t[c]<t[c_nxt]) ans-=t[c];
        else ans+=t[c];
    }
    ans+=t[s[s.size()-1]];
    return ans;
}

//LC0009 run;
//cout << run.isPalindrome(1000000001) << endl;
bool LC0009::isPalindrome(int x) {
    if(x<0) return false;

    int f=x, b=0;
    while(x>0 && b<INT32_MAX/10) {
        b = b*10 + x%10;
        x/=10;
    }
    return f==b;
}