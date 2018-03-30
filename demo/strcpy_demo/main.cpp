#include <iostream>
#include <string>
#include <cstring>
#include <cassert>
using namespace std;

char* strcpy_s(char*, const char*);


int main(int argc, char *argv[])
{
   char* a;
   char* b = "abcdefgh";
    cout << strcpy_s(a, b) << endl;
    return 0;
}


char* strcpy_s(char* dst, const char* src) {
    // 判断参数不为空指针
    assert(dst != nullptr);
    assert(src != nullptr);

    char* strTmp = new char[strlen(src) + 1];
    char* pTmp = strTmp;    // 保存首地址

    // 把src的内容拷贝到临时指针变量里
    while ((*strTmp++ = *src++) != '\0');
    strTmp = pTmp;  // 恢复到起点

    char* pdst = dst;
    // 复制到目标字符串
    while ((*pdst++ = *pTmp++) != '\0');
    delete [] strTmp;
    return dst;
}
