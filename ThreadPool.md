使用C++写线程池
=========
### 背景：
多线程编程是C++开发者的一个基本功，但是很多开发者都是直接使用公司封装好的线程库，并没有去了解具体实现。而有些线程库的实现也是因为高度优化，而写的很难懂，让初学者看的很吃力。
本文将以简单的方式讲讲实现原理，从而能够让学习多线程编程的C++初学者能够看懂。
### C++编写线程池的原理：
_**在线程池中先创建若干数量的线程，并让这些线程一直不断地从线程池中的任务列表中取任务，然后执行（线程从任务池中取任务的过程中，是需要实行同步锁机制的）。当任务池中没有任务之后，所有的线程都会处于`wait状态`（又称为`睡眠状态`）。**_
之后，会将所有的线程销毁掉。销毁之前，需要将`处于睡眠状态的所有线程` **唤醒**，即发出同步信号唤醒所有睡眠（不干活的）线程，然后才能销毁。<br />
:question: 可能你也许会问：为什么要搞得这么麻烦，如果每当客户端有新的请求时，我就创建一个新的线程不就完了？这也许是个不错的方法，因为它能使得你编写代码相对容易一些，但你却忽略了一个重要的问题—— **性能**。
如果为每个客户端请求创建一个新线程的话，那耗费的CPU时间和内存将是惊人的，如果采用一个拥有200个线程的线程池，那将会节约大量的的系统资源，使得更多的CPU时间和内存用来处理实际的商业应用，而不是频繁的线程创建与销毁。
 
### C++线程池
**Talk is cheap, show me the demo!** 好，现在我们先奉上如何创建线程池的代码：
#### thread.h
```cpp
#pragma once

#include <vector>
#include <string>
#include <pthread.h>    // for class pthread_t
#include <windows.h>    // for Sleep(millionseconds)
using namespace std;

/**
 * 执行任务的类 ：设置任务数据并执行
*/
class CTask {
public:
    CTask() {}  /** 默认构造函数 */
    CTask(string taskName) : m_strTaskName(taskName){ } /** 带有一个参数的构造函数 */
    virtual int Run() = 0;  /** 纯虚函数 : 说明该类是一个抽象基类（不能直接初始化）*/
    void SetData(void*);   /** 设置任务数据 */
    ~CTask() {}

protected:
    string m_strTaskName;   /** 任务的名称 */
    void* m_ptrData = nullptr;  /** 要执行的任务的具体数据*/
};

/**
 * 线程池管理类
*/
class CThreadPool {
private:
    static          vector<CTask*> m_vecTaskList;    /** 任务列表 （任务池）*/
    static          bool shutdown;      /** 线程退出标志*/
    int             m_iThreadNum = 0;       /** 线程池中启动的线程数 */
    pthread_t*      pthread_id;

    static pthread_mutex_t m_pthreadMutex;  /** 线程同步锁 */
    static pthread_cond_t m_pthreadCond;    /** 线程同步的条件变量 */
protected:
    static void* ThreadFunc(void*);     /** 新线程的线程回调函数 */
    static int MoveToIdle(pthread_t);       /** 线程执行结束后，把自己放入空闲线程中 */
    static int MoveToBusy(pthread_t);       /** 移入到忙碌线程中去 */

    int Create();       /** 在线程池中创建线程 */
public:
    CThreadPool(int threadNum = 10);    /** 默认在线程池中创建10个线程 : 每个线程都在循环地（不停地）从任务列表中取出任务，然后直行任务 */
    int AddTask(CTask*);    /** 把任务添加到任务队列中 */
    int StopAll();      /** 使线程池中的线程退出 */
    int GetTaskSize();  /** 获取当前任务列表中的任务数量 */
};

```

