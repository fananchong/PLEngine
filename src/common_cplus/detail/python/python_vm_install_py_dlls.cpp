
#ifdef ENABLE_PLENGINE_PYTHON

#include "python_vm_install_py_dlls.h"
#include "log.h"

#pragma warning(push)
#pragma warning(disable:4244)
#include <boost/python.hpp>
#pragma warning(pop)

typedef PyObject* (*pyfunc)(void);
#define EXTERN_PYTHON_FUNC1(NAME) extern "C" PyObject* PyInit_##NAME(void)
#define EXTERN_PYTHON_FUNC2(NAME) &PyInit_##NAME
#define EXTERN_PYTHON_FUNC3(NAME) "PyInit_"#NAME

#ifdef _MSC_VER

//#define ENABLE_PLENGINE_PYTHON_TKINTER
//#define ENABLE_PLENGINE_PYTHON_MSI
//#define ENABLE_PLENGINE_SQLITE3
//#define ENABLE_PLENGINE_BZ2
//#define ENABLE_PLENGINE_LZMA
//#define ENABLE_PLENGINE_SSL

#pragma comment(lib, "Crypt32.lib")

#ifdef ENABLE_PLENGINE_PYTHON_MSI
#pragma comment(lib, "Msi.lib")
#pragma comment(lib, "Rpcrt4.lib")
#pragma comment(lib, "Cabinet.Lib")
#endif

#ifdef _DEBUG
#pragma comment(lib, "python36_d.lib")
#pragma comment(lib, "ssleay_d.lib")
#pragma comment(lib, "libeay_d.lib")

#ifdef ENABLE_PLENGINE_LZMA
#pragma comment(lib, "liblzma_d.lib")
#endif

#ifdef ENABLE_PLENGINE_SQLITE3
#pragma comment(lib, "sqlite3_d.lib")
#endif

#ifdef ENABLE_PLENGINE_PYTHON_TKINTER
#pragma comment(lib, "tcl86tg.lib")
#pragma comment(lib, "tk86tg.lib")
#endif

#pragma comment(lib, "_ctypes_d.pyd")
#pragma comment(lib, "unicodedata_d.pyd")
#pragma comment(lib, "pyexpat_d.pyd")
#pragma comment(lib, "_decimal_d.pyd")
#pragma comment(lib, "_multiprocessing_d.pyd")
#pragma comment(lib, "_socket_d.pyd")
#pragma comment(lib, "select_d.pyd")
#pragma comment(lib, "_overlapped_d.pyd")
#pragma comment(lib, "_asyncio_d.pyd")
#ifdef ENABLE_PLENGINE_BZ2
#pragma comment(lib, "_bz2_d.pyd")
#endif
#pragma comment(lib, "_elementtree_d.pyd")
#pragma comment(lib, "_hashlib_d.pyd")
#ifdef ENABLE_PLENGINE_LZMA
#pragma comment(lib, "_lzma_d.pyd")
#endif
#ifdef ENABLE_PLENGINE_PYTHON_MSI
#pragma comment(lib, "_msi_d.pyd")
#endif
#ifdef ENABLE_PLENGINE_SQLITE3
#pragma comment(lib, "_sqlite3_d.pyd")
#endif
#ifdef ENABLE_PLENGINE_SSL
#pragma comment(lib, "_ssl_d.pyd")
#endif
#ifdef ENABLE_PLENGINE_PYTHON_TKINTER
#pragma comment(lib, "_tkinter_d.pyd")
#endif
#else
#pragma comment(lib, "python36.lib")
#pragma comment(lib, "ssleay.lib")
#pragma comment(lib, "libeay.lib")

#ifdef ENABLE_PLENGINE_LZMA
#pragma comment(lib, "liblzma.lib")
#endif

#ifdef ENABLE_PLENGINE_SQLITE3
#pragma comment(lib, "sqlite3.lib")
#endif

#ifdef ENABLE_PLENGINE_PYTHON_TKINTER
#pragma comment(lib, "tcl86t.lib")
#pragma comment(lib, "tk86t.lib")
#endif

