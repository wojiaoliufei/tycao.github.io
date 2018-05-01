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

//�̳߳�,�����ύ��κ�����lambda���ʽ����������ִ��,���Ի�ȡִ�з���ֵ
//��֧�����Ա����, ֧���ྲ̬��Ա������ȫ�ֺ���,Opteron()������
class threadpool
{
    using Task = std::function<void()>;
    // �̳߳�
    std::vector<std::thread> pool;
    // �������
    std::queue<Task> tasks;
    // ͬ��
    std::mutex mtx_;
    // ��������
    std::condition_variable cond_;
    // �Ƿ�ر��ύ
    std::atomic<bool> stoped;
    //�����߳�����
    std::atomic<int>  idlThrNum;

public:
    inline threadpool(unsigned short size = 4) :stoped{ false }
    {
        idlThrNum = size < 1 ? 1 : size;
        for (size = 0; size < idlThrNum; ++size)
        {   //��ʼ���߳�����
            pool.emplace_back(
                [this]
                { // �����̺߳���
                    while(!this->stoped)
                    {
                        std::function<void()> task;
                        {   // ��ȡһ����ִ�е� task
                            std::unique_lock<std::mutex> lock{ this->mtx_ };// unique_lock ��� lock_guard �ĺô��ǣ�������ʱ unlock() �� lock()
                            this->cond_.wait(lock, [this] { return this->stoped.load() || !this->tasks.empty(); } ); // wait ֱ���� task
                            if (this->stoped && this->tasks.empty())
                                return;     // ����������������߳��˳�
                            task = std::move(this->tasks.front()); // ȡһ�� task : std::function<>�����ܿ�����ֻ���ƶ�
                            this->tasks.pop();
                        }   // �뿪������std::unique_lock<std::mutex>�������������Զ����� ��lock.unlock()
                        idlThrNum--;
                        task();
                        idlThrNum++;    // ��һ����ʲô��˼������
                    }
                }
            );
        }
    }
    inline ~threadpool()
    {
        stoped.store(true);
        cond_.notify_all(); // ���������߳�ִ��
        for (std::thread& thread : pool) {
            //thread.detach(); // ���̡߳���������
            if(thread.joinable())
                thread.join(); // �ȴ���������� ǰ�᣺�߳�һ����ִ����
        }
    }

public:
    // �ύһ������
    // ����.get()��ȡ����ֵ��ȴ�����ִ����,��ȡ����ֵ
    // �����ַ�������ʵ�ֵ������Ա��
    // һ����ʹ��   bind�� .commit(std::bind(&Dog::sayHello, &dog));
    // һ������ mem_fn�� .commit(std::mem_fn(&Dog::sayHello), &dog)
    template<class F, class... Args>
    auto commit(F&& f, Args&&... args) ->std::future<decltype(f(args...))>
    {
        if (stoped.load())    // stop == true ??
            throw std::runtime_error("commit on ThreadPool is stopped.");

        using RetType = decltype(f(args...)); // typedef typename std::result_of<F(Args...)>::type RetType; ���� f �ķ���ֵ����

        auto task = std::make_shared<std::packaged_task<RetType()>> (
            std::bind(std::forward<F>(f), std::forward<Args>(args)...)
        );    // wtf !
        std::future<RetType> future = task->get_future();
        {    // ������񵽶���
            std::lock_guard<std::mutex> lock{ mtx_ };//�Ե�ǰ���������  lock_guard �� mutex �� stack ��װ�࣬�����ʱ�� lock()��������ʱ�� unlock()
            tasks.emplace(
                [task]() ->void
                { // push(Task{...})
                    (*task)();
                }
            );
        }   // �˳��������std::lock_guard<std::mutex>���������������Զ����� lock.unlock()
        cond_.notify_one(); // ����һ���߳�ִ��

        return future;
    }

    //�����߳�����
    int idlCount() { return idlThrNum; }

};

}
