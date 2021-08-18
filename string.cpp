//
// Created by steve on 2021-08-18.
//

#include "string.h"

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

bool LC0009::isPalindrome(int x) {
    if(x<0) return false;

    int f=x, b=0;
    while(x>0 && b<INT32_MAX/10) {
        b = b*10 + x%10;
        x/=10;
    }
    return f==b;
}