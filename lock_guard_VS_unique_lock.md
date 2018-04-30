C++11 std::unique_lock与std::lock_guard区别及多线程应用实例
========
**时间：** 2018-04-30<br />
今天是五一假期的第三天了。明天就是最后一天了。有时候真的觉得时间过的好快~<br />
**背景：** 最近一直在写线程池，然后就会对lock_guard和unqiue_lock这两个锁机制产生了迷惑。谨以此篇做个比较。
**********
### 前言
**std::unique_lock与std::lock_guard都是包含在头文件 `mutex` 里的。它们都是通过对lock和unlock进行一次简单的封装，实现自动unlock的功能。** <br />
C++多线程编程中通常会对共享的数据进行写保护，以防止多线程在对共享数据成员进行读写时造成资源争抢导致程序出现未定义的行为。通常的做法是在修改共享数据成员的时候进行加锁--mutex。
 **在使用锁的时候通常是在对共享数据进行修改之前进行lock操作，在写完之后再进行unlock操作。** 经常会出现由于疏忽导致 **lock之后在离开共享成员操作区域时忘记unlock，导致死锁。** <br />
下面我们来给个sample：<br />
### threadPool.h
```cpp
#pragma once
#include <mutex>                // for mutex
#include <condition_variable>   // for condition_variable
#include <queue>                // for queue<>

template <typename T>
class ThreadSafeQueue{
public:
         void Insert(T value);
         void Popup(T &value);
         bool Empty() const;
private:
       mutable std::mutex mut_;
       std::queue<T> que_;
       std::condition_variable cond_;
};
template <typename T>
void ThreadSafeQueue<T>::Insert(T value){
    std::lock_guard<std::mutex> lk(mut_);
    que_.push(value);
    cond_.notify_one();
}


template <typename T>
void ThreadSafeQueue<T>::Popup(T &value){
    std::unique_lock<std::mutex> lk(mut_);
    cond_.wait(lk, [this]{return !que_.empty();});
    value = que_.front();
    que_.pop();
}


template <typename T>
bool ThreadSafeQueue<T>::Empty() const{
        std::lock_guard<std::mutex> lk(mut_);
        return que_.empty();
}
```
### main.cpp
```cpp
#include "threadPool.h"

int main(int argc, char *argv[])
{
    ThreadSafeQueue<int> thrd;
    for (size_t i = 0; i != 10; ++i) {
        thrd.Insert(i);
    }
    for (size_t i = 0; i != 10; ++i) {
        int j;
        if (!thrd.Empty()) {
            thrd.Popup(j);
            printf("%d\n", j);
        }
    }

    return 0;
}
```
!["lock_guard"](https://github.com/tycao/tycao.github.io/blob/master/src/lock_guard.png "lock_guard")<br />
上面代码只实现了关键的几个函数，并使用了C++11新引入的condition_variable条件变量。从Popup与Inert两个函数看std::unique_lock相对std::lock_guard更灵活的地方在于: <br />
在等待中的线程如果在等待期间需要解锁mutex，阻塞在`cond_.wait()`那一行。并在唤醒之后又可以重新将其锁定。而std::lock_guard却不具备这样的功能。

上面代码中的：<br />
```cpp
cond_.wait(lk, [this]{return !Empty();});  
```
可能比较难以理解：<br />
```cpp
[this]{return !Empty();}
```
是C++11新引入的功能，lambda表达式，是一种匿名函数。方括号内表示捕获变量。当lambda表达式返回true时（即queue不为空），wait函数会锁定mutex。当lambda表达式返回false时，wait函数会解锁mutex同时会将当前线程置于阻塞或等待状态。
还存在另一种读写锁，但是并没有引入C++11，但是boost库提供了对应的实现。读写锁主要适合在于共享数据更新频率较低，但是读取共享数据频率较高的场合。

******************
### Reference:
["std::unique_lock<std::mutex> or std::lock_guard<std::mutex>":question:](https://stackoverflow.com/questions/20516773/stdunique-lockstdmutex-or-stdlock-guardstdmutex)<br />
