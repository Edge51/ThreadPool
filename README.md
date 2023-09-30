# ThreadPool

Project learning programming

# Interface Design

this design is learning from [progschj/ThreadPool](https://github.com/progschj/ThreadPool)

``` c++
class ThreadPool {
public:
    ThreadPool(size_t n);
    ~ThreadPool();
    int32_t EnQueue();

private:
    std::vector<std::thread> workers;
    std::queue<std::function<void()>> tasks;
private:
    std::mutex queueMutex;
    std::condition_variable condition;
    bool running;
}
```

## What to implement tasks?

``` c++
function<void()>
```

questions

- why is it a function?
- why the type is void ()

thoughts

- a task is some steps we want to do which are a group of instructions in programming language.
- TODO

