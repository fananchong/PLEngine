#pragma warning(push)
#pragma warning(disable:4267)
#pragma warning(disable:4996)

#include "console.h"
#include "log.h"
#include "program_options.h"
#include "readline.h"
#include <boost/algorithm/string.hpp>

Console::Console()
    : m_prompt("")
    , m_termination(true)
{

}

Console::~Console()
{

}

void Console::open(const std::string &prompt)
{
    m_prompt = fmt::format("{}> ", prompt);
    m_termination = false;
    m_future = std::async(std::launch::async, [this]()
    {
        while (!m_termination)
        {
            std::string line;

            if (Readline::wait(m_prompt, line))
            {
                break;
            }

            std::vector<std::string> params;
            boost::split(params, line, boost::is_any_of(" "));

            if (params.size() == 0)
            {
                continue;
            }

            std::string &cmd = params[0];
            auto it = m_cmds.find(cmd);

            if (it != m_cmds.end())
            {
                it->second(std::move(params));

                if (cmd == "quit" || cmd == "exit")
                {
                    break;
                }
            }
            else
            {
                if (m_default)
                {
                    m_default(std::move(line));
                }
                else
                {
                    ERR("no find cmd. cmd = {}", line);
                }
            }
        }
    });
}

void Console::close()
{
    m_termination = true;
    fclose(stdin);
    m_future.wait();
}

void Console::register_cmd(const char *cmd, const ConsoleCmdType &handler)
{
    if (m_cmds.find(cmd) != m_cmds.end())
    {
        WARN("repeat command. cmd = {}", cmd);
        assert(0);
    }

    m_cmds[cmd] = handler;
}

void Console::register_default(const ConsoleDefaultType &handler)
{
    if (m_default)
    {
        WARN("repeat default handler.");
        assert(0);
    }

    m_default = handler;
}

#pragma warning(pop)