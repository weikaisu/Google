
#ifndef GOOGLE_STRING_H
#define GOOGLE_STRING_H

#include "main.h"
#include <sstream>

using namespace std;

/***********  Easy  **********/
struct LC0937 { vector<string> reorderLogFiles(vector<string>& logs); };
struct LC0925 { bool isLongPressedName(string name, string typed); };
struct LC0917 { string reverseOnlyLetters(string s); };
struct LC0824 { string toGoatLatin(string sentence); };
struct LC0953 { bool isAlienSorted(vector<string>& words, string order); };
struct LC0929 { int numUniqueEmails(vector<string>& emails) ; };
struct LC0884 { vector<string> uncommonFromSentences(string s1, string s2); };
struct LC0819 { string mostCommonWord(string paragraph, vector<string>& banned); };
struct LC0796 { bool rotateString(string s, string goal); };
struct LC0709 { string toLowerCase(string s); };
struct LC0696 { int countBinarySubstrings(string s) ; };
struct LC0521 { int findLUSlength(string a, string b); };
struct LC0520 { bool detectCapitalUse(string word); };
struct LC0482 { string licenseKeyFormatting(string s, int k); };
struct LC0459 { bool repeatedSubstringPattern(string s); };
struct LC0434 { int countSegments(string s); };
struct LC0415 { string addStrings(string num1, string num2); };
struct LC0412 { vector<string> fizzBuzz(int n); };
struct LC0392 { bool isSubsequence(string s, string t); };
struct LC0290 { bool wordPattern(string pattern, string s); };
struct LC0125 { bool isPalindrome(string s); };
struct LC0067 { string addBinary(string a, string b); };
struct LC0058 { int lengthOfLastWord(string& s); };
struct LC0028 { int strStr(string haystack, string needle); };
struct LC0020 { bool isValid(string s); };
struct LC0014 { string longestCommonPrefix(vector<string>& strs); };
struct LC0013 { int romanToInt(string s); };
struct LC0009 { bool isPalindrome(int x); };

/***********  Medium  **********/

#endif //GOOGLE_STRING_H
