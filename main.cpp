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

    Sort run;
    run.QuickSortRecursive(v, 0, v.size()-1);
//    LC0067 run;
//    cout << run.addBinary("11","1");
//    cout << endl;


//    string s {"ABCDE"};
//    for(auto c:s) cout << c << ' ';
//    cout << endl;

    for(auto i:v) cout << i << ' ';
    cout << endl;

    return 0;
}
