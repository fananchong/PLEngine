#ifndef __PYTHON_VM_IMPL_H__
#define __PYTHON_VM_IMPL_H__

#ifdef ENABLE_PLENGINE_PYTHON

#include "../run_container/run_container.h"
#include <unordered_map>

#pragma warning(push)
#pragma warning(disable:4244)
#include <boost/python.hpp>
#pragma warning(pop)

class PythonVMImpl : public RunContainer
{
public:
    PythonVMImpl();
    ~PythonVMImpl();

    void open(
        const std::string &home_dir,
        const std::string &py_path,
        int argc, char **argv);
    void close();
    void set_path(const std::string &path);
    void print_path();
    bool load_module(const std::string &module);
    void exec(const std::string &s);
    void call(const std::string &module, const std::string &func);

    void open_shell();
    void close_shell();

private:
    bool m_init;

    using ModuleType = std::pair<std::shared_ptr<boost::python::object>, std::shared_ptr<boost::python::object>>;
    std::unordered_map<std::string, PythonVMImpl::ModuleType> m_modules;
};

#endif

#endif