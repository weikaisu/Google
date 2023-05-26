#ifndef GOOGLE_MAIN_H
#define GOOGLE_MAIN_H

#include <array>
#include <iostream>
#include <string>
#include <regex>
#include <algorithm>
#include <utility>
#include <vector>
#include <list>
#include <forward_list>
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <bitset>
#include <functional>
#include <numeric> // std:: accumulate
#include <string_view>

#include "sort.h"
#include "list.h"
#include "search.h"
#include "tree.h"
#include "string.h"
#include "dp.h"
#include "math.h"
#include "bit.h"

using namespace std;

// multi condition for loop
// for(i = 0, j = 0; i < p && j < q; i++, j++){

// XOR
// 1. 相同為0，相異為1
// 2. 跟1做XOR，0變1，1變0
// 0 xor 0 = 0
// 0 xor 1 = 1
// 1 xor 0 = 1
// 1 xor 1 = 0

//struct ListNode {
//    int val;
//    ListNode *next;
//    ListNode(int x) : val(x), next(nullptr) {};
//    ListNode(int x, ListNode *next) : val(x), next(next) {};
//};

// all_of:检查区间[first, last)中是否所有的元素都满足一元判断式p，所有的元素都满足条件返回true，否则返回false。
// any_of：检查区间[first, last)中是否至少有一个元素都满足一元判断式p，只要有一个元素满足条件就返回true，否则返回true。
// none_of：检查区间[first, last)中是否所有的元素都不满足一元判断式p，所有的元素都不满足条件返回true，否则返回false。

class Employee {
public:
    // It's the unique ID of each node.
    // unique id of this employee
    int id;
    // the importance value of this employee
    int importance;
    // the id of direct subordinates
    vector<int> subordinates;
};

struct Interval {
    int start;
    int end;
    Interval() { start = 0; end = 0; }
    Interval(int s, int e) { start = s; end = e; }
};

struct Point {
    int x;
    int y;
    Point() : x(0), y(0) {}
    Point(int a, int b) : x(a), y(b) {}
};

#endif //GOOGLE_MAIN_H
