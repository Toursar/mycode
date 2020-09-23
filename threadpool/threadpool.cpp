// #include"threadpool.h"

// //初始化线程池
// threadpool::threadpool(int thread_num) : stop(false) {
//     for (int i = 0; i < thread_num; ++i) {
//         workers.emplace_back([this]() {
//             while (true)
//             {
//                 std::function<void()> task;
//                 {
//                     std::unique_lock<std::mutex> lock(this->queue_mutex);
//                     //队列为空，线程休眠
//                     while (this->tasks.empty())
//                         this->condition.wait(lock);
//                     //一直运行知道接收到停止命令，并且处理完当前队列的任务
//                     if (this->stop && this->tasks.empty())
//                         return;
//                     task = this->tasks.front();
//                     this->tasks.pop();
//                 }
//                 task();
//             }
//         });
//     }
// }

// threadpool::~threadpool() {
//     //将stop改为1，唤醒所有线程，等待任务运行完成后结束
//     {
//         std::unique_lock<std::mutex> lock(queue_mutex);
//         stop = true;
//     }
//     condition.notify_all();
//     for (std::thread& worker : workers) {
//         worker.join();
//     }
// }

// template <typename F, typename... Args>
// auto threadpool::enqueue(F &&f, Args &&... args) -> std::future<typename std::result_of<F(Args...)>::type> {
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

