#ifndef __PROGRAM_OPTIONS_H__
#define __PROGRAM_OPTIONS_H__

#include <string>
#include <vector>
#include <boost/any.hpp>

#define COMMON_OPTIONS_DEF()                                                                    \
{ "help,h",             "",                     "list all options",                 false },    \
{ "name",               "uname_app",            "this app's name",                  true },     \
{ "log_path",           "logs",                 "log path",                         true },     \
{ "py_home_path",       "../res/py",            "the path of python home dir",      true },     \
{ "py_script_path",     "",                     "the path of python script file",   true },     \
{ "py_shell",           "",                     "open python shell",                false },    \


class ProgramOptions
{
public:

    struct option_t
    {
        std::string name;
        boost::any default_;
        std::string desc;
        bool has_value;
    };

    static bool parse(int argc, char *argv[], const std::vector<option_t> &descs);
    static bool parse(const std::vector<std::string> &args, const std::vector<option_t> &descs);

    static bool get_bool(const std::string &option);
    static int get_int(const std::string &option);
    static float get_float(const std::string &option);
    static std::string get_string(const std::string &option);
    static bool has(const std::string &option);

    static void set(const std::string &option, bool value);
    static void set(const std::string &option, int value);
    static void set(const std::string &option, float value);
    static void set(const std::string &option, const std::string &value);
    static void set(const std::string &option, const char *value);
};

#endif