
#include "string.h"

// 可顯示字元編號範圍是32-126（0x20-0x7E），共95個字元。
// 大寫：65~90, 小寫：97~122
// 數字：48~57(0~9)
// 跟char有關的hash table都可以用 array<int,128> map; map.fill(0);來放

int LC1360::daysBetweenDates(string date1, string date2) {
    // 给定两个日期，年的范围是[ 1971 , 2100 ] [1971,2100][1971,2100]，问两个日期之间隔了多少天。日期以YY-MM-DD形式给出。
    array<int,13> days{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    function<bool(int)> isLeapYear = [&](int year) -> bool {
        return year%400==0 || (year%100 !=0 && year%4 == 0);
    };
    function<int(const string)> daysFrom1971 = [&](const string str) -> int {
        int y, m , d;
        std::sscanf(str.c_str(), "%d-%d-%d", &y, &m, &d);
        int res=0;
        for(int i=1971; i<y; i++)
            res += (365 + isLeapYear(i));
        for(int i=1; i<m; i++) {
            res += days[i];
            if(i==2) res += isLeapYear(y); //注意！這裡isLeapYear傳的是y，不是i
        }
        return res + d;
    };

    return std::abs(daysFrom1971(date1) - daysFrom1971(date2));
}

int LC1332::removePalindromeSub(string s) {
    // 给了一个只有字母a和b的字符串，说是每次可以删除一个"回文子序列"，问最少需要删除多少次，可以将给定字符串变为空串。
    // 不是"回文子字串"
    // 每次移除所有相同的字母，因为相同的字母话，不管多少个，一定是回文串。
    // 又因为题目中说了只有a和b两个字母，那么最多只需要2次就可以清空字符串。
    // 再想想什么情况下可以小于2，当给定字符串是空串的话，不用移除，当然题目中限定了字符串长度至少为1。
    // 再有就是假如给定的字符串本身就是回文串的话，那么直接一次就能可以全部移除了，
    // 所以这道题的返回值只有两种，1或2。想通了这些，代码就很好写了，只需要判断一下给定的字符串是否是回文串就行了，
    // 这里用双指针来一个一个的比较对应字母就行了。首先判空，若为空直接返回0（虽然题目限定了不为空，出于职业习惯，还是加上了）。
    // 然后调用子函数判断是否为回文串，是的话返回1，否则返回2
//    function<bool(string)> isPalindrome = [&](string str) -> bool {
//        int l=0, r=str.size()-1;
//        while(l<r)
//            if(s[l++] != s[r--]) return false;
//        return true;
//    };
//    if(s.empty()) return 0;
//    return isPalindrome(s) ? 1 : 2;

    // 将字符串翻转一下，若和原字符串相同，则是回文串，这也是回文串的定义。这里可以一行解题，用2减去判断是否是回文串的结果，
    // 是回文串的话就会减去1，然后再减去判断空串的结果，若是空串就会减去1

    return 2 - (string(s.rbegin(), s.rend()) == s) - s.empty();

}

int LC1323::maximum69Number(int num) {
    // 给了一个只含有6和9的正整数，现在说是可以将6变成9，或者将9变成6，最多可以变换一次，让返回可以得到的最大的数字。既然要得到最大的数字，
    // 那么肯定是把6变成9得到的数字最大，而且尽量去变高位上的数字。所以方法就是从高位开始遍历，若遇到6，则变为9即可，变换了之后直接 break
    // 掉就行了，因为最多只能变换一次。为了能方便从高位开始遍历，可以将给定的数字转为字符串开始遍历，之后变换完了之后再转为整型数就可以了
    string str = std::to_string(num);
    for(char &c:str)
        if(c == '6') {
            c = '9';
            break;
        }
    return std::stoi(str);
}

string LC1309::freqAlphabets(string s) {
    // 暴力解的时间复杂度也就是O(n)，循环一遍字符串即可。循环时，查看当前位加二的位置是否为井号，如果是，就将当前位与后一位组合起来，查看其对
    // 应的字符，并将该字符加入返回结果，同时下标加二继续循环。反之，如果当前位后2位不是井号，那么将当前位数字对应的字符加入返回结果即可
    string res;
    int l = s.size();
    for(int i=0; i<l; i++) {
        int c =  s[i]-'0';
        if(i+2<l && s[i+2]=='#') {
            int n = c*10 + (s[i+1]-'0');
            res += ('j' + n-10);
            i+=2;
        } else {
            res += ('a' + c-1);
        }
    }
    return res;
}

int LC1154::dayOfYear(string date) {
    // 这里唯一的难点就是判断闰年了吧。先用个数组列出非闰年各个月的天数，然后分别从给定 date 字符串中提取出年月日，并转为整型数。然后将当前月
    // 之前的天数都累加到结果 res 中，接下来判断当前月是否大于2月，没有的话都不用判断闰年了。超过了2月就要判断当前年是否是闰年，判断方法很简
    // 单，若能被 400 整除，一定是闰年，或着不能被 100 整除，但能被4整除的也是闰年。是闰年的话就再多加一天，最后再加上当前的天数返回即可
    array<int,12> days {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int res=0, year=stoi(date.substr(0,4)), month=stoi(date.substr(5,2)), day=stoi(date.substr(8,2));

    for(int i=0; i<month-1; i++)
        res+=days[i];
    if(month>2 && (!(year%400) || (year%100 && !(year%4))))
        res++;
    return res+day;
}

string LC1108::defangIPaddr(string address) {
    // 直接遍历原字符串，遇到点了，就直接把 [.] 加入，否则就加入当前字符即可
    string res;
    for(auto &c:address) {
        if(c=='.')
            res += "[.]";
        else
            res += c;
    }
    return res;

    // 用 regex_replace 来直接进行替换.
    // !處理時間會長很多!
    return regex_replace(address, regex("[.]"), "[.]");
}

vector<string> LC1078::findOcurrences(string text, string first, string second) {
    // 我们并不用保存所有的单词，因为这里只关心前两个单词是啥，所以可以使用两个变量 pre2 和 pre 来记录前面的两个单词，当其分别等于 first
    // 和 second 的时候，将当前单词加入结果 res 中，并且 pre2 赋值为 pre，pre赋值为当前单词即可
    vector<string> res;
    istringstream iss(text);
    string pre2, pre1, curr;
    while(iss>>curr) {
        if(pre2==first && pre1==second) res.push_back(curr);
        pre2=pre1;
        pre1=curr;
    }
    return res;
}

string LC1071::gcdOfStrings(string str1, string str2) {
    // 由于 str1 和 str2 可以被同一个x串整除，那么 str1+str2 和 str2+str1 一定是相同的，不信大家可以自行带例子去验证。而且最大的x的长
    // 度是 str1 和 str2 长度的最大公约数相同（是不是感觉很神奇，求大佬证明），这样的话直接浓缩到一行就搞定了
//    return (str1 + str2 == str2 + str1) ? str1.substr(0, gcd(str1.size(), str2.size())) : "";

    // 若存在这样的x的话，那么短的字符串一定是长的字符串的子串，比如例子1和例子2。这样的话其实是可以化简的，当长串中的前缀（和短串的长度相同）
    // 不等于短串的时候，说明x不存在，可以直接返回空，否则从长串中取出和短串长度相同的前缀，继续调用递归，直到其中一个为空的时候，返回另一个就
    // 可以了
    if(str1.size()<str2.size()) return gcdOfStrings(str2,str1);
    if(str2.empty()) return str1;
    if(str1.substr(0, str2.size()) != str2) return "";
    return gcdOfStrings(str1.substr(str2.size()), str2);

    // 由于这个x会重复出现在字符串中，所以其一定是个前缀，则字符串的所有前缀都有可能是这个x，于是乎只要遍历所有的前缀，然后来验证其是否可以
    // 整除这两个字符串就可以找到要求的x了。遍历 str1 的所有前缀，若 str1 的长度不是这个前缀的长度的整数倍，或者 str2 的长度不是这个前缀
    // 长度的整数倍，直接跳过。否则直接分别复制前缀直到和 str1，str2 的长度相同，再比较，若完全一样，则说明前缀是一个x，赋值给结果 res。
    // 这样遍历下来就能得到长度最长的x了
//    string res;
//    int m=str1.size(), n=str2.size();
//    for(int i=0; i<m; i++) {
//        if( m%(i+1)!=0 || n%(i+1)!=0 ) continue;
//        string pre=str1.substr(0,i+1), tostr1, tostr2;
//
//        for(int j=0; j<m/(i+1); j++)
//            tostr1+=pre;
//        if(tostr1!=str1) continue;
//
//        for(int j=0; j<n/(i+1); j++)
//            tostr2+=pre;
//        if(tostr2!=str2) continue;
//
//        res = pre;
//    }
//    return res;
}

string LC1047::removeDuplicates(string s) {
    // 这道题给了一个字符串，让移除所有相邻的重复字符，注意之前不相邻的字符可以在其他字符移除后变的相邻，从而形成的新的相邻的重复字符，所以只
    // 是简单移除一次不能保证能得到最终的结果。这里需要借助栈的思路来做，可以用字符串来模拟栈的后入先出的特性。遍历每个字符，若 res 不空，且
    // 最后一个字符和当前字符相同，则移除掉 res 的最后一个字符，否则将当前字符加入 res 中，这样最后剩下的即为所求
//    string res;
//    for(auto &c:s) {
//        if(res.size() && res.back() == c)
//            res.pop_back();
//        else
//            res.push_back(c);
//    }
//    return res;

    // 使用双指针来做，两个指针i和j，其中i指向去除重复后的最后一个字符的位置，j为遍历字符串S的位置，首先将 S[j] 赋值给 S[i]，然后看若i大
    // 于0，且 S[i-1] 和 S[i] 相等的，i自减2，这样就移除了重复，最后根据i的位置取出子串返回即可
    int i=0;
    for(int j=0; j<s.size(); j++) {
        s[i]=s[j];
        if(i && s[i]==s[i-1]) i-=2;
        i++;
    }
    return s.substr(0,i);
}

string LC1021::removeOuterParentheses(string s) {
    // 可以写的更简洁一些，并不需要等到找到整个合法括号子串后再加入结果 res，而是在遍历的过程中就加入。因为这里的括号分为两种，一种是合法子串
    // 的最外层括号，这种不能加到结果 res，另一种是其他位置上的括号，这种要加到 res。所以只要区分出这两种情况，就知道当前括号要不要加，区别
    // 的方法还是根据 cnt，当遇到左括号时，若此时 cnt 大于0，则一定不是合法子串的起始位置，可以加入 res，之后 cnt 自增1；同理，若遇到右括
    // 号，若此时 cnt 大于1，则一定不是合法子串的结束位置，可以加入 res，之后 cnt 自减1
    string res;
    int cnt = 0;
    for(auto &c:s) {
        if(c=='(' && cnt++ > 0) res.push_back(c);
        if(c==')' && cnt-- > 1) res.push_back(c);
    }
    return res;

    // 这道题给了一个合法的括号字符串，其可能由多个合法的括号字符子串组成，现在让把所有合法的子串的最外层的括号去掉，将剩下的拼接起来并返回，
    // 根据题目给的例子，不难理解题意。LeetCode 中关于括号的题目还是比较多的，比如 Valid Parentheses，Valid Parenthesis String，
    // Remove Invalid Parentheses，和 Longest Valid Parentheses 等。大多都是考察如何判断一个括号字符串是否合法，所谓的合法，大致就
    // 是左右括号个数要相同，每个右括号前面必须要有对应的左括号，一个比较简单的判断方法就是用一个变量 cnt，遇到左括号则自增1，遇到右括号则自
    // 减1，在这过程中 cnt 不能为负，且最后 cnt 必须为0。这道题限定了括号字符串一定是合法的，但也可以用这个方法来找出每个合法的子串部分，
    // 遍历字符串S，若当前字符为左括号，则 cnt 自增1，否则自减1。若 cnt 不为0，说明还不是一个合法的括号子串，跳过。否则我们就知道了一个合
    // 法括号子串的结束位置，用一个变量 start 记录合法括号子串的起始位置，初始化为0，这样就可以将去除最外层括号后的中间部分直接取出来加入结
    // 果 res 中，然后此时更新 start 为下一个合法子串的起始位置继续遍历即可
//    string res;
//    int cnt = 0, start = 0;
//    for(int i=0; i<s.size(); i++) {
//        (s[i]=='(') ? cnt++ : cnt--;
//        if(cnt) continue;
//        res += s.substr(start+1, i-start-1);
//        start = i+1;
//    }
//    return res;
}

vector<string> LC0937::reorderLogFiles(vector<string>& logs) {
    // We can break this problem into two tasks: 1) Parition 2) Sort letter-logs

    // Partition: letter-logs at the front, digit-logs at the back.
    // We're using stable_partition instead of partition to retain the original order.
    // stable_partition returns an iterator to the first element of the second group.
    auto it = stable_partition(logs.begin(), logs.end(), [](const string &str) {
        return isalpha(str.back());
    });

    // Sort letter-logs: We're only iterating on letter-logs in this case.
    // We're creating a substring for every element we compare that doesn't include the identifier
    // If the logs are the same except the identifier, we compare the strings, otherwise, the substrings
    sort(logs.begin(), it, [](const string &a, const string &b) {
        string suba = string(a.begin()+a.find(' '), a.end());
        string subb = string(b.begin()+b.find(' '), b.end());
        return (suba==subb) ? a<b : suba<subb;
    });

    return logs;

    // 这道题让给日志排序，每条日志是由空格隔开的一些字符串，第一个字符串是标识符，可能由字母和数字组成，后面的是日志的内容，只有两种形式的，
    // 要么都是数字的，要么都是字母的。排序的规则是对于内容是字母的日志，按照字母顺序进行排序，假如内容相同，则按照标识符的字母顺序排。而对于
    // 内容的是数字的日志，放到最后面，且其顺序相对于原顺序保持不变。博主感觉这道题似曾相识啊，貌似之前在很多 OA 中见过，最后还是被 LeetCode
    // 收入囊中了。其实这道题就是个比较复杂的排序的问题，两种日志需要分开处理，对于数字日志，不需要排序，但要记录其原始顺序。这里就可以用一个
    // 数组专门来保存数字日志，这样最后加到结果 res 后面，就可以保持其原来顺序。关键是要对字母型日志进行排序，同时还要把标识符提取出来，
    // 这样在遍历日志的时候，先找到第一空格的位置，这样前面的部分就是标识符了，后面的内容就是日志内容了，此时判断紧跟空格位置的字符，假如是数
    // 字的话，说明当前日志是数字型的，加入数组 digitLogs 中，并继续循环。如果不是的话，将两部分分开，存入到一个二维数组 data 中。之后要
    // 对 data 数组进行排序，并需要重写排序规则，要根据日志内容排序，若日志内容相等，则根据标识符排序。最后把排序好的日志按顺序合并，存入结
    // 果 res 中，最后别忘了把数字型日志也加入 res
//    vector<string> res, dig;
//    vector<vector<string>> let;
//    for(auto &log:logs) {
//        auto pos=log.find(' ');
//        if(isdigit(log[pos+1])) { dig.push_back(log); continue; }
//        let.push_back({log.substr(0,pos), log.substr(pos+1)});
//    }
//
//    sort(let.begin(), let.end(), [](vector<string> &a, vector<string> &b) {
//        return a[1]<b[1] || (a[1]==b[1] && a[0]<b[0]);
//    });
//
//    for(auto &l:let)
//        res.push_back(l[0]+' '+l[1]);
//    for(auto &d:dig)
//        res.push_back(d);
//
//    return res;
}

bool LC0925::isLongPressedName(string name, string typed) {
    // 直接用j遍历 typed 中每个字母，i初识时指向 name 的第一个字母，假如i小于m，且 name[i] 等于 typed[j-1] 时，则i自增1，否则的话，
    // 若此时j为0（说明第一个字母就不匹配），或者 typed[j] 不等于 typed[j - 1]（说明出现了无法匹配的新字母），则直接返回 false。循环退
    // 出后若i等于m则返回 true，否则返回 false
    int i=0, j=0, m=name.size(), n=typed.size();

    for( ; j<n; j++) {
        if(name[i]==typed[j]) i++;
        else if(!j || typed[j]!=typed[j-1]) return false;
    }
    return i==m;

    // 在用键盘敲入名字的时候，对于某个字母可能会长时间按键，这导可能会有多个相同字母输入，这种情况是允许的，现在给了两个字符串，name
    // 是朋友的名字，typed 是朋友敲入的字符串，问 typed 是否是朋友敲入的名字。其实这道题的本质是，对于 name 中每个位置的字母，
    // 对应在 typed 中的出现次数一定要相等或者更多，但是直接统计每个字符出现的次数是不对的，因为位置关系很重要，比如 abb 和 abab，
    // 虽然后者中a和b的出现次数都大于等于前者，但还是要返回 false。博主最先想的方法是用两个指针i和j分别提取 name 和 typed 字符串中每个字
    // 母出现的次数，如果 typed 中的次数小于 name 中的次数，则直接返回 false 即可，最终循环结束后，i和j应该分别为 name 和 typed 的长度，
    // 此时返回 true，否则返回 false
//    int i=0, j=0, m=name.size(), n=typed.size();
//    while(i<m || j<n) {
//        if(name[i]!=typed[j]) return false;
//        int si=i, sj=j;
//        while(i<m-1 && name[i]==name[i+1]) i++;
//        while(j<n-1 && typed[j]==typed[j+1]) j++;
//        if(i-si > j-sj) return false;
//        i++; j++;
//    }
//    return i==m && j==n;
}

string LC0917::reverseOnlyLetters(string s) {
    // 使用两个指针i和j，分别指向S串的开头和结尾。当i指向非字母字符时，指针i自增1，否则若j指向非字母字符时，指针j自减1，
    // 若i和j都指向字母时，则交换 S[i] 和 S[j] 的位置，同时i自增1，j自减1，这样也可以实现只翻转字母的目的
    int l=0, r=s.size()-1;
    while(l<r) {
        while(l<r && !isalpha(s[l])) l++;
        while(l<r && !isalpha(s[r])) r--;
        swap(s[l++],s[r--]);
    }
    return s;
}

string LC0824::toGoatLatin(string sentence) {
    // 将一句话转为山羊拉丁文，有几个规则，如果单词是元音开头的，那么直接在但此后加ma，如果是非元音开头的单词，那么把首字母移到末尾，
    // 并且加ma。还有就是根据当前是第几个单词，后面加几个a，估计是为了模仿羊叫声，拉长音，感觉更像绵羊音一样。此题难度不是很大，
    // 就照题目要求来做，不需要啥特别的技巧。首先为了快速检测开头字母是否为元音，我们将所有元音加入一个HashSet，注意大小写的元音都要加进去。
    // 然后要一个单词一个单词的处理，这里我们使用C++的字符串流类来快速的提取单词，对于每个提取出的单词，我们先加上一个空格，
    // 然后判断开头字母是否为元音，是的话直接加上，不然就去子串去掉首字母，然后将首字母加到末尾。后面再加上ma，还有相对应数目个a。
    // 这里我们定义一个变量cnt，初始化为1，每处理一个单词，cnt自增1，这样我们就知道需要加的a的个数了，最后别忘了把结果res的首空格去掉
    array<int,128> set; set.fill(0);
    set['a']=set['e']=set['i']=set['o']=set['u']=set['A']=set['E']=set['I']=set['O']=set['U']=1;
    istringstream ss(sentence);
    string res, w;
    int cnt=1;
    while(ss>>w)
        res += ' ' + (set[w[0]] ? w : w.substr(1)+w[0]) + "ma" + string(cnt++,'a');
    return res.substr(1);
}

bool LC0953::isAlienSorted(vector<string>& words, string order) {
    // 把順序當作字母的ASCII碼來排序
    array<unsigned,26> map{};
    for(unsigned i=0; i<order.size(); i++)
        map[order[i]-'a']=i;
    for(auto &word:words)
        for(auto &c:word)
            c = map[c-'a'];
    return is_sorted(words.begin(), words.end());

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
}

int LC0929::numUniqueEmails(vector<string>& emails) {
    // 使用lose lose hash function
    // http://www.cse.yorku.ca/~oz/hash.html
    // 來對email產生特定的值，最後再看去重後有幾個
    // 從左到右，從右到左掃一遍string
    auto hash = [](const string &addr) -> size_t {
        size_t val{};
        unsigned n = addr.size();
        unsigned i;
        for(i=0; i<n; i++) {
            char c=addr[i];
            if(c == '.') continue;
            if(c == '+' || c == '@') break;
            val = (val+c) << 1;
        }
        for(i=n-1; i>0; i--) {
            char c=addr[i];
            val = (val+c) << 1;
            if(c == '@') break;
        }
        return val;
    };

    unordered_set<size_t> s;
    for(auto &addr:emails)
        s.emplace(hash(addr));
    return s.size();

    // 邮件名里可能会有两个特殊符号，点和加号，对于点采取直接忽略的做法，对于加号则是忽略其后面所有的东西，现在问我们有多少个不同的邮箱。
    // 没有太多的技巧，就直接遍历一下所有的字符，遇到点直接跳过，遇到 '+' 或者 '@' 直接 break 掉。注意这里其实有个坑，就是域名中也可能有点，
    // 而这个点是不能忽略的，所以要把 '@' 及其后面的域名都提取出来，连到之前处理好的账号后面，一起放到一个 HashSet 中，
    // 利用其可以去重复的特性，最终剩余的个数即为所求
//    unordered_set<string> set;
//    for(auto &email:emails) {
//        string addr;
//        for(auto &c:email) {
//            if(c == '.') continue;
//            if(c == '+' || c== '@') break;
//            addr.push_back(c);
//        }
//        addr += email.substr(email.find('@'));
//        set.insert(move(addr));
//    }
//    return set.size();
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
//    unordered_set<string> set (banned.begin(), banned.end());
//    unordered_map<string,int> map;
//    string res = "";
//    int mx = 0;
//    for(auto &c:paragraph) c = isalpha(c) ? tolower(c) : ' ';
//    istringstream in(paragraph);
//    for(string w; in>>w; )
//        if(!set.count(w) && ++map[w] > mx) {
//            mx = map[w];
//            res = w;
//        }
//    return res;

    // 僅使用一個map再從map裡erase掉banned的字串，一個迴圈同時去掉非字母、轉小寫、及收集出現次數。
    unordered_map<string,int> map;
    string res="";
    int m = 0;
    int n = paragraph.size();

    for(int i=0; i<n; i++) {
        char c = tolower(paragraph[i]);
        if(isalpha(c)) {
            res+=c;
        } else if(res!=""){
            ++map[res];
            res="";
        }
    }
    if(isalpha(paragraph[n-1])) ++map[res];
    res="";

    for(auto s:banned) map.erase(s);

    for(auto e:map) {
        if(e.second>m) {
            res = e.first;
            m = e.second;
        }
    }
    return res;
}

bool LC0796::rotateString(string s, string goal) {
    // 一行完成的方法，就是我们其实可以在A之后再加上一个A，这样如果新的字符串(A+A)中包含B的话，说明A一定能通过偏移得到B。
    // 就比如题目中的例子，A="abcde", B="bcdea"，那么A+A="abcdeabcde"，里面是包括B的，所以返回true即可
//    return s.size()==goal.size() && (s+s).find(goal) != string::npos;
    return s.size() != goal.size() ? false : (s+s).find(goal) != std::string::npos;

    // 这道题给了我们两个字符串A和B，定义了一种偏移操作，以某一个位置将字符串A分为两截，并将两段调换位置，如果此时跟字符串B相等了，
    // 就说明字符串A可以通过偏移得到B。现在就是让我们判断是否存在这种偏移，那么最简单最暴力的方法就是遍历所有能将A分为两截的位置，
    // 然后用取子串的方法将A断开，交换顺序，再去跟B比较，如果相等，返回true即可，遍历结束后，返回false
    if(s.size() != goal.size()) return false;
    for(int i =0; i<s.size(); i++) {
        if(s.substr(i,s.size()-1) + s.substr(0,i) == goal) return true;
    }
    return false;
}

string LC0709::toLowerCase(string s) {
    // 小写字母比其对应的大写字母的ASCII码大32，所以我们只需要遍历字符串，对于所有的大写字母，统统加上32即可
    for(auto &c:s)
        if(c >= 'A' && c <='Z') c+=32;
    return s;

//    for(auto &c:s)
//        c=tolower(c);
//    return s;
}

int LC0696::countBinarySubstrings(string s) {
    // 这道题给了我们一个二进制字符串，然后我们统计具有相同0和1的个数，且0和1各自都群组在一起(即0和1不能交替出现)的子字符串的个数，
    // 题目中的两个例子也很能说明问题。那么我们来分析题目中的第一个例子00110011，符合要求的子字符串要求0和1同时出现，那么当第一个1出
    // 现的时候，前面由于前面有两个0，所以肯定能组成01，再遇到下一个1时，此时1有2个，0有2个，能组成0011，下一个遇到0时，此时0的个数重
    // 置为1，而1的个数有两个，所以一定有10，同理，下一个还为0，就会有1100存在，之后的也是这样分析。那么我们可以发现我们只要分别统计0和1的
    // 个数，而且如果当前遇到的是1，那么只要之前统计的0的个数大于当前1的个数，就一定有一个对应的子字符串，而一旦前一个数字和当前的数字不一
    // 样的时候，那么当前数字的计数要重置为1。所以我们遍历元数组，如果是第一个数字，那么对应的ones或zeros自增1。然后进行分情况讨论，
    // 如果当前数字是1，然后判断如果前面的数字也是1，则ones自增1，否则ones重置为1。如果此时zeros大于ones，res自增1。反之同理，
    // 如果当前数字是0，然后判断如果前面的数字也是0，则zeros自增1，否则zeros重置为1。如果此时ones大于zeros，res自增1。
    int res=0, pre=0, cur=1;
    for(int i=1; i<s.size(); i++) {
        if(s[i]==s[i-1]) cur++;
        else {
            pre=cur;
            cur=1;
        }
        if(pre>=cur) res++;
    }
    return res;
}

int LC0521::findLUSlength(string a, string b) {
    // 如果两个字符串相等，那么一定有共同子序列，反之，如果两个字符串不等，那么较长的那个字符串就是最长非共同子序列
    return a==b ? -1 : max(a.size(), b.size());
}

bool LC0520::detectCapitalUse(string word) {
    // 给了我们一个单词，让我们检测大写格式是否正确，规定了三种正确方式，要么都是大写或小写，要么首字母大写，其他情况都不正确。
    // 那么我们要做的就是统计出单词中所有大写字母的个数cnt，再来判断是否属于这三种情况，如果cnt为0，说明都是小写，正确；
    // 如果cnt和单词长度相等，说明都是大写，正确；如果cnt为1，且首字母为大写，正确，其他情况均返回false
    int cnt = count_if(word.begin(), word.end(), [](char c){return c<='Z';});
    return !cnt || cnt==word.size() || (cnt==1 && word[0]<='Z');
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

    int i=num1.size()-1, j=num2.size()-1, c=0;
    string res;

    while( i>=0 || j>=0 || c) {
        c += i>=0 ? num1[i--]-'0' : 0;
        c += j>=0 ? num2[j--]-'0' : 0;
        res += c%10+'0';
        c /= 10;
    }
    return string(res.rbegin(), res.rend());
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
        if(i>=pattern.size()) return false;
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
    // Given two binary strings a and b, return  their sum as a binary string.
    int i=a.size()-1, j=b.size()-1, c=0;
    string res;

    while( i>=0 || j>=0 || c) {
        c += i>=0 ? a[i--]-'0' : 0;
        c += j>=0 ? b[j--]-'0' : 0;
        res += c%2+'0';
        c /= 2;
    }
    return string(res.rbegin(), res.rend());
}

//LC0058 run;
//cout << run.lengthOfLastWord("luffy is still joyboy") << endl;
int LC0058::lengthOfLastWord(string& s) {
    // Given a string s consists of upper/lower-case alphabets and empty space characters ' ',
    // return the length of last word in the string.
    // If the last word does not exist, return 0.
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
    // Return the index of the first occurrence of needle in haystack, or -1 if needle is not part of haystack.
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
bool LC0020::isValid(string str) {
    // 验证输入的字符串是否为括号字符串，包括大括号，中括号和小括号。这里需要用一个栈，开始遍历输入字符串，如果当前字符为左半边括号时，
    // 则将其压入栈中，如果遇到右半边括号时，若此时栈为空，则直接返回 false，如不为空，则取出栈顶元素，若为对应的左半边括号，则继续循环，
    // 反之返回 false
    stack<char> s;
    for(int i=0; i<str.size(); ++i) {
        if(str[i]=='(' || str[i]=='[' || str[i]=='{')
            s.push(str[i]);
        else {
            if(s.empty()) return false;
            if(s.top()=='(' && str[i]!=')') return false;
            if(s.top()=='[' && str[i]!=']') return false;
            if(s.top()=='{' && str[i]!='}') return false;
            s.pop();
        }
    }
    return s.empty();
}

//LC0014 run;
//vector<string> s{{"flower"},{"flow"},{"flight"}};
//cout << run.longestCommonPrefix(s) << endl;
string LC0014::longestCommonPrefix(vector<string>& strs) {
    // 求一系列字符串的共同前缀
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

//cout << run.letterCasePermutation("PAYPALISHIRING") << endl;
//convert("PAYPALISHIRING", 3) should return "PAHNAPLSIIGYIR".
string LC0006::convert(string s, int numRows) {
    // The string "PAYPALISHIRING" is written in a zigzag pattern on a given number of rows like this:
    // P   A   H   N
    // A P L S I I G
    // Y   I   R
    // then read line by line: "PAHNAPLSIIGYIR"
    // Write the code that will take a string and make this conversion given a number of rows
    if(numRows<=1 || numRows>= s.size()) return s;

    vector<string> t(numRows);
    int row=0, step=1;

    for(int i=0 ; i<s.size() ; i++) {
        if(row == 0)  step = 1;
        if(row == numRows-1) step = -1;
        cout << row << ' ' << s[i] << endl;
        t[row] += s[i];
        row += step;
    }

    string ans;
    for(int i=0 ; i<numRows ; i++) ans+=t[i];

    return ans;
}