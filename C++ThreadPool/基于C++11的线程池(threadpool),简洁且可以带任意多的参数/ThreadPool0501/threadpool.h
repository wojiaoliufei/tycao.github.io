#pragma once
#include <vector>
#include <queue>
#include <thread>
#include <atomic>
#include <condition_variable>
#include <future>               // for std::future<decltype<f(args...)>>
#include <functional>           // for std::function<>
#include <stdexcept>            // for std::runtime_error

namespace std
{
#define  MAX_THREAD_NUM 256

//线程池,可以提交变参函数或lambda表达式的匿名函数执行,可以获取执行返回值
//不支持类成员函数, 支持类静态成员函数或全局函数,Opteron()函数等
class threadpool
{
    using Task = std::function<void()>;
    // 线程池
    std::vector<std::thread> pool;
    // 任务队列
    std::queue<Task> tasks;
    // 同步
    std::mutex mtx_;
    // 条件阻塞
    std::condition_variable cond_;
    // 是否关闭提交
    std::atomic<bool> stoped;
    //空闲线程数量
    std::atomic<int>  idlThrNum;

public:
    inline threadpool(unsigned short size = 4) :stoped{ false }
    {
        idlThrNum = size < 1 ? 1 : size;
        for (size = 0; size < idlThrNum; ++size)
        {   //初始化线程数量
            pool.emplace_back(
                [this]
                { // 工作线程函数
                    while(!this->stoped)
                    {
                        std::function<void()> task;
                        {   // 获取一个待执行的 task
                            std::unique_lock<std::mutex> lock{ this->mtx_ };// unique_lock 相比 lock_guard 的好处是：可以随时 unlock() 和 lock()
                            this->cond_.wait(lock, [this] { return this->stoped.load() || !this->tasks.empty(); } ); // wait 直到有 task
                            if (this->stoped && this->tasks.empty())
                                return;     // 满足此两个条件，线程退出
                            task = std::move(this->tasks.front()); // 取一个 task : std::function<>对象不能拷贝，只能移动
                            this->tasks.pop();
                        }   // 离开作用域，std::unique_lock<std::mutex>的析构函数会自动解锁 ：lock.unlock()
                        idlThrNum--;
                        task();
                        idlThrNum++;    // 这一步是什么意思？？？
                    }
                }
            );
        }
    }
    inline ~threadpool()
    {
        stoped.store(true);
        cond_.notify_all(); // 唤醒所有线程执行
        for (std::thread& thread : pool) {
            //thread.detach(); // 让线程“自生自灭”
            if(thread.joinable())
                thread.join(); // 等待任务结束， 前提：线程一定会执行完
        }
    }

public:
    // 提交一个任务
    // 调用.get()获取返回值会等待任务执行完,获取返回值
    // 有两种方法可以实现调用类成员，
    // 一种是使用   bind： .commit(std::bind(&Dog::sayHello, &dog));
    // 一种是用 mem_fn： .commit(std::mem_fn(&Dog::sayHello), &dog)
    template<class F, class... Args>
    auto commit(F&& f, Args&&... args) ->std::future<decltype(f(args...))>
    {
        if (stoped.load())    // stop == true ??
            throw std::runtime_error("commit on ThreadPool is stopped.");

        using RetType = decltype(f(args...)); // typedef typename std::result_of<F(Args...)>::type RetType; 函数 f 的返回值类型

        auto task = std::make_shared<std::packaged_task<RetType()>> (
            std::bind(std::forward<F>(f), std::forward<Args>(args)...)
        );    // wtf !
        std::future<RetType> future = task->get_future();
        {    // 添加任务到队列
            std::lock_guard<std::mutex> lock{ mtx_ };//对当前块的语句加锁  lock_guard 是 mutex 的 stack 封装类，构造的时候 lock()，析构的时候 unlock()
            tasks.emplace(
                [task]() ->void
                { // push(Task{...})
                    (*task)();
                }
            );
        }   // 退出作用域后，std::lock_guard<std::mutex>的析构函数，会自动解锁 lock.unlock()
        cond_.notify_one(); // 唤醒一个线程执行

        return future;
    }

    //空闲线程数量
    int idlCount() { return idlThrNum; }

};

}
