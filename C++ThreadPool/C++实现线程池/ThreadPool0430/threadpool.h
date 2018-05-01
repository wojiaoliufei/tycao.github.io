#pragma once

#include "task.h"

/**
 * �̳߳ع�����
*/
class CThreadPool {
private:
    static  std::vector<CTask*>      m_vecTaskList;     /** �����б� */
    static  bool                     shutdown;          /** �߳��˳���־ */
    int                              m_iThreadNum;      /** �̳߳����������߳����� */
    pthread_t                       *pthread_id;        /** �߳� */

    static pthread_mutex_t          m_pthreadMutex;     /** �߳�ͬ���� */
    static pthread_cond_t           m_pthreadCond;      /** �߳�ͬ������������ */
protected:
    static void*    ThreadFunc(void *threadData);       /** ���̵߳��̻߳ص����� */
    static int      MoveToIdle(pthread_t tid);          /** �߳������Ǹ������󣬰��Լ����뵽�����߳��� */
    static int      MoveToBusy(pthread_t tid);          /** ���뵽æµ�߳���ȥ */

    int             Create();                           /** �����̳߳��е��߳� */
public:
    CThreadPool(size_t threadNum = 10);                 /** ���캯����Ĭ�������̳߳��д���10���߳� */
    int AddTask(CTask *task);                           /** ��������ӵ���������� */
    int StopAll();                                      /** ʹ�̳߳��е��߳��˳� */
    int GetTaskSize();                                  /** ��ȡ��ǰ��������е������� */
};
