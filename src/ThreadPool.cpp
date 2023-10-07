#include "../include/ThreadPool.h"

#include <iostream>

ThreadPool::ThreadPool(int n)
{
    for (int i = 0; i < n; i++) {
        workers.emplace_back(
            [this]
            {
                while (true) {
                    Task task;
                    {
                        std::unique_lock<std::mutex> lock(this->queueMutex);
                        this->conditionVariable.wait(lock, 
                        [this] { return !this->running || !this->tasks.empty(); });
                        if (!this->running && this->tasks.empty()) {
                            return ;
                        }
                        task = std::move(this->tasks.front());
                        this->tasks.pop();
                    }
                }
            }
        );
    }
}

ThreadPool::~ThreadPool()
{
    std::unique_lock<std::mutex> lock(this->queueMutex);
    this->running = false;
    this->conditionVariable.notify_all();
    for (auto &worker : workers) {
        worker.join();
    }
}

template<class F, class... Args>
auto ThreadPool::EnQueue(F&& f, Args&&... args)
    -> std::future<typename std::result_of<F(Args...)>::type>
{
    using ReturnType = typename std::result_of<F(Args...)>::type;

    auto task = std::make_shared<std::packaged_task<ReturnType()>>(
        std::bind(std::forward(f), std::forward(args)...)
    );

    std::future<ReturnType> result = task.get_future();

    {
        std::unique_lock<std::mutex> lock(queueMutex);
        if (!running) {
            throw std::runtime_error("EnQueue when threadPool not running!");
        }
        tasks.emplace(task);
    }

    conditionVariable.notify_one();

    return result;
}

size_t ThreadPool::Size() const
{
    std::unique_lock<std::mutex>(workersMutex);
    return workers.size();
}