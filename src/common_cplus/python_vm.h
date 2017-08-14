#ifndef __PYTHON_VM_H__
#define __PYTHON_VM_H__

#ifdef ENABLE_PLENGINE_PYTHON

#include <string>
#include <memory>

class PythonVMImpl;
class PythonVM
{
public:

    static void open(
        const std::string &home_dir,
        const std::string &py_path,
        int argc, char **argv);
    static void close();
    static void set_path(const std::string &path);
    static void print_path();
    static bool load_module(const std::string &module);
    static void exec(const std::string &s);
    static void call(const std::string &module, const std::string &func);

    static void open_shell();
    static void close_shell();

    static inline std::shared_ptr<PythonVMImpl> get_impl()
    {
        return m_impl;
    }

private:
    static std::shared_ptr<PythonVMImpl> m_impl;
};

#endif

#endif
