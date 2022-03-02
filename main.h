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

#include "sort.h"
#include "list.h"
#include "search.h"
#include "tree.h"
#include "string.h"
#include "dp.h"
#include "math.h"

using namespace std;

//struct ListNode {
//    int val;
//    ListNode *next;
//    ListNode(int x) : val(x), next(nullptr) {};
//    ListNode(int x, ListNode *next) : val(x), next(next) {};
//};

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