#pragma comment(lib, "_ctypes.pyd")
#pragma comment(lib, "unicodedata.pyd")
#pragma comment(lib, "pyexpat.pyd")
#pragma comment(lib, "_decimal.pyd")
#pragma comment(lib, "_multiprocessing.pyd")
#pragma comment(lib, "_socket.pyd")
#pragma comment(lib, "select.pyd")
#pragma comment(lib, "_overlapped.pyd")
#pragma comment(lib, "_asyncio.pyd")
#ifdef ENABLE_PLENGINE_BZ2
#pragma comment(lib, "_bz2.pyd")
#endif
#pragma comment(lib, "_elementtree.pyd")
#pragma comment(lib, "_hashlib.pyd")
#ifdef ENABLE_PLENGINE_LZMA
#pragma comment(lib, "_lzma.pyd")
#endif
#ifdef ENABLE_PLENGINE_PYTHON_MSI
#pragma comment(lib, "_msi.pyd")
#endif
#ifdef ENABLE_PLENGINE_SQLITE3
#pragma comment(lib, "_sqlite3.pyd")
#endif
#ifdef ENABLE_PLENGINE_SSL
#pragma comment(lib, "_ssl.pyd")
#endif
#ifdef ENABLE_PLENGINE_PYTHON_TKINTER
#pragma comment(lib, "_tkinter.pyd")
#endif
#endif

EXTERN_PYTHON_FUNC1(_ctypes);
EXTERN_PYTHON_FUNC1(unicodedata);
EXTERN_PYTHON_FUNC1(pyexpat);
EXTERN_PYTHON_FUNC1(_decimal);
EXTERN_PYTHON_FUNC1(_multiprocessing);
EXTERN_PYTHON_FUNC1(_socket);
EXTERN_PYTHON_FUNC1(select);
EXTERN_PYTHON_FUNC1(_overlapped);
EXTERN_PYTHON_FUNC1(_asyncio);
#ifdef ENABLE_PLENGINE_BZ2
EXTERN_PYTHON_FUNC1(_bz2);
#endif
EXTERN_PYTHON_FUNC1(_elementtree);
EXTERN_PYTHON_FUNC1(_hashlib);
#ifdef ENABLE_PLENGINE_LZMA
EXTERN_PYTHON_FUNC1(_lzma);
#endif
#ifdef ENABLE_PLENGINE_PYTHON_MSI
EXTERN_PYTHON_FUNC1(_msi);
#endif
#ifdef ENABLE_PLENGINE_SQLITE3
EXTERN_PYTHON_FUNC1(_sqlite3);
#endif
#ifdef ENABLE_PLENGINE_SSL
EXTERN_PYTHON_FUNC1(_ssl);
#endif
#ifdef ENABLE_PLENGINE_PYTHON_TKINTER
EXTERN_PYTHON_FUNC1(_tkinter);
#endif
//EXTERN_PYTHON_FUNC1(pl);


static pyfunc g_funs[] =
{
    EXTERN_PYTHON_FUNC2(_ctypes),
    EXTERN_PYTHON_FUNC2(unicodedata),
    EXTERN_PYTHON_FUNC2(pyexpat),
    EXTERN_PYTHON_FUNC2(_decimal),
    EXTERN_PYTHON_FUNC2(_multiprocessing),
    EXTERN_PYTHON_FUNC2(_socket),
    EXTERN_PYTHON_FUNC2(select),
    EXTERN_PYTHON_FUNC2(_overlapped),
    EXTERN_PYTHON_FUNC2(_asyncio),
#ifdef ENABLE_PLENGINE_BZ2
    EXTERN_PYTHON_FUNC2(_bz2),
#endif
    EXTERN_PYTHON_FUNC2(_elementtree),
    EXTERN_PYTHON_FUNC2(_hashlib),
#ifdef ENABLE_PLENGINE_LZMA
    EXTERN_PYTHON_FUNC2(_lzma),
#endif
#ifdef ENABLE_PLENGINE_PYTHON_MSI
    EXTERN_PYTHON_FUNC2(_msi),
#endif
#ifdef ENABLE_PLENGINE_SQLITE3
    EXTERN_PYTHON_FUNC2(_sqlite3),
#endif
#ifdef ENABLE_PLENGINE_SSL
    EXTERN_PYTHON_FUNC2(_ssl),
#endif
#ifdef ENABLE_PLENGINE_PYTHON_TKINTER
    EXTERN_PYTHON_FUNC2(_tkinter),
#endif
    //EXTERN_PYTHON_FUNC2(pl),
    NULL
};

