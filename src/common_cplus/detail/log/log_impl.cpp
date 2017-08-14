#include "log_impl.h"
#include "program_options.h"
#include <stdexcept>
#include <boost/log/common.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/attributes/timer.hpp>
#include <boost/log/attributes/named_scope.hpp>
#include <boost/log/sources/logger.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/log/support/exception.hpp>
#include <boost/log/trivial.hpp>
#include <boost/filesystem.hpp>
#include <iostream>


#ifdef _MSC_VER
#include<windows.h>
#endif

static const char* const g_strlevel[] = { "<unknown>", "<debug>", "<info> ", "<warn> ", "<error>", "<fatal>" };

template< class CharT, class TraitsT >
static inline std::basic_ostream< CharT, TraitsT >& operator<< (std::basic_ostream< CharT, TraitsT >& strm, E_LOGGER_LEVEL lvl)
{
    return (strm << g_strlevel[lvl]);
};

#ifndef _MSC_VER
static const char *g_color[] =
{
    "\033[0m",
    "\033[0m",
    "\033[;32m",
    "\033[;33m",
    "\033[;31m",
    "\033[;31m"
};
BOOST_LOG_ATTRIBUTE_KEYWORD(severity, "Severity", E_LOGGER_LEVEL)
static const char * get_color(const boost::log::expressions::attribute_actor< E_LOGGER_LEVEL > & lvl)
{
    for (size_t i = 0; i < e_logger_level_size; i++)
    {
        //std::string a = boost::log::expressions::format("%1%") % lvl;
        //std::cout << a << std::endl;

        if (a == g_strlevel[i])
        {
            return g_color[i];
        }
    }

    return g_color[0];
}


#endif

LoggerImpl::LoggerImpl()
#ifdef _DEBUG
    : m_level(e_logger_level_info)
#else
    : m_level(e_logger_level_warning)
#endif
{
}

void LoggerImpl::init(const std::string &logfile)
{
    // console
    if (m_console_sink == nullptr)
    {

#ifdef _MSC_VER
        m_console_sink = boost::log::add_console_log(std::clog);
#else
        boost::shared_ptr<boost::log::sinks::text_ostream_backend> backend =
            boost::make_shared<boost::log::sinks::text_ostream_backend>();
        backend->add_stream(
            boost::shared_ptr< std::ostream >(&std::clog, boost::null_deleter()));
        m_console_sink = boost::make_shared<boost::log::sinks::asynchronous_sink<boost::log::sinks::text_ostream_backend>>(backend);
#endif

#ifdef _MSC_VER
        m_console_formatter_normal = boost::log::expressions::format("%1%") % boost::log::expressions::message;
        m_console_formatter_only_message = boost::log::expressions::format("%1%") % boost::log::expressions::smessage;
#else
        m_console_formatter_normal = boost::log::expressions::format("%1%%2%%3%")
                                     % get_color(boost::log::expressions::attr< E_LOGGER_LEVEL >("Severity"))
                                     % boost::log::expressions::message
                                     % g_color[0];
        m_console_formatter_only_message = boost::log::expressions::format("%1%%2%%3%")
                                           % get_color(boost::log::expressions::attr< E_LOGGER_LEVEL >("Severity"))
                                           % boost::log::expressions::message
                                           % g_color[0];
#endif
        m_console_sink->set_formatter(m_console_formatter_normal);
        boost::log::core::get()->add_sink(m_console_sink);
    }

    // file
    if (logfile != "" && m_file_sink == nullptr)
    {
        std::string logpath = get_log_path();
        boost::system::error_code ec;

        if (!boost::filesystem::exists(logpath, ec))
        {
            boost::filesystem::create_directory(logpath, ec);

            if (ec)
            {
                printf("create log path fail. error = %s\n", ec.message().c_str());
            }
        }

#ifdef _MSC_VER
        m_file_sink =
            boost::log::add_file_log(
                boost::log::keywords::file_name = logpath + logfile + "_%Y-%m-%d_%N.log",
                boost::log::keywords::rotation_size = 10 * 1024 * 1024,
                boost::log::keywords::time_based_rotation = boost::log::sinks::file::rotation_at_time_point(0, 0, 0),
                boost::log::keywords::open_mode = std::ios::app,
                boost::log::keywords::auto_flush = true
            );
#else
        boost::shared_ptr<boost::log::sinks::text_file_backend> file_backend =
            boost::make_shared<boost::log::sinks::text_file_backend>(
                boost::log::keywords::file_name = logpath + logfile + "_%Y-%m-%d_%N.log",
                boost::log::keywords::rotation_size = 10 * 1024 * 1024,
                boost::log::keywords::time_based_rotation = boost::log::sinks::file::rotation_at_time_point(0, 0, 0),
                boost::log::keywords::open_mode = std::ios::app,
                boost::log::keywords::auto_flush = true
            );
        m_file_sink = boost::make_shared<boost::log::sinks::asynchronous_sink<boost::log::sinks::text_file_backend>>(file_backend);
#endif
        m_file_formatter_normal = boost::log::expressions::format("[%1%] %2%: %3%")
                                  % boost::log::expressions::format_date_time< boost::posix_time::ptime >("TimeStamp", "%Y-%m-%d %H:%M:%S")
                                  % boost::log::expressions::attr< E_LOGGER_LEVEL >("Severity")
                                  % boost::log::expressions::message;
        m_file_formatter_only_message = boost::log::expressions::format("%1%") % boost::log::expressions::smessage;
        m_file_sink->set_formatter(m_file_formatter_normal);
        boost::log::core::get()->add_sink(m_file_sink);
    }

    boost::log::add_common_attributes();
}

