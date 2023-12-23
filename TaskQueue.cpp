#include "TaskQueue.hpp"

void TaskQueue::addElement(std::uint16_t task)
{
    std::lock_guard<std::mutex> lock(TaskQueue::mutex);
    this->list.push_back(task);
}

std::uint32_t TaskQueue::removeElement()
{
    std::lock_guard<std::mutex> lock(TaskQueue::mutex);

    std::uint16_t value = this->list.front();
    this->list.pop_front();

    this->setTotalTimesPopped(this->tasksFinished + static_cast<std::uint16_t>(1));

    return value;
}

void TaskQueue::setTotalTimesPopped(std::uint16_t value)
{
    this->tasksFinished = value;
}