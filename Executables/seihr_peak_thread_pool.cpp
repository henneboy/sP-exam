//
// Created by Henri on 13/06/2024.
//
// C++ Program to demonstrate thread pooling

#include "../Observers/PeakObserver.h++"
#include "../Examples/build_seihr.h++"
#include "../thread_pool.h++"

using namespace std;

unsigned static CalcSeihrPeak(){
    auto v = seihr(589755);
    Simulator sim{};
    PeakObserver peakObserver{"H"};
    sim.simulate(100.0, v, peakObserver, false);
    return peakObserver.peak;
}

int main()
{
    vector<unsigned> results{};

    // Create a thread pool with 4 threads
    ThreadPool pool(CalcSeihrPeak, results, 100);

    pool.waitForCompletion();

    // sum of the vector elements
    auto sum = accumulate(results.begin(), results.end(), 0U);

    // average of the vector elements
    auto avg = sum / results.size();
    cout << "Average: " << avg << endl;

    return 0;
}
