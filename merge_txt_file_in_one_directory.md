将指定个目录下的所有`.txt`文件合并在同目录下的一个.txt文件内（本代码直接创建一个merge.txt文件，并将所有.txt文件内容合并在此文件内）
==============
#### 时间: 2018-04-06
#### 背景：清明节假期没有回家，然后就很无聊。翻看朋友圈看见大学程序老师用Java实现了此功能，并截图发在了朋友圈。我之前用C++处理文件相关的程序也写了不少，另外`C++ Primer 5th.`也在`第九章Page390`和`第八章Page290`详细的给出了好几个关于文本处理的经典例子。这让我很想实现一个同样功能的C++版本。当时就想应该逻辑上不难。就是处理字符串和文件。

Talk is cheap, show me the code! 好，我们先上代码：
### merge_txt.h
```cpp
#pragma once
#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <io.h>
using namespace std;
class MergeTxt{
public:
    MergeTxt(const string& path) : filepath(path) {  }
    ~MergeTxt() {}
    void merge();
    void listFiles(const char*);
private:
    const string filepath;
    std::vector<string> strVec; // store all file names in the dir
    ofstream out;
    ifstream in;
};
inline void MergeTxt::merge() {
    listFiles(filepath.c_str());
    out.open(filepath.substr(0, filepath.find_first_of("\\") + 1) + "merge.txt");
    if (!out)
        cout << "out not open!!!\n";
    for (auto& f : strVec) {
        if (f.find(".txt") == string::npos) // only file names in ".txt" format can be handled
            continue;
        string ff = filepath.substr(0, filepath.find_first_of("\\") + 1) + f;
        string line;
        in.open(ff);
        if (!in.is_open())
            continue;
        else {
            out << "-----------------------" << ff << "-------------------\n";
            while (getline(in, line)) {
                out << line << "\n";
            }
            in.close(); // close file handle, and will open next file
        }
    }
}
inline void MergeTxt::listFiles(const char * dir) {
    intptr_t handle;
    _finddata_t findData;

    handle = _findfirst(dir, &findData);    // 查找目录中的第一个文件
    if (handle == -1) {
        cout << "Failed to find first file!\n";
        return;
    }
    do {
        if (findData.attrib & _A_SUBDIR
            && strcmp(findData.name, ".") == 0
            && strcmp(findData.name, "..") == 0
            )    // 是否是子目录并且不为"."或".."
            cout << findData.name << "\t<dir>\n";
        else
            //cout << findData.name << "\t" << findData.size << endl;
            strVec.push_back(findData.name);
    } while (_findnext(handle, &findData) == 0);    // 查找目录中的下一个文件
    cout << "Done!\n";
    _findclose(handle);    // 关闭搜索句柄
}
```

### main.cpp
```cpp
#include "merger_txt.h"

int main()
{
    MergeTxt m("d:\\*.*");
    m.merge();

    return 0;
}
```

