#include "log.h"

#if defined(__ANDROID__) || defined(__APPLE__)
#include "log_simple_impl.h"
#else
#include "log_impl.h"
#endif

#pragma comment(lib,"fmt.lib")

Logger::Logger()
#if defined(__ANDROID__) || defined(__APPLE__)
    : m_impl(new LoggerSimpleImpl())
#else
    : m_impl(new LoggerImpl())
#endif
{
}

Logger::~Logger()
{
}

bool Logger::init(const std::string &logfile)
{
    return m_impl->init(logfile);
}

Logger &Logger::log(E_LOGGER_LEVEL level, const std::string &msg)
{
    m_impl->log(level, msg);
    return *this;
}

std::string Logger::get_log_path()
{
    return m_impl->get_log_path();
}
