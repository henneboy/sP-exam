//
// Created by Henri on 13/06/2024.
//
// C++ Program to demonstrate thread pooling

#include <functional>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>
#include "../Observers/PeakObserver.h++"
#include "../Simulator.hpp"
#include "../Examples/build_seihr.h++"

using namespace std;

// Class that represents a simple thread pool
class ThreadPool {
public:
    // // Constructor to creates a thread pool with given
    // number of threads
    //template<typename T>
    explicit ThreadPool(function<unsigned()> baseTask, std::vector<unsigned>& results, unsigned iterations, size_t num_threads
    = jthread::hardware_concurrency())
    {
        missingIterations_ = iterations;
        // Creating worker threads
        for (size_t i = 0; i < num_threads; ++i) {
            threads_.emplace_back([this, &baseTask, &results] {
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
                    auto result = baseTask();
                    {
                        // Locking the queue so that data
                        // can be shared safely
                        unique_lock<mutex> lock(
                                mutex_);
                        cout << "Missing " << missingIterations_ << " iterations." << endl;
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

unsigned CalcPeak(){
    auto v = seihr(589755);
    Simulator sim{};
    PeakObserver peakObserver{"H"};
    sim.simulate(100.0, v, peakObserver, false);
    return peakObserver.peak;
}

int main()
{
    std::vector<unsigned> results{};

    // Create a thread pool with 4 threads
    ThreadPool pool(CalcPeak, results, 100);

    pool.waitForCompletion();

    // sum of the vector elements
    auto sum = accumulate(results.begin(), results.end(), 0U);

    // average of the vector elements
    auto avg = sum / results.size();
    cout << "Average: " << avg << endl;

    return 0;
}