static const char* g_sfuns[] =
{
    EXTERN_PYTHON_FUNC3(_ctypes),
    EXTERN_PYTHON_FUNC3(unicodedata),
    EXTERN_PYTHON_FUNC3(pyexpat),
    EXTERN_PYTHON_FUNC3(_decimal),
    EXTERN_PYTHON_FUNC3(_multiprocessing),
    EXTERN_PYTHON_FUNC3(_socket),
    EXTERN_PYTHON_FUNC3(select),
    EXTERN_PYTHON_FUNC3(_overlapped),
    EXTERN_PYTHON_FUNC3(_asyncio),
#ifdef ENABLE_PLENGINE_BZ2
    EXTERN_PYTHON_FUNC3(_bz2),
#endif
    EXTERN_PYTHON_FUNC3(_elementtree),
    EXTERN_PYTHON_FUNC3(_hashlib),
#ifdef ENABLE_PLENGINE_LZMA
    EXTERN_PYTHON_FUNC3(_lzma),
#endif
#ifdef ENABLE_PLENGINE_PYTHON_MSI
    EXTERN_PYTHON_FUNC3(_msi),
#endif
#ifdef ENABLE_PLENGINE_SQLITE3
    EXTERN_PYTHON_FUNC3(_sqlite3),
#endif
#ifdef ENABLE_PLENGINE_SSL
    EXTERN_PYTHON_FUNC3(_ssl),
#endif
#ifdef ENABLE_PLENGINE_PYTHON_TKINTER
    EXTERN_PYTHON_FUNC3(_tkinter),
#endif
    //EXTERN_PYTHON_FUNC3(pl),
    ""
};

static PyObject* g_importedModules[] =
{
    NULL,   // _ctypes
    NULL,   // unicodedata
    NULL,   // pyexpat
    NULL,   // _decimal
    NULL,   // _multiprocessing
    NULL,   // _socket
    NULL,   // select
    NULL,   // _overlapped
    NULL,   // _asyncio
#ifdef ENABLE_PLENGINE_BZ2
    NULL,   // _bz2
#endif
    NULL,   // _elementtree
    NULL,   // _hashlib
#ifdef ENABLE_PLENGINE_LZMA
    NULL,   // _lzma
#endif
#ifdef ENABLE_PLENGINE_PYTHON_MSI
    NULL,   // _msi
#endif
#ifdef ENABLE_PLENGINE_SQLITE3
    NULL,   // _sqlite3
#endif
#ifdef ENABLE_PLENGINE_SSL
    NULL,   // _ssl
#endif
#ifdef ENABLE_PLENGINE_PYTHON_TKINTER
    NULL,   // _tkinter
#endif
    //NULL,   // pl
    NULL
};

#else

//EXTERN_PYTHON_FUNC1(pl);

static pyfunc g_funs[] =
{
    //EXTERN_PYTHON_FUNC2(pl),
    NULL
};

static const char* g_sfuns[] =
{
    //EXTERN_PYTHON_FUNC3(pl),
    ""
};

static PyObject* g_importedModules[] =
{
    //NULL,   // pl
    NULL
};

#endif


PyObject* my_import_lib(pyfunc func)
{
    auto m = func();

    if (m)
    {
        PyObject *modules = PyImport_GetModuleDict();
        struct PyModuleDef *def;

        def = PyModule_GetDef(m);

        if (!def)
        {
            PyErr_BadInternalCall();
            Py_DECREF(m);
            return nullptr;
        }

        if (PyState_AddModule(m, def) < 0
                || PyDict_SetItemString(modules, def->m_name, m) < 0)
        {
            Py_DECREF(m);
            return nullptr;
        }
    }

    return m;
}

bool install_py_dlls(void)
{
    PyObject *modules = PyImport_GetModuleDict();
    int i = 0;

    assert(sizeof(g_funs) / sizeof(g_funs[i]) == sizeof(g_funs) / sizeof(g_funs[i]));
    assert(sizeof(g_funs) / sizeof(g_funs[i]) == sizeof(g_importedModules) / sizeof(g_importedModules[i]));

    for (size_t i = 0; i < sizeof(g_funs) / sizeof(g_funs[i]) - 1; i++)
    {
        assert(g_funs[i]);
        assert(g_sfuns[i]);
        PyObject * m = my_import_lib(*g_funs[i]);

        if (!m)
        {
            ERR("install {} fail", g_sfuns[i]);
            assert(0);
            return false;
        }

        g_importedModules[i] = m;
    }

    return true;
}

bool uninstall_py_dlls(void)
{
    PyObject *modules = PyImport_GetModuleDict();
    int i = 0;

    while (true)
    {
        if (g_funs[i] == NULL)
            break;

        INFO("Script::uninstall_py_dlls(): {}", g_sfuns[i]);
        PyObject * m = g_importedModules[i++];

        if (m == NULL)
        {
            return false;
        }

        Py_DECREF(m);

        struct PyModuleDef *def;
        def = PyModule_GetDef(m);

        if (!def)
        {
            PyErr_BadInternalCall();
            return false;
        }

        if (PyState_RemoveModule(def) < 0 || PyDict_DelItemString(modules, def->m_name) < 0)
            return false;
    }

    return true;
}

#endif
