#ifndef __LOG_WARP_H__
#define __LOG_WRAP_H__

#include <plengine/log.h>

namespace logwrap
{
    inline void trace(const std::string &msg)
    {
        TRACE(msg);
    }

    inline void info(const std::string &msg)
    {
        INFO(msg);
    }

    inline void debug(const std::string &msg)
    {
        DEBUG(msg);
    }

    inline void warning(const std::string &msg)
    {
        WARN(msg);
    }

    inline void error(const std::string &msg)
    {
        ERR(msg);
    }

    inline void fatal(const std::string &msg)
    {
        FATAL(msg);
    }
};

#endif
