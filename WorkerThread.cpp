#include "WorkerThread.hpp"


void WorkerThread::operator()()
{
    std::lock_guard<std::mutex> lock(this->mutex);
    auto digit = this->taskQueue.removeElement();
    this->resultTable.saveResult(digit, Bpp::getDecimal(digit));
    ++this->tasksFinished;
}