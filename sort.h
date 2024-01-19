
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
    // HeapSort是給定一堆資料做排序，而Heap(priority_queue)是會有push/pop
    // push : 放到最後，往parent一路比大小上去
    // pop  : 取出首個，把最後一個放到首位，開始遞歸做heapify
    // 所以在Heap(priority_queue)裡是pop會用到heapify

private:
    // for quickSort
    int divide(vector<int>& nums, int lidx, int ridx);
    // for mergeSort
    void merge(vector<int>& nums, int lidx, int midx, int ridx);
    // for heapSort
    void heapify(vector<int>& nums, int n, int i);
};

/*求陣列裡的每個元素有多少小於其的元素*/
struct LC1365 { vector<int> smallerNumbersThanCurrent(vector<int>& nums); };
/*排序一陣列根據每元素二進制時1的數量*/
struct LC1356 { vector<int> sortByBits(vector<int>& arr); };
/*判斷一個陣列裡是否有一個元素是另一個元素的兩倍*/
struct LC1346 { bool checkIfExist(vector<int>& arr); };
/*求陣列裡每個元素對應的rank(值大小順序)*/
struct LC1331 { vector<int> arrayRankTransform(vector<int>& arr); };
/*找出在陣列裡出現超過25%的那個數*/
struct LC1287 { int findSpecialInteger(vector<int>& arr); };
/*求陣列裡所有差值為最小的pair*/
struct LC1200 { vector<vector<int>> minimumAbsDifference(vector<int>& arr); };
/*根據另一陣列裡的相對順序排做排序*/
// struct LC1122 { vector<int> relativeSortArray(vector<int>& arr1, vector<int>& arr2); } // list.h
/*需移動陣列裡多少元素能讓陣列按序排列*/
struct LC1051 { int heightChecker(vector<int>& heights); };
/*求給定矩陣大小內每個元素局離rCenter/cCenter的距離*/
struct LC1030 { vector<vector<int>> allCellsDistOrder(int rows, int cols, int rCenter, int cCenter); };
/*回傳元素平方後的排序陣列*/
struct LC0977 { vector<int> sortedSquares(vector<int>& nums); };
/*按偶數在偶數位置、積數在積數位置的方式排序*/
struct LC0922 { vector<int> sortArrayByParityII(vector<int>& nums); };
/*按所有偶數在前積數在後的方式排序*/
struct LC0905 { vector<int> sortArrayByParity(vector<int>& nums); };
/*两人交换一類糖果，使得交换后两人的糖果总重量相同*/
// struct LC0888 { vector<int> fairCandySwap(vector<int>& aliceSizes, vector<int>& bobSizes); }; // list.h
/*求陣列裡最大且大於所有其他元素二倍的元素index*/
struct LC0747 { int dominantIndex(vector<int>& nums); };
/*找出1～n的陣列裡重複的數和消失的那"個"數字*/
// struct LC0645 { vector<int> findErrorNums(vector<int>& nums); } // list.h
/*找出陣列裡三數相乘之最大值*/
// struct LC0628 { int maximumProduct(vector<int>& nums); } // list.h
/*陣列裡最長harmonious子陣列長度*/
// struct LC0594 { int findLHS(vector<int>& nums); } // list.h
/*求兩兩一對較小數的和最大*/
// struct LC0561 { int arrayPairSum(vector<int>& nums); } // dp.h
/*給定分數陣列，找出相對排名*/
// struct LC0506 { vector<string> findRelativeRanks(vector<int>& score); } // dp.h
/*分發糖果給小孩*/
// struct LC0455 { int findContentChildren(vector<int>& g, vector<int>& s); } // dp.h
/*回傳陣列裡第三大的數*/
// struct LC0414 { int thirdMax(vector<int>& nums); } // list.h
/*t是s重排後加上一字符產生，找出那一字符*/
// struct LC0389 { char findTheDifference(string s, string t); } // list.h
/*找出同時存在兩陣列的子陣列，子陣列無需去重*/
// struct LC0350 { vector<int> intersect(vector<int>& nums1, vector<int>& nums2); } // list.h
/*找出同時存在兩陣列的子陣列，子陣列需去重*/
// struct LC0349 { vector<int> intersection(vector<int>& nums1, vector<int>& nums2); } // list.h
/*找出0～n的陣列裡消失的那"個"數字*/
// struct LC0268 { int missingNumber(vector<int>& nums); } // list.h
/*判斷一個字串是否是另一字串的anagram*/
// struct LC0242 { bool isAnagram(string s, string t); } // list.h
/*判斷一陣列裡是否有值重複出現*/
// struct LC0217 { bool containsDuplicate(vector<int>& nums); } // list.h
/*回傳數量超過一半的那個數*/
// struct LC0169 { int majorityElement(vector<int>& nums); }; // list.h
/*合併兩個排序好的陣列到其中一個*/
struct LC0088 { void merge(vector<int>& nums1, int m, vector<int>& nums2, int n); };
/*找出陣列裡和最接近target的三數*/
struct LC0016 { int threeSumClosest(vector<int>& nums, int target); };
/*回傳所有三數和為0的組合*/
struct LC0015 { vector<vector<int>> threeSum(vector<int>& nums); };

#endif //GOOGLE_SORT_H
