#include "threadpool.h"
#include <unistd.h>

class CMyTask : public CTask {
public:
    CMyTask() {}
    int Run() {
        printf("%s\n", static_cast<char*>(this->m_ptrData));
        sleep(10);
    }
};

int main(int argc, char *argv[])
{
    CMyTask task;
    char szTmp[] = "this is the first thread running...";
    task.SetData(static_cast<void*>(szTmp));
    CThreadPool threadPool(10);

    for (size_t i = 0; i != 20; ++i) {
        threadPool.AddTask(&task);
    }

    while (1) {
        printf("There are still %d tasks need to be handled\n", threadPool.GetTaskSize());
        if (threadPool.GetTaskSize() == 0) {
            if (threadPool.StopAll() == -1) {
                printf("I will now exit from main\n");
                exit(0);
            }
        }
        sleep(2);
    }

    return 0;
}
