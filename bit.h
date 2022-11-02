
#ifndef GOOGLE_BIT_H
#define GOOGLE_BIT_H

#include "main.h"
#include <bitset>

/***********  Easy  **********/
struct LC1763 { string longestNiceSubstring(string s); };
struct LC1720 { vector<int> decode(vector<int>& encoded, int first); };
struct LC1486 { int xorOperation(int n, int start); };
struct LC1342 { int numberOfSteps(int num); };
struct LC1009 { int bitwiseComplement(int n); };
struct LC0868 { int binaryGap(int n); };
struct LC0762 { int countPrimeSetBits(int left, int right); };
struct LC0693 { bool hasAlternatingBits(int n); };
struct LC0476 { int findComplement(int num); };
struct LC0461 { int hammingDistance(int x, int y); };
struct LC0405 { string toHex(int num); };
struct LC0401 { vector<string> readBinaryWatch(int turnedOn); };
// struct LC0389 { char findTheDifference(string s, string t); }; // list.h
struct LC0342 { bool isPowerOfFour(int n); };
struct LC0338 { vector<int> countBits(int n); };
struct LC0266 { bool canPermutePalindrome(string s); };
struct LC0231 { bool isPowerOfTwo(int n); };
struct LC0191 { int hammingWeight(uint32_t n); };
struct LC0190 { uint32_t reverseBits(uint32_t n); };
struct LC0136 { int singleNumber(vector<int>& nums); };

#endif //GOOGLE_BIT_H
