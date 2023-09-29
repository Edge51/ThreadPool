#ifndef THREADPOOL_LIBRARY_H
#define THREADPOOL_LIBRARY_H

#include <vector>
#include <queue>
#include <thread>

class ThreadPool {
public:
    explicit ThreadPool(int n);
    std::string SayHello() const;
    
private:
    std::vector<std::thread> threadPool;
    std::queue<std::thread> tasks;
};

#endif //THREADPOOL_LIBRARY_H
