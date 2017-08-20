workspace "plengine"
    configurations { "Debug", "Release" }
    platforms { "x64" }
    targetdir "../../bin/%{cfg.buildcfg}"
    language "C++"
    includedirs {
        "..",
        "../../deps/include",
    }
    flags {
        "C++11",
        "StaticRuntime",
    }
    links {
        "plengine",
    }

    filter "configurations:Debug"
    defines { "_DEBUG" }
    symbols "On"
    libdirs { }
    filter "configurations:Release"
    defines { "NDEBUG" }
    libdirs { }
    optimize "On"
    filter { }
    
    defines {
        "BOOST_PYTHON_STATIC_LIB",
        "Py_NO_ENABLE_SHARED",
        "ENABLE_PLENGINE_PYTHON",
    }
	
    if os.is("windows") then
        objdir "obj/win/%{cfg.platform}/%{cfg.buildcfg}"
        defines {
            "WIN32",
        }
        includedirs {
            "../../deps/include/python/win",
        }
        libdirs {
            "../../deps/lib_win",
        }
        filter "configurations:Debug"
        libdirs {
            "../../deps/lib_win/debug",
        }
        linkoptions { '/NODEFAULTLIB:"python36.lib"' }
        filter "configurations:Release"
        libdirs {
            "../../deps/lib_win/release",
        }
        filter { }
        linkoptions { "/ignore:4049", "/ignore:4217" }
    end
	
    if os.is("linux") then
        objdir "obj/linux/%{cfg.platform}/%{cfg.buildcfg}"
        defines {
        }
        includedirs {
            "../../deps/include/python/linux",
        }
        linkoptions { "-static-libgcc -static-libstdc++ -Xlinker -export-dynamic" }
        libdirs {
            "../../deps/lib_linux",
        }
        filter "configurations:Debug"
        libdirs {
            "../../deps/lib_linux/debug",
        }
        filter "configurations:Release"
        libdirs {
            "../../deps/lib_linux/release",
        }
        filter { }
        links {
            "boost_program_options",
            "boost_python3",
            "boost_log_setup",
            "boost_log",
            "boost_serialization",
            "boost_thread",
            "boost_filesystem",
            "boost_regex",
            "boost_system",
            "fmt",
            "python3.6m",
            "pthread",
            "dl",
            "util"
        }
    end
    
    
project "pnode"
    kind "ConsoleApp"
    files {
        "../pnode/**",
    }
