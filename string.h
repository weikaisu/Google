﻿
#ifndef GOOGLE_STRING_H
#define GOOGLE_STRING_H

#include "main.h"
#include <sstream>
#include <numeric>
#include <array>

using namespace std;

/*求兩個日期間的天數*/
struct LC1360 { int daysBetweenDates(string date1, string date2); };
/*每次從給定字串刪除一個回文子"序列"，求刪多少次可以將字串清空*/
struct LC1332 { int removePalindromeSub(string s); };
/*做一次數字6換成9可得到的最大數字*/
struct LC1323 { int maximum69Number (int num); };
/*字串替換*/
struct LC1309 { string freqAlphabets(string s); };
/*將日期換算成一年的第幾天*/
struct LC1154 { int dayOfYear(string date); };
/*將IP裡的.換成指定字串*/
struct LC1108 { string defangIPaddr(string address); };
/*回傳文章裡按給定順序的下一個單字*/
struct LC1078 { vector<string> findOcurrences(string text, string first, string second); };
/*最大公約字串*/
struct LC1071 { string gcdOfStrings(string str1, string str2); };
/*移除相鄰相同字符*/
struct LC1047 { string removeDuplicates(string s); };
/*把所有合法的子串的最外层的括号去掉*/
struct LC1021 { string removeOuterParentheses(string s); };
/*排序log裡的字串*/
struct LC0937 { vector<string> reorderLogFiles(vector<string>& logs); };
/*某一單字是否是因為另一單字的字符長按的結果*/
struct LC0925 { bool isLongPressedName(string name, string typed); };
/*按規定調整字串裡字符位置*/
struct LC0917 { string reverseOnlyLetters(string s); };
/*轉譯字串根據對應的單詞表*/
struct LC0824 { string toGoatLatin(string sentence); };
/*是否按指定字典排序*/
struct LC0953 { bool isAlienSorted(vector<string>& words, string order); };
/*email address去重*/
struct LC0929 { int numUniqueEmails(vector<string>& emails) ; };
/*沒有同時出現在兩字串的單字*/
struct LC0884 { vector<string> uncommonFromSentences(string s1, string s2); };
/*字串裡出現次數最多的單字*/
struct LC0819 { string mostCommonWord(string paragraph, vector<string>& banned); };
/*是否可經由選轉子字串來等於另一字串*/
struct LC0796 { bool rotateString(string s, string goal); };
/*將字串裡所有字符轉成小寫*/
struct LC0709 { string toLowerCase(string s); };
/*0/1出現字數相同的子字串*/
struct LC0696 { int countBinarySubstrings(string s) ; };
/*最長不一樣的子字串*/
struct LC0521 { int findLUSlength(string a, string b); };
/*判斷字符大小寫是否正確使用*/
struct LC0520 { bool detectCapitalUse(string word); };
/*重新格式化字串*/
struct LC0482 { string licenseKeyFormatting(string s, int k); };
/*字串是否可用字串裡的子字串來重複組成*/
struct LC0459 { bool repeatedSubstringPattern(string s); };
/*計算字串裡segment的數量*/
struct LC0434 { int countSegments(string s); };
/*十進位字串相加*/
struct LC0415 { string addStrings(string num1, string num2); };
/*分情況設置字串*/
struct LC0412 { vector<string> fizzBuzz(int n); };
/*是否是另一字串的子序列*/
struct LC0392 { bool isSubsequence(string s, string t); };
/*字串pattern是否相同*/
struct LC0290 { bool wordPattern(string pattern, string s); };
/*字串是否回文*/
struct LC0125 { bool isPalindrome(string s); };
/*二進位字串相加*/
struct LC0067 { string addBinary(string a, string b); };
/*字串裡最後一個單字長度*/
struct LC0058 { int lengthOfLastWord(string& s); };
/*子字串第一次出現在字串的位置*/
struct LC0028 { int strStr(string haystack, string needle); };
/*左右括號是否合法*/
struct LC0020 { bool isValid(string s); };
/*最長的common prefix*/
struct LC0014 { string longestCommonPrefix(vector<string>& strs); };
struct LC0008 { int myAtoi(string s); };
/*zigzag掃描轉成line掃描*/
struct LC0006 { string convert(string s, int numRows); };
/*求最長長度無重複字母子字串之長度*/
struct LC0003 { int lengthOfLongestSubstring(string s); };

#endif //GOOGLE_STRING_H
