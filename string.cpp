//
// Created by steve on 2021-08-18.
//

#include "string.h"

bool LC0009::isPalindrome(int x) {
    if(x<0) return false;

    int f=x, b=0;
    while(x>0 && b<INT32_MAX/10) {
        b = b*10 + x%10;
        x/=10;
    }
    return f==b;
}