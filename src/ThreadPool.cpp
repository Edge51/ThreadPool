#include "../include/ThreadPool.h"

#include <iostream>

void hello()
{
    std::cout << "Hello, World!" << std::endl;
}

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

size_t ThreadPool::Size() const
{
    std::unique_lock<std::mutex>(workersMutex);
    return workers.size();
}