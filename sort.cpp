//
// Created by steve on 2021-08-10.
//

#include "sort.h"

void Sort::selectSort(vector<int> &d) {
    for(int i=0; i<d.size(); i++)
        for(int j=i+1 ; j<d.size() ; j++)
            if(d[i]>d[j]) swap (d[i],d[j]);
}

void Sort::insertSort(vector<int> &d) {
    for(int i=1 ; i<d.size() ; i++) {
        int j=i, p=d[j];
        for( ; j && p<d[j-1] ; j--)
            d[j]=d[j-1];
        d[j]=p;
    }
}

void Sort::bubbleSort(vector<int> &d) {
    auto swapped{true};
    while(swapped) {
        swapped = false;
        for(auto i=0 ; i<d.size(); i++)
            if(d[i]>d[i+1]) {swap(d[i], d[i+1]), swapped=true;}
    }
}

int Sort::_divide(vector<int> &d, int l_idx, int r_idx) {
    // take the right most one as pivot,
    // one-side greater than it, one-side smaller than it
    int p{d[r_idx]}, i, j;

    for(i=j=l_idx ; j<r_idx; j++)
        if(d[j]<p) swap(d[i++], d[j]);
    swap(d[i], d[r_idx]);

    return i;
}

void Sort::quickSortRecursive(vector<int>& d, int l_idx, int r_idx) {
    if(l_idx<r_idx) {
        auto m_idx = _divide(d, l_idx, r_idx);
        quickSortRecursive(d, l_idx, m_idx-1);
        quickSortRecursive(d, m_idx+1, r_idx);
    }

}

void Sort::quickSortIterative(vector<int>& d) {
    stack<int> s;
    int l_idx, m_idx, r_idx;

    s.push(0);
    s.push(d.size()-1);
    while(s.size()) {
        r_idx = s.top(); s.pop();
        l_idx = s.top(); s.pop();
        m_idx = _divide(d, l_idx, r_idx);

        if(l_idx<m_idx-1) {
            s.push(l_idx);
            s.push(m_idx-1);
        }
        if(r_idx>m_idx+1) {
            s.push(m_idx+1);
            s.push(r_idx);
        }
    }
}

void Sort::_merge(vector<int>& d, int l_idx, int m_idx, int r_idx) {

}

void Sort::mergeSortRecursive(vector<int>& d) {

}

void Sort::mergeSortIterative(vector<int>& d) {

}

void Sort::_heapify(vector<int>& d, int n, int i) {

}

void Sort::heapSort(vector<int>& d) {

}

