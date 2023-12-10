#pragma once
#include <cstddef>
#include <iostream>
#include <tuple>


template <typename... Args>
class CsvWriter final {
private:
    const std::size_t nrArgs;
    const char separator;

public:
    CsvWriter(char separator);
    ~CsvWriter() = default;

    void log(const std::tuple<Args...>& args);
};


template <typename... Args>
inline CsvWriter<Args...>::CsvWriter(char separator): nrArgs(sizeof...(Args)), separator(separator) {
    std::cout << "CsvWriter: " << nrArgs << " args" << std::endl;
}

template <typename... Args>
inline void CsvWriter<Args...>::log(const std::tuple<Args...>& args) {

    std::cout << std::get<0>(args) << separator;
    std::cout << std::endl;

    // C++17 fold expression
    int i = 0;
    std::apply([](auto&&... a) {((std::cout << a << '\n'), ...);}, args);
    std::cout << std::endl;
}
