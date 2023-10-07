# ThreadPool

Project learning programming

## Interface Design

this design is learning from [progschj/ThreadPool](https://github.com/progschj/ThreadPool)

``` c++
using Task = std::function<void()>;
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

## Note

when using std::condition_variable

``` c++
cv.wait(lock, A || B); // compile error
cv.wait(lock, [this]{ return A || B; }); // OK
```

new function declaration

the following two function declaration are equivalent to each other

``` c++
return-type identifier(args)
auto identifier(args) -> return-type
```

the latter one provide a way for template to declare return type derived from template arguments.

The reason using auto identifier(args) -> return-type is that it wanted to deduct type of return type;

``` c++
template<class F, class... Args>
auto Enqueue(F&& f, Args&&... args)
    -> std::future<typename std::result_of<F(Args...)>::type>
{
    using ReturnType = typename std::result_of<F(Args...)>::type;
	auto task = std::make_shared<std::packaged_task<ReturnType()>>(
		std::bind(std::forward<F>(f), std::forward<Args>(args)...)
	);
	std::future<ReturnType> result = task->get_future();

    {
		std::unique_lock<std::mutex> lock(queueMutex);
		if (!running) {
			throw std::runtime_error("Enqueue when not running threadPool");
		}
		taskQueue.emplace_back([task](){ (*task)(); });
	}

	conditionVariable.notify_one();
	return result
}
```

- template class... why ... is after class
- why using && as parameter
- what's the advantage of declaring ReturnType as using type
- args expand ...

after add the EnQueue function, it stop when running the test  initialize
