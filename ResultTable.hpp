#pragma once

#include <cstdint>
#include <mutex>
#include <string>
#include <unordered_map>

class ResultTable
{
  public:
    void saveResult(std::uint32_t key, std::uint32_t value);
    std::string addValuesOfPi();

  private:
    std::unordered_map<std::uint32_t, std::uint32_t> hashMap;
    std::mutex mutex;
};