#### thread.cpp
```cpp
#include <cstdio>   // for printf
#include "thread.h"


void CTask::SetData(void* data) {
    m_ptrData = data;
}

// static成员变量必须在类外初始化。（并且类外不能加上static）
vector<CTask*> CThreadPool::m_vecTaskList;         //任务列表
bool CThreadPool::shutdown = false;

pthread_mutex_t CThreadPool::m_pthreadMutex = PTHREAD_MUTEX_INITIALIZER;  /** 线程同步锁 */
pthread_cond_t CThreadPool::m_pthreadCond = PTHREAD_COND_INITIALIZER;    /** 线程同步的条件变量 */

// 线程池构造函数 ： 创建（固定数量的）线程
CThreadPool::CThreadPool(int threadNum) {
    this->m_iThreadNum = threadNum;
    printf("I will create %d threads.\n", threadNum);
    Create();
}

// 创建线程池中的线程
int CThreadPool::Create() {
    this->pthread_id  = static_cast<pthread_t*>(malloc(sizeof(pthread_t) * m_iThreadNum));
    for (int i = 0; i != m_iThreadNum; ++i)
        pthread_create(&pthread_id[i], nullptr, ThreadFunc, nullptr);
    return 0;
}
// 线程回调函数
void* CThreadPool::ThreadFunc(void* threadData) {
    pthread_t tid = pthread_self(); // 获取当前线程的线程id
    while (true) {
        pthread_mutex_lock(&m_pthreadMutex);    /** 锁住线程同步锁 */

        /** 若任务池里的所有任务全部都处理完成了（即线程池中的任务池没有任何任务了）, 则线程处于睡眠状态*/
        while (m_vecTaskList.size() == 0 && !shutdown) {
            pthread_cond_wait(&m_pthreadCond, &m_pthreadMutex);
        }

        if (shutdown) {
            pthread_mutex_unlock(&m_pthreadMutex);
            printf("thread %lu will exit\n", tid);
            pthread_exit(nullptr);
        }

        printf("tid %lu run\n", tid);

        /** 取出一个任务，并处理之*/
        vector<CTask*>::iterator iter = m_vecTaskList.begin();
        CTask* task = nullptr;
        if (iter != m_vecTaskList.end()) {
            task = *iter;
            m_vecTaskList.erase(iter);
        }
        pthread_mutex_unlock(&m_pthreadMutex);  /** 解锁线程同步锁 */

        task->Run();    /** 执行任务 */
        printf("tid : %lu idle\n", tid);
    }
    return 0;
}

// 往任务列表里面添加任务，并发出同步线程同步信号
int CThreadPool::AddTask(CTask* task) {
    pthread_mutex_lock(&m_pthreadMutex);
    this->m_vecTaskList.push_back(task);
    pthread_mutex_unlock(&m_pthreadMutex);
    pthread_cond_signal(&m_pthreadCond);
    return 0;
}

// 停止所有线程
int CThreadPool::StopAll() {
    /** 避免重复调用 */
    if (shutdown)
        return -1;
    printf("Now i will end all threads!\n");
    /** 唤醒所有（处于pthread_cond_wait状态的）线程， 线程池要销毁了 */
    shutdown = true;
    pthread_cond_broadcast(&m_pthreadCond);

    /** 阻塞等待线程退出， 否则就成僵尸了 */
    for (int i = 0; i != m_iThreadNum; ++i)
        pthread_join(pthread_id[i], nullptr);

    free(pthread_id);
    pthread_id = nullptr;

    /** 销毁条件变量 和 互斥体 */
    pthread_cond_destroy(&m_pthreadCond);
    pthread_mutex_destroy(&m_pthreadMutex);

    return 0;
}

/**
 * 获取当前队列中任务数
 */
int CThreadPool::GetTaskSize()
{
    return m_vecTaskList.size();
}

```

#### main.cpp
```cpp
#include <iostream>
#include "thread.h"

class CMyTask : public CTask {
public:
    CMyTask(){}     /** constructor */
    int Run() {
        printf("%s\n", static_cast<char*>(this->m_ptrData));
        Sleep(5000);
        return 0;
    }
};


int main() {
    /** 创建任务对象，之后塞入CThreadPool::m_vecTaskList里 */
    CMyTask taskObj;

    char szTmp[] = "this is the first thread running!";
    taskObj.SetData(static_cast<void*>(szTmp));

    /** 创建线程池，包含10个线程 */
    CThreadPool threadPool;

    /** 将20个任务放进线程池中的任务池（任务列表）中 */
    for (int i = 0; i != 20; ++i)
        threadPool.AddTask(&taskObj);

    while (1) {
        printf("there are still %d tasks need to be handled.\n", threadPool.GetTaskSize());
        if (threadPool.GetTaskSize() == 0) { // 当任务池中没有任何任务之后，所有线程都会处于pthread_cond_wait状态，即“睡眠状态”
            if (threadPool.StopAll() == -1) {   // 当执行StopAll()之后，所有的线程都会（从睡眠状态）被唤醒，然后被销毁
                printf("Now i will exit from main.\n");
                exit(0);
            }
        }
        Sleep(2000);
    }
    return 0;
}
```

### 程序运行后的截图：
!["C++实现线程池"](https://github.com/tycao/tycao.github.io/blob/master/thread_pool/result02.png "C++实现线程池")<br />
!["C++实现线程池2"](https://github.com/tycao/tycao.github.io/blob/master/thread_pool/result01.png "C++实现线程池2")<br />


******
参考文档：<br />
* [x] [知乎：用 C++ 写线程池是怎样一种体验？](https://www.zhihu.com/question/27908489)<br />
* [x] [linux c++线程池的实现](https://blog.csdn.net/zhoubl668/article/details/8927090)<br />