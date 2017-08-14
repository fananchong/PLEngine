#pragma warning(push)
#pragma warning(disable:4267)
#pragma warning(disable:4996)

#include "console.h"
#include "log.h"
#include "program_options.h"
#include "linenoise.hpp"
#include <boost/algorithm/string.hpp>

Console::Console()
    : m_prompt("")
    , m_termination(true)
{

}

Console::~Console()
{

}

void Console::open(const char *prompt)
{
    m_prompt = fmt::format("{}> ", prompt);
    m_termination = false;
    m_future = std::async(std::launch::async, [this]()
    {
        std::string path = fmt::format("{}/shell_history.txt", ProgramOptions::get_string("log_path"));
        linenoise::SetMultiLine(false);
        linenoise::SetHistoryMaxLen(50);
        linenoise::LoadHistory(path.c_str());

        while (!m_termination)
        {
            std::string line;

            if (linenoise::Readline(m_prompt.c_str(), line))
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

            linenoise::AddHistory(line.c_str());
            linenoise::SaveHistory(path.c_str());
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