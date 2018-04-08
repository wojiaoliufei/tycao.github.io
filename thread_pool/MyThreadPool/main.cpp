#include <iostream>
#include "thread.h"



class CMyTask : public csx::CTask {
public:
    CMyTask() {}
    int Run() {
        printf("%s\n", static_cast<char*>(this->m_ptrName));
        Sleep(3000);
        return 0;
    }
};

int main() {
    /** 创建任务对象，塞进线程池中的任务队列中，供线程循环取出并执行 */
    CMyTask taskObj;
    char szTmp[] = "this is the first thread running!";
    taskObj.SetData(static_cast<void*>(szTmp));

    /** 创建一个线程池，默认包含10条线程 */
    csx::CThreadPool threadPool(10);

    /** 将20个任务放进线程池中的任务池中 */
    for (int i = 0; i != 20; ++i)
        threadPool.AddTask(&taskObj);

    while (true) {
        printf("there are still %d tasks need to be handled\n", threadPool.GetTaskSize());
        if (threadPool.GetTaskSize() == 0)
            if (threadPool.StopAll() == -1) {
                printf("Now i will exit from main.\n");
                exit(0);
            }
        Sleep(2000);
    }
    return 0;
}
