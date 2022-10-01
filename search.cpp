
#include "search.h"

/***********  Binary Search  **********/
//LC0035 run;
//vector<int> nums{1,3,5,6};
//int target=5;
//cout << run.searchInsert(nums, target) << endl;
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

/***********  Linear Search  **********/
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



/***********  DF Search  **********/
void Search::permutation(vector<int> nums, int n, int m) {
    vector<vector<int>> res;
    vector<int> cur;
    vector<bool> used(nums.size(), false);

    auto per = [&](const auto &self, int depth) {
        if(depth==m)
            {res.push_back(cur); return;}
        for(int i=0; i<nums.size(); i++) {
            if(used[i]) continue;
            cur.push_back(nums[i]); used[i]=true;
            self(self, depth+1);
            cur.pop_back(); used[i]=false;
        }
    };

    per(per, 0);

    for(auto &v:res) {
        for(auto &e:v) cout << e << ' ';
        cout << endl;
    }
    cout<<"P("<<n<<","<<m<<")="<<res.size()<<endl;
}

void Search::combination(vector<int> nums, int n, int m) {
    vector<vector<int>> res;
    vector<int> cur;

    auto com = [&](const auto &self, int depth, int start) {
        if(depth==m)
            {res.push_back(cur); return;}
        for(int i=start; i<nums.size(); i++) {
            cur.push_back(nums[i]);
            self(self, depth+1, i+1);
            cur.pop_back();
        }
    };

    com(com, 0, 0);

    for(auto &v:res) {
        for(auto &e:v) cout << e << ' ';
        cout << endl;
    }
    cout<<"C("<<n<<","<<m<<")="<<res.size()<<endl;
}

/***********  BF Search  **********/