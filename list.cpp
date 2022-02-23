//
// Created by steve on 2021-08-11.
//

#include "list.h"

//LC0066 run;
//vector<int> nums{9,9,9}, ans;
//ans=run.plusOne(nums);
//for(auto n:nums) cout << n << ' ';
//cout << endl;
/***********  Vector List  **********/
vector<int> LC0066::plusOne(vector<int>& digits) {
    int c=1;
    for(int i=digits.size()-1 ; i>=0 ; i--) {
        int v = digits[i]+c;
        digits[i] = v % 10;
        c = v / 10;
    }
    if(c) digits.emplace(digits.begin(), c);
    return digits;
}

//LC0027 run;
//vector<int> n{0,1,2,2,3,0,4,2}; // val=2
//vector<int> n{3,2,2,3}; // val=3
//vector<int> n{1}; // val=1
//cout << run.removeElement(n, 1) << endl;
//for(auto i:n) cout << i << ' ';
//cout << endl;
int LC0027::removeElement(vector<int>& nums, int val) {
    int s=nums.size();
    int r=0;
    for(int i=0 ; i<nums.size() ; i++) {
        if(nums[i]==val)
            s--;
        else
            nums[r++]=nums[i];
    }
    return s;
}

//LC0026 run;
//vector<int> n{0,0,1,1,1,2,2,3,3,4};
//vector<int> n{1,1,2};
//cout << run.removeDuplicates(n) << endl;
//for(auto i:n) cout << i << ' ';
//cout << endl;
int LC0026::removeDuplicates(vector<int>& nums) {
    int s=nums.size(); if(s<=1) return s;
    int r=1, p=nums[0];
    for(int i=1 ; i<nums.size() ; i++) {
        if(p == nums[i])
            s--;
        else
            nums[r++]=nums[i];
        p=nums[i];
    }
    return s;
}

vector<int> LC0001::twoSum(vector<int>& nums, int target) {
    unordered_map<int, int> t;

    // find target-nums[i], save nums[i]
    for(auto i=0 ; i<nums.size(); i++) {
        auto diff = target - nums[i];
        if(t.count(diff))
            return {t[diff], i};
        t[nums[i]]=i;
    }
    return {};

    // find nums[i], save target-nums[i]
    for(auto i=0 ; i<nums.size() ; i++) {
        auto diff = target - nums[i];
        if(t.count(nums[i]))
            return {t[nums[i] ], i};
        t[diff] = i;
    }
    return {};
}


/***********  Linked List  **********/

//LinkedList l2;
//l2.AddNode(1); l2.AddNode(0); l2.AddNode(1);
//LC1290 run;
//cout << run.getDecimalValue(l2.GetListHead()) << endl;
int LC1290::getDecimalValue(ListNode* head) {
    auto fun = [](const auto &self, ListNode* node, int &m) -> int {
        if(!node->next) return node->val;
        int v =  self(self, node->next, m);
        m*=2;
        return node->val*m + v;
    };

    if(!head) return 0;
    int m = 1;
    return fun(fun, head, m);
}

ListNode* LC0876::middleNode(ListNode* head) {
    ListNode *slow=head, *fast=head;

    while(fast->next && fast->next->next) {
        slow = slow->next;
        fast = fast->next->next;
    }

    return fast->next ? slow->next : slow;
}

void LC0237::deleteNode(ListNode* node) {
    // 先把当前节点的值用下一个节点的值覆盖了，然后我们删除下一个节点即可
    ListNode *n = node->next;
    node->val = n->val;
    node->next = n->next;
    delete n;
}

bool LC0234::isPalindrome(ListNode* head) {
    if(!head || !head->next) return true;
    stack<int> s;

    // 先按顺序把所有的结点值都存入到一个栈 stack 里，然后利用栈的后入先出的特性，
    // 就可以按顺序从末尾取出结点值了，此时再从头遍历一遍链表，就可以比较回文的对应位置了，
    // 若不同直接返回 false 即可
//    ListNode* node = head;
//    while(node) {
//        s.push(node->val);
//        node = node->next;
//    }
//    while(head) {
//        int v = s.top(); s.pop();
//        if(v != head->val) return false;
//        head = head->next;
//    }
//    return true;

    // use fast/slow pointer
    ListNode *slow=head, *fast=head;
    s.push(slow->val);
    while(fast->next && fast->next->next) {
        slow = slow->next;
        fast = fast->next->next;
        s.push(slow->val);
    }
    if(!fast->next) s.pop();
    while(slow->next) {
        slow = slow->next;
        int v = s.top(); s.pop();
        if(v != slow->val) return false;
    }
    return true;
}

//LinkedList l;
//l.AddNode(1); l.AddNode(2); l.AddNode(3);
//l.AddNode(4); l.AddNode(5); l.AddNode(6);
//LC0206 run;
//ListNode* r = run.reverseList(l.GetListHead());
//LinkedList::ShowLinkedList(r);
ListNode* LC0206::reverseList(ListNode* head) {
    // time(N), iterative
    ListNode *c=nullptr, *n=nullptr;
    while(head) {
        //把n指到head->next
        //把n放在head->next的位置
        n=head->next;
        head->next=c;
        c=head;
        head=n;
    }
    return c;

    // time(N), recursive
    if(head==nullptr || head->next==nullptr) return head;
    ListNode *h = reverseList(head->next);
    head->next->next = head;
    head->next = nullptr;
    return h;
}
//LinkedList l1;
//l1.AddNode(1); l1.AddNode(2); l1.AddNode(6); l1.AddNode(3); l1.AddNode(4); l1.AddNode(5); l1.AddNode(6);
//LC0203 run;
//ListNode* r = run.removeElements(l2.GetListHead(), 7);
//LinkedList::ShowLinkedList(r);
ListNode* LC0203::removeElements(ListNode* head, int val) {
    if(!head) return head;

    ListNode dummy(0);
    ListNode *pre = &dummy;
    dummy.next = head;

    while(head) {
        if(head->val == val) {
            ListNode *node = head;
            pre->next = head->next;
            head = head->next;
            delete node;
        } else {
            pre = head;
            head = head->next;
        }
    }

    return dummy.next;
}

