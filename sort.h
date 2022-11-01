
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

struct LC1356 { vector<int> sortByBits(vector<int>& arr); };

#endif //GOOGLE_SORT_H
