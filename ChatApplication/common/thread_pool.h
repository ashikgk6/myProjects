/*
 * thread_pool.h
 *
 *  Created on: Aug 17, 2025
 *      Author: ashik-g-k
 */

#ifndef COMMON_THREAD_POOL_H_
#define COMMON_THREAD_POOL_H_


#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <atomic>

class ThreadPool {
public:
    ThreadPool(size_t threads);
    ~ThreadPool();

    template<class F>
    void enqueue(F&& f);

    void waitAll();
    size_t getTaskCount();

private:
    std::vector<std::thread> workers;
    std::queue<std::function<void()>> tasks;

    std::mutex queue_mutex;
    std::condition_variable condition;
    std::condition_variable completion_condition;

    std::atomic<bool> stop;
    std::atomic<size_t> active_tasks;
};

template<class F>
void ThreadPool::enqueue(F&& f) {
    {
        std::unique_lock<std::mutex> lock(queue_mutex);
        tasks.emplace(std::forward<F>(f));
    }
    active_tasks++;
    condition.notify_one();
}


#endif /* COMMON_THREAD_POOL_H_ */
