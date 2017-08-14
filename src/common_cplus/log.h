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
    e_logger_level_default,
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
    void init(const std::string &logfile = "");
    Logger &log(E_LOGGER_LEVEL level, const std::string &msg);
    Logger &show(E_LOGGER_LEVEL level, const std::string &msg);

    E_LOGGER_LEVEL get_level();
    void set_level(E_LOGGER_LEVEL level);

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

#if defined(__ANDROID__) || defined (__APPLE__)

//log
#define DEBUG(...) do{ if (Logger::is_destroyed()) break; Logger::instance().log(e_logger_level_debug, fmt::format(__VA_ARGS__)); }while(false);
#define INFO(...) do{ if (Logger::is_destroyed()) break; Logger::instance().log(e_logger_level_info, fmt::format(__VA_ARGS__)); }while(false);
#define WARN(...) do{ if (Logger::is_destroyed()) break; Logger::instance().log(e_logger_level_warning, fmt::format(__VA_ARGS__)); }while(false);
#define ERR(...) do{ if (Logger::is_destroyed()) break; Logger::instance().log(e_logger_level_error, fmt::format(__VA_ARGS__)); }while(false);

//show
#define SHOW_WHITE(...) do{ if (Logger::is_destroyed()) break; Logger::instance().show(e_logger_level_debug, fmt::format(__VA_ARGS__)); }while(false);
#define SHOW_GREEN(...) do{ if (Logger::is_destroyed()) break; Logger::instance().show(e_logger_level_info, fmt::format(__VA_ARGS__)); }while(false);
#define SHOW_YELLOW(...) do{ if (Logger::is_destroyed()) break; Logger::instance().show(e_logger_level_warning, fmt::format(__VA_ARGS__)); }while(false);
#define SHOW_RED(...) do{ if (Logger::is_destroyed()) break; Logger::instance().show(e_logger_level_error, fmt::format(__VA_ARGS__)); }while(false);

#else

//log
#define DEBUG(...) do{ if (Logger::is_destroyed()) break; Logger::instance().log(e_logger_level_debug, fmt::format(__VA_ARGS__)); }while(false);
#define INFO(...) do{ if (Logger::is_destroyed()) break; Logger::instance().log(e_logger_level_info, fmt::format(__VA_ARGS__)); }while(false);
#define WARN(...) do{ if (Logger::is_destroyed()) break; Logger::instance().log(e_logger_level_warning, fmt::format(__VA_ARGS__)); }while(false);
#define ERR(...) do{ if (Logger::is_destroyed()) break; Logger::instance().log(e_logger_level_error, fmt::format(__VA_ARGS__)); }while(false);

//show
#define SHOW_WHITE(...) do{ if (Logger::is_destroyed()) break; Logger::instance().show(e_logger_level_debug, fmt::format(__VA_ARGS__)); }while(false);
#define SHOW_GREEN(...) do{ if (Logger::is_destroyed()) break; Logger::instance().show(e_logger_level_info, fmt::format(__VA_ARGS__)); }while(false);
#define SHOW_YELLOW(...) do{ if (Logger::is_destroyed()) break; Logger::instance().show(e_logger_level_warning, fmt::format(__VA_ARGS__)); }while(false);
#define SHOW_RED(...) do{ if (Logger::is_destroyed()) break; Logger::instance().show(e_logger_level_error, fmt::format(__VA_ARGS__)); }while(false);

#endif

//set log level
#define SET_LOG_LEVEL_DEBUG() do{ if (Logger::is_destroyed()) break; Logger::instance().set_level(e_logger_level_debug);  }while(false);
#define SET_LOG_LEVEL_INFO() do{ if (Logger::is_destroyed()) break; Logger::instance().set_level(e_logger_level_info);  }while(false);
#define SET_LOG_LEVEL_WARNING() do{ if (Logger::is_destroyed()) break; Logger::instance().set_level(e_logger_level_warning); }while(false);
#define SET_LOG_LEVEL_ERROR() do{ if (Logger::is_destroyed()) break; Logger::instance().set_level(e_logger_level_error); }while(false);
#define SET_LOG_LEVEL_FATAL() do{ if (Logger::is_destroyed()) break; Logger::instance().set_level(e_logger_level_fatal); }while(false);

#endif