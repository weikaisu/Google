
#ifndef GOOGLE_SEARCH_H
#define GOOGLE_SEARCH_H

#include "main.h"
using namespace std;

/***********  Easy  **********/
// binary search
struct LC0035 { int searchInsert(vector<int>& nums, int target); };

// linear search
struct LC0784 { vector<string> letterCasePermutation(string s); };
struct LC0006 { string convert(string s, int numRows); };

// df search
struct LCSearch {
    void permutation(vector<int> nums, int n, int m);
    void combination(vector<int> nums, int n, int m);
};

// bf search
/***********  Medium  **********/


#endif //GOOGLE_SEARCH_H
