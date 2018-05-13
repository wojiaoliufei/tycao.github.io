#pragma once

typedef long long int64;

class Solution {
public:
    int reverse(int x) {
        int64 ret = 0;
        do {
            ret = ret * 10 + x % 10;
        } while (x /= 10);
        return (ret > INT_MAX || ret < INT_MIN) ? 0 : ret;
    }
};
