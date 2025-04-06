#include <iostream>
#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>

class threadpool
{
public:

    threadpool(size_t nums);

    template<class FD, class... Args>
    void thread_add(FD&& f, Args&&... arg);

    ~threadpool();

private:
    std::vector<std::thread> mems;

    std::queue<std::function<void()>> numbers;

    bool stop;

    std::mutex threadlock;

    std::condition_variable iway;

};

threadpool::threadpool(size_t nums):stop(false){
    for(size_t i = 0; i < nums; i++)
    {
        mems.emplace_back([this]{
            while(true)
            {
                std::function<void()> task;
                {
                    std::unique_lock<std::mutex> lock(this->threadlock);

                    this->iway.wait(lock, [this]
                    {
                        return this->stop || !this->numbers.empty();
                    });

                    if(this->stop && this->numbers.empty())
                    {
                        return;
                    }

                    task = std::move(this->numbers.front());

                    this->numbers.pop();
                }
                task();
            }
        });
    }
}


template<class FD, class... Args>
void threadpool::thread_add(FD&& f, Args&&... args)
{
    auto num = std::make_shared<std::function<void()>>(
        std::bind(std::forward<FD> (f), std::forward<Args> (args)...)
    );

    {
        std::unique_lock<std::mutex> lock(threadlock);

        if(stop) 
        throw std::runtime_error("ThreadPool has been stopped");

        numbers.emplace([num]() { (*num)(); } );
    }

    iway.notify_one();
}

threadpool::~threadpool()
{
    {
        std::unique_lock<std::mutex> lock(threadlock);
        stop = true;
    }

    iway.notify_all();
    for(std::thread &mem : mems)
    {
        mem.join();
    }
}

int main()
{
    threadpool pools(10);
    for(int i = 0; i < 20; i++)
    {
        pools.thread_add([i]{
            std::cout << "task " << i << "is " << std::this_thread::get_id() << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        });
    }

    std::this_thread::sleep_for(std::chrono::seconds(2));

    return 0;
}