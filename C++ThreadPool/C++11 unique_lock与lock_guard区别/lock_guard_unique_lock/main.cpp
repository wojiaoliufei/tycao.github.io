#include "demo.h"
#include <unistd.h>


int main(int argc, char *argv[])
{
    ThreadSafeQueue<int> obj(15);
    for (size_t i = 0; i != 20; ++i) {
        obj.Insert(i);
    }


    for (auto&& t : obj.Pool) {
            t.join();
    }

    if (obj.Empty()) {
        printf("obj is empty...\n");
    }
    else {
        while (!obj.Empty()) {
            printf("-%d-", obj.Popup());
        }
    }

    if (obj.Empty()) {
        printf("obj is empty...\n");
    }

    return 0;
}
