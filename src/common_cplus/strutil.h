#ifndef __STRUTIL_H__
#define __STRUTIL_H__

#include <string>

class StrUtil
{
public:
    static std::wstring to_wstring(const std::string & value);
};

#endif