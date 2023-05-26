
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

    // 用lower_bound找出在排序過後的位置
//    vector<int> sorted(nums);
//    const int n = nums.size();
//    vector<int> res(n);
//    std::sort(sorted.begin(), sorted.end());
//    for(int i=0; i<n; i++)
//        res[i] = std::distance(sorted.begin(), std::lower_bound(sorted.begin(), sorted.end(), nums[i]));
//    return res;

    // 已知nums值的範圍，統計每個值出現的次數，再算出直方圖即可統計小於的數量
    const int n = nums.size();
    vector<int> count(101, 0);
    vector<int> prefix(101, 0);
    vector<int> res(n);

    std::for_each(nums.begin(), nums.end(), [&](int num) {count[num]++;});

    for(int i=1; i<101; i++)
        prefix[i] = prefix[i-1] + count[i-1];

    for(int i=0; i<n; i++)
        res[i] = prefix[nums[i]];

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

    // 用兩層迴圈掃每個element的2倍值是否存在，並先判斷是否是偶數來加速。
    // 這方法看似暴力法，實際上卻比下面用table的方式快很多。
    const int size = arr.size();

    for(int i=0; i<size; i++) {
        if(arr[i]%2 == 0)
            for(int j=0; j<size; j++) {
                if(i!=j && arr[i] == 2*arr[j])
                    return true;
            }
    }
    return false;

    // 將所有元素兩倍值存入hash table裡，再循環一次看是否元素在table裡能查找到
//    unordered_map<int, int> m;
//
//    for(int i=0; i<arr.size(); i++)
//        m[arr[i]*2] = i;
//
//    for(int i=0; i<arr.size(); i++)
//        if(m.count(arr[i]) && m[arr[i]] != i)
//            return true;
//    return false;
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

    // use priority queue and merge soldier count and index into one number : cunt*100 + idx;
    const int m=mat.size();
    priority_queue<int, vector<int>, greater<int>> pq;
    vector<int> res(k);

    for(int i=0; i<m; i++)
        pq.push(std::accumulate(mat[i].begin(), mat[i].end(), 0)*100 + i);

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
    const int n = arr.size();
    int rank = 1;
    vector<int> res(n);
    vector<int> sorted(arr);
    unordered_map<int, int> t;

    std::sort(sorted.begin(), sorted.end());
    for(auto &s:sorted)
        if(!t.count(s)) t[s] = rank++;
    for(int i=0; i<n; i++)
        res[i] = t[arr[i]];
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
    // 给了一个没有重复数字的整型数组，现在让找出差的绝对值最小的数对儿。既然是 Easy 的身价，那么就没有太 Fancy 的解法，为了更方便的找出差
    // 的绝对值最小的数对儿，先给数组进行排序，这样最小差值一定会出现在相邻的两个数字之间。接下来就是遍历所有相邻的两个数字，维护一个最小值
    // mn，若当前差值 diff 小于等于 mn，则进行进一步操作，二者中唯一不同的是当 diff 小于 mn 时，结果 res 需要清空。然后将 mn 更新为
    // diff，并把当前数组对儿加入到结果 res 中即可
    vector<vector<int>> res;
    int min = INT_MAX;
    std::sort(arr.begin(), arr.end());
    for(int i=1; i<arr.size(); i++) {
        int diff = arr[i] - arr[i-1];
        if(diff <= min) {
            if(diff < min) {
                res.clear();
                min = diff;
            }
            res.push_back({arr[i-1], arr[i]});
        }
    }

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
    // 一群学生随机的站成一排照相，现在想让学生按照身高来排列，问需要移动多个同学。这是一道很简单的题目没有什么难度，只要复制一个新的数组，
    // 然后给数组排序，再跟原数组逐个按数字来对比，只要数字不同，则结果 res 自增1即可
    int res=0;

    vector<int> sorted(heights);
    std::sort(sorted.begin(), sorted.end());
    for(int i=0; i<heights.size(); i++)
        if(heights[i]!= sorted[i]) res++;

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
    // 给了一个R行C列的矩阵，又给了一个起始点 (r0, c0)，让按照离起始点的曼哈顿距离从小到大排序坐标点。自定义一个 comparator 给 res 数组
    // 重新排序即可，自定义的 comparator 要把 (r0, c0) 当参数传进去，因为要求和其的曼哈顿距离
    vector<vector<int>> res;
    for(int i=0; i<rows; i++)
        for(int j=0; j<cols; j++)
            res.push_back({i, j});
    std::sort(res.begin(), res.end(), [rCenter, cCenter](vector<int> &a, vector<int> &b) {
        return std::abs(a[0]-rCenter) + std::abs(a[1]-cCenter) < std::abs(b[0]-rCenter) + std::abs(b[1]-cCenter);
    });
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
    // 先给数组排个序，这样所有的负数都在数组的前面了，然后此时将前K个负数翻转成正数，注意只是翻转负数，若负数的个数小于K，也不会翻转多余的正
    // 数。然后此时遍历数组，求数组之后，并且求此时数组中最小的数字，此时K还是有奇偶两种情况，当K是偶数的时候（包括0），直接返回数组之和，
    // 若是奇数的时候，此时说明数组中的负数已经全部翻转为了正数，那么最小的数也就是绝对值最小的数，减去其的2倍即可
    int res = 0, min=INT_MAX;

    std::sort(nums.begin(), nums.end());
    for(int i=0; k && i<nums.size() && nums[i]<0; i++, k--)
        nums[i] = -nums[i];
    for(auto &num:nums) {
        res += num;
        min = std::min(min, num);
    }
    return res - (k%2)*2*min;
}

