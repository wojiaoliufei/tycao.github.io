#include "threadpool.h"


int main(int argc, char *argv[])
{
    ThreadSafeQueue<int> obj(10);
    for (size_t i = 0; i != 10; ++i) {
        obj.Insert(i);
    }

    for (auto&& t : obj.Pool) {
            t.join();
    }

    if (obj.Empty()) {
        printf("obj is empty...\n");
    }

    return 0;
}
