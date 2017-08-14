
#if !defined(__ANDROID__) && !defined(__APPLE__)

#include <time.h>
#include "setup.h"
#include "log.h"
#include "program_options.h"
#include "run_container/run_container_main.h"
#include "python_vm.h"
#include "python/python_vm_impl.h"

#ifdef ENABLE_PLENGINE_PYTHON
static const char *entrypoint = "PLMain";
static bool g_pyvm_open = false;
#endif

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
    Logger::instance().init(application_name);
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

#ifdef ENABLE_PLENGINE_PYTHON

    if (g_pyvm_open)
    {
        g_pyvm_open = false;
        PythonVM::get_impl()->post([]()
        {
            PythonVM::call(entrypoint, "on_app_close");
        });
        PythonVM::close();
    }

#endif

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

#ifdef ENABLE_PLENGINE_PYTHON
void setup_pythonvm(bool open_shell)
{
    PythonVM::open(
        ProgramOptions::get_string("py_home_path"),
        ProgramOptions::get_string("py_script_path"),
        g_argc,
        g_argv
    );

    PythonVM::get_impl()->post([]()
    {
        bool success = PythonVM::load_module(entrypoint);
        assert(success);

        if (success)
        {
            PythonVM::call(entrypoint, "on_app_open");

            if (ProgramOptions::has("py_shell"))
            {
                PythonVM::open_shell();
            }
        }
    });
}
#endif

#endif