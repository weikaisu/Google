#include <iostream>
#include <vector>
#include <stack>

using namespace std;

class Play{
public:
    void Recursive(vector<int>& nums, int lidx, int ridx) {
        if(lidx>=ridx) return;

        int m = divide(nums, lidx, ridx);
        Recursive(nums, lidx, m-1);
        Recursive(nums, m+1, ridx);
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