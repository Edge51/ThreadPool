#ifndef THREADPOOL_LIBRARY_H
#define THREADPOOL_LIBRARY_H

#include <vector>
#include <queue>
#include <thread>

void hello();

class ThreadPool{
public:
    explicit ThreadPool(int n);
    
private:
    std::vector<std::thread> threadPool;
    std::queue<std::thread> tasks;
};

#endif //THREADPOOL_LIBRARY_H
