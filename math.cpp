//
// Created by steve on 2021-08-11.
//

#include "math.h"

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