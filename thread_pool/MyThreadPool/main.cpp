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
