#include "main.h"
using namespace std;

int main() {
    cout << "Hello, World!" << endl;

    vector<int> v{9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    for(auto i:v) cout << i << ' ';
    cout << endl;

//    Sort run;
//    run.quickSortIterative(v);
    LC0009 run;
    cout << run.isPalindrome(1000000001) << endl;

    for(auto i:v) cout << i << ' ';
    cout << endl;

    return 0;
}
