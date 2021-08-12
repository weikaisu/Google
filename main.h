//
// Created by steve on 2021-08-10.
//

#ifndef GOOGLE_MAIN_H
#define GOOGLE_MAIN_H

#include <iostream>
#include <string>
#include <regex>
#include <algorithm>
#include <utility>
#include <vector>
#include <list>
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <bitset>
#include <functional>

#include "sort.h"
#include "search.h"
#include "list.h"
#include "math.h"

using namespace std;

struct TreeNode {
    int val;
    int height; //for AVLTree
    TreeNode *left;
    TreeNode *right;
    TreeNode *parent;
    TreeNode(int x) : val(x), height(1), left(NULL), right(NULL), parent(NULL) {}
};

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

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
