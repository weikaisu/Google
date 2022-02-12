//
// Created by steve on 2021-08-10.
//

#ifndef GOOGLE_SORT_H
#define GOOGLE_SORT_H

#include "main.h"
using namespace std;

class Sort {
public:
    void SelectSort(vector<int>& d);
    void InsertSort(vector<int>& d);
    void BubbleSort(vector<int>& d);

    void QuickSortRecursive(vector<int>& d, int l_idx, int r_idx);
    void QuickSortIterative(vector<int>& d);
    void MergeSortRecursive(vector<int>& d);
    void MergeSortIterative(vector<int>& d);
    void HeapSort(vector<int>& d);


private:
    // for quickSort
    int _divide(vector<int>& d, int l_idx, int r_idx);
    // for mergeSort
    void _merge(vector<int>& d, int l_idx, int m_idx, int r_idx);
    // for heapSort
    void _heapify(vector<int>& d, int n, int i);

};


#endif //GOOGLE_SORT_H
