#ifndef __LOG_IMPL_H__
#define __LOG_IMPL_H__

#include "log.h"

#pragma warning(push)
#pragma warning(disable:4819)
#include <boost/log/trivial.hpp>
#include <boost/log/sources/severity_channel_logger.hpp>
#pragma warning(pop)

class LoggerImpl
{
public:
    LoggerImpl();
    ~LoggerImpl();

public:
    bool init(const std::string &logfile);
    LoggerImpl &log(E_LOGGER_LEVEL level, const std::string &text);

    // for debug
public:
    std::string get_log_path();
    std::string get_log_ini_file();

private:
#ifdef _MSC_VER
    void set_console_font_color(E_LOGGER_LEVEL level = e_logger_level_debug);
#endif

private:
    boost::log::sources::severity_channel_logger<boost::log::trivial::severity_level, std::string> m_logger;
};

#endif
