#ifndef GOOGLE_MATH_H
#define GOOGLE_MATH_H

#include "main.h"
using namespace std;

/*求兩個不為零數之和為給定的數*/
struct LC1317 { vector<int> getNoZeroIntegers(int n); };
/*判斷一組二維座標的點是否共線*/
struct LC1232 { bool checkStraightLine(vector<vector<int>>& coordinates); };
/*求給定日期對應的是星期幾*/
struct LC1185 { string dayOfTheWeek(int day, int month, int year); };
/*求1～n的排列數，質數必須在質數的idx上*/
struct LC1175 { int numPrimeArrangements(int n); };
/*判斷三點是否不共線，因此能構成一回力標的三個頂點*/
struct LC1037 { bool isBoomerang(vector<vector<int>>& points); };
/*判斷兩個矩形是否重疊*/
struct LC0836 { bool isRectangleOverlap(vector<int>& rec1, vector<int>& rec2); };
/*求一範圍內所有的自整除數字*/
struct LC0728 { vector<int> selfDividingNumbers(int left, int right); };
/*判斷一數是否為完美數*/
struct LC0507 { bool checkPerfectNumber(int num); };
/*十進制轉七進制*/
struct LC0504 { string convertToBase7(int num); };
/*根據面積求矩形的長跟寬，長寬差距盡量小*/
struct LC0492 { vector<int> constructRectangle(int area); };
/*判斷一個數是否為4的次方數*/
// bool LC0342::isPowerOfFour(int n) // bit.h
/*判斷一個數是否為3的次方數*/
struct LC0326 { bool isPowerOfThree(int n); };
/*判斷一個數是否為2的次方數*/
// struct LC0231 { bool isPowerOfTwo(int n); }; // bit.h
/*判斷拿石子遊戲是否會贏*/
struct LC0292 { bool canWinNim(int n); };
/*判斷一個數是否為醜數*/
struct LC0263 { bool isUgly(int n); };
/*求不斷相加一數所有位數之值*/
struct LC0258 { int addDigits(int num); };
/*字母轉數字，26進位轉10進位問題*/
struct LC0171 { int titleToNumber(string columnTitle); };
/*數字轉字母，10進位轉26進位問題*/
struct LC0168 { string convertToTitle(int columnNumber); };
/*羅馬數字轉整數*/
struct LC0013 { int romanToInt(string s); };
/*一個整數的字面數字是否回文*/
struct LC0009 { bool isPalindrome(int x); };
/*翻轉一數的各個位數*/
struct LC0007 { int reverse(int x); };

#endif //GOOGLE_MATH_H
