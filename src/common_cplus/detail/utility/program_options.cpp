#include "program_options.h"
#include "log.h"
#include <unordered_map>
#include <vector>
#include <boost/program_options.hpp>

static boost::program_options::variables_map g_vm;

bool ProgramOptions::parse(int argc, char *argv[], const std::vector<option_t> &descs)
{
    static boost::program_options::options_description g_all("Allowed options");
    std::vector<ProgramOptions::option_t> p1 = { COMMON_OPTIONS_DEF() };
    p1.insert(p1.end(), descs.begin(), descs.end());

    for (size_t i = 0; i < p1.size(); i++)
    {
        auto &o = p1[i];
        auto &t = o.default_.type();
#define ADD_OPTIONS(TYPE)   \
    static std::vector<TYPE> g_value_##TYPE;  \
    g_value_##TYPE.resize(i+1); \
    TYPE &v = g_value_##TYPE.at(i);    \
    if (o.has_value)    \
    {   \
        g_all.add_options()(o.name.c_str(), boost::program_options::value<TYPE>(&v)->default_value(boost::any_cast<TYPE>(o.default_)), o.desc.c_str());    \
    }   \
    else  \
    {   \
        g_all.add_options()(o.name.c_str(), o.desc.c_str());    \
    }

        if (t == typeid(bool))
        {
            static bool g_value_bool[128] = {0};
            bool &v = g_value_bool[i];

            if (o.has_value)
            {
                g_all.add_options()(o.name.c_str(), boost::program_options::value<bool>(&v)->default_value(boost::any_cast<bool>(o.default_)), o.desc.c_str());
            }
            else
            {
                g_all.add_options()(o.name.c_str(), o.desc.c_str());
            }
        }
        else if (t == typeid(int))
        {
            ADD_OPTIONS(int);
        }
        else if (t == typeid(float))
        {
            ADD_OPTIONS(float);
        }
        else if (t == typeid(char const*))
        {
            static std::vector<std::string> g_value_string(128);
            std::string &v = g_value_string.at(i);

            if (o.has_value)
            {
                g_all.add_options()(o.name.c_str(), boost::program_options::value<std::string>(&v)->default_value(boost::any_cast<char const*>(o.default_)), o.desc.c_str());
            }
            else
            {
                g_all.add_options()(o.name.c_str(), o.desc.c_str());
            }
        }
        else
        {
            assert(0);
        }
    }

    bool psuccess = true;

    try
    {
        boost::program_options::store(
            boost::program_options::parse_command_line(argc, argv, g_all),
            g_vm);
        boost::program_options::notify(g_vm);
    }
    catch (...)
    {
        psuccess = false;
    }

    if (psuccess == false || g_vm.count("help"))
    {
        std::ostringstream info;
        g_all.print(info);
        WARN(info.str());
        info.clear();
        return false;
    }

    return true;
}

bool ProgramOptions::parse(const std::vector<std::string> &args, const std::vector<option_t> &descs)
{
    int argc = (int)args.size();
    const char *argv[128] = {0};

    for (size_t i = 0; i < args.size(); i++)
    {
        argv[i] = args[i].c_str();
    }

    return parse(argc, (char **)argv, descs);
}

template<typename T>
static T _get(const std::string &option)
{
    if (g_vm.count(option))
    {
        return g_vm[option].as<T>();
    }
    else
    {
        assert(0);
        return T();
    }
}

bool ProgramOptions::get_bool(const std::string &option)
{
    return _get<bool>(option);
}

int ProgramOptions::get_int(const std::string &option)
{
    return _get<int>(option);
}

float ProgramOptions::get_float(const std::string &option)
{
    return _get<float>(option);
}

std::string ProgramOptions::get_string(const std::string &option)
{
    return _get<std::string>(option);
}

bool ProgramOptions::has(const std::string &option)
{
    return g_vm.count(option) != 0;
}

static void _set(const std::string &option, boost::any value)
{
    if (g_vm.find(option) != g_vm.end())
    {
        boost::any &tmp = (boost::any &)g_vm[option].value();
        tmp = value;
    }
    else
    {
        assert(0);
    }
}

void ProgramOptions::set(const std::string &option, bool value)
{
    _set(option, value);
}

void ProgramOptions::set(const std::string &option, int value)
{
    _set(option, value);
}

void ProgramOptions::set(const std::string &option, float value)
{
    _set(option, value);
}

void ProgramOptions::set(const std::string &option, const std::string &value)
{
    _set(option, value);
}

void ProgramOptions::set(const std::string &option, const char *value)
{
    _set(option, std::string(value));
}