LoggerImpl::~LoggerImpl()
{
}

std::string LoggerImpl::get_log_path()
{
    std::string logpath = ProgramOptions::get_string("log_path") + "/";
    auto full_path = boost::filesystem::system_complete(boost::filesystem::path(logpath));
    logpath = full_path.string();
    return logpath;
}

LoggerImpl &LoggerImpl::log(E_LOGGER_LEVEL level, const std::string &text)
{
    if (m_console_sink == nullptr)
    {
        init("");
    }

#ifdef _MSC_VER
    set_console_font_color(level);
    BOOST_LOG_SEV(m_logger, level) << text;
    set_console_font_color(e_logger_level_default);
#else
    BOOST_LOG_SEV(m_logger, level) << text;
#endif

    return *this;
}

LoggerImpl &LoggerImpl::show(E_LOGGER_LEVEL level, const std::string &text)
{
    if (m_console_sink == nullptr)
    {
        init("");
    }

#ifdef _MSC_VER

    if (m_console_sink)
    {
        m_console_sink->set_formatter(m_console_formatter_only_message);
    }

    if (m_file_sink)
    {
        m_file_sink->set_formatter(m_file_formatter_only_message);
    }

    set_console_font_color(level);
    BOOST_LOG_SEV(m_logger, level) << text;
    set_console_font_color(e_logger_level_default);

    if (m_console_sink)
    {
        m_console_sink->set_formatter(m_console_formatter_normal);
    }

    if (m_file_sink)
    {
        m_file_sink->set_formatter(m_file_formatter_normal);
    }

#else
    BOOST_LOG_SEV(m_logger, level) << text;
#endif

    return *this;
}

void LoggerImpl::set_console_font_color(E_LOGGER_LEVEL level)
{
#ifdef _MSC_VER

    switch (level)
    {
        case e_logger_level_debug:
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            break;

        case e_logger_level_info:
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
            break;

        case e_logger_level_warning:
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
            break;

        case e_logger_level_error:
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
            break;

        case e_logger_level_fatal:
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
            break;

        default:
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            break;
    }

#endif
}
