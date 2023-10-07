#ifndef THREADPOOL_LIBRARY_H
#define THREADPOOL_LIBRARY_H

#include <vector>
#include <queue>
#include <thread>
#include <future>
#include <condition_variable>
#include <functional>

using Task = std::function<void()>;
class ThreadPool {
public:
    ThreadPool() = delete;
    explicit ThreadPool(int n);
    ~ThreadPool();
    template<class F, class... Args>
    auto EnQueue(F&& f, Args&&... args)
        -> std::future<typename std::result_of<F(Args...)>::type>;
    size_t Size() const;
    
private:
    std::vector<std::thread> workers;
    std::queue<Task> tasks;
    std::condition_variable conditionVariable;
    std::mutex queueMutex;
    std::mutex workersMutex;
    bool running;
};

#endif //THREADPOOL_LIBRARY_H
