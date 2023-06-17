
#ifndef GOOGLE_DP_H
#define GOOGLE_DP_H

#include "main.h"
using namespace std;

/*********** Dynamic Programming ***********/
struct LC0746 { int minCostClimbingStairs(vector<int>& cost); };
struct LC0509 { int fib(int n); };
/*回傳陣列某一區間值之和*/
struct LC0303 { vector<int> dp; LC0303(vector<int>& nums); int sumRange(int left, int right); };
struct LC0070 { int climbStairs(int n); };
struct LC0053 { int maxSubArray(vector<int>& nums); };

/*********** Greedy ***********/
/*給定字串最多能切分出多少個平衡字串*/
struct LC1221 { int balancedStringSplit(string s); };
struct LC1217 { int minCostToMoveChips(vector<int>& position); };
struct LC1013 { bool canThreePartsEqualSum(vector<int>& arr); };
struct LC1005 { int largestSumAfterKNegations(vector<int>& nums, int k);};
struct LC0976 { int largestPerimeter(vector<int>& nums); };
/*根據字符規定返回整數陣列*/
struct LC0942 { vector<int> diStringMatch(string s); };
struct LC0860 { bool lemonadeChange(vector<int>& bills); };
struct LC0717 { bool isOneBitCharacter(vector<int>& bits); };
/*頂多刪一字符可成回文*/
struct LC0680 { bool validPalindrome(string s); };
/*01陣列裡是否可以插入指定1的數量*/
struct LC0605 { bool canPlaceFlowers(vector<int>& flowerbed, int n); };
/*求兩兩一對較小數的和最大*/
struct LC0561 { int arrayPairSum(vector<int>& nums); };
/*被攻擊後持續中毒的秒數*/
struct LC0495 { int findPoisonedDuration(vector<int>& timeSeries, int duration); };
/*分發糖果給小孩*/
struct LC0455 { int findContentChildren(vector<int>& g, vector<int>& s); };
/*回傳能建立最長的回文字串長度*/
struct LC0409 { int longestPalindrome(string s); };

#endif //GOOGLE_DP_H