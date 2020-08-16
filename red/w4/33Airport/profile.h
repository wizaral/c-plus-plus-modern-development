#pragma once

#include <chrono>
#include <iostream>
#include <string>

#define UNIQ_ID_IMPL(line) _a_local_var_##line
#define UNIQ_ID(line) UNIQ_ID_IMPL(line)

class LogDuration {
    std::string message;
    std::chrono::steady_clock::time_point start;
public:
    explicit LogDuration(const std::string &msg = "")
        : message(msg), start(std::chrono::steady_clock::now()) {}

    ~LogDuration() {
        using namespace std::chrono;
        auto finish = steady_clock::now();
        auto duration = finish - start;
        std::cerr << message
            << ": "
            << duration_cast<milliseconds>(duration).count()
            << " ms"
            << std::endl;
    }
};

#define LOG_DURATION(message) LogDuration UNIQ_ID(__LINE__){message};
