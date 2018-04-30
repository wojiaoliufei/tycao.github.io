C++11 std::unique_lock��std::lock_guard���𼰶��߳�Ӧ��ʵ��
========
**ʱ�䣺** 2018-04-30<br />
��������һ���ڵĵ������ˡ�����������һ���ˡ���ʱ����ľ���ʱ����ĺÿ�~
**������** ���һֱ��д�̳߳أ�Ȼ��ͻ��lock_guard��unqiue_lock�����������Ʋ������Ի󡣽��Դ�ƪ�����Ƚϡ�
**********
### ǰ��
**std::unique_lock��std::lock_guard���ǰ�����ͷ�ļ� `mutex` ��ġ����Ƕ���ͨ����lock��unlock����һ�α��ķ�װ��ʵ���Զ�unlock�Ĺ��ܡ�** <br />
C++���̱߳����ͨ����Թ�������ݽ���д�������Է�ֹ���߳��ڶԹ������ݳ�Ա���ж�дʱ�����Դ�������³������δ�������Ϊ��ͨ�������������޸Ĺ������ݳ�Ա��ʱ����м���--mutex��
��ʹ������ʱ��ͨ�����ڶԹ������ݽ����޸�֮ǰ����lock��������д��֮���ٽ���unlock�������������������������� **lock֮�����뿪�����Ա��������ʱ����unlock������������** <br />
��������������sample��<br />
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
�������ֻʵ���˹ؼ��ļ�����������ʹ����C++11�������condition_variable������������Popup��Inert����������std::unique_lock���std::lock_guard�����ĵط�����: <br />
�ڵȴ��е��߳�����ڵȴ��ڼ���Ҫ����mutex��������`cond_.wait()`��һ�С����ڻ���֮���ֿ������½�����������std::lock_guardȴ���߱������Ĺ��ܡ�

��������еģ�<br />
```cpp
cond_.wait(lk, [this]{return !Empty();});  
```
���ܱȽ�������⣺<br />
```cpp
[this]{return !Empty();}
```
��C++11������Ĺ��ܣ�lambda���ʽ����һ�������������������ڱ�ʾ�����������lambda���ʽ����trueʱ����queue��Ϊ�գ���wait����������mutex����lambda���ʽ����falseʱ��wait���������mutexͬʱ�Ὣ��ǰ�߳�����������ȴ�״̬��
��������һ�ֶ�д�������ǲ�û������C++11������boost���ṩ�˶�Ӧ��ʵ�֡���д����Ҫ�ʺ����ڹ������ݸ���Ƶ�ʽϵͣ����Ƕ�ȡ��������Ƶ�ʽϸߵĳ��ϡ�
