#include <cstdio>
#include <cassert>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

// 内存拷贝
// -----在堆（动态内存）里申请内存，临时存放src的内容，然后再拷贝到dest所指的内存区域中
void* Mymemcpy(void* ,const void* ,size_t );
// ------在栈里申请内存，临时存放src的内容，然后再拷贝到dest所指的内存区域中
void * Mymemcpy02(void*, const void*, size_t);


// 字符串拷贝
// -----在堆（动态内存）里申请内存，临时存放src的内容，然后再拷贝到dest所指的内存区域中
char* Mystrcpy(char*, const char*);
// ------在栈里申请内存，临时存放src的内容，然后再拷贝到dest所指的内存区域中
char* Mystrcpy02(char*, const char*);

int main(int argc, char *argv[])
{
    // for Mymemcpy
    char str[]="0123456789";
    printf("char str[] = %s\n", str);
    Mymemcpy(str+1,str+0,9);
    printf("Mymemcpy(str+1,str+0,9) :\nstr = %s\n",str);
    Mymemcpy(str,str+6,4);
    printf("Mymemcpy(str,str+6,4) :\nstr = %s\n",str);

    printf("%s\n", "--------------------------");

    // for Mymemcpy02
    char* c = const_cast<char*>(string("").c_str());
    const char* d = "1234567890";
    printf("Mymemcpy02(c, d) : %s\n", Mymemcpy02(c, d, 11));
    printf("c = %s\n", c);
    printf("d = %s\n", d);

    printf("%s\n", "----------------------------");

    // for Mymemcpy02
    char strr[]="0123456789";
    Mymemcpy02(strr+1,strr+0,9);
    printf("%s\n",strr);
    Mymemcpy02(strr,strr+6,4);
    printf("%s\n",strr);

    printf("%s\n","-----------------------------------------");

    // for Mystrcpy
    char* a = const_cast<char*>(string("12").c_str());
    const char* b = "abcdefgh";
    printf("Mystrcpy(a, b) : %s\n", Mystrcpy(a, b));
    printf("a = %s\n", a);
    printf("b = %s\n", b);

    printf("%s\n", "----------------------------");

    // for Mystrcpy02
    char* aa = const_cast<char*>(string("").c_str());
    const char* bb = "abcdefghi";
    printf("Mystrcpy02(aa, bb) : %s\n", Mystrcpy02(aa, bb));
    printf("aa = %s\n", aa);
    printf("bb = %s\n", bb);

    return 0;
}

// 内存拷贝
// -----在堆（动态内存）里申请内存，临时存放src的内容，然后再拷贝到dest所指的内存区域中
char* Mystrcpy(char* dst, const char* src) {
    // 判断参数不为空指针
    assert(dst != nullptr);
    assert(src != nullptr);
    char* pdst = dst;
    const char* psrc = src;

    char* strTmp = new char[strlen(src) + 1];
    char* pTmp = strTmp;    // 保存首地址

    // 把src的内容拷贝到临时指针变量里
    while ((*strTmp++ = *psrc++) != '\0');
    strTmp = pTmp;  // 恢复到起点

    // 复制到目标字符串
    while ((*pdst++ = *strTmp++) != '\0');
    delete [] pTmp;
    return dst;
}

char* Mystrcpy02(char* dest, const char* src) {
    // 预编译期间 断言两个入参不为0
    assert(dest != nullptr && src != nullptr);
    char* pdest = dest;
    const char* psrc = src;

    char strTmp[strlen(src) + 1] = {0,};
    char* pTmp = strTmp;
    char* ppTmp = pTmp;
    while ((*pTmp++ = *psrc++) != '\0') ;

    while ((*pdest++ = *ppTmp++) != '\0') ;

    return dest;
}


// 字符串拷贝
// -----在堆（动态内存）里申请内存，临时存放src的内容，然后再拷贝到dest所指的内存区域中
void* Mymemcpy(void* dest,const void* src,size_t count)
{
      assert(dest != nullptr && src != nullptr && count > 0);
      char* pdest=static_cast<char*>(dest);//安全转换
      const char* psrc=static_cast<const char*>(src);

      int countTmp = count;
      char* strTmp = new char[strlen(psrc) + 1];
      char* pTmp = strTmp;  // 保存首地址
       while (count--)
           *strTmp++ = *psrc++;
       strTmp = pTmp;
       while (countTmp--)
           *pdest++ = *strTmp++;
       delete [] pTmp;
}

// ------在栈里申请内存，临时存放src的内容，然后再拷贝到dest所指的内存区域中
void * Mymemcpy02(void* dest, const void* src, size_t count) {
    assert(dest != nullptr && src != nullptr && count > 0);

    char* pdest = static_cast<char*>(dest); // 安全转换
    const char* psrc = static_cast<const char*>(src);

    int countTmp = count;

    char strTmp[count] = {0,};
    char* pTmp = strTmp;
    char* ppTmp = pTmp;

    while (count--)
        *pTmp++ = *psrc++;
    while (countTmp--)
        *pdest++ = *ppTmp++;
}



