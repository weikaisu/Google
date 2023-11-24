
#ifndef GOOGLE_DP_H
#define GOOGLE_DP_H

#include "main.h"
using namespace std;

/*********** Dynamic Programming ***********/
/*三元的斐波那契数*/
struct LC1137 { int tribonacci(int n); };
/*求一個數字遊戲是否能贏*/
struct LC1025 { bool divisorGame(int n);};
/*求1步或2步爬到第n層的最小cost*/
struct LC0746 { int minCostClimbingStairs(vector<int>& cost); };
/*二元的斐波那契数*/
struct LC0509 { int fib(int n); };
/*回傳陣列某一區間值之和*/
struct LC0303 { vector<int> dp; LC0303(vector<int>& nums); int sumRange(int left, int right); };
/*求1步或2步爬到第n層的方式*/
struct LC0070 { int climbStairs(int n); };
/*求最大連續子数组之和*/
struct LC0053 { int maxSubArray(vector<int>& nums); };
/*求最長回文子字串*/
struct LC0005 { string longestPalindrome(string s); };

/*********** Greedy ***********/
/*給定字串最多能切分出多少個平衡字串*/
struct LC1221 { int balancedStringSplit(string s); };
/*求最小cost將所有籌碼(chip)移動到一起*/
struct LC1217 { int minCostToMoveChips(vector<int>& position); };
/*能否切出三個陣列和均相等的子陣列*/
struct LC1013 { bool canThreePartsEqualSum(vector<int>& arr); };
/*求經過k次將陣列某一數切換正負號後能得到陣列最大和*/
struct LC1005 { int largestSumAfterKNegations(vector<int>& nums, int k);};
/*回傳能圍成的三角形最大週長*/
struct LC0976 { int largestPerimeter(vector<int>& nums); };
/*根據字符規定返回整數陣列*/
struct LC0942 { vector<int> diStringMatch(string s); };
/*是否可以正確地找零錢*/
struct LC0860 { bool lemonadeChange(vector<int>& bills); };
/*0/1陣列切分後最後一個是否為0字符*/
struct LC0717 { bool isOneBitCharacter(vector<int>& bits); };
/*頂多刪一字符是否可成回文*/
struct LC0680 { bool validPalindrome(string s); };
/*01陣列裡是否可以插入指定1的數量*/
struct LC0605 { bool canPlaceFlowers(vector<int>& flowerbed, int n); };
/*求兩兩一對較小數的和最大*/
struct LC0561 { int arrayPairSum(vector<int>& nums); };
/*被攻擊後持續中毒的秒數*/
struct LC0495 { int findPoisonedDuration(vector<int>& timeSeries, int duration); };
/*分發糖果給小孩*/
struct LC0455 { int findContentChildren(vector<int>& g, vector<int>& s); };
/*給一包含各種高度的陣列，求能裝載最大水量*/
struct LC0011 { int maxArea(vector<int>& height); };

#endif //GOOGLE_DP_H