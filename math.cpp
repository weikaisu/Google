
#include "math.h"

//LC0171 run;
//string s = "A";
//cout << run.titleToNumber(s) << endl;
int LC0171::titleToNumber(string columnTitle) {
    // 这题实际上相当于一种二十六进制转十进制的问题
    // 26 -> 10
    // 其他進位轉十進位：將二進位數、十六進位數的各位數字分別乘以各自基數的(N-1)次方，其相加之和便是相應的十進位數，這是按權相加法。
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

string LC0168::convertToTitle(int columnNumber) {
    // 这题实际上相当于一种十进制转二十六进制的问题
    // 10 -> 26
    // 整數部分用除基取余法，小數部分用乘基取整法，然後將整數與小數部分拼接成一個數作為轉換的最後結果
    // 先让n自减1，变成25，然后再对26取余，得到25，此时再加上字符A，就可以得到字符Z了。叼就叼在这对其他的不能整除26的数也是成立的，完美解决问题
    string res {};
    int n = columnNumber;
    while(n) {
        res += --n % 26 + 'A';
        n/=26;
    }
    return string(res.rbegin(), res.rend());

    // recursive way 結果是錯的，得先計算n%26再計算n/26%, 遞歸的話會顛倒！
//    int n = columnNumber;
//    //return n ? convertToTitle(n/26) + (char)(--n % 26 + 'A') : "";
//    string res {};
//    if(n) {
//        string l = convertToTitle(n/26);
//        string r = string(1, char(--n % 26 + 'A'));
//        res = l + r;
//    } else {
//        res = "";
//    }
//    return res;
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