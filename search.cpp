//
// Created by steve on 2021-08-12.
//

#include "search.h"


int LC0035::searchInsert(vector<int>& nums, int target) {
    int l=0, r=nums.size();

    while(l<r) {
        int m=l+(r-l)/2;
        if(target>nums[m]) l=m+1;
        else if(target<nums[m]) r=m;
        else return m;
    }
    return l;
}

//LC0784 run;
//vector<string> ans=run.letterCasePermutation("a1b2");
//for(auto a:ans) cout << a << endl;
vector<string> LC0784::letterCasePermutation(string s) {
    vector<string> ans;
    function<void(int)> dfs = [&](int d) {
        if(d==s.size()) { ans.push_back(s); return; }
        dfs(d+1);

        if(!isalpha(s[d])) { return; }
        s[d]^=32;
        dfs(d+1);
        s[d]^=32;
    };
    dfs(0);
    return ans;
}

//LC0006 run;
//cout << run.letterCasePermutation("PAYPALISHIRING") << endl;
//convert("PAYPALISHIRING", 3) should return "PAHNAPLSIIGYIR".
string LC0006::convert(string s, int numRows) {
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