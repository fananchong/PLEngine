#ifndef __PYMAIN_H__
#define __PYMAIN_H__

#pragma warning(push)
#pragma warning(disable:4244)
#include <boost/python.hpp>
#pragma warning(pop)

#include <string>

extern const char *entrypoint;
extern std::string pymain;

extern "C" PyObject* PyInit_pl(void);
typedef PyObject* (*pyfunc)(void);
PyObject* my_import_lib(pyfunc func);

#endif