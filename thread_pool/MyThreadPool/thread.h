#pragma once

#include <vector>
#include <string>
#include <cstdio>   /** for printf() */
#include <pthread.h>    /** for pthread_t */
#ifdef WIN32_
#include <windows.h>    /** for windows Sleep() */
#else
#include <unistd.h>     /** for Linux sleep(seconds) & usleep(millionseconds) */
#endif
using namespace std;

namespace csx {


/**
 * 执行任务的类 ： 设置数据并执行
*/
class CTask {
public:
    CTask(){}   /** 默认构造函数 */
    CTask(string taskName) : m_strTaskName(taskName) {} /** 带有一个string参数的构造函数 */
    ~CTask(){}  /** 析构函数 */

    virtual int Run(void) = 0;  /** 纯虚函数：说明本类CTask是以一个抽象基类，不能直接初始化，Run函数需要在各个派生类中实现各自特定的功能 */
    void SetData(void*);    /** 设置任务数据 */
protected:
    string m_strTaskName;   /** 任务的名称 */
    void* m_ptrName = nullptr;  /** 要执行的任务的具体数据 */
};

/**
 * 线程池管理类
*/
class CThreadPool {
private:
    static vector<CTask*>   m_vecTaskList;      /** 任务池（任务队列） */
    static bool             shutdown;           /** 线程退出标志 */
    int                     m_iThreadNum = 0;   /** 线程池中启动的线程数量 */
    pthread_t*              pthread_id = nullptr;
    static pthread_mutex_t  m_pthreadMutex;     /** 线程同步锁 */
    static pthread_cond_t   m_pthreadCond;      /** 线程同步的条件变量 */
protected:
    static void*    ThreadFunc(void*);          /** 新线程的线程回调函数 */
    static int      MoveToIdle(pthread_t);      /** 线程执行结束后，把自己放入到空闲线程中 */
    static int      MoveToBusy(pthread_t);      /** 移入到忙碌线程中去 */
    int             Create(void);               /** 在线程池中创建线程 */
public:
    CThreadPool(int threadNum = 10);    /** 在线程池中创建线程（默认10个）：每个线程都在循环地（不停地）从任务列表中取出任务，然后执行 */
    int AddTask(CTask*);    /** 把任务添加到任务队列中 */
    int StopAll();          /** 使线程池中的线程退出 */
    int GetTaskSize();      /** 获取当前任务列表中的任务数量 */
};


}
