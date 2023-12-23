#pragma once

#include <cstdint>
#include <list>
#include <mutex>

class TaskQueue
{
  public:
    void addElement(std::uint16_t task);
    std::uint32_t removeElement();
    void setTotalTimesPopped(std::uint16_t value);

  private:
    std::list<std::uint16_t> list;
    std::uint16_t tasksFinished;
    std::mutex mutex;
};
