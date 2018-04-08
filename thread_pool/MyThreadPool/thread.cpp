#include "thread.h"

namespace csx {



void CTask::SetData(void* data) {
    m_ptrName = data;
}

/** static 成员变量必须在类外初始化，且类外不能继续加上static */
vector<CTask*>   CThreadPool::m_vecTaskList;                                 /** 任务池（任务队列） */
bool             CThreadPool::shutdown = false;                              /** 线程退出标志 */
pthread_mutex_t  CThreadPool::m_pthreadMutex = PTHREAD_MUTEX_INITIALIZER;    /** 线程同步锁 */
pthread_cond_t   CThreadPool::m_pthreadCond = PTHREAD_COND_INITIALIZER;      /** 线程同步的条件变量 */

/** 构造函数：创建（固定数量的）线程 */
CThreadPool::CThreadPool(int threadNum)
    : m_iThreadNum(threadNum)
{
    printf("i will create %d threads\n", m_iThreadNum);
    Create();
}

/** 创建线程池中线程 */
int CThreadPool::Create(void)
{
    pthread_id = static_cast<pthread_t*>(malloc(sizeof(pthread_t) * m_iThreadNum));
    for (int i = 0; i != m_iThreadNum;  ++i)
        pthread_create(&pthread_id[i], nullptr, ThreadFunc, nullptr);
    return 0;
}

/** 线程回调函数 */
void* CThreadPool::ThreadFunc(void* threadData) {
    pthread_t tid = pthread_self(); // 获取当前线程的线程id
    while (true) {
        pthread_mutex_lock(&m_pthreadMutex);

        /** 若任务池中没有任何任务之后，则线程处于睡眠状态 */
        if (m_vecTaskList.size() == 0 && !shutdown)
            pthread_cond_wait(&m_pthreadCond, &m_pthreadMutex);

        if (shutdown) {
            pthread_mutex_unlock(&m_pthreadMutex);
            printf("tid %lu will exit\n", tid);
            pthread_exit(nullptr);
        }

        printf("tid %lu run\n", tid);
        /** 取出一个任务，并执行 */
        vector<CTask*>::iterator iter = m_vecTaskList.begin();
        CTask* task;
        if (iter != m_vecTaskList.end()) {
            task = *iter;
            m_vecTaskList.erase(iter);
        }
        pthread_mutex_unlock(&m_pthreadMutex);

        task->Run();    /** 执行任务 */
        printf("tid %lu idle\n", tid);
    }
    return 0;
}
/** 把任务添加到任务队列中 */
int CThreadPool::AddTask(CTask* task) {
    pthread_mutex_lock(&m_pthreadMutex);
    m_vecTaskList.push_back(task);
    pthread_mutex_unlock(&m_pthreadMutex);
    pthread_cond_signal(&m_pthreadCond);
    return 0;
}
/** 使线程池中的线程退出 */
int CThreadPool::StopAll() {
    /** 避免重复调用 */
    if (shutdown) return -1;

    printf("i will end all threads.\n");
    /** 唤醒所有（处于pthread_cond_wait状态）线程，线程池要销毁啦 */
    shutdown = true;
    pthread_cond_broadcast(&m_pthreadCond);

    /** 使阻塞等待线程退出，否则就成僵尸线程了 */
    for (int i = 0; i != m_iThreadNum; ++i)
        pthread_join(pthread_id[i], nullptr);

    /** 释放线程池 */
    free(pthread_id);
    pthread_id = nullptr;

    /** 销毁条件变量 和 互斥体 */
    pthread_cond_destroy(&m_pthreadCond);
    pthread_mutex_destroy(&m_pthreadMutex);

    return 0;
}
/** 获取当前任务列表中的任务数量 */
int CThreadPool::GetTaskSize() {
    return m_vecTaskList.size();
}


}
