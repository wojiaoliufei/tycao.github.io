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
