#ifndef __PYTHON_WRAP_H__
#define __PYTHON_WRAP_H__

#pragma warning(push)
#pragma warning(disable:4244)
#pragma warning(disable:4267)
#include <boost/python.hpp>
#pragma warning(pop)

void export_pywrap();
BOOST_PYTHON_MODULE(pl)
{

    boost::python::object a;
    a.is_none();

    export_pywrap();
}

#endif