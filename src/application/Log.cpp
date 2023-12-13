#include "Log.h"
#include <filesystem>
#include "easylogging++.h"

INITIALIZE_EASYLOGGINGPP

void Log::init(const std::filesystem::path& logfilePath) {
    el::Configurations cfg;
    cfg.setGlobally(el::ConfigurationType::Format, "%datetime{%H:%m:%s.%g} %level %msg");
    if (std::filesystem::exists(logfilePath)) {
        cfg.setGlobally(el::ConfigurationType::ToFile, "true");
        cfg.setGlobally(el::ConfigurationType::Filename, logfilePath.string().c_str());
    }

    el::Loggers::setDefaultConfigurations(cfg, true);
}

el::Logger* Log::getLoggerInstance(void) {
    // Lazily registers the "default" logger if not available.
    return el::Loggers::getLogger("default", true);
}
