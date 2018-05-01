#pragma once
#include <mutex>                // for mutex
#include <condition_variable>   // for condition_variable
#include <queue>                // for queue<>
#include <thread>
#include <vector>
#include <unistd.h>

template <typename T>
class ThreadSafeQueue{
public:
         void Insert(T value);
         T Popup();
         bool Empty() const;
         ThreadSafeQueue(size_t threadNum) {
             for (size_t i = 0; i != threadNum; ++i) {
                 Pool.emplace_back([this]{
                    printf("Popup()...%d\n", Popup());
                  });
             }
         }
         // Ïß³Ì³Ø
        std::vector<std::thread> Pool;
private:
       mutable std::mutex mut_;
       std::queue<T> que_;
       std::condition_variable cond_;
};
template <typename T>
void ThreadSafeQueue<T>::Insert(T value){
    std::lock_guard<std::mutex> lk(mut_);
    que_.push(value);
    cond_.notify_one();
}

template <typename T>
T ThreadSafeQueue<T>::Popup(){
    std::unique_lock<std::mutex> lk(mut_);
    cond_.wait(lk, [this]{return !que_.empty();});
    T &value = que_.front();
    que_.pop();
    return value;
}

template <typename T>
bool ThreadSafeQueue<T>::Empty() const{
        std::lock_guard<std::mutex> lk(mut_);
        return que_.empty();
}
