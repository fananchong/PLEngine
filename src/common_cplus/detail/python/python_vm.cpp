
#ifdef ENABLE_PLENGINE_PYTHON

#include "python_vm.h"
#include "python_vm_impl.h"

std::shared_ptr<PythonVMImpl> PythonVM::m_impl;

void PythonVM::open(
    const std::string &home_dir,
    const std::string &py_path,
    int argc, char **argv)
{
    if (!m_impl)
    {
        m_impl = std::make_shared<PythonVMImpl>();
        m_impl->open(home_dir, py_path, argc, argv);
    }
}
void PythonVM::close()
{
    if (m_impl)
    {
        m_impl->close();
        m_impl.reset();
    }
}
void PythonVM::set_path(const std::string &path)
{
    if (m_impl)
    {
        m_impl->set_path(path);
    }
}
void PythonVM::print_path()
{
    if (m_impl)
    {
        m_impl->print_path();
    }
}

void PythonVM::exec(const std::string &s)
{
    if (m_impl)
    {
        m_impl->exec(s);
    }
}

void PythonVM::open_shell()
{
    if (m_impl)
    {
        m_impl->open_shell();
    }
}

void PythonVM::close_shell()
{
    if (m_impl)
    {
        m_impl->close_shell();
    }
}

#endif
