#include "ResultTable.hpp"

#include <sstream>

// Save the digit result to a hashmap
void ResultTable::saveResult(std::uint32_t key, std::uint32_t value)
{
    std::lock_guard<std::mutex> lock(ResultTable::mutex);
    this->hashMap.insert(key, value);
}

// Print out the n digits of PI
std::string ResultTable::addValuesOfPi()
{
    std::lock_guard<std::mutex> lock(ResultTable::mutex);

    std::stringstream total;
    std::uint32_t digitsOfPi = 1000;

    for (std::uint32_t i = 0; i < digitsOfPi; ++i)
    {
        std::uint32_t value = this->hashMap[i];
        total << value;
    }
    return total.str();
}