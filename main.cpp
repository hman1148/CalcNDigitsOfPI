#include "ResultTable.hpp"
#include "TaskQueue.hpp"
#include "WorkerThread.hpp"

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <random>
#include <thread>
#include <vector>

int main()
{
    std::uint16_t tasksFinished = 0;

    std::vector<std::uint16_t> vectorList;
    std::uint16_t totalTasks = 1001;
    TaskQueue taskQueue;
    ResultTable resultTable;

    unsigned int nThreads = std::thread::hardware_concurrency();

    for (std::uint16_t i = 0; i < totalTasks; ++i)
    {
        vectorList.push_back(i);
    }

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

    std::default_random_engine engine(seed);

    // shuffle the vector
    std::shuffle(vectorList.begin(), vectorList.end(), engine);

    for (auto& item : vectorList)
    {
        taskQueue.addElement(item);
    }

    std::vector<std::thread> workerThreads(nThreads);

    std::uint8_t dotCount{ 0 };
    std::uint8_t newLineCount{ 0 };
    auto start = std::chrono::steady_clock::now();

    for (decltype(totalTasks) i = 0; i < totalTasks; ++i)
    {
        auto index = i % workerThreads.size();

        if (workerThreads[index].joinable())
        {
            workerThreads[index].join();
        }

        workerThreads[index] = std::thread(WorkerThread(taskQueue, resultTable, tasksFinished));
    }
}
