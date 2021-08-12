//
// Created by steve on 2021-08-10.
//

#ifndef GOOGLE_SORT_H
#define GOOGLE_SORT_H

#include "main.h"
using namespace std;

class Sort {
public:
    void selectSort(vector<int>& d);
    void insertSort(vector<int>& d);
    void bubbleSort(vector<int>& d);

    void quickSortRecursive(vector<int>& d, int l_idx, int r_idx);
    void quickSortIterative(vector<int>& d);
    void mergeSortRecursive(vector<int>& d);
    void mergeSortIterative(vector<int>& d);
    void heapSort(vector<int>& d);


private:
    // for quickSort
    int _divide(vector<int>& d, int l_idx, int r_idx);
    // for mergeSort
    void _merge(vector<int>& d, int l_idx, int m_idx, int r_idx);
    // for heapSort
    void _heapify(vector<int>& d, int n, int i);

};


#endif //GOOGLE_SORT_H
