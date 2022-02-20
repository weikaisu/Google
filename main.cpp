#include "main.h"
#include "play.cpp"
using namespace std;

int main() {
    cout << "Hello, World!" << endl;

    vector<int> v{9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    for(auto i:v) cout << i << ' ';
    cout << endl;

//    Play play;
//    play.Iterative(v);

//    Sort run;
//    run.HeapSort(v);
//    LC0067 run;
//    cout << run.addBinary("11","1");
//    cout << endl;

    TreeNode *root;
    root->BuildTree(root);
    LC110 run;
    cout << run.isBalanced(root) << endl;
    root->CleanTree(root);



//    string s {"ABCDE"};
//    for(auto c:s) cout << c << ' ';
//    cout << endl;

    for(auto i:v) cout << i << ' ';
    cout << endl;

    return 0;
}
