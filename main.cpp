#include "main.h"
using namespace std;

int main() {
    cout << "Hello, World!" << endl;

    vector<int> v{9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    for(auto i:v) cout << i << ' ';
    cout << endl;

//    Sort run;
//    run.quickSortIterative(v);
    LinkedList l1, l2;
    l1.AddNode(1); l1.AddNode(2); l1.AddNode(4);
    l2.AddNode(1); l2.AddNode(3); l2.AddNode(4);
    LinkedList().ShowLinkedList(l1.GetListHead());
    LinkedList().ShowLinkedList(l2.GetListHead());
    LC0021 run;
    ListNode* r = run.mergeTwoLists(l1.GetListHead(), l2.GetListHead());
    LinkedList().ShowLinkedList(r);

//    string s {"ABCDE"};
//    for(auto c:s) cout << c << ' ';
//    cout << endl;

    for(auto i:v) cout << i << ' ';
    cout << endl;

    return 0;
}
