#include <iostream>
#include "threadpool.h"

using namespace std;

// static静态变量在类外赋初始化
std::vector<CTask*> CThreadPool::m_vecTaskList;     /** 任务列表 */
bool    CThreadPool::shutdown = false;          /** 线程退出标志 */
pthread_mutex_t          CThreadPool::m_pthreadMutex = PTHREAD_MUTEX_INITIALIZER;     /** 线程同步锁 */
pthread_cond_t           CThreadPool::m_pthreadCond  = PTHREAD_COND_INITIALIZER;      /** 线程同步的条件变量 */

// 新线程的线程回调函数
void*   CThreadPool::ThreadFunc(void *threadData) {
    pthread_t tid = pthread_self();
    while (1) {
        pthread_mutex_lock(&m_pthreadMutex);
        while (m_vecTaskList.empty() && !shutdown) {
            pthread_cond_wait(&m_pthreadCond, &m_pthreadMutex);
        }

        if (shutdown) {
            pthread_mutex_unlock(&m_pthreadMutex);
            printf("thread %lu will exit\n", tid);
            pthread_exit(0);
        }

        printf("tid %lu run\n", tid);

        vector<CTask*>::iterator iter = m_vecTaskList.begin();
        CTask* task = 0;
        // 取出一个任务并执行
        if (iter != m_vecTaskList.end()) {
            task = *iter;
            m_vecTaskList.erase(iter);
        }

        pthread_mutex_unlock(&m_pthreadMutex);
        task->Run();    // 执行任务
        printf("tid %lu idle\n", tid);
    }
    return 0;
}
int CThreadPool::MoveToIdle(pthread_t tid) {}          /** 线程执行结束后，把自己放入到空闲线程中 */
int CThreadPool::MoveToBusy(pthread_t tid) {}          /** 移入到忙碌线程中去 */

// 创建线程池中的线程
int CThreadPool::Create() {
    pthread_id = reinterpret_cast<pthread_t*>(malloc(sizeof(pthread_t) * m_iThreadNum));
    for (size_t i = 0; i != m_iThreadNum; ++i) {
        pthread_create(&pthread_id[i], nullptr, &ThreadFunc, nullptr);
    }
    return 0;
}

// 线程池管理类 构造函数
CThreadPool::CThreadPool(size_t threadNum) {
    this->m_iThreadNum = threadNum;
    printf("I will now create %d threads\n", threadNum);
    Create();
}
// 把任务添加到任务队列中, 并发出同步信号
int CThreadPool::AddTask(CTask *task) {
    pthread_mutex_lock(&m_pthreadMutex);
    this->m_vecTaskList.push_back(task);
    pthread_mutex_unlock(&m_pthreadMutex);

    // 发出同步信号
    // 该函数的作用是解除一个等待参数cond所指定的条件变量的线程的阻塞状态。当有多个线程挂起等待该条件变量，也只唤醒一个线程。
    pthread_cond_signal(&m_pthreadCond);
    return 0;
}

// 使线程池中的线程退出
int CThreadPool::StopAll() {
    // 避免重复调用
    if (shutdown)
        return -1;
    printf("I will now end all threads\n");
    shutdown = true;
    // 该函数用来对所有等待参数cond所指定的条件变量的线程解除阻塞，调用成功返回0，否则返回错误代码。
    pthread_cond_broadcast(&m_pthreadCond);

    // 阻塞等待线程退出，否则就是僵尸线程了
    for (size_t i = 0; i != m_iThreadNum; ++i) {
        pthread_join(pthread_id[i], 0);
    }

    free(pthread_id);
    pthread_id = nullptr;

    // 销毁 条件变量 与 互斥变量
    //该函数用来释放分配给参数mutex 的资源。调用成功时返回值为0,否则返回一个非0 的错误代码。
    pthread_mutex_destroy(&m_pthreadMutex);

    // 该函数的作用是释放一个条件变量。释放为条件变量cond 所分配的资源。调用成功返回值为0，否则返回错误代码。
    pthread_cond_destroy(&m_pthreadCond);

    return 0;
}

// 获取当前任务队列中的任务数
int CThreadPool::GetTaskSize() {
    return m_vecTaskList.size();
}

