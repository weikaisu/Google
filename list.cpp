//
// Created by steve on 2021-08-11.
//

#include "list.h"

/***********  Vector List  **********/

vector<int> LC0349::intersection(vector<int>& nums1, vector<int>& nums2) {
    // 用个 HashSet 把 nums1 都放进去，然后遍历 nums2 的元素，如果在 HashSet 中存在，
    // 说明是交集的部分，加入结果的 HashSet 中，最后再把结果转为 vector 的形式即可
    unordered_set<int> res, set(nums1.begin(), nums1.end());
    for(auto n:nums2)
        if(set.count(n)) res.insert(n);
    return vector<int>(res.begin(), res.end());
}

//LC0268 run;
//vector<int> v {3,0,1};
//cout << run.missingNumber(v);
int LC0268::missingNumber(vector<int>& nums) {
    // 用等差数列的求和公式求出0到n之间所有的数字之和，然后再遍历数组算出给定数字的累积和，然后做减法，差值就是丢失的那个数字
    int sum=0, n=nums.size();

    for_each(nums.begin(), nums.end(), [&](int n) {sum+=n;});
    return (n*(n+1))/2 - sum;
}

bool LC0242::isAnagram(string s, string t) {
    // 先判断两个字符串长度是否相同，不相同直接返回false。然后把s中所有的字符出现个数统计起来，
    // 存入一个大小为26的数组中，因为题目中限定了输入字符串为小写字母组成。然后我们再来统计t字符串，如果发现不匹配则返回false。
    if(s.size()!=t.size()) return false;

    array<int, 26> set; set.fill(0);
    for(auto c:s)
        ++set[c-'a'];
    for(auto c:t) {
        if(--set[c-'a'] < 0) return false;
    }
    return true;
}

bool LC0219::containsNearbyDuplicate(vector<int>& nums, int k) {
    unordered_map<int, int> map;
    for(int i=0; i<nums.size(); i++) {
        if(map.count(nums[i]) && i-map[nums[i]] <=k) return true;
        map[nums[i]] = i;
    }
    return false;
}

bool LC0217::containsDuplicate(vector<int>& nums) {
    unordered_set <int> set;
    for(auto n:nums) {
        if(set.count(n)) return true;
        set.insert(n);
    }
    return false;
}

//LC0205 run;
//cout << run.isIsomorphic("ab", "aa") << endl;
bool LC0205::isIsomorphic(string s, string t) {
    // 原字符串中的每个字符可由另外一个字符替代，可以被其本身替代，相同的字符一定要被同一个字符替代，
    // 且一个字符不能被多个字符替代，即不能出现一对多的映射。根据一对一映射的特点，需要用两个 HashMap
    // 分别来记录原字符串和目标字符串中字符出现情况，由于 ASCII 码只有 256 个字符，所以可以用一个 256
    // 大小的数组来代替 HashMap，并初始化为0，遍历原字符串，分别从源字符串和目标字符串取出一个字符，
    // 然后分别在两个数组中查找其值，若不相等，则返回 false，若相等，将其值更新为 i + 1
    array<int, 256> sa; sa.fill(-1);
    array<int, 256> st; st.fill(-1);

    for(int i=0; i<s.size(); i++) {
        if(sa[s[i]]!=st[t[i]]) return false;
        sa[s[i]] = st[t[i]] = i;
    }
    return true;
}

bool LC0202::isHappy(int n) {
    // 我们可以用 HashSet 来记录所有出现过的数字，然后每出现一个新数字，
    // 在 HashSet 中查找看是否存在，若不存在则加入表中，若存在则跳出循环，并且判断此数是否为1，
    // 若为1返回true，不为1返回false
//    unordered_set<int> set;
//    while(n!=1) {
//        int sum = 0;
//        while(n) {
//            sum += pow(n%10,2);
//            n /=10;
//        }
//        if(set.count(sum)) return false;
//        set.insert(sum);
//        n=sum;
//    }
//    return true;

    // 可以不用 HashSet 来做，我们并不需要太多的额外空间，关于非快乐数有个特点，循环的数字中必定会有4
    while(n!=1 && n!=4) {
        int sum = 0;
        while(n) {
            sum += pow(n%10, 2);
            n /= 10;
        }
        n = sum;
    }
    return n==1;
}

int LC0169::majorityElement(vector<int>& nums) {
    // 将第一个数字假设为过半数，然后把计数器设为1，比较下一个数和此数是否相等，若相等则计数器加一，
    // 反之减一。然后看此时计数器的值，若为零，则将下一个值设为候选过半数。以此类推直到遍历完整个数组，
    // 当前候选过半数即为该数组的过半数。
    // 为啥遇到不同的要计数器减1呢，为啥减到0了又要更换候选者呢？首先是有那个强大的前提存在，
    // 一定会有一个出现超过半数的数字存在，那么如果计数器减到0了话，说明目前不是候选者数字的个数已经跟候选者的出现个数相同了，
    // 那么这个候选者已经很 weak，不一定能出现超过半数，此时选择更换当前的候选者。那有可能你会有疑问，
    // 那万一后面又大量的出现了之前的候选者怎么办，不需要担心，如果之前的候选者在后面大量出现的话，其又会重新变为候选者，
    // 直到最终验证成为正确的过半数
    int val=0, cnt=0;
    for(auto n:nums) {
        if(!cnt) {
            val = n;
            cnt++;
        } else {
            (val==n) ? cnt++ : cnt--;
        }
    }
    return val;
}

//LC0066 run;
//vector<int> nums{9,9,9}, ans;
//ans=run.plusOne(nums);
//for(auto n:nums) cout << n << ' ';
//cout << endl;
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
