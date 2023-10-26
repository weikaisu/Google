
#include "list.h"

// 可顯示字元編號範圍是32-126（0x20-0x7E），共95個字元。
// 大寫：65~90, 小寫：97~122
// 跟char有關的hash table都可以用 array<int,128> map; map.fill(0);來放

/***********  Two Pointers  **********/
void LC0283::moveZeroes(vector<int>& nums) {
    // 这道题让我们将一个给定数组中所有的0都移到后面，把非零数前移，要求不能改变非零数的相对应的位置关系，而且不能拷贝额外的数组，那么只能用
    // 替换法in-place来做，需要用两个指针，一个不停的向后扫，找到非零位置，然后和前面那个指针交换位置即可
    // 用快慢指針
    int slow=0;
    for(int fast=0; fast<nums.size(); ++fast)
        if(nums[fast]) std::swap(nums[slow++], nums[fast]);
}

//LC0027 run;
//vector<int> n{0,1,2,2,3,0,4,2}; // val=2
//vector<int> n{3,2,2,3}; // val=3
//vector<int> n{1}; // val=1
//cout << run.removeElement(n, 1) << endl;
//for(auto i:n) cout << i << ' ';
//cout << endl;
int LC0027::removeElement(vector<int>& nums, int val) {
    // 除一个数组中和给定值相同的数字，并返回新的数组的长度。
    // fast開始掃，若不是指定的值的話表示可以留在nums裡，就會往slow放。若是指定的值，slow則不會++，準備下次被覆蓋。
    int slow=0;
    for(int fast=0; fast<nums.size(); ++fast)
        if(nums[fast] != val) nums[slow++] = nums[fast];
    return slow;
}

//LC0026 run;
//vector<int> n{0,0,1,1,1,2,2,3,3,4};
//vector<int> n{1,1,2};
//cout << run.removeDuplicates(n) << endl;
//for(auto i:n) cout << i << ' ';
//cout << endl;
int LC0026::removeDuplicates(vector<int>& nums) {
    // 使用快慢指针来记录遍历的坐标，最开始时两个指针都指向第一个数字，如果两个指针指的数字相同，则快指针向前走一步，如果不同，则两个指针都向
    // 前走一步，这样当快指针走完整个数组后，慢指针当前的坐标加1就是数组中不同数字的个数
    int slow=0;
    // fast每次進一步，slow若一直跟fast指到的是一樣的，就會不動。當不一樣時再把fast指到的放到slow的下一個，下一個一定是跟slow本身一樣
    // 才會使得之前slow不動。
    for(int fast=0; fast<nums.size(); fast++)
        if(nums[fast] != nums[slow]) nums[++slow] = nums[fast];
    return nums.size() ? slow+1 : 0;

    // 用变量i表示当前覆盖到到位置，由于不能有重复数字，则只需要用当前数字 num 跟上一个覆盖到到数字 nums[i-1] 做个比较，只要 num 大，
    // 则一定不会有重复（前提是数组必须有序）
//    int i=0;
//    for(int &num:nums)
//        if(i<1 || num > nums[i-1])
//            nums[i++] = num;
//    return i;
}

int StackArithmetic::priority(char c) {
    if(priority_map.count(c))
        return priority_map[c];
    else
        return -1;
}

string StackArithmetic::toPostFix(string str) {
    stack<char> s;
    string res;
    char e;
    for(auto &c:str) {
        switch(c) {
            case '(':
                s.push(c);
                break;
            case ')':
                while(s.size() && (e=s.top() != '(')) {
                    res+=c;
                    s.pop();
                }
                break;
            case '+':
            case '-':
            case '*':
            case '/':
                while(priority(e=s.top()) >= priority(c)) {
                    res+=e;
                    s.pop();
                }
                break;
            default:
                if(isdigit(c))
                    res+=c;
                break;
        }
    }
    while(s.size()) {
        res+=s.top();
        s.pop();
    }

    return res;
}

int StackArithmetic::calculate(string str) {
    priority_map['(']=0; priority_map['+']=1; priority_map['-']=1; priority_map['*']=2; priority_map['/']=2;

    stack<int> s;
    int v = 0;
    for(auto &c:str) {
        if(isdigit(c)) {
            v = v*10 + (c-'0'); continue;
        }
        if(v) {
            s.push(v);
            v = 0;
        }

        int z = 0;
        int y = s.top(); s.pop();
        int x = s.top(); s.pop();

        switch(c) {
            case '+': z=x+y; break;
            case '-': z=x-y; break;
            case '*': z=x*y; break;
            case '/': z=x/y; break;
        }

        s.push('0'+z);
    }
    return s.top()-'0';
}
