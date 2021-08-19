#include "main.h"
using namespace std;

int main() {
    cout << "Hello, World!" << endl;

    vector<int> v{9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    for(auto i:v) cout << i << ' ';
    cout << endl;

//    Sort run;
//    run.quickSortIterative(v);
    LC0026 run;
    vector<int> n{0,0,1,1,1,2,2,3,3,4};
    //vector<int> n{1,1,2};
    cout << run.removeDuplicates(n) << endl;
    for(auto i:n) cout << i << ' ';
    cout << endl;


//    string s {"ABCDE"};
//    for(auto c:s) cout << c << ' ';
//    cout << endl;

    for(auto i:v) cout << i << ' ';
    cout << endl;

    return 0;
}
