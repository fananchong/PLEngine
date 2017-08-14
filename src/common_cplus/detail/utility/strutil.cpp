#include "strutil.h"

std::wstring StrUtil::to_wstring(const std::string & value)
{
    std::wstring temp(value.length(), L' ');
    std::copy(value.begin(), value.end(), temp.begin());
    return temp;
}