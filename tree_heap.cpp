#include "tree.h"

/***********  Heap  **********/
vector<int> LC1337::kWeakestRows(vector<vector<int>>& mat, int k) {
    /*回傳前k行最弱的rows*/
    // You are given an m x n binary matrix mat of 1's (representing soldiers) and 0's (representing civilians).
    // The soldiers are positioned in front of the civilians. That is, all the 1's will appear to the left of all
    // the 0's in each row.
    // A row i is weaker than a row j if one of the following is true:
    // The number of soldiers in row i is less than the number of soldiers in row j.
    // Both rows have the same number of soldiers and i < j.
    // Return the indices of the k weakest rows in the matrix ordered from weakest to strongest.
    // Input: mat =
    //[[1,1,0,0,0],
    // [1,1,1,1,0],
    // [1,0,0,0,0],
    // [1,1,0,0,0],
    // [1,1,1,1,1]],
    // k = 3
    // Output: [2,0,3]
    // Explanation:
    // The number of soldiers in each row is:
    // - Row 0: 2
    // - Row 1: 4
    // - Row 2: 1
    // - Row 3: 2
    // - Row 4: 5
    // The rows ordered from weakest to strongest are [2,0,3,1,4].

    // use priority queue and merge soldier count and index into one number : cunt*100 + idx;
    const int m=mat.size();
    priority_queue<int, vector<int>, greater<int>> pq;
    vector<int> res(k);

    for(int i=0; i<m; i++)
        pq.push(std::accumulate(mat[i].begin(), mat[i].end(), 0) * 100 + i);

    for(int i=0; i<k; i++) {
        res[i] = pq.top() % 100;
        pq.pop();
    }

    return res;

//    // 算出每個row 1的個數，建立pair(1's, row), 調用std::sort即可根據pair的第一個欄位排序，如此得到前k名row的index
//    const int m=mat.size();
//    vector<int> res(k);
//    vector<pair<int, int>> v(m);
//
//    for(int i=0; i<m; i++) {
//        int n = std::accumulate(mat[i].begin(), mat[i].end(), 0);
//        v[i] = pair(n,i);
//    }
//
//    std::sort(v.begin(), v.end());
//
//    for(int i=0; i<k && i<m; i++)
//        res[i] = v[i].second;
//
//    return res;
}

// LC0703
struct KthLargest {
    /*求第K大的元素*/
    // 让我们在数据流中求第K大的元素，跟之前那道Kth Largest Element in an Array很类似，但不同的是，那道题的数组是确定的，不会再增加元
    // 素，这样确定第K大的数字就比较简单。而这道题的数组是不断在变大的，所以每次第K大的数字都在不停的变化。那么我们其实只关心前K大个数字就可
    // 以了，所以我们可以使用一个最小堆来保存前K个数字，当再加入新数字后，最小堆会自动排序，然后把排序后的最小的那个数字去除，则堆中还是K个数
    // 字，返回的时候只需返回堆顶元素即可
    priority_queue<int, vector<int>, greater<int>> pq;
    int min_k;
    KthLargest(int k, vector<int>& nums) {
        min_k = k;
        for(int &num:nums) {
            pq.push(num);
            if(pq.size()>min_k) pq.pop();
        }
    };
    int add(int val) {
        pq.push(val);
        if(pq.size()>min_k) pq.pop();
        return pq.top();
    };

    // use multiset, 較慢
//    multiset<int> pq;
//    int min_k;
//    KthLargest(int k, vector<int>& nums) {
//        min_k = k;
//        for(int &num:nums) {
//            pq.insert(num);
//            if(pq.size()>min_k) pq.erase(pq.begin());
//        }
//    }
//    int add(int val) {
//        pq.insert(val);
//        if(pq.size()>min_k) pq.erase(pq.begin());
//        return *pq.begin();
//    }
};

int LC1046::lastStoneWeight(vector<int>& stones) {
    /*從陣列裡持續挑兩數出來相減，問最後減剩的值*/
    // 给了一堆重量不同的石头，每次选出两个最重的出来相互碰撞，若二者重量相同，则直接湮灭了，啥也不剩，否则剩一个重量为二者差值的石头。然后继
    // 续如此操作，直至啥也不剩（返回0），或者剩下一个石头（返回该石头的重量）。这道题是一道 Easy 的题目，没有太大的难度，主要就是每次要选出
    // 最大的两个数字，若是给数组排序，是可以知道最后两个数字是最大的，然是碰撞过后若有剩余，要将这个剩余的石头加到数组的合适位置，每次都排一
    // 次序显然时间复杂度太大。这里需要用一个更合理的数据结构，最大堆，在 C++ 中用优先队列实现的，每次加入一个新的石头，就会自动根据其重量加
    // 入到正确的位置。起始时将所有的石头加入优先队列中，然后进行循环，条件是队列中的石头个数大于1，然后取出队首两个石头，假如重量不等，则将
    // 差值加入队列。最终只需要判断队列是否为空，是的话返回0，否则返回队首元素
    priority_queue<int> pq;
    for(int &stone:stones) pq.push(stone);
    while(pq.size()>1) {
        int first  = pq.top(); pq.pop();
        int second = pq.top(); pq.pop();
        if(first>second) pq.push(first-second);
    }
    return pq.empty() ? 0 : pq.top();

    // use multiset, 不能用set，set裡同值只能有一個
//    multiset<int> pq;
//    for(int &stone:stones) pq.insert(stone);
//    while(pq.size()>1) {
//        // 最大的在最後面，要刪除時要刪std::prev(pq.end())
//        int first  = *pq.rbegin(); pq.erase(std::prev(pq.end()));
//        int second = *pq.rbegin(); pq.erase(std::prev(pq.end()));
//        if(first>second) pq.insert(first-second);
//    }
//    return pq.empty() ? 0 : *pq.begin();
}

vector<string> LC0506::findRelativeRanks(vector<int>& score) {
    // 这道题给了我们一组分数，让我们求相对排名，前三名分别是金银铜牌，后面的就是名次数，利用map的自动排序的功能，不过map是升序排列的，所以
    // 我们遍历的时候就要从最后面开始遍历，最后一个是金牌，然后往前一次是银牌，铜牌，名次数等
//    vector<string> res(score.size(), "");
//    map<int,int> m;
//    for(int i=0; i<score.size(); i++)
//        m[score[i]]=i;
//    int cnt=1;
//    for(auto it=m.rbegin(); it!=m.rend(); it++) {
//        if(cnt==1) res[it->second] = "Gold Medal";
//        else if(cnt==2) res[it->second] = "Silver Medal";
//        else if(cnt==3) res[it->second] = "Bronze Medal";
//        else res[it->second] = to_string(cnt);
//        cnt++;
//    }
//    return res;

    // 建立一个坐标数组，不过排序的时候比较的不是坐标，而是该坐标位置上对应的数字，后面的处理方法和之前的并没有什么不同
    int n = score.size();
    vector<string> res(n,"");
    vector<int> idx(n);
    for(int i=0; i<n; i++) idx[i]=i;
    sort(idx.begin(), idx.end(), [&](int i, int j){return score[i]>score[j];});
    for(int i=0; i<n; i++) {
        if(i==0) res[idx[i]] = "Gold Medal";
        else if(i==1) res[idx[i]] = "Silver Medal";
        else if(i==2) res[idx[i]] = "Bronze Medal";
        else res[idx[i]] = to_string(i+1);
    }
    return res;
}