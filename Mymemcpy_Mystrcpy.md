定义自己的内存拷贝函数（以及字符串拷贝函数）
=======

### Talk is checp, show me the demo!好的，我们先上代码：
```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
#include <cassert>

using namespace std;

void* Mymemcpy(void* ,const void* ,size_t );
char* Mystrcpy(char*, const char*);


int main()
{
    // for Mymemcpy
    char str[]="0123456789";
    Mymemcpy(str+1,str+0,9);
    printf("%s\n",str);
    Mymemcpy(str,str+6,4);
    printf("%s\n",str);

    printf("%s\n","-----------------------------------------");

    // for Mystrcpy
    char* a = const_cast<char*>(string("1234567890").c_str());
    char* b = "abcdefgh";
    cout << Mystrcpy(a, b) << endl;
    cout << a << endl;

    return 0;
}

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


```


****
###总结：
无论是字符串拷贝，还是内存拷贝。其实思路都是一样的：
* [x] 首先要断言判断是否参数为空指针（以及size_t count是否小于0），若是，直接返回错误信息，或者抛出异常。
* [x] 定义两个临时指针变量，char* pdest, char* psrc 用来操作两个内存区域。（不要直接在两个入参上操作）
* [x] 在堆（也称为动态内存）内申请一块内存，用来临时存放src所指内存的内容。然后在把这个临时内存的内容拷贝到dest所指的内存中。这样做是为了方式两块内存存在重叠区域。
* [x] 最后不要忘记，将申请的动态内存手动释放。防止内存泄露。

以上！