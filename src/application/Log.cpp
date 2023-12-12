#include "Log.h"
#include "easylogging++.h"

INITIALIZE_EASYLOGGINGPP

void Log::Init(void) {
    el::Configurations cfg;
    cfg.setGlobally(el::ConfigurationType::Format, "%datetime{%H:%m:%s.%g} %level %msg");
    cfg.setGlobally(el::ConfigurationType::ToFile, "true");
    cfg.setGlobally(el::ConfigurationType::Filename, "log.txt");   // TODO: Full path to output log file

    el::Loggers::setDefaultConfigurations(cfg, true);
}


el::Logger* Log::GetLoggerInstance(void) {
    // Lazily registers the "default" logger if not available
    return el::Loggers::getLogger("default", true);
}


