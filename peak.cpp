//
// Created by Mov on 6/2/2023.
//

#include <vector>
#include <deque>
#include <fstream>
#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

/* 可以根據cache size, page size來調整一次檔案讀出的量，後續都從cache讀資料會比一行行從檔案讀快許多 */
static const auto BUFFER_SIZE = 8*1024;

/* 起一個thread平行讀取資料並將char轉換成int */
void thread_read_data(ifstream &file, char *buf_char, int *buf_int, int &buf_int_size) {
    int in_size=0;
    if (file.is_open()) {
        int seek_back = 0;
        in_size = file.read(buf_char, BUFFER_SIZE).gcount();
        if(!in_size) return;
        if(!file.eof()) {
            /* 確保每次讀入buffer的末值是一個完整的數字 */
            while (buf_char[in_size] != '\n') {
                in_size--;
                seek_back--;
            }
        }
        buf_char[in_size] = '\0';
        file.seekg(seek_back+1, ios::cur);
    }

    int v=0;
    buf_int_size=0;
    for(int i=0; i<in_size; i++) {
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

vector<vector<int>> shortest_continuous_subseq(int target, string file_path) {

    /* 佔用stack以獲得連續空間取得較好存取性能 */
    char buf_char[BUFFER_SIZE];
    int  buf1_int [BUFFER_SIZE];
    int  buf1_int_size=0;
    int  buf2_int [BUFFER_SIZE];
    int  buf2_int_size=0;

    ifstream file_in (file_path, ios::in|ios::binary|ios::ate);
    if (file_in.is_open())
        file_in.seekg(0, ios::beg);

    std::thread thread;

    /* 第一批次抓取資料，後續從第二批次開始會隱藏在運算背後 */
    thread = std::thread(thread_read_data, std::ref(file_in), std::ref(buf_char), std::ref(buf1_int), std::ref(buf1_int_size));
    thread.join();

    vector<vector<int>> res;
    deque<int> dq;
    int n=0, buf_num=1, min_dist=INT_MAX, sum=0, dist=0;

    while(buf1_int_size || buf2_int_size) {
        int *buf= nullptr;
        if(buf1_int_size) {
            buf = buf1_int;
            n = buf1_int_size;
            buf_num=1;
            /* 開始運算前也起一個thread平行讀取下一批次資料 */
            thread = std::thread(thread_read_data, std::ref(file_in), std::ref(buf_char), std::ref(buf2_int), std::ref(buf2_int_size));
        } else {
            buf = buf2_int;
            n = buf2_int_size;
            buf_num=2;
            /* 開始運算前也起一個thread平行讀取下一批次資料 */
            thread = std::thread(thread_read_data, std::ref(file_in), std::ref(buf_char), std::ref(buf1_int), std::ref(buf1_int_size));
        }

        /* main thread開始處理上一批次讀取的資料
         * O(n) 用一deque當sliding window掃過一次序列 */
        for (int i = 0; i < n; i++) {
            int v = buf[i];
            sum += v;
            dist++;
            dq.push_back(v);
            while ((sum >= target) && dq.size()) {
                if (dist <= min_dist) {
                    if (dist < min_dist) {
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

        (buf_num == 1) ? buf1_int_size=0 : buf2_int_size=0;

        /* 確認另一讀取資料thread結束開始下一次sliding window迴圈 */
        thread.join();
    }

    file_in.close();
    return res;
}

int main(int argc, char *argv[]) {

    int target = 0;
    for(int i=0; std::isdigit(argv[1][i]); i++)
        target = target*10 + (argv[1][i] - '0');

    string file_path(argv[2]);

    auto begin = std::chrono::high_resolution_clock::now();
    vector<vector<int>> res=shortest_continuous_subseq(target, file_path);
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);

    for(auto re:res) {
        for (auto r: re)
            cout << r << ' ';
        cout << endl;
    }

    cout << "duration: " << elapsed.count() << " ns" << endl;

    return 0;
}