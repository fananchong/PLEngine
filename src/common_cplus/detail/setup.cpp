
#if !defined(__ANDROID__) && !defined(__APPLE__)

#include <time.h>
#include "setup.h"
#include "log.h"
#include "program_options.h"
#include "run_container/run_container_main.h"
#include "python_vm.h"
#include "python/python_vm_impl.h"
#include "console.h"


int setup(
    const std::vector<std::string> &args,
    const std::function<void()> &on_app_open,
    const std::function<void()> &on_app_close,
    const std::vector<ProgramOptions::option_t> &options)
{
    srand((unsigned)time(0));

    if (ProgramOptions::parse(args, options) == false)
    {
        return 0;
    }

    const std::string &application_name = ProgramOptions::get_string("name");

    if (Logger::instance().init(application_name) == false)
    {
        return 0;
    }

    void myexit(std::vector<std::string> &&);
    Console::instance().register_cmd("quit", myexit);
    Console::instance().register_cmd("exit", myexit);

    g_pmain = std::make_shared<RunContainerMain>();

    if (on_app_open)
    {
        on_app_open();
    }

    g_pmain->run();

    if (on_app_close)
    {
        on_app_close();
    }

    return 0;
}

static int g_argc;
static char **g_argv;

int setup(
    int argc, char *argv[],
    const std::function<void()> &on_app_open,
    const std::function<void()> &on_app_close,
    const std::vector<ProgramOptions::option_t> &options)
{
    std::vector<std::string> args;

    for (size_t i = 0; i < argc; i++)
    {
        args.push_back(argv[i]);
    }

    g_argc = argc;
    g_argv = argv;
    return setup(args, on_app_open, on_app_close, options);
}


void myexit(std::vector<std::string> &&)
{
    g_pmain->stop();
}

#ifdef ENABLE_PLENGINE_PYTHON

void open_pythonvm(bool open_shell, const std::function<void()> &on_vm_open)
{
    PythonVM::open(
        ProgramOptions::get_string("py_home_path"),
        ProgramOptions::get_string("py_script_path"),
        g_argc,
        g_argv
    );

    if (on_vm_open)
    {
        PythonVM::get_impl()->post([on_vm_open]()
        {
            on_vm_open();
        });
    }
}

void close_pythonvm(const std::function<void()> &on_vm_close)
{
    if (on_vm_close)
    {
        PythonVM::get_impl()->post([on_vm_close]()
        {
            on_vm_close();
        });
    }
}

#endif

#endif