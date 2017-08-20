#include "log_impl.h"
#include "program_options.h"
#include "io.h"
#include <boost/filesystem.hpp>
#include <boost/algorithm/string/replace.hpp>

#pragma warning(push)
#pragma warning(disable:4819)
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/setup/from_stream.hpp>
#include <boost/log/utility/setup/formatter_parser.hpp>
#include <boost/log/utility/setup/filter_parser.hpp>
#pragma warning(pop)

#ifdef _MSC_VER
#include<windows.h>
#pragma comment(lib, "Psapi.lib")
#endif

LoggerImpl::LoggerImpl()
{
}

bool LoggerImpl::init(const std::string &logfile)
{
    boost::log::add_common_attributes();
    boost::log::register_simple_formatter_factory<boost::log::trivial::severity_level, char>("Severity");
    boost::log::register_simple_filter_factory<boost::log::trivial::severity_level, char>("Severity");

    try
    {
        std::string ini = get_filecontent(get_log_ini_file());
        boost::algorithm::replace_all(ini, "{logpath}", get_log_path());
        boost::algorithm::replace_all(ini, "{appname}", ProgramOptions::get_string("name"));
        std::istringstream iss(ini);
        boost::log::init_from_stream(iss);
    }
    catch (const std::exception& e)
    {
        std::cout << "init_logger is fail, read log config file fail. curse: " << e.what() << std::endl;
        return false;
    }

    return true;
}

LoggerImpl::~LoggerImpl()
{
}

std::string LoggerImpl::get_log_path()
{
    std::string logpath = ProgramOptions::get_string("log_path");
    auto full_path = boost::filesystem::system_complete(boost::filesystem::path(logpath));
    logpath = full_path.string();
    boost::algorithm::replace_all(logpath, "\\", "/");
    return logpath;
}

std::string LoggerImpl::get_log_ini_file()
{
    std::string ini = ProgramOptions::get_string("log_ini_file");
    auto full_path = boost::filesystem::system_complete(boost::filesystem::path(ini));
    ini = full_path.string();
    return ini;
}

LoggerImpl &LoggerImpl::log(E_LOGGER_LEVEL level, const std::string & text)
{
#ifdef _MSC_VER

    if (!ProgramOptions::has("log_with_color"))
    {
        BOOST_LOG_SEV(m_logger, boost::log::trivial::severity_level(level)) << text;
    }
    else
    {
        set_console_font_color(level);
        BOOST_LOG_SEV(m_logger, boost::log::trivial::severity_level(level)) << text;
        set_console_font_color(e_logger_level_debug);
    }

#else
    static const char *g_color[] =
    {
        "\033[36m",
        "\033[0m",
        "\033[;32m",
        "\033[;33m",
        "\033[;31m",
        "\033[;35m"
    };

    if (!ProgramOptions::has("log_with_color"))
    {
        BOOST_LOG_SEV(m_logger, boost::log::trivial::severity_level(level)) << text;
    }
    else
    {
        BOOST_LOG_SEV(m_logger, boost::log::trivial::severity_level(level)) << g_color[level] << text << g_color[e_logger_level_debug];
    }

#endif

    return *this;
}

#ifdef _MSC_VER
void LoggerImpl::set_console_font_color(E_LOGGER_LEVEL level)
{
    static WORD g_color[] =
    {
        FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE,
        FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
        FOREGROUND_INTENSITY | FOREGROUND_GREEN,
        FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN,
        FOREGROUND_INTENSITY | FOREGROUND_RED,
        FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE
    };
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), g_color[level]);
}
#endif
