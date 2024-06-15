//
// Created by Henri on 14/06/2024.
//

#ifndef SP_EXAM_THREAD_POOL_H
#define SP_EXAM_THREAD_POOL_H

#include <atomic>
#include <functional>
#include <mutex>
#include <queue>
#include <thread>
#include "Observers/PeakObserver.h++"
#include "Simulator.hpp"
#include "Examples/build_seihr.h++"

using namespace std;

// Requirement: 8. Implement support for multiple computer cores by parallelizing the computation of several simulations at the same time.

// Class that represents a simple thread pool
class ThreadPool {
public:
    // Constructor to creates a thread pool with given number of threads
    explicit ThreadPool(const function<unsigned(size_t)>& baseTask, const size_t N, std::vector<unsigned>& results, unsigned iterations, unsigned long long int num_threads
    = jthread::hardware_concurrency()) : missingIterations_(iterations)
    {
        // Creating worker threads
        for (unsigned long long int i = 0; i < num_threads; ++i) {
            threads_.emplace_back([this, &baseTask, &results, &N] {
                while (true) {
                    // The reason for putting the below code
                    // here is to unlock before
                    // executing the task so that other
                    // threads can access the shared data
                    {
                        // Locking so that data
                        // can be shared safely
                        unique_lock<mutex> lock(mutex_);

                        // exit the thread in case there are no tasks
                        if (missingIterations_ == 0) {
                            return;
                        }

                        missingIterations_--;
                    }
                    auto result = baseTask(N);
                    {
                        // Locking so that data
                        // can be shared safely
                        unique_lock<mutex> lock(mutex_);
                        results.push_back(result);
                    }
                }
            });
        }
    }

    // Destructor to stop the thread pool
    ~ThreadPool()
    {
        missingIterations_ = 0;
        // Joining all worker threads to ensure they have
        // completed their tasks
        waitForCompletion();
    }

    void waitForCompletion(){
        for (auto& thread : threads_) {
            if (thread.joinable())
                thread.join();
        }
    }

    ThreadPool(ThreadPool&& other) = delete; // move ctor
    ThreadPool(const ThreadPool& other) = delete; // copy ctor
    ThreadPool& operator=(ThreadPool&& other) = delete; // move assignment
    ThreadPool& operator=(const ThreadPool& other) = delete; // copy assignment

private:
    // Vector to store worker threads
    vector<jthread> threads_;

    // Mutex to synchronize access to shared data
    mutex mutex_;

    std::atomic<unsigned> missingIterations_;
};

#endif //SP_EXAM_THREAD_POOL_H
