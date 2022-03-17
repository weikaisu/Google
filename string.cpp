
#include "string.h"

// 可顯示字元編號範圍是32-126（0x20-0x7E），共95個字元。
// 大寫：65~90, 小寫：97~122
// 數字：48~57(0~9)
// 跟char有關的hash table都可以用 array<int,128> map; map.fill(0);來放

bool LC0953::isAlienSorted(vector<string>& words, string order) {
    array<int,128> map; map.fill(0);
    for(int i=0; i<order.size(); i++)
        map[order[i]]=i;

    // 对于正常的字母顺序，就是按字母来比较，只要有字母不同的话，就可以知道两个单词的顺序了，假如比较的字母均相同，但是有一个单词提前结束了，
    // 而另一个单词后面还有字母，则短的那个单词排前面。整体比较的思路仍然相同，就是字母顺序要用其给定的顺序，所以用一个 HashMap
    // 来建立字母和其对应位置之间的映射，这样在比较字母顺序的时候就可以从 HashMap 中直接取值。在验证顺序的时候，只需要两两进行验证，
    // 若某一对的顺序不符合，则直接返回 false。具体的比较方法还是跟之前说的，逐个字母进行比较，为了避免越界，遍历的时候只能遍历到二者中较短
    // 的长度。若对应位上的字母相同，则直接跳过；若前面的字母顺序靠后，则直接返回 false，否则 break 掉（注意这里不能直接返回 true
    // 的原因是后面有可能还会出现不合题目要求的情况）。之后还要验证前面提到的一种情况，就是当较短的单词是较长单词的子串时，而且后面的单词较短
    // 时，也需要返回 false。当外层 for 循环正常退出后，返回 true 即可
//    for(int i=1; i<words.size(); i++) {
//        string w0=words[i-1], w1=words[i];
//        for(int j=0; j<w0.size()&&j<w1.size(); j++) {
//            if(w0[j]==w1[j]) continue;
//            if(map[w0[j]]>map[w1[j]]) return false;
//            else break;
//        }
//        if(w0.size()>w1.size() && w0.substr(0,w1.size()) == w1) return false;
//    }
//    return true;

    // 把順序當作字母的ASCII碼來排序
    for(auto &word:words)
        for(auto &c:word)
            c = map[c];
    return is_sorted(words.begin(), words.end());
}

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

string LC0482::licenseKeyFormatting(string s, int k) {
    // 正确的注册码的格式是每K个字符后面跟一个短杠，每一部分的长度为K，第一部分长度可以小于K，另外，字母必须是大写的。那么由于第一部分可以
    // 不为K，那么我们可以反过来想，我们从S的尾部往前遍历，把字符加入结果res，每K个后面加一个短杠，那么最后遍历完再把res翻转一下即可，
    // 注意翻转之前要把结尾的短杠去掉(如果有的话)
    string res = "";
    for(int i=s.size()-1; i>=0; i--)
        if(s[i]!='-')
            ((res.size()%(k+1)-k) ? res : res+='-') += toupper(s[i]);
    return string(res.rbegin(), res.rend());
}

bool LC0459::repeatedSubstringPattern(string s) {
    // 这道题给了我们一个字符串，问其是否能拆成n个重复的子串。那么既然能拆分成多个子串，那么每个子串的长度肯定不能大于原字符串长度的一半，
    // 那么我们可以从原字符串长度的一半遍历到1，如果当前长度能被总长度整除，说明可以分成若干个子字符串，我们将这些子字符串拼接起来看跟原字符
    // 串是否相等。 如果拆完了都不相等，返回false
    int n = s.size();
    for(int i=n/2; i>=1; i--)
        if(n%i==0) {
            string t="";
            for(int j=0; j<n/i; j++)
                t += s.substr(0,i);
            if(t==s) return true;
        }

    return false;
}

int LC0434::countSegments(string s) {
    // 遍历字符串，遇到空格直接跳过，如果不是空格，则计数器加1，然后用个while循环找到下一个空格的位置，这样就遍历完了一个单词，
    // 再重复上面的操作直至结束
    int res = 0;
//    for(int i=0; i<s.size(); i++) {
//        if(s[i] == ' ') continue;
//        res++;
//        while(i<s.size() && s[i] != ' ') i++;
//    }
//    return res;

    // 统计单词开头的第一个字符，因为每个单词的第一个字符前面一个字符一定是空格，利用这个特性也可以统计单词的个数
    for(int i=0; i<s.size(); i++)
        if(s[i]!=' ' && (i==0 || s[i-1]==' ')) res++;
    return res;
}

string LC0415::addStrings(string num1, string num2) {
    // 一位一位相加，然后算和算进位，最后根据进位情况看需不需要补一个高位
    int i=num1.size()-1, j=num2.size()-1;
    string res;
    int c = 0;
    while(i>=0 || j>=0) {
        int a = i>=0 ? num1[i--]-'0' : 0;
        int b = j>=0 ? num2[j--]-'0' : 0;
        int sum = a + b + c;
        res.insert(res.begin(), sum%10+'0');
        c = sum/10;
    }
    return c ? '1'+res : res;
}

vector<string> LC0412::fizzBuzz(int n) {
    // 这道题真心没有什么可讲的，就是分情况处理就行了。
    // 注意！i%15需先括號起來再判斷是否為0
    vector<string> res;
    for(int i=1; i<=n; i++) {
        if(!(i%15)) res.push_back("FizzBuzz");
        else if(!(i%3)) res.push_back("Fizz");
        else if(!(i%5)) res.push_back("Buzz");
        else res.push_back(to_string(i));
    }
    return res;
}

bool LC0392::isSubsequence(string s, string t) {
    // 用两个指针分别指向字符串s和t，然后如果字符相等，则i和j自增1，反之只有j自增1，最后看i是否等于s的长度，等于说明s已经遍历完了，
    // 而且字符都有在t中出现过
    int i=0;
    for(int j=0; i<s.size()&&j<t.size(); j++)
        if(s[i]==t[j]) i++;
    return i==s.size();
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

bool LC0125::isPalindrome(string s) {
    // 所谓回文，就是一个正读和反读都一样的字符串，比如“level”或者“noon”等等就是回文串。但是这里，加入了空格和非字母数字的字符，
    // 增加了些难度，但其实原理还是很简单：只需要建立两个指针，left和right, 分别从字符的开头和结尾处开始遍历整个字符串，
    // 如果遇到非字母数字的字符就跳过，继续往下找，直到找到下一个字母数字或者结束遍历，如果遇到大写字母，就将其转为小写。
    // 等左右指针都找到字母数字时，比较这两个字符，若相等，则继续比较下面两个分别找到的字母数字，若不相等，直接返回false
    // tolower傳非字母進去會直接回傳
    if(s.empty()) return true;
    int l=0, r=s.size()-1;
    while(l<r) {
        if(!isalnum(s[l])) l++;
        else if(!isalnum(s[r])) r--;
        else if (tolower(s[l++]) != tolower(s[r--])) return false;
    }
    return true;
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