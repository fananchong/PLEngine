#include "py_wrap.h"
#include "log_wrap.h"

void export_pywrap()
{
    // logger
    {
        boost::python::enum_<E_LOGGER_LEVEL>("E_LOGGER_LEVEL")
        .value("trace", e_logger_level_trace)
        .value("debug", e_logger_level_debug)
        .value("info", e_logger_level_info)
        .value("warn", e_logger_level_warning)
        .value("error", e_logger_level_error)
        .value("fatal", e_logger_level_fatal)
        ;

        boost::python::def("trace", logwrap::trace);
        boost::python::def("debug", logwrap::debug);
        boost::python::def("info", logwrap::info);
        boost::python::def("warn", logwrap::warning);
        boost::python::def("error", logwrap::error);
        boost::python::def("fatal", logwrap::fatal);
    }
}