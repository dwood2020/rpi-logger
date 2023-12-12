#pragma once
#include <memory>
#include "easylogging++.h"


class Log final {
public:
    static void Init(void);
    static el::Logger* GetLoggerInstance(void);
};


#define LOG_INFO(...) Log::GetLoggerInstance()->info(__VA_ARGS__)
#define LOG_WARN(...) Log::GetLoggerInstance()->warn(__VA_ARGS__)
#define LOG_ERROR(...) Log::GetLoggerInstance()->error(__VA_ARGS__)
