#include <iostream>
#include <thread>
#include <future>
#include <cmath>
#include <vector>
#include <chrono>

void workerFunction(int n)
{
    // print system id of worker thread
    std::cout << "Worker thread id = " << std::this_thread::get_id() << std::endl;

    // perform work
    for (int i = 0; i < n; ++i)
    {
        sqrt(12345.6789);
    }
}

int main()
{
    // print system id of worker thread
    std::cout << "Main thread id = " << std::this_thread::get_id() << std::endl;

    // start time measurement
    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
    
    // launch various tasks
    std::vector<std::future<void>> futures;


    // Example cases: 

    //int nLoops = 1e7 , nThreads = 4 , std::launch::async        overall runtime: ~45 milliseconds
    //int nLoops = 1e7 , nThreads = 5 , std::launch::deferred     overall runtime: ~126 milliseconds
    //int nLoops = 10 , nThreads = 5 , std::launch::async         overall runtime: ~3 milliseconds
    //int nLoops = 10 , nThreads = 5 , std::launch::deferred      overall runtime: 0.01 milliseconds 


    int nLoops = 10, nThreads = 5;
    for (int i = 0; i < nThreads; ++i)
    {
        
        futures.emplace_back(std::async(workerFunction, nLoops));
    }

    // wait for tasks to complete
    for (const std::future<void> &ftr : futures)
        ftr.wait();

    // stop time measurement and print execution time
    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
    std::cout << "Execution finished after " << duration <<" microseconds" << std::endl;
    
    return 0;
}