//
// Created by steve on 2021-08-11.
//

#include "math.h"

//LC0171 run;
//string s = "A";
//cout << run.titleToNumber(s) << endl;
int LC0171::titleToNumber(string columnTitle) {
    // 这题实际上相当于一种二十六进制转十进制的问题
    int n = columnTitle.size();
    double m = 1;
    double r = 0;

    while(n > 0) {
        r += (columnTitle[n-1]-'A'+1) * m;
        n--;
        m *= 26;
    }
    return static_cast<int> (r);
}

//LC0007 run;
//cout << run.reverse(-2147483648) << endl;
int LC0007::reverse(int x) {
    int ans{0}, max{INT32_MAX/10}, min{INT32_MIN/10};
    while(x) {
        if( ans>max || ans<min ) return 0;
        ans = ans*10 + x%10;
        x/=10;
    }
    return ans;
}