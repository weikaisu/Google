//
// Created by steve on 2021-08-18.
//

#include "string.h"

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