#include <plengine/setup.h>
#include <plengine/log.h>
#include <plengine/program_options.h>
#include <plengine/version.h>
#include <plengine/python_vm.h>

#include "pymain.h"

static void show_copy_right(const std::string &appname)
{
    INFO("-------------------------------------------------------------");
    INFO("[PLEngine] {}", appname);
    INFO("");
    INFO("Copyright (c) 2017 fananchong.");
    INFO("-------------------------------------------------------------");
    INFO("Version    : {}", std::string(APP_VERSION, 10));
    INFO("Build Time : {}", APP_BUILD_TIME);
    INFO("");
    INFO("");
}

static PyObject *g_module_pl = nullptr;
static void install_pl()
{
    g_module_pl = my_import_lib(PyInit_pl);

    if (!g_module_pl)
    {
        ERR("install pl fail");
        assert(0);
        return ;
    }

    PythonVM::exec(pymain);
    PythonVM::exec("PLMain.on_app_open()");

    if (ProgramOptions::has("py_shell"))
    {
        PythonVM::open_shell();
    }
}

static void on_app_open()
{
    show_copy_right(ProgramOptions::get_string("name"));

    bool openshell = false;
#ifdef _MSC_VER
    openshell = true;
#endif
#ifdef _DEBUG
    openshell = true;
#endif
    open_pythonvm(openshell, install_pl);
}

static void on_app_close()
{
    close_pythonvm([]()
    {
        if (ProgramOptions::has("py_shell"))
        {
            PythonVM::close_shell();
        }

        PythonVM::exec("PLMain.on_app_close()");
        PythonVM::close();
    });
}

int main(int argc, char *argv[])
{
    return setup(argc, argv, on_app_open, on_app_close);
}