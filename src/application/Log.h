/*
 * Copyright (C) 2024  David Woodward
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#pragma once
#include <filesystem>
#include "easylogging++.h"


class Log final {
public:
    static void init(const std::filesystem::path& logfilePath);
    static el::Logger* getLoggerInstance(void);
};


#define LOG_INFO(...) Log::getLoggerInstance()->info(__VA_ARGS__)
#define LOG_WARN(...) Log::getLoggerInstance()->warn(__VA_ARGS__)
#define LOG_ERROR(...) Log::getLoggerInstance()->error(__VA_ARGS__)
