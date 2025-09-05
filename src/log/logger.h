#ifndef LOG_LOGGER_H
#define LOG_LOGGER_H

#include <format>
#include <iostream>

#include <other/utility.h>

enum class LogLevel
{
    Trace = 0,
    Debug,
    Info,
    Warning,
    Error,
    Critical,
};

const char *LogLevelStr(LogLevel Level);
LogLevel LogLevelFromTGBMStr(const std::string &StrLevel);

const char *LogLevelColor(LogLevel Level);

class Logger
{
    LogLevel m_Level = LogLevel::Info;

public:
    void SetLogLevel(LogLevel Level)
    {
        m_Level = Level;
    }

    template<typename... TArgs>
    void Log(LogLevel Level, std::format_string<TArgs...> Fmt, TArgs&&... Args)
    {
        if(Level < m_Level)
            return;
        std::cout << std::format("{}[{}] {}: {}\n", LogLevelColor(Level), current_date_time(), LogLevelStr(Level), std::format(Fmt, std::forward<TArgs>(Args)...)) << std::flush;
    }
};

extern Logger g_Logger;

#endif // LOG_LOGGER_H