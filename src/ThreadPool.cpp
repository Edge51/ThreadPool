#include "../include/ThreadPool.h"

#include <iostream>

void hello() {
    std::cout << "Hello, World!" << std::endl;
}

ThreadPool::ThreadPool(int n) {

}

std::string ThreadPool::SayHello() const
{
    return "hello";
}