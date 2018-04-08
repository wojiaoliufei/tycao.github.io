使用C++11实现线程池
=========
### 首先，我们了解下线程池的原理
!["thrPool1"](https://github.com/tycao/Cpp_mini_projects/blob/master/thread_pool/threadpool_1.png "thrPool1")<br />
由上图，我们可以看出：**线程池就是一个 _工厂_ ，它包含固定数量的线程，这些线程一直不停地从任务池（又称任务队列）中取出任务，并执行。**
在执行任务的过程中，各个线程之间的操作是互斥的，以确保线程安全。

### 先上代码
#### thread.h
```cpp
#pragma once

#include <stdio.h>  // for printf()
#include <iostream>
#include <thread>
#include <chrono>   // for std::chrono::seconds()
#include <future>   // for future<>
#include <string>
#include <vector>
#include <queue>
#include <memory>   // for make_shared<>, shared_ptr<>
#include <functional>   // for std::function<>

class ThreadPool {
public:
    ThreadPool(size_t threads);
    ~ThreadPool();

    template<typename F, typename... Args>
    auto enqueue(F &&f, Args&&... args)
    -> std::future<typename std::result_of<F(Args...)>::type>;

private:
    std::vector<std::thread> workers;
    std::queue<std::function<void()>> tasks;

    std::mutex queue_mutex;
    std::condition_variable condition;

    bool stop;
};

inline ThreadPool::ThreadPool(size_t threads)
    : stop(false)
{
    /** 在线程池中创建（数量为threads个）线程 */
    for (size_t i = 0; i < threads; ++i)
    {
        workers.emplace_back([this] {
            for (;;) {
                std::function<void()> task;
                {
                    std::unique_lock<std::mutex> lock(this->queue_mutex);

                    this->condition.wait(lock, [this] {
                        return this->stop || !this->tasks.empty();
                    });

                    /** 对象销毁之前，先销毁所有的睡眠线程 */
                    if (this->stop && this->tasks.empty())
                        return;

                    task = std::move(this->tasks.front());
                    this->tasks.pop();
                }
                task();
            }
        });
    }
}

inline ThreadPool::~ThreadPool() {
    {
        std::unique_lock<std::mutex> lock(queue_mutex);
        stop = true;
    }

    /** 唤醒所有（不干活的）睡眠线程 */
    condition.notify_all();

    /** 销毁所有线程；最后销毁main主线程 */
    for (std::thread &worker: workers)
        worker.join();
}

/**
 * 往线程池的任务队列里添加任务
*/
template <typename F, typename... Args>
auto ThreadPool::enqueue(F&& f, Args&&... args)
                ->std::future<typename std::result_of<F(Args...)>::type>
{

    using return_type = typename std::result_of<F((Args...))>::type;

    auto task =
    std::make_shared<std::packaged_task<return_type()>>(std::bind(std::forward<F>(f), std::forward<Args>(args)...));

    std::future<return_type> res = task->get_future();

    {
        std::unique_lock<std::mutex> lock(queue_mutex);

        if (stop)
            throw std::runtime_error("enqueue on stopped ThreadPool");

        tasks.emplace([task]{(*task)();});
    }

    condition.notify_one();
    return res;

}
```

#### main.cpp
```cpp
#include "thread.h"

int main(int argc, const char * argv[])
{
    /** 在线程池中创建4个线程 */
    ThreadPool pool(4);

    std::vector<std::future<std::string>> results;

    for (int i = 0; i < 8; i++)
    {
        results.emplace_back(
            pool.enqueue([i] {
                std::cout << (std::string("hello") + std::to_string(i)) << std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(16 - i * 2));
                std::cout << (std::string("world") + std::to_string(i)) << std::endl;
                return std::string("---thread") + std::to_string(i) + std::string( "finished---");
            })
        );
    }

    for (auto && result: results)
        std::cout << result.get() << ' ';
    std::cout << std::endl;
    return 0;
}
```

### 程序运行之后的截图：
!["C++实现线程池3"](https://github.com/tycao/tycao.github.io/blob/master/thread_pool/result03.png "C++实现线程池3")<br />

### 接下来，我们详细讲解`ThreadPool`这个线程类
* [x] **ThreadPool::ThreadPool(size_t threads)** <br />
这个线程池的构造函数，做了一些很重要的事情：`在线程池构造的过程中，创建了固定数量的线程，并将创建的线程放进线程列表内。`  **一开始所有线程都会处于睡眠状态，等待被唤醒。** <br />
`当stop为true或者任务队列不为空时，` 线程就会一直不停地往任务池里取任务，并执行。<br />
`当stop为true且任务队列为空时，` 此时说明任务被全部执行完毕，线程也都重新处于等待被唤醒的状态（睡眠状态）。这时就需要销毁所有睡眠的线程。最后销毁main主线程。<br />
**各个线程之间的操作是互斥的，以确保线程安全的执行。**

* [x] **template <typename F, typename... Args> auto ThreadPool::enqueue(F&& f, Args&&... args)->std::future<typename std::result_of<F(Args...)>::type> {}** <br />
这个函数是为了往任务池中添加任务 ： 每次添加一个任务，就会唤醒一个线程去处理此任务。

* [x] **ThreadPool::~ThreadPool()** <br />
线程池类的析构函数：此时加同步锁（确保线程安全），然后修改成员变量stop为true。当执行`condition.notify_all()`之后，所有线程都会被唤醒，然后执行下面的代码：<br />
```cpp
/** 对象销毁之前，先销毁所有的睡眠线程 */
                    if (this->stop && this->tasks.empty())
                        return;
```
由上述可知，每个线程都会退出。然后被销毁：
```cpp
/** 销毁所有线程；最后销毁main主线程 */
    for (std::thread &worker: workers)
        worker.join();
```
最后所有线程都被销毁之后，主线程才被最后销毁。
