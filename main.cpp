#include "main.h"
using namespace std;

int main() {
    cout << "Hello, World!" << endl;

    vector<int> v{9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    for(auto i:v) cout << i << ' ';
    cout << endl;

//    Sort run;
//    run.quickSortIterative(v);
    LC0027 run;
    //vector<int> n{0,1,2,2,3,0,4,2}; // val=2
    //vector<int> n{3,2,2,3}; // val=3
    vector<int> n{1}; // val=1
    cout << run.removeElement(n, 1) << endl;
    for(auto i:n) cout << i << ' ';
    cout << endl;


//    string s {"ABCDE"};
//    for(auto c:s) cout << c << ' ';
//    cout << endl;

    for(auto i:v) cout << i << ' ';
    cout << endl;

    return 0;
}
