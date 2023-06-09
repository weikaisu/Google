
#ifndef GOOGLE_DP_H
#define GOOGLE_DP_H

#include "main.h"
using namespace std;

// Dynamic Programming
struct LC0746 { int minCostClimbingStairs(vector<int>& cost); };
struct LC0509 { int fib(int n); };
/*回傳陣列某一區間值之和*/
struct LC0303 { vector<int> dp; LC0303(vector<int>& nums); int sumRange(int left, int right); };
struct LC0070 { int climbStairs(int n); };
struct LC0053 { int maxSubArray(vector<int>& nums); };

//Greedy
struct LC1013 { bool canThreePartsEqualSum(vector<int>& arr); };
struct LC0717 { bool isOneBitCharacter(vector<int>& bits); };
/*求兩兩一對較小數的和最大*/
struct LC0561 { int arrayPairSum(vector<int>& nums); };
/*被攻擊後持續中毒的秒數*/
struct LC0495 { int findPoisonedDuration(vector<int>& timeSeries, int duration); };
/*分發糖果給小孩*/
struct LC0455 { int findContentChildren(vector<int>& g, vector<int>& s); };

#endif //GOOGLE_DP_H