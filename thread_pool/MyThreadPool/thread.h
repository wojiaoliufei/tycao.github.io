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
