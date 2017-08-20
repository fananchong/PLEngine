#include "python_vm_print_error.h"
#include "log.h"

#pragma warning(push)
#pragma warning(disable:4244)
#include <boost/python.hpp>
#pragma warning(pop)

void pythonvm_print_error()
{
    PyObject *exc, *val, *tb;
    PyErr_Fetch(&exc, &val, &tb);
    PyErr_NormalizeException(&exc, &val, &tb);
    boost::python::handle<> hexc(exc);
    boost::python::handle<> hval(boost::python::allow_null(val));
    boost::python::handle<> htb(boost::python::allow_null(tb));

    std::string err = "";

    if (!hval)
    {
        err = boost::python::extract<std::string>(boost::python::str(hexc));
    }
    else
    {
        boost::python::object traceback(boost::python::import("traceback"));
        boost::python::object format_exception(traceback.attr("format_exception"));
        boost::python::object formatted_list(format_exception(hexc, hval, htb));
        boost::python::object formatted(boost::python::str("").join(formatted_list));
        err = boost::python::extract<std::string>(formatted);
    }

    PyErr_Clear();
    ERR(err);
}
