//
// Created by Henri on 13/06/2024.
//
// C++ Program to demonstrate thread pooling

#include "../Observers/PeakObserver.h++"
#include "../thread_pool.h++"
#include "../utilities.h++"

using namespace std;

int main()
{
    vector<unsigned> results{};

    // Create a thread pool with 4 threads
    ThreadPool pool(SimulateSeihrPeak, 589755, results, 100);

    pool.waitForCompletion();

    // average of the vector elements
    auto avg = average(results);
    cout << "Average: " << avg << endl;

    return 0;
}
