
#ifndef GOOGLE_BIT_H
#define GOOGLE_BIT_H

#include "main.h"
#include <bitset>
/*求一數積偶位數各有多少是1*/
struct LC2595 { vector<int> evenOddBit(int n); };
/*求最少flip次數將start變成goal的值*/
struct LC2220 { int minBitFlips(int start, int goal); };
/*判斷一陣列是否能分成n對pair，每對值相同*/
struct LC2206 { bool divideArray(vector<int>& nums); };
/*求陣列所有subset做XOR之和*/
struct LC1863 { int subsetXORSum(vector<int>& nums); };
/*求最長子字串字符大小寫全包含*/
struct LC1763 { string longestNiceSubstring(string s); };
/*用XOR來做編碼，求編碼前的原始資料*/
struct LC1720 { vector<int> decode(vector<int>& encoded, int first); };
/*求n次做XOR運算後的值*/
struct LC1486 { int xorOperation(int n, int start); };
/*偶數除2，積數減1，給定一數求多少步驟可變0*/
struct LC1342 { int numberOfSteps(int num); };
/*求陣列裡有幾組數字相加後能被60整除*/
struct LC1009 { int bitwiseComplement(int n); };
/*求一整數二進制兩個1之間最大距離*/
struct LC0868 { int binaryGap(int n); };
/*給定一範圍，統計有多少整數其二進制1的個數為質數*/
struct LC0762 { int countPrimeSetBits(int left, int right); };
/*判斷一個數的二進制1和0是否交替出現*/
struct LC0693 { bool hasAlternatingBits(int n); };
/*求一個數的補數*/
struct LC0476 { int findComplement(int num); };
/*兩數之間二進制對應位數不同的個數*/
struct LC0461 { int hammingDistance(int x, int y); };
/*回傳能建立最長的回文字串長度*/
struct LC0409 { int longestPalindrome(string s); };
/*將十進位整數轉成十六進位表示*/
struct LC0405 { string toHex(int num); };
/*給一二進制手錶的亮燈數，列出可能的時間*/
struct LC0401 { vector<string> readBinaryWatch(int turnedOn); };
/*t是s重排後加上一字符產生，找出那一字符*/
// struct LC0389 { char findTheDifference(string s, string t); }; // list.h
/*判斷一個數是否為4的次方數*/
struct LC0342 { bool isPowerOfFour(int n); };
/*統計0到n每個數二進制1的個數*/
struct LC0338 { vector<int> countBits(int n); };
/*判斷一個字串是否重排後可形成回文*/
struct LC0266 { bool canPermutePalindrome(string s); };
/*判斷一個數是否為2的次方數*/
struct LC0231 { bool isPowerOfTwo(int n); };
/*求整數裡有多少bit是1*/
struct LC0191 { int hammingWeight(uint32_t n); };
/*反轉整數裡bits的位置*/
struct LC0190 { uint32_t reverseBits(uint32_t n); };
/*找出陣列裡唯一出現一次的數字*/
struct LC0136 { int singleNumber(vector<int>& nums); };

#endif //GOOGLE_BIT_H
