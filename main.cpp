#include "main.h"
#include "play.cpp"
using namespace std;

#include <fstream>
#include <thread>
static const auto BUFFER_SIZE = 8*1024;

void read_data(ifstream file, char *buf_char, int *buf_int, int buf_int_size) {
    if (file.is_open()) {
        int seek_back = 0;
        int in_size = file.read(buf_char, BUFFER_SIZE).gcount();
        while(buf_char[in_size]!='\n') {
            in_size--;
            seek_back--;
        }
        buf_char[in_size] = '\0';
        file.seekg(seek_back, ios::cur);
    }

    int v=0;
    buf_int_size=0;
    for(int i=0; buf_char[i]!='\0'; i++) {
        char c = buf_char[i];
        if(!std::isdigit(c) && c!='\n')
            continue;
        if (c=='\n') {
            buf_int[buf_int_size++]=v;
            v=0;
        } else {
            v = v * 10 + (c - '0');
        }
    }
    buf_int[buf_int_size++]=v;
}


vector<vector<int>> sw(string s, int target) {

    // 佔用stack以獲得連續空間取得較好存取性能
    char buf_char[BUFFER_SIZE+1];
    int  buf_int [BUFFER_SIZE];
    int  buf_int_size=0;

    ifstream file_in ("test.txt", ios::in|ios::binary|ios::ate);
    if (file_in.is_open()) {
        file_in.seekg(0, ios::beg);
//        int in_size = file_in.read(buf1, BUFFER_SIZE).gcount();
//        buf1[in_size] = '\0';
    }

    thread mThread( read_data, std::ref(file_in), std::ref(buf_char), std::ref(buf_int), std::ref(buf_int_size) );
    mThread.join();

//    vector<int> nums;
    vector<vector<int>> res;
    int n=buf_int_size, min_dist=INT_MAX, sum=0, dist=0;
    deque<int> dq;

    for(int i=0; i<n; i++) {
        int v = buf_int[i];
        sum += v;
        dist++;
        dq.push_back(v);
        while((sum >= target) && dq.size()) {
            if(dist <= min_dist) {
                if(dist < min_dist) {
                    min_dist = dist;
                    res.clear();
                }
                res.push_back({dq.begin(), dq.end()});
            }
            sum -= dq.front();
            dq.pop_front();
            dist--;
        }
    }

    file_in.close();
    return res;
}

int main() {
    cout << "Hello, World!" << endl;
//    vector<int> v{3,1,7,11};
//    vector<int> {3, 17, 42, 1, 26, 8, 0, 63};
    string s{"3\n17\n42\n1\n26\n8\n0\n63"};
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
//    LC0083 run;
//    ListNode* r = run.deleteDuplicates(l1.GetListHead());
//    LinkedList::ShowLinkedList(r);

//    LC1346 run;
//    run.checkIfExist(v);
    vector<vector<int>> res = sw(s, 80);
    for(auto re:res) {
        for (auto r: re)
            cout << r << ' ';
        cout << endl;
    }

//    string s {"ABCDE"};
//    for(auto c:s) cout << c << ' ';
//    cout << endl;

    return 0;
}