### 程序运行后的截图：<br />
!["result"](https://github.com/tycao/tycao.github.io/blob/master/merge_txt_src/result.png "result")<br />

### 这是代码截图：<br />
!["code"](https://github.com/tycao/tycao.github.io/blob/master/merge_txt_src/merge_done2.png "code")<br />

#### PS : 该程序会在同一路径下生成`merge.txt`的文件，该目录下的所有其他的`.txt`文件的内容全部都合并在了此新生成的文件内了。

### 总结：
本来也是觉得这是一个很简单的功能，可是在代码实现的过程中，竟然也踩坑了！**那就是文件的路径问题。一开始一直就是没有`merge.txt`生成，这个问题好办，那肯定是ofstream out在执行out.open(filename)时失败了。** 这个问题解决后，新的问题出现：**`merge.txt`文件里一直没有任何合并之后的内容。**
程序运行也没有报错。当我debug到该行的时候：`while (getline(in, line))`， 这一行直接跳过，没有去执行。后来我加了判断：`if (!in.is_open()) cout << "file not opened!\n"`，这个时候才发现原来是文件流ifstream没有打开文件！找到问题原因后（因为没报错，找了一会的时间），就在找为什么没打开文件。然后才发现原来是 **没有在该文件名的前面加上绝对路径！** 当在文件名前面拼接上绝对路径后，一切都正常了。


*****


### 更新 ----2018-04-06 21:17
#### 上面的代码是在某一个指定目录下（ **当前目录的下一级，而不是下一级目录下的下一级** ）的所有txt文件的合并。
接下来增加功能： __**对当前目录中的所有的txt文件进行合并在一个txt文件内。**__ 按照惯例，我们先奉上代码：
### merge_txt.h
```cpp
#pragma once
#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <cstring>  // for strcat
#include <io.h>     // for class _finddata_t
#include <windows.h>    // for Sleep()
using namespace std;
class MergeTxt{
public:
    MergeTxt(const string& path) : filepath(path) {  }
    ~MergeTxt() {}
    void merge();
    void listFiles(const char*);
    void listAllFiles(const char*);
private:
    const string filepath;
    std::vector<string> strVec; // store all file names in the dir
    ofstream out;
    ifstream in;
};
inline void MergeTxt::merge() {
    listAllFiles(filepath.c_str());
    //out.open(filepath.substr(0, filepath.find_first_of("\\") + 1) + "merge.txt");
    out.open(filepath + "\\merge.txt");
    if (!out) {
        cout << "out not open!!!\n";
        return;
    }
    for (auto& f : strVec) {
        if (f.find(".txt") == string::npos) // only file names in ".txt" format can be handled
            continue;
        //string ff = filepath.substr(0, filepath.find_first_of("\\") + 1) + f;
        string line;
        in.open(f);
        if (!in.is_open())
            continue;
        else {
            out << "-----------------------" << f << "-------------------\n";
            while (getline(in, line)) {
                out << line << "\n";
            }
            in.close(); // close file handle, and will open next file
        }
    }
}
inline void MergeTxt::listFiles(const char * dir) {
    char dirNew[20000] = "";
    strcpy(dirNew, dir);
    strcat(dirNew, "\\*.*");
    intptr_t handle;
    _finddata_t findData;

    handle = _findfirst(dirNew, &findData);    // 查找目录中的第一个文件
    if (handle == -1) {
        cout << "Failed to find first file!\n";
        return;
    }
    do {
        if (findData.attrib & _A_SUBDIR
            || strcmp(findData.name, ".") == 0
            || strcmp(findData.name, "..") == 0
            )    // 是否是子目录并且不为"."或".."
            cout << string(dir) + "\\" + findData.name << "\t<dir>\n";
        else {
            cout << string(dir) + "\\" + findData.name << "\t" << findData.size << endl;
            strVec.push_back(string(dir) + "\\" + findData.name);
        }
    } while (_findnext(handle, &findData) == 0);    // 查找目录中的下一个文件
    cout << "Done!\n";
    _findclose(handle);    // 关闭搜索句柄
}


inline void MergeTxt::listAllFiles(const char * dir) {
    //Sleep(3000);
    char dirNew[20000] = "";
    strcpy(dirNew, dir);
    strcat(dirNew, "\\*.*");
    intptr_t handle;
    _finddata_t findData;

    handle = _findfirst(dirNew, &findData);    // 查找目录中的第一个文件
    if (handle == -1) {
        cout << "Failed to find first file!\n";
        return;
    }
    do {
        if (findData.attrib & _A_SUBDIR) {   // 是否是子目录并且不为"."或".."
            if (strcmp(findData.name, ".") == 0 || strcmp(findData.name, "..") == 0)
                continue;   // 子目录下，忽略"."或".."
            cout << string(dir) + "\\" + findData.name << "\t<dir>\n";
            memset(dirNew, '\0', sizeof(dirNew));
            strcpy(dirNew, dir);
            strcat(dirNew, "\\");
            strcat(dirNew, findData.name);

            listAllFiles(dirNew);
        }
        else {
            cout << string(dir) + "\\" + findData.name << "\t" << findData.size << endl;
            strVec.push_back(string(dir) + "\\" + findData.name);
        }
    } while (_findnext(handle, &findData) == 0);    // 查找目录中的下一个文件
    cout << "Done!\n";
    _findclose(handle);    // 关闭搜索句柄

}
```

### main.cpp
```cpp
#include "merger_txt.h"

int main()
{
    MergeTxt m("D:\\Git_Dir");
    m.merge();

    return 0;
}
```

* 通过跟上一个版本对比可知：
	* 我们增加了`void MergeTxt::listAllFiles(const char *)`成员函数。它的作用是**遍历当前目录中以及所有下一级的下一级的所有txt文件，然后将这些txt文件合并在一个`merge.txt`文件里。**
	* 整个编码过程中，唯一的难点就是在拼接`txt文本文件的绝对路径`。希望大家不要搞错路径，否则程序运行之后等不到我们预期的效果。

### 运行程序之前的目录截图：<br />
!["path"](https://github.com/tycao/tycao.github.io/blob/master/merge_txt_src/path.png "path")<br />
	
### 程序运行之后的截图：<br />
!["path2"](https://github.com/tycao/tycao.github.io/blob/master/merge_txt_src/path2.png "path2")<br />
!["result2"](https://github.com/tycao/tycao.github.io/blob/master/merge_txt_src/result2.png "result2")<br />

以及`D:\Git_Dir\` **目录中的** 所有txt文件，经过合并后生成的`merge.txt`内容：<br />
!["merge_result"](https://github.com/tycao/tycao.github.io/blob/master/merge_txt_src/merge_result.png "merge_result")<br />