ListNode* LC0160::getIntersectionNode(ListNode *headA, ListNode *headB) {
    if(!headA || !headB) return nullptr;

    // slower way
//    unordered_set <ListNode*> set;
//    while(headA) {
//        set.emplace(headA);
//        headA = headA->next;
//    }
//    while(headB) {
//        if(set.count(headB)) return headB;
//        set.emplace(headB);
//        headB = headB->next;
//    }
//    return nullptr;

    // faster way
    // 如果两个链长度相同的话，那么对应的一个个比下去就能找到，所以只需要把长链表变短即可。
    // 具体算法为：分别遍历两个链表，得到分别对应的长度。然后求长度的差值，把较长的那个链表向后移动这个差值的个数，然后一一比较即可
//    auto diff = [](ListNode* l1, ListNode* l2) -> int  {
//        int len1 = 0;
//        while(l1) {
//            l1 = l1->next;
//            len1++;
//        }
//        int len2 = 0;
//        while(l2) {
//            l2 = l2->next;
//            len2++;
//        }
//        return len1-len2;
//    };
//
//    int n = diff(headA, headB);
//    if(n>0)
//        while(n-- > 0)
//            headA = headA->next;
//    else
//        while(n++ < 0)
//            headB = headB->next;
//
//    while(headA && headB && headA!=headB) {
//        headA = headA->next;
//        headB = headB->next;
//    }
//    return (headA && headB) ? headA : nullptr;

    // tricky way
    // 虽然题目中强调了链表中不存在环，但是可以用环的思想来做，
    // 这里让两条链表分别从各自的开头开始往后遍历，当其中一条遍历到末尾时，
    // 跳到另一个条链表的开头继续遍历。两个指针最终会相等，而且只有两种情况，一种情况是在交点处相遇，
    // 另一种情况是在各自的末尾的空节点处相等。为什么一定会相等呢，因为两个指针走过的路程相同，
    // 是两个链表的长度之和，所以一定会相等。这个思路真的很巧妙，而且更重要的是代码写起来特别的简洁
    ListNode *a=headA, *b=headB;
    while(a!=b) {
        a = a ? a->next : headB;
        b = b ? b->next : headA;
    }
    return a;
}

bool LC0141::hasCycle(ListNode *head) {
    // time(N) space(N)
    unordered_set<ListNode*> set;
    while(head!=nullptr) {
        if(set.count(head)) return true;
        else {
            set.insert(head);
            head=head->next;
        }
    }
    return false;

    // fast/slow pointers, no extra space
    ListNode *fast, *slow;
    fast=slow=head;
    while(fast) {
        if(fast->next==nullptr) return false;
        if((fast=fast->next->next)==(slow=slow->next)) return true;
    }
    return false;
}

//LinkedList l1;
//l1.AddNode(1); l1.AddNode(2); l1.AddNode(5); l1.AddNode(2); l1.AddNode(2);
//LC0083 run;
//ListNode* r = run.deleteDuplicates(l1.GetListHead());
//LinkedList::ShowLinkedList(r);
ListNode* LC0083::deleteDuplicates(ListNode* head) {
    if(!head || !head->next) return head;

    unordered_set<int> set;
    set.insert(head->val);
    ListNode* tail = head;

    while(tail->next) {
        if(!set.count(tail->next->val)) {
            set.insert(tail->next->val);
            tail = tail->next;
        } else {
            ListNode* node = tail->next;
            tail->next = tail->next->next;
            delete node;
        }
    }

    return head;
}

//LinkedList l1, l2;
//l1.AddNode(1); l1.AddNode(2); l1.AddNode(4);
//l2.AddNode(1); l2.AddNode(3); l2.AddNode(4);
//LC0021 run;
//ListNode* r = run.mergeTwoLists(l1.GetListHead(), l2.GetListHead());
//LinkedList::ShowLinkedList(r);
ListNode* LC0021::mergeTwoLists(ListNode* l1, ListNode* l2) {
    // time(N), iterative
    ListNode head(0);
    ListNode *tail=&head;
    while(l1 && l2) {
        if(l1->val < l2->val) {
            tail->next = l1;
            l1 = l1->next;
        } else {
            tail->next = l2;
            l2 = l2->next;
        }
        tail=tail->next;
    }
    if(l1) tail->next=l1;
    if(l2) tail->next=l2;
    return head.next;

    // time(N), recursive
    if(l1==nullptr || l2==nullptr) return l1==nullptr ? l2 : l1;
    if(l1->val < l2->val) {
        l1->next = mergeTwoLists(l1->next , l2);
        return l1;
    } else {
        l2->next = mergeTwoLists(l1, l2->next);
        return l2;
    }
}
