#include <iostream>
#include "threadpool.h"

using namespace std;

// static��̬���������⸳��ʼ��
std::vector<CTask*> CThreadPool::m_vecTaskList;     /** �����б� */
bool    CThreadPool::shutdown = false;          /** �߳��˳���־ */
pthread_mutex_t          CThreadPool::m_pthreadMutex = PTHREAD_MUTEX_INITIALIZER;     /** �߳�ͬ���� */
pthread_cond_t           CThreadPool::m_pthreadCond  = PTHREAD_COND_INITIALIZER;      /** �߳�ͬ������������ */

// ���̵߳��̻߳ص�����
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
        // ȡ��һ������ִ��
        if (iter != m_vecTaskList.end()) {
            task = *iter;
            m_vecTaskList.erase(iter);
        }

        pthread_mutex_unlock(&m_pthreadMutex);
        task->Run();    // ִ������
        printf("tid %lu idle\n", tid);
    }
    return 0;
}
int CThreadPool::MoveToIdle(pthread_t tid) {}          /** �߳�ִ�н����󣬰��Լ����뵽�����߳��� */
int CThreadPool::MoveToBusy(pthread_t tid) {}          /** ���뵽æµ�߳���ȥ */

// �����̳߳��е��߳�
int CThreadPool::Create() {
    pthread_id = reinterpret_cast<pthread_t*>(malloc(sizeof(pthread_t) * m_iThreadNum));
    for (size_t i = 0; i != m_iThreadNum; ++i) {
        pthread_create(&pthread_id[i], nullptr, &ThreadFunc, nullptr);
    }
    return 0;
}

// �̳߳ع����� ���캯��
CThreadPool::CThreadPool(size_t threadNum) {
    this->m_iThreadNum = threadNum;
    printf("I will now create %d threads\n", threadNum);
    Create();
}
// ��������ӵ����������, ������ͬ���ź�
int CThreadPool::AddTask(CTask *task) {
    pthread_mutex_lock(&m_pthreadMutex);
    this->m_vecTaskList.push_back(task);
    pthread_mutex_unlock(&m_pthreadMutex);

    // ����ͬ���ź�
    // �ú����������ǽ��һ���ȴ�����cond��ָ���������������̵߳�����״̬�����ж���̹߳���ȴ�������������Ҳֻ����һ���̡߳�
    pthread_cond_signal(&m_pthreadCond);
    return 0;
}

// ʹ�̳߳��е��߳��˳�
int CThreadPool::StopAll() {
    // �����ظ�����
    if (shutdown)
        return -1;
    printf("I will now end all threads\n");
    shutdown = true;
    // �ú������������еȴ�����cond��ָ���������������߳̽�����������óɹ�����0�����򷵻ش�����롣
    pthread_cond_broadcast(&m_pthreadCond);

    // �����ȴ��߳��˳���������ǽ�ʬ�߳���
    for (size_t i = 0; i != m_iThreadNum; ++i) {
        pthread_join(pthread_id[i], 0);
    }

    free(pthread_id);
    pthread_id = nullptr;

    // ���� �������� �� �������
    //�ú��������ͷŷ��������mutex ����Դ�����óɹ�ʱ����ֵΪ0,���򷵻�һ����0 �Ĵ�����롣
    pthread_mutex_destroy(&m_pthreadMutex);

    // �ú������������ͷ�һ�������������ͷ�Ϊ��������cond ���������Դ�����óɹ�����ֵΪ0�����򷵻ش�����롣
    pthread_cond_destroy(&m_pthreadCond);

    return 0;
}

// ��ȡ��ǰ��������е�������
int CThreadPool::GetTaskSize() {
    return m_vecTaskList.size();
}

