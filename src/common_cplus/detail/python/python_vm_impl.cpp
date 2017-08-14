
#ifdef ENABLE_PLENGINE_PYTHON

#include "python_vm_impl.h"
#include "python_vm.h"
#include "python_vm_install_py_dlls.h"
#include "log.h"
#include "strutil.h"
#include "program_options.h"
#include "console.h"
#include <boost/algorithm/string/replace.hpp>
#include <boost/filesystem.hpp>

#ifdef _MSC_VER
#pragma comment(lib, "Shlwapi.lib")
#pragma comment(lib, "Version.lib")
#endif


PythonVMImpl::PythonVMImpl()
    : RunContainer("python_vm")
    , m_init(false)
{
}

PythonVMImpl::~PythonVMImpl()
{
#ifdef _DEBUG
    INFO("enter ~PythonVMImpl()");
#endif
}

void PythonVMImpl::open(
    const std::string &home_dir,
    const std::string &py_path,
    int argc, char **argv)
{
    if (m_init)
    {
        return;
    }

    m_init = true;
    RunContainer::post([home_dir, py_path, argc, argv]()
    {
#ifdef _MSC_VER
        const char * home_path[] =
        {
            "win",
            "win/DLLs",
            "win/Lib",
            "win/Lib/site-packages"
        };
#else
        const char * home_path[] =
        {
            "linux",
            "linux/DLLs",
            "linux/Lib",
            "linux/Lib/lib-dynload",
            "linux/Lib/site-packages"
        };
#endif

#pragma warning(push)
#pragma warning(disable:4996)
        std::string paths = "";
        namespace fs = boost::filesystem;
        auto full_path = fs::system_complete(fs::path(py_path));
        paths = full_path.string();

        for (size_t i = 0; i < sizeof(home_path) / sizeof(home_path[0]); i++)
        {
            full_path = fs::system_complete(fs::path(fmt::format("{0}/{1}", home_dir, home_path[i])));
            paths += ";" + full_path.string();
        }

        paths += ";";
        boost::algorithm::replace_all(paths, "\\", "/");
#pragma warning(pop)

        full_path = fs::system_complete(fs::path(home_dir));
        auto home_dir2 = full_path.string();
        boost::algorithm::replace_all(home_dir2, "\\", "/");
        std::wstring temp = StrUtil::to_wstring(home_dir2);
        Py_SetPythonHome((wchar_t *)temp.c_str());
        Py_NoSiteFlag = 1;
#ifndef _MSC_VER
        boost::algorithm::replace_all(paths, ";", ":");
#endif
        temp = StrUtil::to_wstring(paths);
        Py_SetPath(temp.c_str());

        const wchar_t *tmpargv1[64] = {0};
        std::vector<std::wstring> tmpargv2;

        for (size_t i = 0; i < argc; i++)
        {
            tmpargv2.push_back(StrUtil::to_wstring(argv[i]));
            tmpargv1[i] = tmpargv2[tmpargv2.size() - 1].c_str();
        }

        Py_SetProgramName((wchar_t *)tmpargv1[0]);
        Py_InitializeEx(0);
        PySys_SetArgv(argc, (wchar_t **)tmpargv1);

        if (!Py_IsInitialized())
        {
            ERR("Py_Initialize is failed!");
            return;
        }

        install_py_dlls();
    });
    RunContainer::run(false);
}

void PythonVMImpl::close()
{
    m_init = false;

    if (ProgramOptions::has("py_shell"))
    {
        close_shell();
    }

    RunContainer::stop();

    if (Py_IsInitialized())
    {
        Py_Finalize();
    }
}

void PythonVMImpl::set_path(const std::string &path)
{
}

void PythonVMImpl::print_path()
{
    exec("print sys.path");
}

bool PythonVMImpl::load_module(const std::string &module)
{
    try
    {
        if (m_modules.find(module) == m_modules.end())
        {
            auto mobj = PyImport_ImportModule(module.c_str());

            if (mobj)
            {
                auto module_ = std::make_shared<boost::python::object>(boost::python::handle<>(mobj));
                auto namespace_ = std::make_shared<boost::python::object>(module_->attr("__dict__"));
                m_modules[module] = { module_, namespace_ };
                return true;
            }
            else
            {
                PyErr_Print();
                PyErr_Clear();
            }
        }
    }
    catch (...)
    {
        PyErr_Print();
        PyErr_Clear();
    }

    ERR("failed to load py module, module = {}", module);
    return false;
}

void PythonVMImpl::exec(const std::string &s)
{
    try
    {
        PyRun_SimpleString(s.c_str());
    }
    catch (...)
    {
        PyErr_Print();
        PyErr_Clear();
    }
}

void PythonVMImpl::call(const std::string &module, const std::string &func)
{
    auto it = m_modules.find(module);

    if (it != m_modules.end())
    {
        try
        {
            boost::python::call_method<void>(it->second.first->ptr(), func.c_str());
        }
        catch (...)
        {
            PyErr_Print();
            PyErr_Clear();
        }
    }
    else
    {
        ERR("no find module. module = {}", module);
        assert(0);
    }
}

void PythonVMImpl::open_shell()
{
    auto self = shared_from_this();
    Console::instance().register_default([self](std::string && cmd)
    {
        self->post([cmd]()
        {
            PythonVM::exec(cmd);
        });
    });
    Console::instance().open("python");
}

void PythonVMImpl::close_shell()
{
    Console::instance().close();
}

#endif
