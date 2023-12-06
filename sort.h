﻿
#ifndef GOOGLE_SORT_H
#define GOOGLE_SORT_H

#include "main.h"
using namespace std;

class Sort {
public:
    void SelectSort(vector<int>& nums);
    void InsertSort(vector<int>& nums);
    void BubbleSort(vector<int>& nums);

    void QuickSortRecursive(vector<int>& nums, int lidx, int ridx);
    void QuickSortIterative(vector<int>& nums);
    void MergeSortRecursive(vector<int>& nums, int lidx, int ridx);
    void MergeSortIterative(vector<int>& nums);
    void HeapSort(vector<int>& nums);

private:
    // for quickSort
    int divide(vector<int>& nums, int lidx, int ridx);
    // for mergeSort
    void merge(vector<int>& nums, int lidx, int midx, int ridx);
    // for heapSort
    void heapify(vector<int>& nums, int n, int i);
};

struct LC1365 { vector<int> smallerNumbersThanCurrent(vector<int>& nums); };
struct LC1356 { vector<int> sortByBits(vector<int>& arr); };
struct LC1346 { bool checkIfExist(vector<int>& arr); };
struct LC1331 { vector<int> arrayRankTransform(vector<int>& arr); };
struct LC1287 { int findSpecialInteger(vector<int>& arr); };
struct LC1200 { vector<vector<int>> minimumAbsDifference(vector<int>& arr); };
// struct LC1122 { vector<int> relativeSortArray(vector<int>& arr1, vector<int>& arr2); } // list.h
struct LC1051 { int heightChecker(vector<int>& heights); };
/*求給定矩陣大小內每個元素局離rCenter/cCenter的距離*/
struct LC1030 { vector<vector<int>> allCellsDistOrder(int rows, int cols, int rCenter, int cCenter); };
struct LC0977 { vector<int> sortedSquares(vector<int>& nums); };
struct LC0922 { vector<int> sortArrayByParityII(vector<int>& nums); };
struct LC0905 { vector<int> sortArrayByParity(vector<int>& nums); };
// struct LC0888 { vector<int> fairCandySwap(vector<int>& aliceSizes, vector<int>& bobSizes); }; // list.h
struct LC0747 { int dominantIndex(vector<int>& nums); };
// struct LC0645 { vector<int> findErrorNums(vector<int>& nums); } // list.h
// struct LC0628 { int maximumProduct(vector<int>& nums); } // list.h
// struct LC0594 { int findLHS(vector<int>& nums); } // list.h
// struct LC0561 { int arrayPairSum(vector<int>& nums); } // dp.h
// struct LC0506 { vector<string> findRelativeRanks(vector<int>& score); }
// struct LC0455 { int findContentChildren(vector<int>& g, vector<int>& s); } // dp.h
// struct LC0414 { int thirdMax(vector<int>& nums); } // list.h
// struct LC0389 { char findTheDifference(string s, string t); } // list.h
// struct LC0350 { vector<int> intersect(vector<int>& nums1, vector<int>& nums2); } // list.h
// struct LC0349 { vector<int> intersection(vector<int>& nums1, vector<int>& nums2); } // list.h
// struct LC0268 { int missingNumber(vector<int>& nums); } // list.h
// struct LC0242 { bool isAnagram(string s, string t); } // list.h
// struct LC0217 { bool containsDuplicate(vector<int>& nums); } // list.h
// struct LC0169 { int majorityElement(vector<int>& nums); }; // list.h
struct LC0088 { void merge(vector<int>& nums1, int m, vector<int>& nums2, int n); };
struct LC0016 { int threeSumClosest(vector<int>& nums, int target); };
struct LC0015 { vector<vector<int>> threeSum(vector<int>& nums); };

#endif //GOOGLE_SORT_H
