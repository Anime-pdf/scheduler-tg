#include "logger.h"

Logger g_Logger;

const char *LogLevelStr(LogLevel Level)
{
    switch (Level) {
        case LogLevel::Trace:
            return "Trace";
        case LogLevel::Debug:
            return "Debug";
        case LogLevel::Info:
            return "Info";
        case LogLevel::Warning:
            return "Warning";
        case LogLevel::Error:
            return "Error";
        case LogLevel::Critical:
            return "Critical";
    }
    return "Trace";
}
LogLevel LogLevelFromTGBMStr(const std::string &StrLevel)
{
    if (StrLevel.rfind("[INFO]") == 0)
        return LogLevel::Info;
    if (StrLevel.rfind("[ERROR]") == 0)
        return LogLevel::Error;
    if (StrLevel.rfind("[WARN]") == 0)
        return LogLevel::Warning;
    if (StrLevel.rfind("[DEBUG]") == 0)
        return LogLevel::Debug;
    return LogLevel::Trace;
}
const char *LogLevelColor(LogLevel Level)
{
    switch (Level) {
        case LogLevel::Trace:
            return "\033[90m"; // Grey
        case LogLevel::Debug:
            return "\033[36m"; // Cyan
        case LogLevel::Info:
            return "\033[0m"; // Default
        case LogLevel::Warning:
            return "\033[33m"; // Yellow
        case LogLevel::Error:
            return "\033[31m"; // Red
        case LogLevel::Critical:
            return "\033[31m"; // Red
    }
    return "\033[0m";
}