vector<int> LC0977::sortedSquares(vector<int>& nums) {
    // Given an integer array nums sorted in non-decreasing order, return an array of the squares of each
    // number sorted in non-decreasing order.
    // Input: nums = [-4,-1,0,3,10]
    // Output: [0,1,9,16,100]
    // Explanation: After squaring, the array becomes [16,1,0,9,100].
    // After sorting, it becomes [0,1,9,16,100].

    // 使用双指针来做，用两个变量分别指向开头和结尾，然后比较，每次将绝对值较大的那个数的平方值先加入数组的末尾，然后依次往前更新，
    // 最后得到的就是所求的顺序
    const int n = nums.size();
    vector<int> res(n);
    int r = 0, l = n-1;
    for(int i=n-1; i>=0; i--) {
        (std::abs(nums[r]) < std::abs(nums[l])) ? res[i] = nums[l]*nums[l--] : res[i] = nums[r]*nums[r++];
    }
    return res;

    // 由於平方過後大小關係會改變，所以先對每數做平方，再做排序
//    for(auto &num:nums)
//        num*=num;
//    std::sort(nums.begin(), nums.end());
//    return nums;
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

    // 给了个正整数数组，让从中选三个数当作三角形的三条边，问能组成的三角形的最大周长是多少。因为要组成三角形，所以必须要满足两边之和大于
    // 第三边这一条性质，我们并不用去检测所有的组合情况，而是只要判断较短的两边之和是否大于最长的那条边就可以了。虽然这道是 Easy 题目，但
    // 是 OJ 仍然不让用暴力搜索法，遍历任意三条边是会超时的。所以只能想优化的解法，既然要周长最长，则肯定是选较大的数字先测比较好。这里就
    // 先给数组排个序，然后从末尾开始，每次取出三个数字，先检测能否组成三角形，可以的话直接返回周长，不行的话就继续往前取，若都不行的话，就
    // 返回0
    std::sort(nums.begin(), nums.end());
    for(int i=nums.size()-1; i>=2; i--)
        if(nums[i] < nums[i-1] + nums[i-2])
            return nums[i] + nums[i-1] + nums[i-2];
    return 0;
}

vector<int> LC0922::sortArrayByParityII(vector<int>& nums) {
    // Given an array of integers nums, half of the integers in nums are o\dd, and the other half are even.
    // Sort the array so that whenever nums[i] is odd, i is odd, and whenever nums[i] is even, i is even.
    // Return any answer array that satisfies this condition.
    // Input: nums = [4,2,5,7]
    // Output: [4,5,2,7]
    // Explanation: [4,7,2,5], [2,5,4,7], [2,7,4,5] would also have been accepted.

    // 不需要使用额外的空间，思路是用两个指针，i指针一直指向偶数位置，j指针一直指向奇数位置，当 A[i] 是偶数时，则跳到下一个偶数位置，直到i
    // 指向一个偶数位置上的奇数，同理，当 A[j] 是奇数时，则跳到下一个奇数位置，直到j指向一个奇数位置上的偶数，当 A[i] 和 A[j] 分别是奇数
    // 和偶数的时候，则交换两个数字的位置，从而满足题意
    const int n = nums.size();
    int i = 0, j = 1;
    while(i<n && j<n) {
        if(nums[i]%2==0) i+=2;
        else if(nums[j]%2==1) j+=2;
        else std::swap(nums[i], nums[j]);
    }
    return nums;

    // 用兩個index指標分別指向奇偶數的位置，遞增時+=2
//    vector<int> res(nums.size());
//    int eidx = 0, oidx = 1;
//    for(auto &num:nums)
//        //(num%2==0) ? res[eidx+=2]=num : res[oidx+=2]=num; <-- incorrect
//        if(num%2==0) {
//            res[eidx] = num;
//            eidx+=2;
//        } else {
//            res[oidx] = num;
//            oidx+=2;
//        }
//    return res;
}

