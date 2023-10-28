#include <iostream>
#include <vector>
#include <stack>
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <string>
#include <algorithm>
#include <numeric>
#include <queue>
#include <functional>
#include <array>
#include <bitset>

using namespace std;

class Play{
public:
    int countNegatives(vector<vector<int>>& grid) {
        int res=0;
        int m=grid.size(), n=grid[0].size();
        for(int i=0; i<m; i++) {
            int q=0, p=n-1, idx=-1;
            while(q<p) {
                int mid = q + (p-q)/2;
                if(grid[i][mid] >= 0) {
                    q = m + 1;
                } else {
                    idx = mid;
                    p = m;
                }
            }
            if(idx != -1) res += (n-idx);
        }
        return res;
    }

    int findComplement(int num) {
        unsigned int mask = UINT_MAX;
        while(num & mask) mask <<= 1;
        return ~mask & ~num;
    }

    void Iterative(vector<int>& nums) {
        stack<int> s;
        int lidx, midx, ridx;

        s.push(0);
        s.push(nums.size()-1);
        while(s.size()) {
            ridx=s.top(); s.pop();
            lidx=s.top(); s.pop();
            midx=divide(nums, lidx, ridx);

            if(lidx<midx-1) {
                s.push(lidx);
                s.push(midx-1);
            }
            if(ridx>midx+1) {
                s.push(midx+1);
                s.push(ridx);
            }
        }
    }
private:
    int divide(vector<int>& nums, int lidx, int ridx) {
        int p=nums[ridx], i, j;
        i=j=lidx;

        while(j<ridx) {
            if(nums[j]<p) swap(nums[i++],nums[j]);
            j++;
        }
        swap(nums[i], nums[ridx]);

        return i;
    }
};