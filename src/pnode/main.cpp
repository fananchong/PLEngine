#include <plengine/setup.h>
#include <plengine/log.h>
#include <plengine/program_options.h>
#include <plengine/version.h>

#pragma warning(push)
#pragma warning(disable:4244)
#include <boost/python.hpp>
#pragma warning(pop)

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

typedef PyObject* (*pyfunc)(void);
extern "C" PyObject* PyInit_pl(void);
PyObject* my_import_lib(pyfunc func);
static PyObject *g_module_pl = nullptr;
static void install_pl()
{
    PyObject * m = my_import_lib(PyInit_pl);

    if (!m)
    {
        ERR("install pl fail");
        assert(0);
        return ;
    }

    g_module_pl = m;
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
    setup_pythonvm(openshell, install_pl);
}

static void on_app_close()
{
}

int main(int argc, char *argv[])
{
    return setup(argc, argv, on_app_open, on_app_close);
}