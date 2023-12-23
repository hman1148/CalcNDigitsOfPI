#pragma once

#include "Bpp.hpp"
#include "ResultTable.hpp"
#include "TaskQueue.hpp"

#include <mutex>
#include <thread>
#include <vector>

class WorkerThread
{
  public:
    WorkerThread(TaskQueue& taskQueue, ResultTable& resultTable, std::uint16_t& tasksFinished) :
        taskQueue(taskQueue), resultTable(resultTable), tasksFinished(tasksFinished) {}

    void operator()();

  private:
    TaskQueue& taskQueue;
    ResultTable& resultTable;
    std::uint16_t& tasksFinished;
    std::mutex mutex;
};
