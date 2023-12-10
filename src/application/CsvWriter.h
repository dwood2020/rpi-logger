#pragma once
#include <cstddef>
#include <iostream>


template <typename... Args>
class CsvWriter final {
private:
    const std::size_t nrArgs;
    const char separator;

public:
    CsvWriter(char separator);
    ~CsvWriter() = default;
};


template <typename... Args>
inline CsvWriter<Args...>::CsvWriter(char separator): nrArgs(sizeof...(Args)), separator(separator) {
    std::cout << "CsvWriter: " << nrArgs << " args" << std::endl;
}
