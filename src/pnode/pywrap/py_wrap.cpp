#include "py_wrap.h"
#include "log_wrap.h"

void export_pywrap()
{
    // logger
    {
        boost::python::enum_<E_LOGGER_LEVEL>("E_LOGGER_LEVEL")
        .value("debug", e_logger_level_debug)
        .value("info", e_logger_level_info)
        .value("warn", e_logger_level_warning)
        .value("error", e_logger_level_error)
        ;

        boost::python::def("debug", logwrap::debug);
        boost::python::def("info", logwrap::info);
        boost::python::def("warn", logwrap::warn);
        boost::python::def("error", logwrap::err);
        boost::python::def("set_log_level", logwrap::set_level);
        boost::python::def("get_log_level", logwrap::get_level);
    }
}