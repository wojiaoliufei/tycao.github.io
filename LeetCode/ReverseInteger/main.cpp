#include <climits>
#include <iostream>
#include "reverseinteger.h"

int main(int argc, char *argv[])
{
    Solution s;
    std::cout << s.reverse(-2147483648) << "\n";

    // 我的机器上 int 和 long都只占32bit， long long占用64bit。
    printf("sizeof(long) : %d\n", sizeof(long));
    printf("sizeof(long long) : %d\n", sizeof(long long));
    printf("sizeof(int) : %d\n", sizeof(int));

    return 0;
}
