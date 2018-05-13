������ת������һ��32bit���з������ͣ��ߵ�������͵�����˳��
================
LeetCode��ַ :point_right: [Reverse Integer](https://leetcode.com/problems/reverse-integer/description/)<br>
˼·�ܼ�, `ԭ���ĸ�λ ==> ��������λ. ԭ�������λ ==> ����ĸ�λ. ` <br>
�ҵĴ������£�<br>

#### reverseinteger.h

```cpp
#pragma once

//    printf("sizeof(long) : %d\n", sizeof(long));   							output : 4
//    printf("sizeof(int) : %d\n", sizeof(int));									output : 4
// 		printf("sizeof(long long) : %d\n", sizeof(long long));			output : 8
// �ҵĻ����� int �� long����32bit�� ���������Ҫʹ��long long����������ret����
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

* �������:
	* ��λ��0�����(10, 100.)? 
		* ������ǵ�ѭ���Ѿ�������, ���ԭ���ĸ�λ��0, res ���һֱ������0, ֱ����0�ĳ���.
	* overflow������?
		* ���ܼ�, �� ret ��Ϊ long long, ����һ�� int ��ô��ת�����ᳬ�� long long �ķ�Χ�˰�? Ȼ���ж� ret �� INT_MAX INT_MIN�Ĺ�ϵ�Ϳ�����.


