#ifndef __LOG_WARP_H__
#define __LOG_WRAP_H__

#include <plengine/log.h>

namespace logwrap
{
    inline void info(const std::string &msg)
    {
        INFO(msg);
    }

    inline void debug(const std::string &msg)
    {
        DEBUG(msg);
    }

    inline void warn(const std::string &msg)
    {
        WARN(msg);
    }

    inline void err(const std::string &msg)
    {
        ERR(msg);
    }

    inline void set_level(E_LOGGER_LEVEL level)
    {
        Logger::instance().set_level(level);
    }

    inline E_LOGGER_LEVEL get_level()
    {
        return Logger::instance().get_level();
    }
};

#endif
