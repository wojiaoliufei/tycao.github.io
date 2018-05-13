整数反转：给定一个32bit的有符号整型，颠倒这个整型的数字顺序
================
LeetCode地址 :point_right: [Reverse Integer](https://leetcode.com/problems/reverse-integer/description/)<br>
思路很简单, `原数的个位 ==> 结果的最高位. 原数的最高位 ==> 结果的个位. ` <br>
我的代码如下：<br>

#### reverseinteger.h

```cpp
#pragma once

//    printf("sizeof(long) : %d\n", sizeof(long));   							output : 4
//    printf("sizeof(int) : %d\n", sizeof(int));									output : 4
// 		printf("sizeof(long long) : %d\n", sizeof(long long));			output : 8
// 我的机器上 int 和 long都是32bit， 因此这里需要使用long long类型来定义ret变量
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
```

#### main.cpp
```cpp
#include <climits>
#include <iostream>
#include "reverseinteger.h"

int main(int argc, char *argv[])
{
    Solution s;
    std::cout << s.reverse(-2147483648) << "\n";
    printf("sizeof(long) : %d\n", sizeof(long));
    printf("sizeof(int) : %d\n", sizeof(int));

    return 0;
}
```

* 特殊情况:
	* 后几位是0的情况(10, 100.)? 
		* 这个我们的循环已经考虑了, 如果原数的个位是0, res 则会一直保持是0, 直到非0的出现.
	* overflow的问题?
		* 检测很简单, 将 ret 设为 long long, 那你一个 int 怎么反转都不会超出 long long 的范围了吧? 然后判断 ret 和 INT_MAX INT_MIN的关系就可以了.


