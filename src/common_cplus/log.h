#ifndef __LOG_H__
#define __LOG_H__

#include <string>
#include <memory>
#include <fmtlib/format.h>
#include "singleton.h"

#if !defined(__ANDROID__) && !defined(__APPLE__)
#include <boost/log/attributes/named_scope.hpp>
#endif

enum E_LOGGER_LEVEL
{
    e_logger_level_trace,
    e_logger_level_debug,
    e_logger_level_info,
    e_logger_level_warning,
    e_logger_level_error,
    e_logger_level_fatal,
    e_logger_level_size,
};

#if defined(__ANDROID__) || defined(__APPLE__)
class LoggerSimpleImpl;
#else
class LoggerImpl;
#endif
class Logger : public Singleton<Logger>
{
public:
    Logger();
    virtual ~Logger();

public:
    bool init(const std::string &logfile = "");
    Logger &log(E_LOGGER_LEVEL level, const std::string &msg);

    // for debug
public:
    std::string get_log_path();

private:
#if defined(__ANDROID__) || defined(__APPLE__)
    std::unique_ptr<LoggerSimpleImpl> m_impl;
#else
    std::unique_ptr<LoggerImpl> m_impl;
#endif
};


//log
#define TRACE(...) do{ if (Logger::is_destroyed()) break; Logger::instance().log(e_logger_level_trace, fmt::format(__VA_ARGS__)); }while(false);
#define DEBUG(...) do{ if (Logger::is_destroyed()) break; Logger::instance().log(e_logger_level_debug, fmt::format(__VA_ARGS__)); }while(false);
#define INFO(...) do{ if (Logger::is_destroyed()) break; Logger::instance().log(e_logger_level_info, fmt::format(__VA_ARGS__)); }while(false);
#define WARN(...) do{ if (Logger::is_destroyed()) break; Logger::instance().log(e_logger_level_warning, fmt::format(__VA_ARGS__)); }while(false);
#define ERR(...) do{ if (Logger::is_destroyed()) break; Logger::instance().log(e_logger_level_error, fmt::format(__VA_ARGS__)); }while(false);
#define FATAL(...) do{ if (Logger::is_destroyed()) break; Logger::instance().log(e_logger_level_fatal, fmt::format(__VA_ARGS__)); }while(false);

#endif