//
// Created by steve on 2021-08-10.
//

#include "sort.h"

void Sort::SelectSort(vector<int> &nums) {
    for(int i=0; i<nums.size(); i++)
        for(int j=i+1 ; j<nums.size() ; j++)
            if(nums[i]>nums[j]) swap (nums[i],nums[j]);
}

//將第i張紙牌加入「前i−1張排序過」的紙牌組合，得到i張排序過的紙牌組合。
void Sort::InsertSort(vector<int> &nums) {
    for(int i=1 ; i<nums.size() ; i++) {
        int j=i, p=nums[j];
        for( ; j && nums[j]<nums[j-1] ; j--)
            nums[j]=nums[j-1];
        nums[j]=p;
    }
}

void Sort::BubbleSort(vector<int> &nums) {
    bool swapped=true;
    while(swapped) {
        swapped = false;
        for(int i=0 ; i<nums.size()-1; i++)
            if(nums[i]>nums[i+1]) {
                swap(nums[i], nums[i+1]);
                swapped=true;
            }
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

void Sort::QuickSortRecursive(vector<int>& d, int l_idx, int r_idx) {
    if(l_idx<r_idx) {
        auto m_idx = _divide(d, l_idx, r_idx);
        QuickSortRecursive(d, l_idx, m_idx-1);
        QuickSortRecursive(d, m_idx+1, r_idx);
    }

}

void Sort::QuickSortIterative(vector<int>& d) {
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

void Sort::MergeSortRecursive(vector<int>& d) {

}

void Sort::MergeSortIterative(vector<int>& d) {

}

void Sort::_heapify(vector<int>& d, int n, int i) {

}

void Sort::HeapSort(vector<int>& d) {

}

