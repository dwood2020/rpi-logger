#include "Log.h"
#include <filesystem>
#include "easylogging++.h"

INITIALIZE_EASYLOGGINGPP

void Log::init(const std::filesystem::path& logfilePath) {
    el::Configurations cfg;
    cfg.setGlobally(el::ConfigurationType::Format, "%datetime{%H:%m:%s.%g} %level %msg");
    if (std::filesystem::exists(logfilePath)) {
        auto path = logfilePath;
        path.append("rpiLoggerAppLog.txt");
        cfg.setGlobally(el::ConfigurationType::Filename, path.string().c_str());
        cfg.setGlobally(el::ConfigurationType::ToFile, "true");
    }

    el::Loggers::setDefaultConfigurations(cfg, true);
}

el::Logger* Log::getLoggerInstance(void) {
    // Lazily registers the "default" logger if not available.
    return el::Loggers::getLogger("default", true);
}
