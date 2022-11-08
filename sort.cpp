
#include "sort.h"

//反覆從未排序數列中找出最小值，將它與左邊的數做交換。
void Sort::SelectSort(vector<int> &nums) {
    for(int i=0; i<nums.size()-1; i++)
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

int Sort::divide(vector<int> &nums, int lidx, int ridx) {
    // take the right most one as pivot,
    // one-side greater than it, one-side smaller than it
    int p=nums[ridx], i, j;
    i=j=lidx;

    while(j < ridx) {
        if(nums[j] < p) swap(nums[i++], nums[j]);
        j++;
    }
    swap(nums[i], nums[ridx]);

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

void Sort::heapify(vector<int>& nums, int n, int i) {
    // n elements, i is the root, if its child is greater than it, swap.
    int root=i, lchild=2*i+1, rchild=2*i+2;

    if(lchild<n && nums[lchild]>nums[root]) root=lchild;
    if(rchild<n && nums[rchild]>nums[root]) root=rchild;
    if(root != i) {
        swap(nums[root], nums[i]);
        heapify(nums, n, root);
    }
}

void Sort::HeapSort(vector<int>& nums) {
    // create a max heap, keep removing the 1st element, the max one
    // begin from the last node's parent i=n/2-1.
    int i, n=nums.size();
    if(n<2) return;

    for(i=n/2-1; i>=0; i--)
        heapify(nums, n, i);
    // swaps first and last node
    for(i=n-1; i>=0; i--) {
        swap(nums[0], nums[i]);
        heapify(nums, i, 0);
    }
}

vector<int> LC1365::smallerNumbersThanCurrent(vector<int>& nums) {
    // Given the array nums, for each nums[i] find out how many numbers in the array are smaller than it.
    // That is, for each nums[i] you have to count the number of valid j's such that j != i and nums[j] < nums[i].
    // Return the answer in an array.
    // Input: nums = [8,1,2,2,3]
    // Output: [4,0,1,1,3]
    // Explanation:
    // For nums[0]=8 there exist four smaller numbers than it (1, 2, 2 and 3).
    // For nums[1]=1 does not exist any smaller number than it.
    // For nums[2]=2 there exist one smaller number than it (1).
    // For nums[3]=2 there exist one smaller number than it (1).
    // For nums[4]=3 there exist three smaller numbers than it (1, 2 and 2).
    // 循環一次用hash table記下index，排序過後從最大值開始檢查有多小於不等於其之值
    vector<int> res;
    return res;
}

vector<int> LC1356::sortByBits(vector<int>& arr) {
    // given an integer array arr. Sort the integers in the array in ascending order by the number of 1's
    // in their binary representation and in case of two or more integers have the same number of 1's you
    // have to sort them in ascending order
    // 利用bitset來計算1之個數
//    std::sort(arr.begin(), arr.end(), [&](const int &a, const int  &b)->bool {
//        int cnt_a = bitset<32>(a).count();
//        int cnt_b = bitset<32>(b).count();
//        // return期望結果之邏輯
//        return cnt_a != cnt_b ? cnt_a < cnt_b : a < b;
//    });
//    return arr;

    // 利用內建函數計算1之個數, 比用bitset快
//    std::sort(arr.begin(), arr.end(), [&](const int &a, const int &b) -> bool {
//        int cnt_a = __builtin_popcount(a);
//        int cnt_b = __builtin_popcount(b);
//        return cnt_a != cnt_b ? cnt_a < cnt_b : a < b;
//    });
//    return arr;

    // 數字做 n=n & (n-1)直到0的次數恰為含1之個數
    std::sort(arr.begin(), arr.end(), [&](const int &a, const int &b) -> bool {
        function<int(int)> cnt = [&](int num) -> int {
            int n = 0;
            while(num) {
                num &= (num-1);
                n++;
            }
            return n;
        };
        int cnt_a = cnt(a);
        int cnt_b = cnt(b);
        return cnt_a != cnt_b ? cnt_a < cnt_b : a < b;
    });
    return arr;

    /*
    0    0000    0
    -------------
    1    0001    1
    -------------
    2    0010    1
    3    0011    2
    -------------
    4    0100    1
    5    0101    2
    6    0110    2
    7    0111    3
    -------------
    8    1000    1
    9    1001    2
    10   1010    2
    11   1011    3
    12   1100    2
    13   1101    3
    14   1110    3
    15   1111    4
     */
}

bool LC1346::checkIfExist(vector<int>& arr) {
    // Given an array arr of integers, check if there exist two indices i and j such that :
    // i != j
    // 0 <= i, j < arr.length
    // arr[i] == 2 * arr[j]
    // Input: arr = [10,2,5,3]
    // Output: true
    // Explanation: For i = 0 and j = 2, arr[i] == 10 == 2 * 5 == 2 * arr[j]
    // 將所有元素兩倍值存入hash table裡，再循環一次看是否元素在table裡能查找到
    bool res=false;
    return res;
}

vector<int> LC1337::kWeakestRows(vector<vector<int>>& mat, int k) {
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
    // 算出每個row 1的個數，建立pair(row, 1's), pair再根據1's排序，即可得到前k名row的index
    vector<int> res;
    return res;
}

vector<int> LC1331::arrayRankTransform(vector<int>& arr) {
    // Given an array of integers arr, replace each element with its rank.
    // The rank represents how large the element is. The rank has the following rules:
    // Rank is an integer starting from 1.
    // The larger the element, the larger the rank. If two elements are equal, their rank must be the same.
    // Rank should be as small as possible.
    // Input: arr = [40,10,20,30]
    // Output: [4,1,2,3]
    // Explanation: 40 is the largest element. 10 is the smallest. 20 is the second smallest. 30 is the third smallest.
    // Input: arr = [100,100,100]
    // Output: [1,1,1]
    // Explanation: Same elements share the same rank.
    // 排序過後用一hash table建立rank, 再查找table得出每個值的rank
    vector<int> res;
    return res;
}

vector<vector<int>> LC1200::minimumAbsDifference(vector<int>& arr) {
    // Given an array of distinct integers arr, find all pairs of elements with the minimum absolute difference of
    // any two elements.
    // Return a list of pairs in ascending order(with respect to pairs), each pair [a, b] follows
    // a, b are from arr
    // a < b
    // b - a equals to the minimum absolute difference of any two elements in arr
    // Input: arr = [4,2,1,3]
    // Output: [[1,2],[2,3],[3,4]]
    // Explanation: The minimum absolute difference is 1. List all pairs with difference equal to 1 in ascending order.
    // 排序過後找出兩兩相鄰相差最小之值，循環一次把符合的pair放進res
    vector<vector<int>> res;
    return res;
}

int LC1051::heightChecker(vector<int>& heights) {
    // A school is trying to take an annual photo of all the students. The students are asked to stand in a
    // single file line in non-decreasing order by height. Let this ordering be represented by the integer
    // array expected where expected[i] is the expected height of the ith student in line.
    // You are given an integer array heights representing the current order that the students are standing in.
    // Each heights[i] is the height of the ith student in line (0-indexed).
    //
    // Return the number of indices where heights[i] != expected[i].
    //
    // Input: heights = [1,1,4,2,1,3]
    // Output: 3
    // Explanation:
    // heights:  [1,1,4,2,1,3]
    // expected: [1,1,1,2,3,4]
    // Indices 2, 4, and 5 do not match.
    // 排序過後看每一位置不相等的有幾個
    int res=0;
    return res;
}

vector<vector<int>> LC1030::allCellsDistOrder(int rows, int cols, int rCenter, int cCenter) {
    // You are given four integers row, cols, rCenter, and cCenter. There is a rows x cols matrix and you
    // are on the cell with the coordinates (rCenter, cCenter).
    // Return the coordinates of all cells in the matrix, sorted by their distance from (rCenter, cCenter)
    // from the smallest distance to the largest distance. You may return the answer in any order that
    // satisfies this condition.
    // The distance between two cells (r1, c1) and (r2, c2) is |r1 - r2| + |c1 - c2|.
    //
    // Input: rows = 1, cols = 2, rCenter = 0, cCenter = 0
    // Output:
    // [[0,0], [0,1]]
    // Explanation: The distances from (0, 0) to other cells are: [0,1]
    //
    // Input: rows = 2, cols = 2, rCenter = 0, cCenter = 1
    // Output: [[0,1],[0,0],[1,1],[1,0]]
    // [[0,0], [0,1],
    //  [1,0], [1,1]]
    // Explanation: The distances from (0, 1) to other cells are: [0,1,1,2]
    // The answer [[0,1],[1,1],[0,0],[1,0]] would also be accepted as correct.
    //
    // Input: rows = 2, cols = 3, rCenter = 1, cCenter = 2
    // Output: [[1,2],[0,2],[1,1],[0,1],[1,0],[0,0]]
    // [[0,0], [0,1], [0,2]
    //  [1,0], [1,1], [1,2]]
    // Explanation: The distances from (1, 2) to other cells are: [0,1,1,2,2,3]
    // There are other answers that would also be accepted as correct, such as [[1,2],[1,1],[0,2],[1,0],[0,1],[0,0]].
    // 雙層迴圈從(rCenter,cCenter)遞減依序枚舉出相近點之座標。
    vector<vector<int>> res;
    return res;
}

int LC1005::largestSumAfterKNegations(vector<int>& nums, int k) {
    // Given an integer array nums and an integer k, modify the array in the following way:
    // choose an index i and replace nums[i] with -nums[i].
    // You should apply this process exactly k times. You may choose the same index i multiple times.
    // Return the largest possible sum of the array after modifying it in this way.
    // Input: nums = [4,2,3], k = 1
    // Output: 5
    // Explanation: Choose index 1 and nums becomes [4,-2,3].
    // Example 2:
    // Input: nums = [3,-1,0,2], k = 3
    // Output: 6
    // Explanation: Choose indices (1, 2, 2) and nums becomes [3,1,0,2].
    // Example 3:
    // Input: nums = [2,-3,-1,5,-4], k = 2
    // Output: 13
    // Explanation: Choose indices (1, 4) and nums becomes [2,3,-1,5,4].
    // 先將原本nums做排序，若有負數，先將k次機會用在將負數轉正，若只有正數則先將最小數轉負，
    // 因此可以說k次就依序用在最小的k數上，再求總合
    int res=0;
    return res;
}

vector<int> LC0977::sortedSquares(vector<int>& nums) {
    // Given an integer array nums sorted in non-decreasing order, return an array of the squares of each
    // number sorted in non-decreasing order.
    // Input: nums = [-4,-1,0,3,10]
    // Output: [0,1,9,16,100]
    // Explanation: After squaring, the array becomes [16,1,0,9,100].
    // After sorting, it becomes [0,1,9,16,100].
    // 由於平方過後大小關係會改變，所以先對每數做平方，再做排序
    vector<int> res;
    return res;
}

int LC0976::largestPerimeter(vector<int>& nums) {
    // Given an integer array nums, return the largest perimeter of a triangle with a non-zero area,
    // formed from three of these lengths. If it is impossible to form any triangle of a non-zero area, return 0.
    // Input: nums = [2,1,2]
    // Output: 5
    // Input: nums = [1,2,1]
    // Output: 0
    // 三角形任意兩邊的和大於第三邊，任意兩邊的差小於第三邊。
    // 先把nums排序過，從最大的三個值開始檢查是否符合三角形邊長規則，若否則遞減一值
    int res=0;
    return res;
}

vector<int> LC0922::sortArrayByParityII(vector<int>& nums) {
    // Given an array of integers nums, half of the integers in nums are odd, and the other half are even.
    // Sort the array so that whenever nums[i] is odd, i is odd, and whenever nums[i] is even, i is even.
    // Return any answer array that satisfies this condition.
    // Input: nums = [4,2,5,7]
    // Output: [4,5,2,7]
    // Explanation: [4,7,2,5], [2,5,4,7], [2,7,4,5] would also have been accepted.
    // 用兩個index指標分別指向奇偶數的位置，遞增時+=2
    vector<int> res;
    return res;
}

vector<int> LC0905::sortArrayByParity(vector<int>& nums) {
    // Given an integer array nums, move all the even integers at the beginning of the array followed by all the odd integers.
    // Return any array that satisfies this condition.
    // Input: nums = [3,1,2,4]
    // Output: [2,4,3,1]
    // Explanation: The outputs [4,2,3,1], [2,4,1,3], and [4,2,1,3] would also be accepted.
    // 創建一vector, 兩個index分別指向頭尾，nums根據機偶數依序分別存入。
    vector<int> res;
    return res;
}

int LC0747::dominantIndex(vector<int>& nums) {
    // You are given an integer array nums where the largest integer is unique.
    // Determine whether the largest element in the array is at least twice as much as every other number in
    // the array. If it is, return the index of the largest element, or return -1 otherwise.
    // Input: nums = [3,6,1,0]
    // Output: 1
    // Explanation: 6 is the largest integer.
    // For every other number in the array x, 6 is at least twice as big as x.
    // The index of value 6 is 1, so we return 1.
    // 用hash table循環記下index，並找出max值，再一個循環檢查是否都大於兩倍其他數
    int res=0;
    return res;
}

void LC0088::merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
    // You are given two integer arrays nums1 and nums2, sorted in non-decreasing order, and two integers m and n,
    // representing the number of elements in nums1 and nums2 respectively.
    // Merge nums1 and nums2 into a single array sorted in non-decreasing order.
    // The final sorted array should not be returned by the function, but instead be stored inside the array nums1.
    // To accommodate this, nums1 has a length of m + n, where the first m elements denote the elements that should
    // be merged, and the last n elements are set to 0 and should be ignored. nums2 has a length of n.
    // 結果會放在nums1裡，可以從nums1的後面開始往前放相比的element.
}