
#ifndef GOOGLE_DP_H
#define GOOGLE_DP_H

#include "main.h"
using namespace std;

// Dynamic Programming
/*回傳陣列某一區間值之和*/
struct LC0303 { vector<int> dp; LC0303(vector<int>& nums); int sumRange(int left, int right); };
struct LC0070 { int climbStairs(int n); };
struct LC0053 { int maxSubArray(vector<int>& nums); };

//Greedy
/*被攻擊後持續中毒的秒數*/
struct LC0495 { int findPoisonedDuration(vector<int>& timeSeries, int duration); };
/*分發糖果給小孩*/
struct LC0455 { int findContentChildren(vector<int>& g, vector<int>& s); };

#endif //GOOGLE_DP_H
