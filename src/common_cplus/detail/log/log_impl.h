#ifndef __LOG_IMPL_H__
#define __LOG_IMPL_H__

#include "log.h"

#pragma warning(push)
#pragma warning(disable:4819)
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sinks.hpp>
#pragma warning(pop)

class LoggerImpl
{
public:
    LoggerImpl();
    ~LoggerImpl();

public:
    void init(const std::string &logfile);
    LoggerImpl &log(E_LOGGER_LEVEL level, const std::string &text);
    LoggerImpl &show(E_LOGGER_LEVEL level, const std::string &text);

    inline E_LOGGER_LEVEL get_level()
    {
        return m_level;
    }
    inline void set_level(E_LOGGER_LEVEL level)
    {
        m_level = level;
    }

    // for debug
public:
    std::string get_log_path();

private:
    void set_console_font_color(E_LOGGER_LEVEL level = e_logger_level_default);

private:
    // logger
    boost::log::sources::severity_logger_mt<E_LOGGER_LEVEL> m_logger;
    E_LOGGER_LEVEL m_level;

    // console sink
#ifdef _MSC_VER
    boost::shared_ptr<boost::log::sinks::synchronous_sink<boost::log::sinks::text_ostream_backend>> m_console_sink;
#else
    boost::shared_ptr<boost::log::sinks::asynchronous_sink<boost::log::sinks::text_ostream_backend>> m_console_sink;
#endif
    boost::log::formatter m_console_formatter_normal;
    boost::log::formatter m_console_formatter_only_message;

    // file sink
#ifdef _MSC_VER
    boost::shared_ptr<boost::log::sinks::synchronous_sink<boost::log::sinks::text_file_backend >> m_file_sink;
#else
    boost::shared_ptr<boost::log::sinks::asynchronous_sink<boost::log::sinks::text_file_backend >> m_file_sink;
#endif
    boost::log::formatter m_file_formatter_normal;
    boost::log::formatter m_file_formatter_only_message;
};

#endif
