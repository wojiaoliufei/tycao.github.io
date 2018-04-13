C++实现 使用指定字符/子字符串 分割字符串
========
* 首先，我们可以先实现： `使用C++替换所有指定的字符串`
### C++实现 替换所有指定的字符串
参考链接：[C++中替换所有指定的子串](https://blog.csdn.net/K346K346/article/details/47951857)<br />

```cpp
/** 
 * 替换指定的子串
 * src		:	原字符串
 * target	:	待被替换的子串
 * subs		:	替换的子串
 */
string replaceALL(const char* src, const string& target,const string& subs) 
{
    string tmp(src);
    string::size_type pos =tmp.find(target),targetSize =target.size(),resSize =subs.size();  
    while(pos!=string::npos)//found  
    {  
        tmp.replace(pos,targetSize,subs);   
        pos =tmp.find(target, pos + resSize);   
    }  
    return tmp;
}
```
#### 这个函数看起来没什么作用，但是配合接下来的一个函数就会很好用了。 :smile: :blush:
* 接着我们了解下： C++实现 使用指定字符分割字符串
### 使用C标准库中的strtok函数
strtok函数原型： <br />
```cpp
char* strtok(char* str, const char* delim);
```
例子：
```cpp
#include <cstdio>	// for printf
#include <cstring>	// for strtok
using namespace std;

int main() {
	char s[] = "Golden Global     	View, disk *desk";
	const char* d = " ,*";	// 分隔符包含 ' '（空格）    ','（逗号）    '*'（※号）
	char* p = 0;
	p = strtok(s, d);
	while (p) {
		printf("%s\n", p);
		p = strtok(nullptr, d);
	}
	return 0;
}
```
### 利用以上两个函数，我们可以用C++实现：`用指定的子字符串，分割字符串`
* 首先，利用`replaceAll()` 替换函数，用某一个字符，假设`s`来替换所有子字符串，然后再通过`strtok`函数，用字符`s`来分割字符串。
### 最后，给上本次的demo:
```cpp
#include <cstdio>
#include <cstring>
#include <string>
using namespace std;

string replaceALL(const char*, const string&,const string&);

int main() {
    char s[] = "     Golden     Global          , View, disk *desk";
    const char* d = " ,*";	// 分隔符包含 ' '（空格）    ','（逗号）    '*'（※号）
    char* p = 0;
    p = strtok(s, d);
    while (p) {
        printf("%s\n", p);
        p = strtok(nullptr, d);
    }
    printf("----------------------------\n");
    string str("this is a demo for testing... and also for demostration....");
    string tmp = replaceALL(str.c_str(), "for", "/");
    printf("%s\n", tmp.c_str());
    char* t = strtok(const_cast<char*>(tmp.c_str()), " /");
    while (t) {
        printf("%s\n", t);
        t = strtok(nullptr, " /");
    }
    return 0;
}


string replaceALL(const char* src, const string& target,const string& subs)
{
    string tmp(src);
    string::size_type pos =tmp.find(target),targetSize =target.size(),resSize =subs.size();
    while(pos!=string::npos)//found
    {
        tmp.replace(pos,targetSize,subs);
        pos =tmp.find(target, pos + resSize);
    }
    return tmp;
}

```
!["strtok"](https://github.com/tycao/tycao.github.io/blob/master/src/strtok.png "strtok")<br />
