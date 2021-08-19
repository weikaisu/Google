#include "main.h"
using namespace std;

int main() {
    cout << "Hello, World!" << endl;

    vector<int> v{9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    for(auto i:v) cout << i << ' ';
    cout << endl;

//    Sort run;
//    run.quickSortIterative(v);
    LinkedList l;
    l.AddNode(1); l.AddNode(2); l.AddNode(3);
    l.AddNode(4); l.AddNode(5); l.AddNode(6);
    LC0206 run;
    ListNode* r = run.reverseList(l.GetListHead());
    LinkedList().ShowLinkedList(r);

//    string s {"ABCDE"};
//    for(auto c:s) cout << c << ' ';
//    cout << endl;

    for(auto i:v) cout << i << ' ';
    cout << endl;

    return 0;
}
