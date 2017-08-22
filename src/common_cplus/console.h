#ifndef __CONSOLE_H__
#define __CONSOLE_H__

#include <string>
#include <vector>
#include <unordered_map>
#include <functional>
#include <future>
#include <atomic>
#include "singleton.h"

typedef std::function < void(std::vector<std::string> &&) > ConsoleCmdType;
typedef std::function < void(std::string &&) > ConsoleDefaultType;

class Console : public Singleton<Console>
{
public:
    Console();
    ~Console();

    void open(const std::string &prompt);
    void close();
    void register_cmd(const char *cmd, const ConsoleCmdType &handler);
    void register_default(const ConsoleDefaultType &handler);

private:
    std::string m_prompt;
    std::unordered_map<std::string, ConsoleCmdType> m_cmds;
    ConsoleDefaultType m_default;
    std::future<void> m_future;
    std::atomic<bool> m_termination;
};

#endif