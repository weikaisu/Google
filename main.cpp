#include "main.h"
using namespace std;

int main() {
    cout << "Hello, World!" << endl;

    vector<int> v{9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    for(auto i:v) cout << i << ' ';
    cout << endl;

    Sort run;
    run.quickSortIterative(v);
//    LC0784 run;
//    vector<string> ans=run.letterCasePermutation("a1b2");
//    for(auto a:ans) cout << a << endl;
//    cout << run.letterCasePermutation("a1b2") << endl;

    for(auto i:v) cout << i << ' ';
    cout << endl;

    return 0;
}
