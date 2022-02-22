#include "main.h"
#include "play.cpp"
using namespace std;

int main() {
    cout << "Hello, World!" << endl;

//    vector<int> v{9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
//    for(auto i:v) cout << i << ' ';
//    cout << endl;
//    Sort run;
//    run.HeapSort(v);
//    LC0067 run;
//    cout << run.addBinary("11","1");
//    cout << endl;
//    for(auto i:v) cout << i << ' ';
//    cout << endl;

//    Play play;
//    play.Iterative(v);

//    TreeNode *root;
//    root->BuildTree(root);
//    root->TraverseBottomUp(root);
//    root->CleanTree(root);

    LinkedList l1, l2;
    l1.AddNode(1); l1.AddNode(2); l1.AddNode(5); l1.AddNode(2); l1.AddNode(2);
    l2.AddNode(1); l2.AddNode(3); l2.AddNode(4);
//    Play run;
//    ListNode* r = run.mergeTwoLists(l1.GetListHead(), l2.GetListHead());
    LC0083 run;
    ListNode* r = run.deleteDuplicates(l1.GetListHead());
    LinkedList::ShowLinkedList(r);

//    string s {"ABCDE"};
//    for(auto c:s) cout << c << ' ';
//    cout << endl;



    return 0;
}
