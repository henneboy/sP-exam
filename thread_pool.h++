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


// Class that represents a simple thread pool
class ThreadPool {
public:
    // // Constructor to creates a thread pool with given
    // number of threads
    //template<typename T>
    explicit ThreadPool(function<unsigned(size_t)> baseTask, const size_t N, std::vector<unsigned>& results, unsigned iterations, unsigned long long int num_threads
    = jthread::hardware_concurrency())
    {
        missingIterations_ = iterations;
        // Creating worker threads
        for (unsigned long long int i = 0; i < num_threads; ++i) {
            threads_.emplace_back([this, &baseTask, &results, &N] {
                while (true) {
                    // The reason for putting the below code
                    // here is to unlock the queue before
                    // executing the task so that other
                    // threads can perform enqueue tasks
                    {
                        // Locking the queue so that data
                        // can be shared safely
                        unique_lock<mutex> lock(
                                mutex_);

                        // exit the thread in case the pool
                        // is stopped and there are no tasks
                        if (missingIterations_ == 0) {
                            return;
                        }

                        // Get the next task from the queue
                        missingIterations_--;
                    }
                    auto result = baseTask(N);
                    {
                        // Locking the queue so that data
                        // can be shared safely
                        unique_lock<mutex> lock(
                                mutex_);
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

private:
    // Vector to store worker threads
    vector<jthread> threads_;

    // Mutex to synchronize access to shared data
    mutex mutex_;

    std::atomic<unsigned> missingIterations_;
};

#endif //SP_EXAM_THREAD_POOL_H
