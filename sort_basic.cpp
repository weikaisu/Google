﻿#include "sort.h"

//反覆從未排序數列中找出最小值，將它與左邊的數做交換。
void Sort::SelectSort(vector<int> &nums) {
    for(int i=0; i<nums.size()-1; i++)
        for(int j=i+1 ; j<nums.size() ; j++)
            if(nums[i]>nums[j]) std::swap (nums[i],nums[j]);
}

//將第i張紙牌加入「前i−1張排序過」的紙牌組合，得到i張排序過的紙牌組合。
void Sort::InsertSort(vector<int> &nums) {
    for(int i=1 ; i<nums.size() ; i++) {
        int j=i, p=nums[j];
        while (j && p < nums[j-1]) {
            nums[j] = nums[j - 1];
            j--;
        }
        nums[j]=p;
    }
}

void Sort::BubbleSort(vector<int> &nums) {
    bool swapped=true;
    while(swapped) {
        swapped = false;
        for(int i=0 ; i<nums.size()-1; i++)
            if(nums[i]>nums[i+1]) {
                std::swap(nums[i], nums[i+1]);
                swapped=true;
            }
    }
}

int Sort::divide(vector<int> &nums, int lidx, int ridx) {
    // take the right most one as pivot,
    // one-side greater than it, one-side smaller than it
    int p=nums[ridx], i, j;
    i=j=lidx;

    while(j < ridx) {
        if(nums[j] < p) std::swap(nums[i++], nums[j]);
        j++;
    }
    std::swap(nums[i], nums[ridx]);

    return i;
}

// run.QuickSortRecursive(nums, 0, nums.size()-1);
void Sort::QuickSortRecursive(vector<int>& nums, int lidx, int ridx) {
    if(lidx >= ridx) return;

    int m_idx = divide(nums, lidx, ridx);
    QuickSortRecursive(nums, lidx, m_idx - 1);
    QuickSortRecursive(nums, m_idx + 1, ridx);
}

void Sort::QuickSortIterative(vector<int>& nums) {
    stack<int> s;
    int l_idx, m_idx, r_idx;

    s.push(0);
    s.push(nums.size() - 1);
    while(s.size()) {
        r_idx = s.top(); s.pop();
        l_idx = s.top(); s.pop();
        m_idx = divide(nums, l_idx, r_idx);

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

void Sort::merge(vector<int>& nums, int lidx, int midx, int ridx) {
    vector<int> ldata, rdata;
    int i=0, j=0, k=lidx;

    ldata.assign(nums.begin() + lidx, nums.begin() + midx + 1);
    rdata.assign(nums.begin() + midx + 1, nums.begin() + ridx + 1);

    while(i<ldata.size() && j<rdata.size())
        ldata[i]<rdata[j] ? nums[k++]=ldata[i++] : nums[k++]=rdata[j++];
    while(i<ldata.size())
        nums[k++]=ldata[i++];
    while(j<rdata.size())
        nums[k++]=rdata[j++];
}

// run.MergeSortRecursive(v, 0, v.size()-1);
void Sort::MergeSortRecursive(vector<int>& nums, int lidx, int ridx) {
    if(lidx>=ridx) return;

    int midx = lidx+((ridx-lidx)>>1);

    MergeSortRecursive(nums, lidx, midx);
    MergeSortRecursive(nums, midx+1, ridx);
    merge(nums, lidx, midx, ridx);
}

void Sort::MergeSortIterative(vector<int>& nums) {
    // bottom up, no need to use another stack.
    int stride, lidx, midx, ridx;

    for(stride=1; stride<nums.size(); stride<<=1)
        for(lidx=0; lidx<nums.size(); lidx+=stride<<1) {
            midx = min(int(lidx+stride-1), int(nums.size()-1));
            ridx = min(int(lidx+(stride<<1)-1), int(nums.size()-1));
            merge(nums, lidx, midx, ridx);
        }
}

void Sort::heapify(vector<int>& nums, int n, int node) {
    // n elements, node is the root, if its child is greater than it, swap.
    // heapify 的功能為確保以node為root以下滿足heap條件
    int root=node, lchild=2*node+1, rchild=2*node+2;

    // 把自己跟lchild/rchild比較，跟最大的那個做swap
    // 確保每個parent都比lchild/rchild大
    if(lchild<n && nums[lchild]>nums[root]) root=lchild;
    if(rchild<n && nums[rchild]>nums[root]) root=rchild;
    if(root != node) {
        std::swap(nums[root], nums[node]);
        // 把較小的值繼續往下放直到leaf
        // 要繼續往下的原因是確保swap過後整個subtree仍滿足heap條件
        heapify(nums, n, root);
    }
}

void Sort::HeapSort(vector<int>& nums) {
    // create a max heap, keep removing the 1st element, the max one
    // begin from the last node's parent i=n/2-1.
    int i, n=nums.size();
    if(n<2) return;

    // 從最後一個parent往root確認每個內部node以下都滿足heap條件
    // 從最後一個往回處理是為了確保最大值可以拋到root
    for(i=n/2-1; i>=0; i--)
        heapify(nums, n, i);
    // 當root為最大值後，持續將root放到最後，vector就會變成一個排序好的vector
    // 下面動作是為了讓vector內按順序排列，heap本身資料結構不需要
    for(i=n-1; i>=0; i--) {
        std::swap(nums[0], nums[i]);
        heapify(nums, i, 0);
    }
}