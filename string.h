
#ifndef GOOGLE_STRING_H
#define GOOGLE_STRING_H

#include "main.h"
#include <sstream>

using namespace std;

/***********  Easy  **********/
struct LC1047 { string removeDuplicates(string s); };
/*移除相鄰相同字符*/
struct LC1021 { string removeOuterParentheses(string s); };
/*根據字符規定返回整數陣列*/
struct LC0942 { vector<int> diStringMatch(string s); };
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
/*判斷大寫字符是否正確使用*/
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
/*是否是另一字串的子字串*/
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
/*羅馬數字轉整數*/
struct LC0013 { int romanToInt(string s); };
/*一個整數的字面數字是否回文*/
struct LC0009 { bool isPalindrome(int x); };

/***********  Medium  **********/

#endif //GOOGLE_STRING_H
