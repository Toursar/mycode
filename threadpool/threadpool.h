#pragma once
#include<mutex>
#include<queue>
#include<vector>
#include<thread>
#include<condition_variable>
#include<future>
#include<iostream>
#include<functional>
#include <utility>

class threadpool {
private:
    //工作队列
    std::vector<std::thread> workers;
    //任务队列
    std::queue<std::function<void()>> tasks;
    //为任务队列服务的锁
    std::mutex queue_mutex;
    std::condition_variable condition;
    //标识何时回收线程池
    bool stop;
public:
    threadpool(int thread_num) : stop(false) {
        for (int i = 0; i < thread_num; ++i) {
            workers.emplace_back([this, i]() {
                while (true)
                {
                    std::cout << "worker " << i << " working..." << std::endl;
                    std::function<void()> task;
                    {
                        std::unique_lock<std::mutex> lock(this->queue_mutex);
                        //队列为空，线程休眠
                        if (this->tasks.empty())
                            this->condition.wait(lock);
                        //一直运行知道接收到停止命令，并且处理完当前队列的任务
                        if (this->stop && this->tasks.empty())
                            return;
                        task = this->tasks.front();
                        this->tasks.pop();
                    }
                    task();
                    std::cout << "worker " << i << " done" << std::endl;
                }
            });
        }
    }

    ~threadpool() {}

    //enqueue方法利用变长模板参数方法，将不同的返回值与参数的函数打包为woid()的形式，放入队列中
    //使用decltype来确认需要执行的任务的函数返回值
    template <typename F, typename... Args>
    auto enqueue(F &&f, Args &&... args) -> std::future<decltype(f(args...))> {
        std::function<decltype(f(args...))()> func = std::bind(std::forward<F>(f), std::forward<Args>(args)...);
        auto task = std::make_shared<std::packaged_task<decltype(f(args...))()>>(func);
        std::function<void()> func_temp = [task]() {
                (*task)();
            };
        {
            std::unique_lock<std::mutex> lock(queue_mutex);
            if (stop)
                std::cerr << "thread pool is already stopped!" << std::endl;
            //将当前传入的函数打包为void()型的函数，其中返回值已被res接收，然后放入任务队列中
            tasks.emplace(func_temp);
        }
        this->condition.notify_one();
        return task->get_future();
    }


    // template <typename F, typename... Args>
    // auto enqueue(F &&f, Args &&... args) -> std::future<typename std::result_of<F(Args...)>::type> {
    //     using return_type = typename std::result_of<F(Args...)>::type;
    //     auto task = std::make_shared<std::packaged_task<return_type()>>(
    //         std::bind(std::forward<F>(f), std::forward<Args>(args)...));
    //     //std::future<return_type> res = task->get_future();
    //     {
    //         std::unique_lock<std::mutex> lock(queue_mutex);
    //         if (stop)
    //             std::cerr << "thread pool is already stopped!" << std::endl;
    //         //将当前传入的函数打包，放入任务队列中
    //         tasks.emplace([task]() {
    //             (*task)();
    //         });
    //     }
    //     condition.notify_one();
    //     return task->get_future();
    // }


    void shutdown() {
        //将stop改为1，唤醒所有线程，等待任务运行完成后结束
        {
            std::unique_lock<std::mutex> lock(queue_mutex);
            stop = true;
        }
        condition.notify_all();
        for (std::thread& worker : workers) {
            worker.join();
        }
    }
};