vector<int> LC0905::sortArrayByParity(vector<int>& nums) {
    // Given an integer array nums, move all the even integers at the beginning of the array followed by all the odd integers.
    // Return any array that satisfies this condition.
    // Input: nums = [3,1,2,4]
    // Output: [2,4,3,1]
    // Explanation: The outputs [4,2,3,1], [2,4,1,3], and [4,2,1,3] would also be accepted.

    // 优化空间复杂度，不新建额外的数组，而是采用直接交换数字的位置，使用两个指针i和j，初始化均为0。然后j往后遍历，若遇到了偶数，则将
    // A[j] 和 A[i] 交换位置，同时i自增1，这样操作下来，同样可以将所有的偶数都放在奇数前面
    for(int i=0, j=0; j<nums.size(); j++)
        if (nums[j]%2 == 0) std::swap(nums[i++], nums[j]);
    return nums;

    // 創建一vector, 兩個index分別指向頭尾，nums根據機偶數依序分別存入。
//    vector<int> res(nums.size());
//    int h = 0, t = nums.size()-1;
//    for(auto &num:nums)
//        (num & 1) ? res[t--] = num : res[h++] = num;
//    return res;
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

    // 找一个至少是其他数字两倍的最大数字，那么我们想，首先明确的一点是这个要求的数字一定是数组中的最大数字，因为其是其他所有的数
    // 字的至少两倍。然后就是，如果该数字是数组中第二大的数字至少两倍的话，那么它一定是其他所有数字的至少两倍，所以我们可以遍历一
    // 次数组分别求出最大数字和第二大数字，然后判断一下最大数字是否是第二大数字的两倍即可，注意这里我们判断两倍的方法并不是直接相
    // 除，为了避免除以零的情况，我们采用减法
//    int idx=0, firstMX = INT_MIN, secondMX = INT_MIN;
//    for(int i=0; i<nums.size(); i++) {
//        if(nums[i] > firstMX) {
//            secondMX = firstMX;
//            firstMX = nums[i];
//            idx = i;
//        } else if(nums[i] > secondMX) {
//            secondMX = nums[i];
//        }
//    }
//    return (firstMX - secondMX >= secondMX) ? idx : -1;

    // 使用更straightforward的方法，首先遍历一遍数组找出最大数字，然后再遍历一遍数组，验证这个数字是否是其他数字的至少两倍
    int idx = 0, mx = INT_MIN;
    for(int i=0; i<nums.size(); i++)
        if(nums[i]>mx) {
            mx = nums[i];
            idx = i;
        }
    for(auto &num:nums)
        if(num!=mx && mx-num<num) return -1;
    return idx;
}

void LC0088::merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
    // You are given two integer arrays nums1 and nums2, sorted in non-decreasing order, and two integers m and n,
    // representing the number of elements in nums1 and nums2 respectively.
    // Merge nums1 and nums2 into a single array sorted in non-decreasing order.
    // The final sorted array should not be returned by the function, but instead be stored inside the array nums1.
    // To accommodate this, nums1 has a length of m + n, where the first m elements denote the elements that should
    // be merged, and the last n elements are set to 0 and should be ignored. nums2 has a length of n.
    // 結果會放在nums1裡，可以從nums1的後面開始往前放相比的element.
    int i = m + n - 1;
    m--;
    n--;
    while(n >= 0) {
        nums1[i--] = (m >= 0 && nums1[m] > nums2[n]) ? nums1[m--] : nums2[n--];
    }
}