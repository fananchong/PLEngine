#ifndef __READLINE_H__
#define __READLINE_H__

#include <string>

class Readline
{
public:
    static bool wait(const std::string &prompt, std::string &line);
};

#endif