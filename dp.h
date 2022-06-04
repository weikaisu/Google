
#ifndef GOOGLE_DP_H
#define GOOGLE_DP_H

#include "main.h"
using namespace std;

/*回傳陣列某一區間值之和*/
struct LC0303 { vector<int> dp; LC0303(vector<int>& nums); int sumRange(int left, int right); };
struct LC0070 { int climbStairs(int n); };
struct LC0053 { int maxSubArray(vector<int>& nums); };


#endif //GOOGLE_DP_H
